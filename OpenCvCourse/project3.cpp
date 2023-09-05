#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Project 3  //////////////////////

/////////////////  Webcam  //////////////////////


void main() {

    VideoCapture cap(1);
    Mat img;


    CascadeClassifier plateCascade;

    plateCascade.load("Resources/haarcascade_russian_plate_number.xml");
    if (plateCascade.empty()) { cout << "XML file not loaded" << endl; }

    vector<Rect> plates;

    while (true) {

        cap.read(img);




        plateCascade.detectMultiScale(img, plates, 1.1, 10);
        for (int i = 0; i < plates.size(); i++)
        {
            Mat imgCrop = img(plates[i]);
            //imshow(to_string(i), imgCrop);
            imwrite("Resources/Plates/" + to_string(i) + ".png", imgCrop);
            rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);
        }


        imshow("Image", img);
        waitKey(1);

        //I'll provide a revised version of the code that takes into account the potential issue of non-overlapping shapes. In this version, we'll ensure that the grid cells for masking overlap with the extent of your raster data. We'll also transform the grid cell shapes to match the CRS of the raster data. Please make sure that your raster data and Corine Land Cover classes are aligned correctly geographically.
                //I'll provide a revised version of the code that takes into account the potential issue of non-overlapping shapes. In this version, we'll ensure that the grid cells for masking overlap with the extent of your raster data. We'll also transform the grid cell shapes to match the CRS of the raster data. Please make sure that your raster data and Corine Land Cover classes are aligned correctly geographically.

                //I'll provide a revised version of the code that takes into account the potential issue of non-overlapping shapes. In this version, we'll ensure that the grid cells for masking overlap with the extent of your raster data. We'll also transform the grid cell shapes to match the CRS of the raster data. Please make sure that your raster data and Corine Land Cover classes are aligned correctly geographically.

    }

}