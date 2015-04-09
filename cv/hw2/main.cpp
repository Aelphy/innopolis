#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <dirent.h>
#include <unordered_map>

#define bottles_per_image 5
#define neck_threshold 10
#define empty_threshold 10
#define straight_threshold 5
#define centered_threshold 18

using namespace cv;
using namespace std;

vector <string> answers;
const string labels_a[] = {
    "not centered/straight",
    "not centered/straight",
    "centered/straight",
    "centered/straight",
    "no label",
    "not_centered/not straight",
    "no label",
    "not_centered/not straight",
    "centered/straight",
    "not_centered/not straight",
    "centered/not straight",
    "not_centered/not straight",
    "not_centered/not straight",
    "no label",
    "centered/straight",
    "centered/straight",
    "no label",
    "no label",
    "not_centered/not straight",
    "centered/straight",
    "no label",
    "centered/straight",
    "centered/straight",
    "no label",
    "centered/not straight",
    "not centered/not straight",
    "not centered/not straight",
    "not centered/not straight",
    "not centered/not straight",
    "no label"
};

const string classes_a[] = {
    "no label",
    "centered/straight",
    "centered/not straight",
    "not_centered/straight",
    "not_centered/not straight"
};

vector <string> labels (labels_a, labels_a + sizeof(labels_a) / sizeof(labels_a[0]));
vector <string> classes (classes_a, classes_a + sizeof(classes_a) / sizeof(classes_a[0]));

void compute_statistics(vector <string> &answers, vector <string> &labels, vector <string> &classes) {
    int class_elements_number = 0;
    int not_class_elements_number = 0;
    int false_positives = 0;
    int false_negatives = 0;
    int true_positives = 0;
    int true_negatives = 0;

    for(int i = 0; i < classes.size(); i++) {
        for (int j = 0; j < answers.size(); j++) {
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

    cout << "precision is " << precision << endl;
    cout << "recall is " << recall << endl;
    cout << "accuracy is " << accuracy << endl;
    cout << endl;
}

void process_bottle(Mat bottle) {
    int i,j;
    int neck_index = 0;
    unordered_map <int, int> left_index;
    unordered_map <int, int> right_index;
    unordered_map <int, int> box_left_index;
    unordered_map <int, int> box_right_index;
    unordered_map <int, int> left_clearance;
    unordered_map <int, int> right_clearance;

    // find indexes of exteranl edges
    for(i = bottle.rows - 1; i >= 0; i--) {
        bool skip = false;

        // go from the right side
        for(j = bottle.cols - 1; j >= 0; j--) {
            uchar intensity = bottle.at<uchar>(i, j);

            if (j == 0) {
                skip = true;

                if (intensity > 0) {
                    right_index[i] = j;
                    left_index[i] = j;
                }
            } else if (intensity == 255) {
                right_index[i] = j;

                break;
            }
        }

        // go from the left side if there is
        if (!skip) {
            for (j = 0; j < bottle.cols; j++) {
                uchar intensity = bottle.at<uchar>(i, j);

                if (intensity  == 255) {
                    left_index[i] = j;

                    break;
                }
            }
        }
    }

    // find neck
    int total = 0;

    for (i = bottle.rows - 1; i >= 1; i--) {
        int width = right_index[i] - left_index[i];
        int next_width = right_index[i - 1] - left_index[i - 1];

        if (width - next_width > 0) {
            total++;
        }

        if (total >= neck_threshold) {
            neck_index = i;
            break;
        }
    }

    // extract box
    Rect box_rect(0, neck_index, bottle.cols, bottle.rows - neck_index);
    Mat box = bottle(box_rect);

//    imshow("box", box);

    // find indexes of external edges and clearance for the box
    for(i = 0; i < box.rows; i++) {
        // go from the right side
        for(j = box.cols - 1; j >= 0; j--) {
            uchar intensity = box.at<uchar>(i, j);

            if (intensity == 255) {
                box_right_index[i] = j;

                for (int k = j - 2; k >= 0; k--) {
                    uchar next_intensity = box.at<uchar>(i, k);

                    if (next_intensity == 255) {
                        right_clearance[i] = j - k;
                        break;
                    }
                }

                break;
            }
        }

        // go from the left side if there is
        for (j = 0; j < bottle.cols; j++) {
            uchar intensity = box.at<uchar>(i, j);

            if (intensity  == 255) {
                box_left_index[i] = j;

                for (int k = j + 2; k < box.cols; k++) {
                    uchar next_intensity = box.at<uchar>(i, k);

                    if (next_intensity == 255) {
                        left_clearance[i] = k - j;
                        break;
                    }
                }

                break;
            }
        }
    }

    if (mean(box)[0] < empty_threshold) {
      answers.push_back("no label");
    } else {
        // analyze clearance
        int left_diff = 0;
        int right_diff = 0;
        int center_diff = 0;

        int left1 = left_clearance[box.rows / 8];
        int left2 = left_clearance[box.rows / 5 * 2];
        int left3 = left_clearance[box.rows / 3 * 2];

        left_diff += abs(left1 - left2) + abs(left2 - left3);

        int right1 = right_clearance[box.rows / 8];
        int right2 = right_clearance[box.rows / 3];
        int right3 = right_clearance[box.rows / 3 * 2];

        right_diff += abs(right1 - right2) + abs(right2 - right3);

        center_diff += abs(left1 - right1) + abs(left2 - right2) + abs(left3 - right3);

        if (center_diff < centered_threshold) {
            answers.push_back("centered/");
        } else {
            answers.push_back("not centered/");
        }

        if (left_diff <= straight_threshold && right_diff <= straight_threshold && left_diff + right_diff < straight_threshold) {
            answers[answers.size() - 1] += "straight";
        } else {
            answers[answers.size() - 1] += "not straight";
        }
    }
}

// extract botles from images and callify it one by one
void process_botles(Mat drawing) {
    bool is_delimiter = true;
    bool is_prev_delimiter = true;
    int begin_col = 0;
    int end_col = 0;
    int bottles_number = 0;

    vector <Mat> bottles;

    // every bottle
    while (bottles_number < bottles_per_image) {
        int i = 0;
        int j = 0;

        // find the borders of the next bottle
        for (i = end_col + 1; i < drawing.cols; i++) {
            for (j = 0; j < drawing.rows; j++) {
                uchar intensity = drawing.at<uchar>(j, i);

                if (intensity > 0) {
                    is_delimiter = false;
                }
            }

            // check for begining of bottle
            if (is_prev_delimiter && !is_delimiter) {
                begin_col = i;
            }

            // check for the end of the bottle
            if (!is_prev_delimiter && is_delimiter) {
                end_col = i + 1;
                bottles_number++;

                Rect bottle_rect(begin_col, 0, end_col - begin_col, drawing.rows);
                Mat bottle = drawing(bottle_rect);

                bottles.push_back(bottle);
            }

            is_prev_delimiter = is_delimiter;
            is_delimiter = true;
        }
    }

    for (int i = 0; i < bottles.size(); i++) {
        process_bottle(bottles[i]);
//        imshow("bottle", bottles[i]);
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
            if (image_name[0] != '.') {
                sample_images.push_back(imread("/Users/aelphy/Documents/innopolis/cv/hw2/Glue/" + image_name));
            }
        }
        closedir (dir);
    } else {
        cout << "not present" << endl;
    }

    for (int i = 0; i < sample_images.size(); i++) {
        Mat src = sample_images[i];
        Mat src_gray, edges;

        // convert image to gray scale
        GaussianBlur(src, src, Size(5, 5), 0, 0, BORDER_DEFAULT);
        cvtColor(src, src_gray, CV_RGB2GRAY);

//        imshow("src gray", src_gray);

        // extract edges
        Canny(src, edges, 50, 200);

//        imshow("edges", edges);

        // find contours
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;

        findContours(edges, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

        // filter small contours
        Mat drawing = Mat::zeros(edges.size(), CV_8U);

        for (int i = 0; i < contours.size(); i++) {
            if (contours[i].size() > 200) {
                drawContours(drawing, contours, i, Scalar(255, 255, 255), 1, 1, hierarchy, 0, Point());
            }
        }

//        imshow("drawing", drawing);

        process_botles(drawing);
//        cvWaitKey(0);
    }

    compute_statistics(answers, labels, classes);

    return 0;
}
