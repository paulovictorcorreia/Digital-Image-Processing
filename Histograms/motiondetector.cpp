#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, image2; // The images we will write to calculate it's histograms
  int width, height;
  VideoCapture cap;
  vector<Mat> planes;
  Mat histR, histR2; //Mat objects for histogram comparison
  int nbins = 64;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

  double diff;

  cap.open(0);
  
  if(!cap.isOpened()){
    cout << "unavaiable camera\n";
    return -1;
  }
  
  width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);//Width of the image filmed
  height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);//Width of the image filmed
  cout << "largura = " << width << endl; 
  cout << "altura  = " << height << endl; 

  int histw = nbins, histh = nbins/2;
  Mat histImgG(histh, histw, CV_8UC3, Scalar(0,0,0));

  do{
    cap >> image;//Captures first image to compare
    split (image, planes);//splits into a vector of Mat objects
    calcHist(&planes[1], 1, 0, Mat(), histR, 1,
             &nbins, &histrange,
             uniform, acummulate); // calculate histograms
    

    normalize(histR, histR, 0, histImgG.rows, NORM_MINMAX, -1, Mat());//normalize it's value beween 0 and 1

    cap >> image2;//captures the second image for comparison
    split (image2, planes);//splits image into a vector of Mat objects
    calcHist(&planes[1], 1, 0, Mat(), histR2, 1,
             &nbins, &histrange,
             uniform, acummulate);//Calculate the second image histogram
    

    normalize(histR2, histR2, 0, histImgG.rows, NORM_MINMAX, -1, Mat());//normalize it's values
    diff = compareHist(histR2, histR, 0);//calculate the correlation between the two histogram
    									 //that means that if diff == 1, we're comparing two equal images

    if(diff <= 0.9925)//Here we set the correlation value
    {
    	cout << diff << endl;//prints the correlation of the 2 images
    	cout << "Motion Detected!!!\n\n";//Prints a warning if motion is detected
    }


    



    imshow("image", image2);
    if(waitKey(30) >= 0) break;
  }while(1);
  return 0;
}