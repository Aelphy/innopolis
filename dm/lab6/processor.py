from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import AdaBoostClassifier

import numpy as np

labels_test = []
labels_train = []
features_test = []
features_train = []
motion_distribution_features_train = []
fram_diff_distribution_features_train = []
text_area_distribution_features_train = []
bag_of_audio_words_features_train = []
motion_distribution_features_test = []
fram_diff_distribution_features_test = []
text_area_distribution_features_test = []
bag_of_audio_words_features_test = []

MAX_LEN_MOTION = 41
MAX_FRAM_DIFF = 32
MAX_TEXT_AREA = 28
MAX_BAG_OF_WORDS = 85

def extract_data(file_name, labels, features, motion_distribution_features, fram_diff_distribution_features, text_area_distribution_features, bag_of_audio_words_features):
    with open(file_name) as f:
        total = 0

        for line in f:
            motion_distributions = []
            fram_diff_distributions = []
            text_area_distributions = []
            bag_of_audio_words = []

            for index, element in enumerate(line.strip().split()):
                if index == 0:
                    labels.append(int(element))
                else:
                    n = int(element.split(':')[0])
                    v = float(element.split(':')[1])

                    if n == 1:
                        length = v
                    elif n == 2:
                        motion_distribution_mean = v
                    elif n == 3:
                        motion_distribution_var = v
                    elif n == 4:
                        frame_diff_mean = v
                    elif n == 5:
                        frame_diff_var = v
                    elif n == 6:
                        short_time_energy_mean = v
                    elif n == 7:
                        short_time_energy_var = v
                    elif n == 8:
                        ZCR_mean = v
                    elif n == 9:
                        ZCR_var = v
                    elif n == 10:
                        spectral_centroid_mean = v
                    elif n == 11:
                        spectral_centroid_var = v
                    elif n == 12:
                        spectral_roll_off_mean = v
                    elif n == 13:
                        spectral_roll_off_var = v
                    elif n == 14:
                        spectral_flux_mean = v
                    elif n == 15:
                        spectral_flux_var = v
                    elif n == 16:
                        fundamental_freq_mean = v
                    elif n == 17:
                        fundamental_freq_var = v
                    elif n >= 18 and n <= 58:
                        motion_distributions.append(v)
                    elif n >= 59 and n <= 91:
                        fram_diff_distributions.append(v)
                    elif n >= 92 and n <= 122:
                        text_area_distributions.append(v)
                    elif n >= 123 and n <= 4123:
                        bag_of_audio_words.append(v)
                    elif n == 4124:
                        edge_change_ratio_mean = v
                    elif n == 4125:
                        edge_change_ratio_var = v

            features.append([length,
                             motion_distribution_mean,
                             motion_distribution_var,
                             frame_diff_mean,
                             frame_diff_var,
                             short_time_energy_mean,
                             short_time_energy_var,
                             ZCR_mean,
                             ZCR_var,
                             spectral_centroid_mean,
                             spectral_centroid_var,
                             spectral_roll_off_mean,
                             spectral_roll_off_var,
                             spectral_flux_mean,
                             spectral_flux_var,
                             fundamental_freq_mean,
                             fundamental_freq_var,
                             edge_change_ratio_mean,
                             edge_change_ratio_var])

            for i in range(MAX_LEN_MOTION - len(motion_distributions)):
                motion_distributions.append(0)
            for i in range(MAX_FRAM_DIFF - len(fram_diff_distributions)):
                fram_diff_distributions.append(0)
            for i in range(MAX_TEXT_AREA - len(text_area_distributions)):
                text_area_distributions.append(0)
            for i in range(MAX_BAG_OF_WORDS - len(bag_of_audio_words)):
                bag_of_audio_words.append(0)

            motion_distribution_features.append(motion_distributions)
            fram_diff_distribution_features.append(fram_diff_distributions)
            text_area_distribution_features.append(text_area_distributions)
            bag_of_audio_words_features.append(bag_of_audio_words)

            features[-1] += motion_distributions
            features[-1] += fram_diff_distributions
            features[-1] += text_area_distributions
            features[-1] += bag_of_audio_words

            total += 1
            print(total)


extract_data('train.txt', labels_train, features_train, motion_distribution_features_train, fram_diff_distribution_features_train, text_area_distribution_features_train, bag_of_audio_words_features_train)
extract_data('test.txt', labels_test, features_test, motion_distribution_features_test, fram_diff_distribution_features_test, text_area_distribution_features_test, bag_of_audio_words_features_test)

clf = AdaBoostClassifier(n_estimators=250)
clf.fit(features_train, labels_train)
print(clf.score(features_test, labels_test))
