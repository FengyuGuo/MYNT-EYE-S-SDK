// mynteyes_demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <opencv2/highgui/highgui.hpp>

#include <mynteye/api/api.h>

int main(int argc, char *argv[])
{
	using namespace mynteye;

	auto &&api = API::Create(argc, argv);
	if (!api)
		return 1;

	api->Start(Source::VIDEO_STREAMING);

	cv::namedWindow("frame");

	while (true) {
		api->WaitForStreams();

		auto &&left_data = api->GetStreamData(Stream::LEFT);
		auto &&right_data = api->GetStreamData(Stream::RIGHT);

		cv::Mat img;
		cv::hconcat(left_data.frame, right_data.frame, img);
		cv::imshow("frame", img);

		char key = static_cast<char>(cv::waitKey(1));
		if (key == 27 || key == 'q' || key == 'Q') {  // ESC/Q
			break;
		}
	}

	api->Stop(Source::VIDEO_STREAMING);
	return 0;
}
