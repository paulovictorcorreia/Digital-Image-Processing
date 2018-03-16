#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, mask;
  int width, height;
  int nobjects, nlabel;
  int nbubbles;
  CvPoint p;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  p.x=0;
  p.y=0;

  // busca objetos com buracos presentes
  /*
  nobjects=0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
		// achou um objeto
		nobjects++;
		p.x=j;
		p.y=i;
		floodFill(image,p,nobjects);
	  }
	}
  }*/
  for(int i = 0; i < width; i++){
    p.y = 0;
    p.x = i;
    floodFill(image, p, 0);
    p.y = height-1;
    floodFill(image, p, 0);
  }
  for(int i = 0; i < height; i++){
    p.x = 0;
    p.y = i;
    floodFill(image, p, 0);
    p.x = height-1;
    floodFill(image, p, 0);
  }
/*
  nobjects=0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
    // achou um objeto
    nobjects++;
    p.x=j;
    p.y=i;
    floodFill(image,p,nobjects);
    }
  }
  }*/
  p.x = 0;
  p.y = 0;
  floodFill(image, p, 0);
  nbubbles = 0;
  nlabel = 0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if((image.at<uchar>(i,j) != 0)){
        // achou um objeto
        nlabel++;
        p.x=j;
        p.y=i;
        floodFill(image,p,nlabel);
      }
      else{
        if(image.at<uchar>(i,j-1) != 0){
          nbubbles++;
          p.x=j;
          p.y=i;
          floodFill(image,p,image.at<uchar>(i,j-1));
        }
      }

    }
  }
  //cout << "Número total de objetos com ou sem bolhas: " << nobjects << endl;
  cout << "Número total de objetos com bolhas: " << nbubbles << endl;
  //height é rows
  //width é cols
  imshow("image", image);
  imwrite("labeling.png", image);
  waitKey();
  return 0;
}