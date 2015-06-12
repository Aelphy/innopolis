from normalizer import Normalizer
from inserter import Inserter
from datetime import datetime
from glob import glob
import os


class Preprocessor():
    def __init__(self, data_dir, start_index=0):
        self.normalizer = Normalizer()
        self.data_dir = data_dir
        self.docs_number = len(glob(os.path.join(self.data_dir, '**', '*.nxml')))
        self.inserter = Inserter()
        self.start_index = 0


    def preprocess(self):
        print('Start time: {0}'.format(datetime.now()))
        for index, file_name in enumerate(sorted(glob(os.path.join(self.data_dir, '**', '*.nxml')))):
            if index >= self.start_index:
                terms = self.normalizer.normalize(file_name)

                for term in set(terms):
                    self.inserter.insert(term, self.doc_id(file_name), terms.count(term))

                if index % 100 == 0:
                    print('processing doc {0}/{1}'.format(index + 1, self.docs_number))

        print('Fineished at: {0}'.format(datetime.now()))


    def doc_id(self, file_name):
        return os.path.splitext(os.path.basename(file_name))[0]
