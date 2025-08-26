#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>


namespace WebCamCap
{
	class WebCam
	{
	public:
		cv::VideoCapture WebCamInit();
		cv::Mat GetCamData(cv::VideoCapture WebCamObj);
		void ShowWebCamData();
		void ShowWebCamDataLive(cv::VideoCapture WebCamObj);
		void WriteWebCamPicture(std::string filename);
		void WriteWebCamVideo(std::string filename, cv::VideoCapture WebCamObj);
		void IterWriteImg(std::vector <std::string> files);
		void WebCamShutdown(cv::VideoCapture WebCamObj);
		void WebCamWriterShutdown(cv::VideoWriter WebCamWriterObj);
	private:
		cv::VideoWriter writer;
		cv::Mat Frame;
		double fps = 10.0;
	};

	cv::VideoCapture WebCam::WebCamInit()
	{
		cv::VideoCapture WebCamObj(0);

		if (!WebCamObj.isOpened())
		{
			std::cerr << "Webcam is inaccesable" << std::endl;
			exit(1);
		}

		return WebCamObj;
	}

	cv::Mat WebCam::GetCamData(cv::VideoCapture WebCamObj)
	{
		WebCamObj >> Frame;

		if (Frame.empty())
		{
			std::cerr << "Failed to Capture Sufficent Frames from Webcam" << std::endl;
			exit(1);
		}

		return Frame;
	}
	void WebCam::ShowWebCamData()
	{
		cv::namedWindow("Press ESC to quit", cv::WINDOW_NORMAL);
		cv::imshow("Press ESC to quit", Frame);
		if (cv::waitKey(0) == 27)
		{
			cv::destroyAllWindows();
		}
		else
		{
			std::cout << "Press ESC to quit" << std::endl;
		}
	}
	void WebCam::ShowWebCamDataLive(cv::VideoCapture WebCamObj)
	{
		cv::namedWindow("Press ESC to quit", cv::WINDOW_NORMAL);
		
		while (GetAsyncKeyState(VK_ESCAPE) == NULL && cv::waitKey(1) != 27)
		{
			WebCamObj >> Frame;
			cv::imshow("Press ESC to quit", Frame);
		}
		cv::destroyAllWindows();
	}
	void WebCam::WebCamShutdown(cv::VideoCapture WebCamObj)
	{
		WebCamObj.release();
	}
	void WebCam::WebCamWriterShutdown(cv::VideoWriter WebCamWriterObj)
	{
		WebCamWriterObj.release();
	}
	void WebCam::WriteWebCamPicture(std::string filename)
	{
		cv::imwrite(filename, Frame);
	}
	void WebCam::WriteWebCamVideo(std::string filename, cv::VideoCapture WebCamObj)
	{
		int frameWidth = WebCamObj.get(cv::CAP_PROP_FRAME_WIDTH);
		int frameHeight = WebCamObj.get(cv::CAP_PROP_FRAME_HEIGHT);

		cv::VideoWriter writer(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(frameWidth, frameHeight));

		while (GetAsyncKeyState(VK_ESCAPE) == NULL)
		{
			cv::Mat CamData = GetCamData(WebCamObj);
			if (CamData.empty())
			{
				break;
			}
			writer.write(CamData);
			cv::imshow("Press ESC to quit", CamData);
			unsigned char key = cv::waitKey(1);
			if (key == 27)
			{
				break;
			}
		}
		WebCamShutdown(WebCamObj);
		WebCamWriterShutdown(writer);
		
		cv::destroyAllWindows();
	}
	void WebCam::IterWriteImg(std::vector <std::string> files)
	{
		for (int i = 0; i < files.size(); i++)
		{
			WebCam::WriteWebCamPicture(files[i]);
		}
	}
}