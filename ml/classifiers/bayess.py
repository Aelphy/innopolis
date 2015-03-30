import os
import math

emails_root = 'Emails'

word_features = {}
spam_email_number = 0
nonspam_email_number = 0
spam_words_number = 0
nonspam_words_number = 0

def predict_class(filename, word_features):
    spam_probabilities = []
    nonspam_probabilities = []

    with open(filename) as f:
        for string in f:
            for word in string.strip().split(' '):
                if word in word_features:
                    spam_word_prob = (word_features[word]['spam'] + 1) / float(spam_words_number + len(word_features))
                    nonspam_word_prob = (word_features[word]['nonspam'] + 1) / float(nonspam_words_number + len(word_features))

                    spam_probabilities.append(spam_word_prob)
                    nonspam_probabilities.append(nonspam_word_prob)

        probs = 0
        nonprobs = 0

        for prob in spam_probabilities:
            probs += math.log(prob)
        for nonprob in nonspam_probabilities:
            nonprobs += math.log(nonprob)

        p = (spam_email_number / float(spam_email_number + nonspam_email_number)) * probs
        v_p = (nonspam_email_number / float(spam_email_number + nonspam_email_number)) * nonprobs
    print([filename, p > v_p])


def add_word_from_class(classname, word_features):
    for filename in os.listdir(os.path.join(emails_root, classname)):
        with open(os.path.join(emails_root, classname, filename)) as f:
            for string in f:
                for word in string.strip().split(' '):
                    if word not in word_features:
                        word_features[word] = {'total' : 0, 'spam' : 0, 'nonspam' : 0}

                    word_features[word]['total'] += 1
                    word_features[word]['spam' if classname.startswith('spam') else 'nonspam'] += 1


for classname in ['spam-train', 'nonspam-train']:
    add_word_from_class(classname, word_features)

spam_email_number = len(os.listdir(os.path.join(emails_root, 'spam-train')))
nonspam_email_number = len(os.listdir(os.path.join(emails_root, 'nonspam-train')))

for word, data in word_features.items():
    spam_words_number += data['spam']
    nonspam_words_number += data['nonspam']

for classname in ['spam-test', 'nonspam-test']:
    for filename in os.listdir(os.path.join(emails_root, classname)):
        predictcted_class = predict_class(os.path.join(emails_root, classname, filename), word_features)
