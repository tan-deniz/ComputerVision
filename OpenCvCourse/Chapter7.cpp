#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Images  //////////////////////


void getContours(Mat imgDil, Mat img) {


    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    

    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //drawContours(img, contours, -1, Scalar(255, 0, 255), 2);


    for (int i = 0; i < contours.size(); i++) 
    {
        int area = contourArea(contours[i]);
        cout << area << endl;
        
        vector<vector<Point>> conPoly(contours.size());
        vector<Rect> boundRect(contours.size());
        string objectType;

        if (area > 1000) 
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i],0.02*peri, true);
            cout << conPoly[i].size() << endl;
            boundRect[i] = boundingRect(conPoly[i]);
            

            int objCor = (int)conPoly[i].size();

            if (objCor == 3) { objectType = "Tri"; }
            else if (objCor == 4) { 
                float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
                if (aspRatio > 0.95 && aspRatio < 1.05) {
                    objectType = "Square";
                }
                else {
                    objectType = "Rect";
                }
            }
            else if (objCor > 4) { objectType = "Circile"; }


            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);

            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

            putText(img, objectType, { boundRect[i].x, boundRect[i].y-4 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 1);

        }
    }

}





void main() {

    string path = "Resources/shapes.png";
    Mat img = imread(path);
    Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

    //Preprocessing
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
    dilate(imgCanny, imgDil, kernel);

    getContours(imgDil, img);

    imshow("Image", img);
    

    waitKey(0);

} 