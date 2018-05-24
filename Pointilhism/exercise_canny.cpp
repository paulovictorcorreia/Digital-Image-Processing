#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace cv;

#define STEP 5
#define JITTER 3
#define RAIO 3

int top_slider = 10;
int top_slider_max = 200;

char TrackbarName[50];

Mat image, border;
void on_trackbar_canny(int, void*){
  vector<int> yrange;
  vector<int> xrange;

  Mat points;

  int width, height, gray;
  int x, y;
  

  srand(time(0));
  
  
  width=image.size().width;
  height=image.size().height;

  
  points = Mat(height, width, CV_8U, Scalar(255));
  ///////////////////
  Canny(image, border, top_slider, 3*top_slider);
  
  for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
      if(border.at<uchar>(i,j)==255){
        gray = image.at<uchar>(i,j);
      circle(points,
             cv::Point(j,i),
             RAIO,
             CV_RGB(gray,gray,gray),
             -1,
             CV_AA);
      }
    }
  }
  imshow("canny", points);
}
int main(int argc, char** argv){
  int width, height;

  image= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  width=image.size().width;
  height=image.size().height;

  sprintf( TrackbarName, "Threshold inferior", top_slider_max );

  namedWindow("canny",1);
  createTrackbar( TrackbarName, "canny",
                &top_slider,
                top_slider_max,
                on_trackbar_canny );

  on_trackbar_canny(top_slider, 0 );

  waitKey();
  imwrite("cannyborders.png", border);
  return 0;
}