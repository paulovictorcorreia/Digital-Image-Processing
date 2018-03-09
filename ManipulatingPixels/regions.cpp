#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image;
  int P1[2], P2[2];//points in which the user determines the area of the rectangle
  uchar aux;//Auxiliar variable to help inverting the colors
  int minX, minY;//minimum values of parameters X and Y of the rectangle
  int maxX, maxY;//maximum values of parameters X and Y of the rectangle
  int rows, cols;
  //write the image file into a Mat object
  image= imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data){
    cout << "nao abriu biel.png" << endl;
    exit(0);
  }
  rows = image.rows;//number of rows
  cols = image.cols;//number of columns  
  //read area that user wishes to invert the colors
  //and do this only, if only, the given area is
  //valid within the size of the image
  do{
    cout << "P1(x, y): ";
    cin >> P1[0];
    cin >> P1[1];
    cout << "P2(x, y): ";
    cin >> P2[0];
    cin >> P2[1];
  }while((P1[0]>rows) || (P2[0]>rows) || (P1[1]>cols) || (P2[1]>cols));

  //Condition that checks the minimum and maximum
  //values of the cordinate X
  if(P1[0] > P2[0]){
    minX = P2[0];
    maxX = P1[0];
  }
  else{
    minX = P1[0];
    maxX = P2[0];
  }
  //Condition that checks the minimum and maximum
  //values of the cordinate Y
  if(P1[1] > P2[1]){
    minY = P2[1];
    maxY = P1[1];
  }
  else{
    minY = P1[1];
    maxY = P2[1];
  }
  //loop that uses the ranges previously determined to invert
  //the colors of each pixel on grayscale
  for(int i=minX;i<maxX;i++){
    for(int j=minY;j<maxY;j++){
      aux = image.at<uchar>(i,j);
      image.at<uchar>(i,j) = 255 - aux;
    }
  }
  //shows image on a window
  imshow("janela", image);  
  waitKey();

  return 0;
}
