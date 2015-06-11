from normalizer import Normalizer
from inserter import Inserter
import glob
import os

class Preprocessor():
    def __init__(self, data_dir):
        self.normalizer = Normalizer()
        self.data_dir = data_dir
        self.docs_number = len(glob.glob(os.path.join(self.data_dir, '**', '**')))
        self.inserter = Inserter()


    def preprocess(self):
        for index, file_name in enumerate(glob.glob(os.path.join(self.data_dir, '**', '**'))):
            terms = self.normalizer.normalize(file_name)

            for term in terms:
                self.inserter.insert(term, self.doc_id(file_name), terms.count(term), self.docs_number)

            print('processing doc {0}/{1}'.format(index + 1, self.docs_number))


    def doc_id(self, file_name):
        return os.path.splitext(os.path.basename(file_name))[0]


if __name__ == '__main__':
    preprocessor = Preprocessor()
