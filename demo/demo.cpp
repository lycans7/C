/*
 * demo.cpp
 *
 *  Created on: 14-Jun-2018
 *      Author: eximiusdesign
 */

#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
 char* imageName = argv[1];
 Mat image;
 image = imread( imageName, IMREAD_COLOR );
 if( argc != 2 || !image.data )
 {
   printf( " No image data \n " );
   return -1;
 }
 Mat gray_image;
 cvtColor( image, gray_image, COLOR_BGR2RGBA );
 imwrite( "/home/eximiusdesign/Desktop/parth/eclipse/Image/gray.jpeg", gray_image );
 namedWindow( imageName, WINDOW_NORMAL );
 namedWindow( "Gray image", WINDOW_NORMAL );
 imshow( imageName, image );
 imshow( "Gray image", gray_image );
 waitKey(0);
 return 0;
}
