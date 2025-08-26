#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <Windows.h>
#include <iostream>
#include <string>

namespace ScreenCap
{
	class HWNDToMat
	{
	public:
		HWNDToMat();
		virtual ~HWNDToMat();
		virtual void GetScreen();

		cv::Mat src;
	private:
		HWND hwnd = GetDesktopWindow();
		HDC WindowDC, WindowCompatDC;
		HBITMAP HBWindow;
		BITMAPINFOHEADER bitmapInfo;
		RECT WindowSize;
		int Width, Height, ScreenWidth, ScreenHeight;
	};

	HWNDToMat::HWNDToMat()
	{
		WindowDC = GetDC(hwnd);
		WindowCompatDC = CreateCompatibleDC(WindowDC);
		SetStretchBltMode(WindowCompatDC, COLORONCOLOR);
		GetClientRect(hwnd, &WindowSize);

		Width = WindowSize.right;
		Height = WindowSize.bottom;
		ScreenWidth = WindowSize.right;
		ScreenHeight = WindowSize.bottom;

		src.create(Height, Width, CV_8UC4);

		HBWindow = CreateCompatibleBitmap(WindowDC, Width, Height);
		bitmapInfo.biSize = sizeof(BITMAPINFOHEADER);
		bitmapInfo.biWidth = Width;
		bitmapInfo.biHeight = -Height;
		bitmapInfo.biPlanes = 1;
		bitmapInfo.biBitCount = 32;
		bitmapInfo.biCompression = BI_RGB;
		bitmapInfo.biSizeImage = 0;
		bitmapInfo.biXPelsPerMeter = 0;
		bitmapInfo.biYPelsPerMeter = 0;
		bitmapInfo.biClrUsed = 0;
		bitmapInfo.biClrImportant = 0;

		SelectObject(WindowCompatDC, HBWindow);
	}

	void HWNDToMat::GetScreen()
	{
		StretchBlt(WindowCompatDC, 0, 0, Width, Height, WindowDC, 0, 0, ScreenWidth, ScreenHeight, SRCCOPY);
		GetDIBits(WindowCompatDC, HBWindow, 0, Height, src.data, (BITMAPINFO*)&bitmapInfo, DIB_RGB_COLORS);
	}

	HWNDToMat::~HWNDToMat()
	{
		DeleteObject(HBWindow);
		DeleteDC(WindowCompatDC);
		ReleaseDC(hwnd, WindowDC);
	}

	class ScreenCapture
	{
	public:
		void ScreenCaptureWriteImg(std::string filename);
		void ScreenCaptureWriteVid(std::string filename);
	private:
		cv::Mat Frame;
		double fps = 20;
	};

	void ScreenCapture::ScreenCaptureWriteImg(std::string filename)
	{
		HWNDToMat Screen;
		Screen.GetScreen();
		cv::cvtColor(Screen.src, Frame, cv::COLOR_BGRA2BGR);
		cv::imwrite(filename, Frame);
	}

	void ScreenCapture::ScreenCaptureWriteVid(std::string filename)
	{
		HWNDToMat Screen;

		cv::VideoWriter writer(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, Screen.src.size(), true);

		if (!writer.isOpened())
		{
			std::cerr << "Failed to start writer" << std::endl;
			exit(1);
		}

		while (GetAsyncKeyState(VK_PAUSE) == NULL)
		{
			cv::namedWindow("Press PAUSE to quit", cv::WINDOW_NORMAL);
			Screen.GetScreen();
			cv::cvtColor(Screen.src, Frame, cv::COLOR_BGRA2BGR);
			writer.write(Frame);
			cv::imshow("Press PAUSE to quit", Frame);
			cv::waitKey(1);
		}
		cv::destroyAllWindows();

		writer.release();
	}
}