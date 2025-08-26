#include "WebCamCapture.hpp"
#include "ScreenCapture.hpp"
#include "StringConv.hpp"

extern "C"
{
#include "ApplicationHandler.h"
}


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Too little args" << std::endl;
		return EXIT_FAILURE;
	}
	else
	{
		std::cout << "Good args" << std::endl;
	}
	if (strcmp(argv[2], "-web") == 0)
	{
		WebCamCap::WebCam CamObj;
		cv::VideoCapture CamVidObj = CamObj.WebCamInit();
		CamObj.GetCamData(CamVidObj);
		std::string filenameStrFormat = StrConv::charstartostdstring(argv[1]);
		if (strcmp(argv[3], "-scr") == 0)
		{
			LPCWSTR FileStr = StrConv::charstarttolpcwstr(argv[1]);
			LPCWSTR ThirdStr = StrConv::charstarttolpcwstr(argv[3]);
			LPCWSTR ParamsOne = StrConcat::concatLPCWSTR(FileStr, L" ");
			LPCWSTR ParamsTwo = StrConcat::concatLPCWSTR(ParamsOne, ThirdStr);
			Execute(0, ParamsTwo);
			if (strcmp(argv[4], "-pic") == 0)
			{
				CamObj.WriteWebCamPicture(filenameStrFormat);
				CamObj.WebCamShutdown(CamVidObj);
			}
			else
			{
				CamObj.WriteWebCamVideo(filenameStrFormat, CamVidObj);
			}
		}
		else
		{
			if (strcmp(argv[3], "-pic") == 0)
			{
				CamObj.WriteWebCamPicture(filenameStrFormat);
				CamObj.WebCamShutdown(CamVidObj);
			}
			else
			{
				CamObj.WriteWebCamVideo(filenameStrFormat, CamVidObj);
			}
		}
	}
	else if (strcmp(argv[2],"-scr") == 0)
	{
		ScreenCap::ScreenCapture ScrObj;
		std::string filenameStrFormat = StrConv::charstartostdstring(argv[1]);

		if (strcmp(argv[3], "-web") == 0)
		{
			LPCWSTR FileStr = StrConv::charstarttolpcwstr(argv[1]);
			LPCWSTR ThirdStr = StrConv::charstarttolpcwstr(argv[3]);
			LPCWSTR ParamsOne = StrConcat::concatLPCWSTR(FileStr, L" ");
			LPCWSTR ParamsTwo = StrConcat::concatLPCWSTR(ParamsOne, ThirdStr);
			Execute(0, ParamsTwo);
			if (strcmp(argv[4], "-pic") == 0)
			{
				ScrObj.ScreenCaptureWriteImg(filenameStrFormat);
			}
			else
			{
				ScrObj.ScreenCaptureWriteVid(filenameStrFormat);
			}
		}
		else
		{
			if (strcmp(argv[3], "-pic") == 0)
			{
				ScrObj.ScreenCaptureWriteImg(filenameStrFormat);
			}
			else
			{
				ScrObj.ScreenCaptureWriteVid(filenameStrFormat);
			}
		}
	}
	else
	{
		std::cerr << "Failed invalid. Insufficent arguments." << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}