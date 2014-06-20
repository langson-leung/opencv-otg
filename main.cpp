#include <windows.h>
#include <opencv2/opencv.hpp>
#pragma comment(lib, "C:/opencv/build/lib/Debug/opencv_core249d.lib")
#pragma comment(lib, "C:/opencv/build/lib/Debug/opencv_imgproc249d.lib")
#pragma comment(lib, "C:/opencv/build/lib/Debug/opencv_highgui249d.lib")

int main(int argc, char *argv[])
{
	int err = 0;
	cv::Mat videoFrame;
	cv::VideoCapture *vCapture = new cv::VideoCapture(0);
	if (!vCapture->isOpened()) { 
		err = ::GetLastError();
		goto hell;
	}
	cv::namedWindow("CaptureScene");
	cv::namedWindow("hComponent");
	cv::namedWindow("sComponent");
	cv::namedWindow("vComponent");

	do {
		vCapture->read(videoFrame);

		cv::Mat hsvImage;
		cv::cvtColor(videoFrame, hsvImage, CV_BGR2HSV);
		cv::vector<cv::Mat> hsv;
		cv::split(hsvImage, hsv);
		cv::imshow("hComponent", hsv[0]);
		cv::imshow("sComponent", hsv[1]);
		cv::imshow("vComponent", hsv[2]);

		cv::imshow("CaptureScene", videoFrame);
	} while (cv::waitKey(30) != 0x1b);

hell:
	cv::destroyAllWindows();
	if (vCapture) delete vCapture;
	return err;
}