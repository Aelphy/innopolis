from normalizer import Normalizer
from color import *
import socket
import math
import sys
import os
import ipdb


class Client():
    def __init__(self, host='192.168.0.107', port=7777, list_file='inputfiles-full.txt', freqs_file='wordlist', dataset_dir='/home/aelphy/Desktop/ir_project_dataset'):
        self.normalizer = Normalizer()
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((host, port))
        self.document_freqs_list_filename = freqs_file
        self.document_list_filename = list_file
        self.dataset_dir = dataset_dir

        self.documents_freqs = {}
        self.document_identificators = {}
        self.identificator_documents = {}

        with open(self.document_list_filename) as f:
            for line in f:
                data = line.strip().split()
                index = int(data[0])
                identifier = data[1]
                self.document_identificators[index] = identifier
                self.identificator_documents[identifier] = index

        self.documents_number = index

        with open(self.document_freqs_list_filename) as f:
            for line in f:
                data = line.strip().split()
                self.documents_freqs[self.identificator_documents[data[1]]] = int(data[0])

        self.avgdl = sum(self.documents_freqs.values()) / float(self.documents_number)
        self.k1 = 2.0
        self.b = 0.75


    def process_query(self, query):
        terms = self.normalizer.normalize_line(query)

        if not terms:
            return set()

        inverted_index = {}
        term_doc_tf = {}

        for term in terms:
            self.send_message(term)
            term_doc_tf[term] = self.parse_message_array(self.recieve_message().split())
            inverted_index[term] = term_doc_tf[term].keys()

        documents = self.merge(inverted_index, terms)

        if not documents:
            return set()

        return self.rank(documents, term_doc_tf, terms)


    def recieve_message(self):
        message = ''

        while not message.endswith('\n'):
            message += self.socket.recv(1024).decode('utf-8')

        return message.strip()


    def send_message(self, message):
        self.socket.send((message + '\n').encode('utf-8'))


    def parse_message_array(self, message_array):
        result = {}
        i = 0

        while i <= len(message_array) - 1:
            result[int(message_array[i])] = int(message_array[i + 1])
            i = i + 2

        return result


    def merge(self, inverted_index, terms):
        result = set(inverted_index[terms[0]])

        for i in range(1, len(terms)):
            result = result.intersection(set(inverted_index[terms[i]]))

        return result


    def rank(self, documents, term_doc_tf, terms):
        document_scores = {}
        document_freqs = {}

        for document in documents:
            document_scores[document] = self.score_document(document, term_doc_tf, terms)

        result = sorted(document_scores.items(), key=lambda x: x[1], reverse=True)
        best_match = result[0]
        best_match_file = open(os.path.join(self.dataset_dir, client.document_identificators[best_match[0]]), 'r')
        best_match_data = ' '.join(best_match_file.readlines())

        for term in terms:
            best_match_data = best_match_data.replace(term, color.RED + term + color.END)

        print(best_match_data)
        return result


    def score_document(self, document, term_doc_tf, terms):
        result = 0

        for term in terms:
            IDF = math.log((self.documents_number - len(term_doc_tf[term]) + 0.5) / (len(term_doc_tf[term]) + 0.5))
            f = term_doc_tf[term][document]

            result += IDF * (f * (self.k1 + 1)) / (f + self.k1 * (1 - self.b + self.b * self.documents_freqs[document] / self.avgdl))

        return result


if __name__ == '__main__':
    client = Client()

    while True:
        query = input('Enter new search query: ')

        if query == 'exit':
            break

        result = client.process_query(query)

        if not result:
            print('Nothing was found')
        else:
            for document, score in result:
                print(client.document_identificators[document], score)

    sys.exit()
