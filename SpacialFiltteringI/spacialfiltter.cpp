#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void printmask(Mat &m){
  for(int i=0; i<m.size().height; i++){
    for(int j=0; j<m.size().width; j++){
      cout << m.at<float>(i,j) << ",";
    }
    cout << endl;
  }
}

void menu(){
  cout << "\npressione a tecla para ativar o filtro: \n"
	"a - calcular modulo\n"
    "m - media\n"
    "g - gauss\n"
    "v - vertical\n"
	"h - horizontal\n"
    "l - laplaciano\n"
    "s - laplacian of gaussian 5x5\n"
    "d - laplacian of gaussian 9x9\n"
	"esc - sair\n";
}

int main(int argvc, char** argv){
  VideoCapture video;
  int lg_flag = 0;
  float media[] = {1,1,1,
				   1,1,1,
				   1,1,1};
  float gauss[] = {1,2,1,
				   2,4,2,
				   1,2,1};
  float vertical[]={-1,0,1,
					  -2,0,2,
					  -1,0,1};
  float horizontal[]={-1,-2,-1,
					0,0,0,
					1,2,1};
  float laplacian[]={0,-1,0,
					 -1,4,-1,
					 0,-1,0};
  float lg[] = {0, 1, 1, 2, 2, 2, 1, 1, 0, //9x9 mask for laplacian of gaussian
                1, 2, 4, 5, 5, 5, 4, 2, 1,
                1, 4, 5, 3, 0, 3, 5, 4, 1,
                2, 5, 3, -12, -24, -12, 3, 5, 2,
                2, 5, 0, -24, -40, -24, 0, 5, 2,
                2, 5, 3, -12, -24, -12, 3, 5, 2,
                1, 4, 5, 3, 0, 3, 5, 4, 1,
                1, 2, 4, 5, 5, 5, 4, 2, 1,
                0, 1, 1, 2, 2, 2, 1, 1, 0};
  float lg2[] = { //5x5 mask for laplacian gaussian
    0, 0, 1, 0, 0,
    0, 1, 2, 1, 0,
    1, 2, -16, 2, 1,
    0, 1, 2, 1, 0,
    0, 0, 1, 0, 0};

    int c1 = 1;
    int c2 = 1;
  Mat cap, frame, frame32f, frameFiltered;
  Mat mask(3,3,CV_32F), mask1;
  Mat result, result1;
  double width, height, min, max;
  int absolut;
  char key;
  video.open(0);
  if(!video.isOpened())
    return -1;
  width=video.get(CV_CAP_PROP_FRAME_WIDTH);
  height=video.get(CV_CAP_PROP_FRAME_HEIGHT);
  std::cout << "largura=" << width << "\n";;
  std::cout << "altura =" << height<< "\n";;

  namedWindow("filtroespacial",1);
  mask = Mat(3, 3, CV_32F, media);
  scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1);
  swap(mask, mask1);
  absolut=1; // calcs abs of the image

  menu();
  for(;;){
    video >> cap;
    cvtColor(cap, frame, CV_BGR2GRAY);
    flip(frame, frame, 1);
    imshow("original", frame);
    frame.convertTo(frame32f, CV_32F);
    filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(c1,c1), 0);
    if(absolut){
      frameFiltered=abs(frameFiltered);
    }
    frameFiltered.convertTo(result, CV_8U);
    imshow("filtroespacial", result);
    key = (char) waitKey(10);
    if( key == 27 ) break; // esc pressed!
    switch(key){
    case 'a':
	  menu();
      absolut=!absolut;
      c1 = 1;
      break;
    case 'm':
	  menu();
      mask = Mat(3, 3, CV_32F, media);
      scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1);
      mask = mask1;
      printmask(mask);
      c1 = 1;
      break;
    case 'g':
	  menu();
      mask = Mat(3, 3, CV_32F, gauss);
      scaleAdd(mask, 1/16.0, Mat::zeros(3,3,CV_32F), mask1);
      mask = mask1;
      printmask(mask);
      c1 = 1;
      break;
    case 'h':
	  menu();
      mask = Mat(3, 3, CV_32F, horizontal);
      printmask(mask);
      c1 = 1;
      break;
    case 'v':
	  menu();
      mask = Mat(3, 3, CV_32F, vertical);
      printmask(mask);
      c1 = 1;
      break;
    case 'l':
	  menu();
      mask = Mat(3, 3, CV_32F, laplacian);
      printmask(mask);
      c1 = 1;
      break;
    case 's':
      mask = Mat(5, 5, CV_32F, lg2);
      printmask(mask);
      c1 = 2;
      break;
      case 'd':
        mask = Mat(9, 9, CV_32F, lg);
        printmask(mask);
        c1 = 4;
        break;
    default:
      break;
    }
  }
  return 0;
}
