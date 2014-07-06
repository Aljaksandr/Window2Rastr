#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "screenCapture.h"
#include "PlotCircles.h"
#include "BitmapToRast.h"
#include <atlbase.h>
#include <math.h>


#define Xnum 27
#define Ynum 17
#define RADIUS 10
#define Xsize ceil((Xnum-1)*RADIUS*sqrt(3.0)) + 2*RADIUS
#define Ysize Ynum*2*RADIUS

using namespace cv;
using namespace std;



int main( int argc, char** argv )
{
if( (argc != 2) && (argc != 6))
 {
	cout <<" Usage: Window2Rastr WindowName [Top Bottom Left Right]" << endl;
	return -1;
 }

 size_t Top, Bottom, Left, Right;
 if (argc == 6)
 {
	Top		= atoi(argv[2]);
	Bottom	= atoi(argv[3]);
	Left	= atoi(argv[4]);
	Right	= atoi(argv[5]);
 }
 else
 {
	Top		= 0;
	Bottom	= 0;
	Left	= 0;
	Right	= 0;
 }


 std::vector<HWND> Processes;
 USES_CONVERSION;
 getHwndsByProcessName(A2CW(argv[1]), Processes);

 if (!Processes.size())
 {
	 std::cout << "There is no process with name " << argv[1] << std::endl;
	 std::cout << "The programm will be stopped" << std::endl;
	 return -1;
 }

 std::cout << "Found " << Processes.size() << " processes with name " << argv[1] << std::endl;
 std::cout << "Please select number of process" << std::endl;

 unsigned short Number;
 std::cin >> Number;

 if ((Number <= 0)||(Number > Processes.size()))
 {
	 std::cout << "Incorrect entered Number!! The programm will be stopped" << std::endl;
	 return -1;
 }
 
 WindowCapture cap(Processes[Number-1]);
 
 Mat image;
 PlotCircles Rastr(Xnum, Ynum, RADIUS);
 BitmapToRast ToRastr(Xnum, Ynum);

 cv::Scalar BigRastrColors[Ynum*(Xnum+1)/2];
 cv::Scalar SmallRastrColors[(Ynum-1)*(Xnum-1)/2];
 
 Mat RastrImage(Ysize, Xsize, CV_8UC3);
 RastrImage = cv::Scalar(35, 2, 2);

 //namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
 namedWindow( "Rastred Image", WINDOW_AUTOSIZE ); // Create a window for display.

 while(true)
 {
	  cap.captureFrame(image);

	  ToRastr.Convert(image(cv::Rect(Left, Top, image.cols - Left - Right, image.rows - Bottom - Top))); 
	  Rastr.PlotRastr(RastrImage, ToRastr.GetBigGridColors(), ToRastr.GetSmallGridColors());

	  //imshow( "Display window", image ); // Show our image inside it.
	  imshow( "Rastred Image", RastrImage ); // Show our image inside it.

	  if( waitKey(20) != (-1)) // Wait for a keystroke in the window)
		return 0;
 }

 return 0;
}