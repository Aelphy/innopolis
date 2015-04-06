#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <dirent.h>

using namespace cv;
using namespace std;

void compute_statistics(string *answers, string *labels, string *classes) {
    int class_elements_number = 0;
    int not_class_elements_number = 0;
    int false_positives = 0;
    int false_negatives = 0;
    int true_positives = 0;
    int true_negatives = 0;

    for(int i = 0; i < 3; i++) {
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

int main() {
    DIR *dir;
    string images_dir = "/Users/aelphy/Documents/innopolis/cv/hw2/Glue/";
    string image_name;
    dir = opendir(images_dir.c_str());
    struct dirent *ent;

    vector <Mat> sample_images;

    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            image_name = ent->d_name;
            cout << image_name << endl;
            if (image_name[0] != '.') {
                sample_images.push_back(imread("/Users/aelphy/Documents/innopolis/cv/hw2/Glue/" + image_name));
            }
        }
        closedir (dir);
    } else {
        cout << "not present" << endl;
    }

    Mat src = sample_images[0];
    Mat src_gray, edges;
    imshow("orig", src);

    GaussianBlur(src, src, Size(3,3), 0, 0, BORDER_DEFAULT);
    cvtColor(src, src_gray, CV_RGB2GRAY);

    Canny(src, edges, 50, 200);
    imshow("edges", edges);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(edges, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

    
//    imshow("orig1", contours[1]);

    cvWaitKey(0);

//    for (int i = 0; i < 3; i++) {
//        sample_images[i] = imread(sample_files[i], CV_LOAD_IMAGE_COLOR); // Read the file
//
//        if(!sample_images[i].data) {                                     // Check for invalid input
//            cout <<  "Could not open or find the image" << std::endl ;
//            return -1;
//        }
//    }
//
//    Mat test_images[18];
//
//    for (int i = 0; i < 18; i++) {
//        test_images[i] = imread(test_files[i], CV_LOAD_IMAGE_COLOR);   // Read the file
//
//        if(!test_images[i].data) {                                     // Check for invalid input
//            cout <<  "Could not open or find the image" << std::endl ;
//            return -1;
//        }
//    }
//
//    vector <Mat> rgb;
//
//    split(sample_images[2], rgb);
//    imwrite("red2.jpg", rgb[2]);
//
//    for(int i = 0; i < 18; i++) {
//        split(test_images[i], rgb);
//
//        if (cv::mean(2 * rgb[2] - rgb[0] - rgb[1])[0] < max_empty_treshold) {
//            answers[i] = "empty";
//        } else if (cv::mean(2 * rgb[2] - rgb[0] - rgb[1])[0] < max_one_treshold) {
//            answers[i] = "one spoon";
//        } else {
//            answers[i] = "two spoons";
//        }
//    }

    return 0;
}
