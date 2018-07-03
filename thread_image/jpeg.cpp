#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

extern "C" void Image();

int main(int argc, char** argv) {
	 Image();
	 Mat image;
	 image = imread( "Converted_Image.png", IMREAD_COLOR );
	 if(!image.data )
	 {
	   printf( " No image data \n " );
	   return -1;
	 }
	 Mat gray_image;
	 cvtColor( image, gray_image, COLOR_BGR2RGBA );

	 imwrite( "orange.jpeg", gray_image );
	 namedWindow( "window", WINDOW_NORMAL );
	 namedWindow( "Orange", WINDOW_NORMAL );
	 imshow( "window", image );
	 imshow( "Orange", gray_image );
	 waitKey(0);
	 return 0;
}
