// opecv1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>


/*
int main() {
	// Open the first camera attached to your computer
	cv::VideoCapture cap(0);
	if (!cap.isOpened()) {
		std::cout << "Unable to open the camera\n";
		std::exit(-1);
	}

	// Get the width/height and the FPS of the vide
	int width = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_WIDTH));
	int height = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	double FPS = cap.get(CV_CAP_PROP_FPS);

	cv::Mat image;
	cv::Mat panel_middle, panel_right;
	int delta = width / 3;

	// Read camera frames (at approx 24 FPS) and show the result
	while (true) {
		cap >> image;
		panel_middle = image(cv::Rect(delta, 0, image.cols / 3, image.rows));

		
		// Copy the middle panel from the image and convert it to gray
		panel_middle = image(cv::Rect(delta, 0, image.cols / 3, image.rows));
		cv::cvtColor(panel_middle, panel_middle, cv::COLOR_BGR2GRAY);
		cv::cvtColor(panel_middle, panel_middle, cv::COLOR_GRAY2BGR);

		// Copy the modified middle panel back to the source image
		panel_middle.copyTo(image(cv::Rect(delta, 0, image.cols / 3, image.rows)));

		if (image.empty()) {
			std::cout << "Can't read frames from your camera\n";
			break;
		}

		cv::imshow("Camera feed", image);

		// Stop the camera if users presses the "ESC" key
		if (cv::waitKey(1000.0 / FPS) == 27) break;
	}

	return 0;
}
*/