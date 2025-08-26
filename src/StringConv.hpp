#include <Windows.h>
#include <iostream>
#include <string>

namespace StrConv
{
	std::string charstartostdstring(char* str)
	{
		std::string CompatStr = std::string(str);

		return CompatStr;
	}
	LPCWSTR stdstringtolpcwstr(std::string str)
	{
		std::wstring tempStdString = std::wstring(str.begin(), str.end());

		LPCWSTR CompatString = tempStdString.c_str();

		return CompatString;
	}
	LPCWSTR charstarttolpcwstr(char* str)
	{
		std::string chartostring = charstartostdstring(str);
		LPCWSTR stringtolpcwstr = stdstringtolpcwstr(chartostring);
		return stringtolpcwstr;
	}
}

namespace StrConcat
{
	LPCWSTR concatLPCWSTR(LPCWSTR StringOne, LPCWSTR StringTwo)
	{
		LPCWSTR Result = (std::wstring(StringOne) + std::wstring(StringTwo)).c_str();
		return Result;
	}
}