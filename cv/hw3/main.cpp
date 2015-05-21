#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <iostream>
#include <dirent.h>
#include <unordered_map>

#define SIGNS_NUMBER 9
#define BOUND_SIZE 800

using namespace cv;
using namespace std;

vector <string> answers;
const string labels_a[] = {
    "parking",
    "no_straight",
    "no_right_turn",
    "unknown",
    "no_left_turn",
    "go_straight",
    "go_right",
    "go_straight",
    "yield",
    "go_left",
    "unknown",
    "yield",
    "parking",
    "no_straight",
    "no_right_turn",
    "unknown",
    "no_left_turn",
    "go_straight",
    "go_right",
    "unknown"
};

const string classes_a[] = {
    "go_left",
    "go_right",
    "go_straight",
    "no_left_turn",
    "no_parking",
    "no_right_turn",
    "no_straight",
    "parking",
    "yield",
    "unknown"
};

// mapping between signs and their names
unordered_map<int, std::string> sign_names(SIGNS_NUMBER);

vector <string> labels (labels_a, labels_a + sizeof(labels_a) / sizeof(labels_a[0]));
vector <string> classes (classes_a, classes_a + sizeof(classes_a) / sizeof(classes_a[0]));

void compute_statistics(vector <string> &answers, vector <string> &labels, vector <string> &classes) {
    int class_elements_number = 0;
    int not_class_elements_number = 0;
    int false_positives = 0;
    int false_negatives = 0;
    int true_positives = 0;
    int true_negatives = 0;

    // for each existing class
    for(int i = 0; i < classes.size(); i++) {
        // for all your answers
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

    double precision = (double) true_positives / (double) (true_positives + false_positives);
    double recall = (double) true_positives / (double) (true_positives + false_negatives);
    double accuracy = (double) (true_positives + true_negatives) / (double) (true_positives + false_positives + true_negatives + false_negatives);

    cout << "precision is " << precision << endl;
    cout << "recall is " << recall << endl;
    cout << "accuracy is " << accuracy << endl;
    cout << endl;

    for (int i = 0; i < answers.size(); i++) {
        cout << answers[i] << endl;
    }
}

void process_sign_candidate(Mat &sign_candidate, vector <Mat> &signs) {
    Mat sign_candidate_gray;
    Mat sign_candidate_edges;
    vector <double> scores;
    vector<vector<Point> > points;

    // extract edges from sign candidate
    cvtColor(sign_candidate, sign_candidate_gray, CV_BGR2GRAY);
    equalizeHist(sign_candidate_gray, sign_candidate_gray);
    erode(sign_candidate_gray, sign_candidate_gray, Mat(), Point(-1, -1));
    GaussianBlur(sign_candidate_gray, sign_candidate_gray, Size(5, 5), 0);
    Canny(sign_candidate_gray, sign_candidate_edges, 120, 180);

    // check the best match for every known sign
    for (int i = 0; i < signs.size(); i++) {
        Mat scaled_candidate;
        Mat scaled_candidate_edges;
        vector<vector<Point> > results;
        vector<float> costs;

        // recise sign to the size of candidate and extract edges
        resize(signs[i], scaled_candidate, sign_candidate.size());
        GaussianBlur(scaled_candidate_edges, scaled_candidate_edges, Size(7, 7), 2);
        Canny(scaled_candidate, scaled_candidate_edges, 120, 180);

        int best = chamerMatching(sign_candidate_edges, scaled_candidate_edges, results, costs, 1, 40, 0.1, 1, 1, 30, 0.8, 1.6, 0.8, 20);

        if( best < 0 ) {
            scores.push_back(-1); // no match
        }

        scores.push_back(costs[best]);
        points.push_back(results[best]);
    }

    // find the best match of all signs
    double best_score = 1;
    int best_index = 0;

    for (int i = 0; i < scores.size(); i++) {
        if (best_score > scores[i]) {
            best_score = scores[i];
            best_index = i;
        }
    }

    // write answer
    answers.push_back(sign_names[best_index]);

    // draw answer
    size_t i, n = points[best_index].size();

    for(i = 0; i < n; i++) {
        Point pt = points[best_index][i];
        if (pt.inside(Rect(0, 0, sign_candidate.cols, sign_candidate.rows)))
            sign_candidate.at<Vec3b>(pt) = Vec3b(0, 255, 0);
    }

    cout << best_score << " " << sign_names[best_index] << endl;
}

// process one problem
void process_problem(Mat &problem, vector <Mat> &signs) {
    Mat bin_problem;
    vector < vector <Point> > contours;
    vector < Vec4i > hierarchy;

    // extract regions with sign cadidates
    cvtColor(problem, bin_problem, CV_BGR2GRAY);
    dilate(bin_problem, bin_problem, Mat(), Point(-1, -1), 2);
    threshold(bin_problem, bin_problem, 250, 255, CV_THRESH_BINARY_INV);
    findContours(bin_problem, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));

    vector < vector <Point> > contours_poly(contours.size());
    vector < Rect > bound_rectangles(contours.size());
    vector < Rect > sign_candidates;

    // find border rectangles
    for (int i = 0; i < contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
        bound_rectangles[i] = boundingRect(Mat(contours_poly[i]));
    }

    // filter small counturs
    for (int i = 0; i < contours.size(); i++) {
        if (bound_rectangles[i].area() > BOUND_SIZE) {
            sign_candidates.push_back(bound_rectangles[i]);
        }
    }

    // process every sign
    for (int i = 0; i < sign_candidates.size(); i++) {
        Mat sign = problem(sign_candidates[i]);

        process_sign_candidate(sign, signs);
    }

    imshow("problem", problem);
    waitKey();
}

// extract signs from samples
void process_signs(vector <Mat> &signs, vector <Mat> &processed_signs) {
    for (int i = 0; i < signs.size(); i++) {
        Mat bin_problem;
        vector < vector <Point> > contours;
        vector < Vec4i > hierarchy;

        // extract edges
        cvtColor(signs[i], bin_problem, CV_BGR2GRAY);
        erode(bin_problem, bin_problem, Mat(), Point(0, 0), 4);
        threshold(bin_problem, bin_problem, 127, 255, CV_THRESH_BINARY_INV);
        findContours(bin_problem, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        vector < vector <Point> > contours_poly(contours.size());

        approxPolyDP(Mat(contours[0]), contours_poly[0], 3, true);

        Mat sign = signs[i](boundingRect(Mat(contours_poly[0])));

        processed_signs.push_back(sign);
    }
}

int main() {
    DIR *dir;
    string images_dir = "/Users/aelphy/Documents/innopolis/cv/hw3/RoadSigns/";
    string image_name;
    dir = opendir(images_dir.c_str());
    struct dirent *ent;

    vector <Mat> images;

    // read the data
    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            image_name = ent->d_name;
            if (image_name[0] != '.') {
                images.push_back(imread(images_dir + image_name));
            }
        }

        closedir (dir);
    } else {
        cout << "not present" << endl;
    }

    vector <Mat> problems;
    vector <Mat> signs;
    vector <Mat> processed_signs;

    problems.push_back(images[16]);
    problems.push_back(images[17]);

    for (int i = 1; i < SIGNS_NUMBER; i++) {
        signs.push_back(images[i]);
    }

    signs.push_back(images[18]);

    for (int i = 0; i < signs.size(); i++) {
        sign_names[i] = classes_a[i];
    }

    // extract signs patterns from samples
    process_signs(signs, processed_signs);

    // process each problem composite
    for (int i = 0; i < problems.size(); i++) {
        process_problem(problems[i], processed_signs);
    }

    compute_statistics(answers, labels, classes);

    return 0;
}
