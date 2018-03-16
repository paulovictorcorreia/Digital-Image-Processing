#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, mask;
  int width, height;
  int nobjects, nlabel;
  int nbubbles;
  CvPoint p;//OpenCV Class for reading a point and use on floodFill
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE); //Read iamge in grayscale
  
  if(!image.data)//Checks if image successfully loaded
  {
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  //Removes top and bottom objects on the border
  for(int i = 0; i < width; i++)
  {
    p.y = 0;
    p.x = i;
    floodFill(image, p, 0);
    p.y = height-1;
    floodFill(image, p, 0);
  }
  // Removes left and right objects on the border
  for(int i = 0; i < height; i++)
  {
    p.x = 0;
    p.y = i;
    floodFill(image, p, 0);
    p.x = height-1;
    floodFill(image, p, 0);
  }
  //Counts The total number of objects
  nobjects=0;
  for(int i=0; i<height; i++)
  {
    for(int j=0; j<width; j++)
    {
      if(image.at<uchar>(i,j) == 255)
      {
        // achou um objeto
        nobjects++;
        p.x=j;
        p.y=i;
        floodFill(image,p,nobjects);
      }
    }
  }
  //Counts the number of objects with holes in it
  p.x = 0;
  p.y = 0;
  nbubbles = 0;
  nlabel = 1;//Initialiaze label with 1
  floodFill(image, p, 1);
  
  for(int i=0; i<height; i++)
  {
    for(int j=0; j<width; j++)
    {
      //Checks if the left pixel has the same color of the curent label
      if((image.at<uchar>(i,j-1) == nlabel) && (image.at<uchar>(i,j) == 0))
      {
        // achou um objeto
        nbubbles++;
        p.x=j;
        p.y=i;
        floodFill(image,p,0);
        nlabel++;
      }
      //Checks if the hole is from an object with 2+ holes
      else if((image.at<uchar>(i,j-1) < nlabel) && (image.at<uchar>(i,j) == 0))
      {
        p.x=j;
        p.y=i;
        floodFill(image,p,(int)image.at<uchar>(i,j-1));
      }
      // Make the loop beging again to search for a object with the following label
      if((i == height-1) && (j == width - 1) && (nlabel < nobjects))
      {
        i = 0;
        j = 0;
        nlabel++;

      }
    }
  }
  cout << "Total number of objects: " << nobjects << endl;
  cout << "Total number of objects with bubbles " << nbubbles << endl;
  imshow("image", image);
  imwrite("labeling.png", image);
  waitKey();
  return 0;
}