#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]){
    Mat inv_image;
	int rows, cols;//Number of columns and rows
	uchar aux;//Auxiliar variable to change pixels
	string picture;
	if(argc != 2){
		cout << "Input error!\n";
		exit(0);
	}
	picture = argv[1];
	inv_image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);//Read image into Mat object
	if(!inv_image.data){//Checks if picture has a valid format 
		cout << "nao abriu imagem" << endl;
		exit(0);
	}
	rows = inv_image.rows;//number of rows
	cols = inv_image.cols;//number of columns

	namedWindow("janela",WINDOW_AUTOSIZE);


	//Loop that inverts the image horizontally
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols/2;j++){
	    	aux = inv_image.at<uchar>(i, j);
	    	inv_image.at<uchar>(i, j) = inv_image.at<uchar>(i, j + cols/2);
	    	inv_image.at<uchar>(i, j + cols/2) = aux;
	    }
	}
	//Loop tha inverts the picture vertically
	for(int i=0;i<rows/2;i++){
		for(int j=0;j<cols;j++){
	    	aux = inv_image.at<uchar>(i, j);
	    	inv_image.at<uchar>(i, j) = inv_image.at<uchar>(i + rows/2, j);
	    	inv_image.at<uchar>(i + rows/2, j) = aux;
	    }
	}
	//The output picture is an inverted version of the original picture
	//in whiche we invert the quadrants of the picture.
	imshow("janela", inv_image);  
	waitKey();

 
  return 0;
}
