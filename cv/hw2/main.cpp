#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <dirent.h>

#define bottles_per_image 5

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

// extract botles from images and callify it one by one
void process_botles(Mat drawing) {
//    int
    bool is_delimiter = true;
    bool is_prev_delimiter = true;
    int begin_col = 0;
    int end_col = 0;
    int bottles_number = 0;

    while (bottles_number < bottles_per_image) {
        int i = 0;
        int j = 0;

            for (i = end_col + 1; i < drawing.cols; i++) {
                for (j = 0; j < drawing.rows; j++) {
                    Scalar intensity = drawing.at<uchar>(j, i);

                    if (intensity.val[0] > 0) {
                        is_delimiter = false;
                    }
                }

                if (is_prev_delimiter && !is_delimiter) {
                    begin_col = i;
                }

                if (!is_prev_delimiter && is_delimiter) {
                    end_col = i - 1;
                    bottles_number++;
                    line(drawing, Point(begin_col, 50), Point(end_col, 50), Scalar(255,255,255));
                    imshow("bottles", drawing);
                    process_bottle();
                }

                is_prev_delimiter = is_delimiter;
                is_delimiter = true;
            }
    }
}

int main() {
    DIR *dir;
    string images_dir = "/Users/aelphy/Documents/innopolis/cv/hw2/Glue/";
    string image_name;
    dir = opendir(images_dir.c_str());
    struct dirent *ent;

    vector <Mat> sample_images;

    // read the sample data
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

    Mat src = sample_images[2];
    Mat src_gray, edges;
    imshow("orig", src);

    // convert image to gray scale
    GaussianBlur(src, src, Size(5,5), 0, 0, BORDER_DEFAULT);
    cvtColor(src, src_gray, CV_RGB2GRAY);

    // extract edges
    Canny(src, edges, 50, 200);
    imshow("edges", edges);

    // find contours
    vector< vector< Point > > contours;
    vector< Vec4i > hierarchy;

    findContours(edges, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

    // filter small contours
    Mat drawing = Mat::zeros(edges.size(), CV_8UC3);

    for( int i = 0; i< contours.size(); i++ ) {
        if (contours[i].size() > 200) {
            drawContours(drawing, contours, i, Scalar(255, 255, 255), 1, 1, hierarchy, 0, Point());
        }
    }

    cvtColor(drawing, drawing, CV_RGB2GRAY);
    imshow("Contours", drawing);

    process_botles(drawing);

    cvWaitKey(0);

    return 0;
}
