#include "VideoCaptureProcess.h"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

int main()
{
	try
	{
		//const char* addr = "rtsp://192.168.0.100/axis-media/media.amp";
		const char* addr = "C:/Users/Mehdi/Downloads/face_eigen_movie.avi";

		VideoCaptureProcess cap(0, 50);
		cap.start();
		cv::Mat image;
		cv::Mat edges;
		long long time;
		cv::namedWindow("Original");
		cv::namedWindow("Edges");
		cv::namedWindow("Resized");
		while (true)
		{
			/** grab image from capturing thread
			Input Parameters:
			cv::Mat image = destination image
			long long time = time between starting capture thread and capturing image
			int lag = default 0, grab cached images
			*/
			cap.grabFrameWithTime(image, time, 10);
			if (!image.empty())
			{
				char txt[100];
				sprintf(txt, "TimeStamp = %d", time);
				cv::Canny(image, edges, 10, 155);
				cv::putText(image, txt, cv::Point(50, 50), 0, 1.0, cv::Scalar(0, 0, 255));
				imshow("Original", image);
				imshow("Edges", edges);
			}
			char c = cv::waitKey(30);
			if (c == 'c')
				break;
			else if (c == 's')
				cap.stop();//stop capturing thread
			else if (c == 'p')
				cap.start();//start capturing thread
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	return 0;
}