#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

double alfa;
int alfa_slider = 0;
int alfa_slider_max = 100;

int top_slider = 0;
int top_slider_max = 100;

double l1, l2;//Variables for tiltshift window size
double diff; //difference between the two parameters of the window size
double d; //Decay strength between original image and unfocused image
Mat image1, image2, blended;
Mat imageTop; 

char TrackbarName[50];

void on_trackbar_blend(int, void*){
 alfa = (double) alfa_slider/alfa_slider_max ;
 addWeighted( image1, alfa, imageTop, 1-alfa, 0.0, blended);
 imshow("addweighted", blended);
}

void on_trackbar_line(int, void*){
  image1.copyTo(imageTop);
  int limit = top_slider*255/100;
  if(limit > 0){
	Mat tmp = image2(Rect(0, 0, 256, limit));
	tmp.copyTo(imageTop(Rect(0, 0, 256, limit)));
  }
  on_trackbar_blend(alfa_slider,0);
}

int main(int argvc, char** argv){
    float media[] = {1,1,1,
				   1,1,1,
				   1,1,1};
	Mat mask = Mat(3, 3, CV_32F, media);
    scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1);
    filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);

    image1 = imread("blend1.jpg");
    image2 = imread("blend2.jpg");
    image2.copyTo(imageTop);
    namedWindow("addweighted", 1);
  
    sprintf( TrackbarName, "Alpha x %d", alfa_slider_max );
    createTrackbar( TrackbarName, "addweighted",
				  &alfa_slider,
				  alfa_slider_max,
				  on_trackbar_blend );
    on_trackbar_blend(alfa_slider, 0 );
  
    sprintf( TrackbarName, "Scanline x %d", top_slider_max );
    createTrackbar( TrackbarName, "addweighted",
				  &top_slider,
				  top_slider_max,
				  on_trackbar_line );
    on_trackbar_line(top_slider, 0 );

    waitKey(0);
  return 0;
}