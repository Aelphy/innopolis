#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    double max_empty_treshold = 10;
    double max_one_treshold = 30;

    string sample_files[] = {
        "BabyFood/BabyFood-Sample0.JPG",
        "BabyFood/BabyFood-Sample1.JPG",
        "BabyFood/BabyFood-Sample2.JPG"
    };

    string test_files[] = {
        "BabyFood/BabyFood-Test1.JPG",
        "BabyFood/BabyFood-Test2.JPG",
        "BabyFood/BabyFood-Test3.JPG",
        "BabyFood/BabyFood-Test4.JPG",
        "BabyFood/BabyFood-Test5.JPG",
        "BabyFood/BabyFood-Test6.JPG",
        "BabyFood/BabyFood-Test7.JPG",
        "BabyFood/BabyFood-Test8.JPG",
        "BabyFood/BabyFood-Test9.JPG",
        "BabyFood/BabyFood-Test10.JPG",
        "BabyFood/BabyFood-Test11.JPG",
        "BabyFood/BabyFood-Test12.JPG",
        "BabyFood/BabyFood-Test13.JPG",
        "BabyFood/BabyFood-Test14.JPG",
        "BabyFood/BabyFood-Test15.JPG",
        "BabyFood/BabyFood-Test16.JPG",
        "BabyFood/BabyFood-Test17.JPG",
        "BabyFood/BabyFood-Test18.JPG"
    };

    string labels[] = {
        "one spoon",
        "one spoon",
        "two spoons",
        "one spoon",
        "one spoon",
        "two spoons",
        "empty",
        "one spoon",
        "empty",
        "one spoon",
        "two spoons",
        "one spoon",
        "one spoon",
        "two spoons",
        "one spoon",
        "empty",
        "empty",
        "one spoon"
    };

    string classes[] = {
        "one spoon",
        "two spoons",
        "empty"
    };

    string answers[18];

    Mat sample_images[3];

    for (int i = 0; i < 3; i++) {
        sample_images[i] = imread(sample_files[i], CV_LOAD_IMAGE_COLOR); // Read the file

        if(!sample_images[i].data) {                                     // Check for invalid input
            cout <<  "Could not open or find the image" << std::endl ;
            return -1;
        }
    }

    Mat test_images[18];

    for (int i = 0; i < 18; i++) {
        test_images[i] = imread(test_files[i], CV_LOAD_IMAGE_COLOR);   // Read the file

        if(!test_images[i].data) {                                     // Check for invalid input
            cout <<  "Could not open or find the image" << std::endl ;
            return -1;
        }
    }

    vector <Mat> rgb;

    split(sample_images[2], rgb);
    imwrite("red2.jpg", rgb[2]);

    for(int i = 0; i < 18; i++) {
        split(test_images[i], rgb);

        if (cv::mean(2 * rgb[2] - rgb[0] - rgb[1])[0] < max_empty_treshold) {
            answers[i] = "empty";
        } else if (cv::mean(2 * rgb[2] - rgb[0] - rgb[1])[0] < max_one_treshold) {
            answers[i] = "one spoon";
        } else {
            answers[i] = "two spoons";
        }
    }

    for(int i = 0; i < 3; i++) {
        int class_elements_number = 0;
        int not_class_elements_number = 0;
        int false_positives = 0;
        int false_negatives = 0;
        int true_positives = 0;
        int true_negatives = 0;

        for (int j = 0; j < 18; j++) {
            if (answers[j] == classes[i]) {
                class_elements_number++;

                if (labels[j] == answers[j]) {
                    true_positives++;
                } else {
                    false_negatives++;
                }
            } else {
                not_class_elements_number++;
            }
        }

        false_positives = class_elements_number - true_positives;
        true_negatives = not_class_elements_number - false_negatives;

        double precision = ((double) true_positives) / ((double) (true_positives + false_positives));
        double recall = ((double) true_positives) / ((double) (true_positives + false_negatives));
        double accuracy = ((double) (true_positives + true_negatives)) / ((double) (true_positives + false_positives + true_negatives + false_negatives));

        cout << "precision is " << precision << '\n';
        cout << "recall is " << recall << '\n';
        cout << "accuracy is " << accuracy << '\n';
        cout << '\n';
    }

    return 0;
}
