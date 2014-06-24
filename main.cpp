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

	do {
		vCapture->read(videoFrame);

		cv::Mat hsvImage;
		cv::cvtColor(videoFrame, hsvImage, CV_BGR2HSV);
		cv::vector<cv::Mat> hsv;
		cv::split(hsvImage, hsv);

		/*/////////////////////////////////////////////////////////////////////////
		cv::Mat hsvHist[3];
		int histSize = 256;
		float range[]  = { 0.0f, 256.0f };
		const float *ranges[] = { range };
		cv::calcHist(&hsv[0], 1, NULL, cv::Mat(), hsvHist[0], 1, &histSize, ranges);
		cv::calcHist(&hsv[1], 1, NULL, cv::Mat(), hsvHist[1], 1, &histSize, ranges);
		cv::calcHist(&hsv[2], 1, NULL, cv::Mat(), hsvHist[2], 1, &histSize, ranges);

		int histWidth = 512, histHeight = 400;
		int binWidth = cvRound( 1.0 * histWidth / histSize );
		cv::Mat histImg = cv::Mat::zeros(histHeight, histWidth, CV_8UC3);

		cv::normalize(hsvHist[0], hsvHist[0], 0, histImg.rows, cv::NORM_MINMAX);
		cv::normalize(hsvHist[1], hsvHist[1], 0, histImg.rows, cv::NORM_MINMAX);
		cv::normalize(hsvHist[2], hsvHist[2], 0, histImg.rows, cv::NORM_MINMAX);

		for(int i = 1; i < histSize; ++i) {
			cv::line( histImg, cv::Point( binWidth*(i-1), histHeight - cvRound(hsvHist[0].at<float>(i-1)) ) ,
				cv::Point( binWidth*(i), histHeight - cvRound(hsvHist[0].at<float>(i)) ),
				cv::Scalar( 255, 0, 0), 2, 8, 0  );
			cv::line( histImg, cv::Point( binWidth*(i-1), histHeight - cvRound(hsvHist[1].at<float>(i-1)) ) ,
				cv::Point( binWidth*(i), histHeight - cvRound(hsvHist[1].at<float>(i)) ),
				cv::Scalar( 0, 255, 0), 2, 8, 0  );
			cv::line( histImg, cv::Point( binWidth*(i-1), histHeight - cvRound(hsvHist[2].at<float>(i-1)) ) ,
				cv::Point( binWidth*(i), histHeight - cvRound(hsvHist[2].at<float>(i)) ),
				cv::Scalar( 0, 0, 255), 2, 8, 0  );
		}
		cv::imshow("hist", histImg);
		/////////////////////////////////////////////////////////////////////////*/

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
