#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <iostream>
#include <dirent.h>
#include <unordered_map>

using namespace cv;
using namespace std;

int main() {
    DIR *dir;
    string images_dir = "/Users/aelphy/Documents/innopolis/cv/hw4/ObjectAbandonmentAndRemoval/";
    vector <string> videos;
    dir = opendir(images_dir.c_str());
    struct dirent *ent;

    vector <Mat> images;

    // read the data
    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name[0] != '.') {
                videos.push_back(ent->d_name);
            }
        }

        closedir (dir);
    } else {
        cout << "not present" << endl;
        return -1;
    }

    for (int i = 0; i < videos.size(); i++) {
        VideoCapture cap(images_dir + videos[i]);

        // if not success, exit program
        if (!cap.isOpened()) {
            cout << "Cannot open the video file" << endl;
            return -1;
        }

        //get the frames per seconds of the video
        double fps = cap.get(CV_CAP_PROP_FPS);

        //create a window called "MyVideo"
        namedWindow(videos[i],CV_WINDOW_AUTOSIZE);
        cout << fps << endl;

        break;
    }

    return 0;
}