#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

double alfa;
int center_slider = 0;
int center_slider_max = 100;

int alfa_slider = 0;
int alfa_slider_max = 100;

int top_slider = 0;
int top_slider_max = 100;

Mat image1, image2, blended;
Mat imageTop;


char TrackbarName[50];

void on_trackbar_blend(int, void*){
 alfa = (double) alfa_slider/alfa_slider_max ;
 addWeighted( image1, alfa, imageTop, 1-alfa, 0.0, blended);
 imshow("addweighted", blended);
}
void on_trackbar_change(int, void*) {
    image2.copyTo(imageTop);
    Size tamanho = image2.size();
    int largura = tamanho.width;
    int altura = tamanho.height;
  int limit = top_slider*largura/100;
  int base = center_slider*largura/100;
  if(limit > 0){
    if(base >= 0 && base <= altura-limit){
  Mat tmp = image1(Rect(0, base, largura,limit));
  tmp.copyTo(imageTop(Rect(0, base, largura,limit)));
}
else{
  Mat tmp = image1(Rect(0, altura-limit, largura,limit));
  tmp.copyTo(imageTop(Rect(0, altura-limit, largura,limit)));}

  }

  on_trackbar_blend(alfa_slider,0);
}


int main(int argvc, char** argv){

  image1 = imread("paulo.png");
  image2 = image1.clone();
  Mat aux, mask, mask1;
    float media[] = {1,1,1,1,1,
                     1,1,1,1,1,
                     1,1,1,1,1,
                     1,1,1,1,1,
                     1,1,1,1,1};

  mask = Mat(5, 5, CV_32F, media);
  scaleAdd(mask, 1/25.0, Mat::zeros(5,5,CV_32F), mask1);
  swap(mask, mask1);
  image2.convertTo(aux, CV_32F);

  for (int i = 0; i < 10; i++) {
        filter2D(aux, aux, aux.depth(), mask, Point(1, 1), 0);
    }
    aux=abs(aux);
    aux.convertTo(image2, CV_8UC3);
  image1.copyTo(imageTop);
  namedWindow("addweighted", 1);

  sprintf( TrackbarName, "Alpha ");
  createTrackbar( TrackbarName, "addweighted",
				  &alfa_slider,
				  alfa_slider_max,
				  on_trackbar_blend );
  on_trackbar_blend(alfa_slider, 0 );

  sprintf( TrackbarName, "Altura ");
  createTrackbar( TrackbarName, "addweighted",
				  &top_slider,
				  top_slider_max,
				  on_trackbar_change );
  on_trackbar_change(top_slider, 0 );
  sprintf( TrackbarName, "Posição");
  createTrackbar( TrackbarName, "addweighted",
          &center_slider,
          center_slider_max,
          on_trackbar_change );
  on_trackbar_change(center_slider, 0 );

  waitKey(0);
  return 0;
}