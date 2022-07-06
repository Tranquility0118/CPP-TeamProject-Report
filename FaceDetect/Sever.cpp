#include "opencv2/opencv.hpp"
#include<iostream>



using namespace std;
using namespace cv;

void detect_face();




int main()
{
    detect_face();
}

void detect_face()
{
    Mat src = imread("C:\\Users\\VisualS2\\Desktop\\Network\\Client_Side\\TEST.png");
    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    CascadeClassifier classifier("haarcascade_frontalface_default.xml");

    if (classifier.empty())
    {
        cerr << "XML load failed!" << endl;
        return;
    }
    vector<Rect> faces;
    classifier.detectMultiScale(src,faces);

    for (Rect rc : faces)
    {
        rectangle(src, rc, Scalar(0, 0, 255), 2);
    }
    imshow("src", src);

    waitKey();
    destroyAllWindows();

}