#pragma once

#ifndef APPLICATIONHANDLER_H
#define APPLICATIONHANDLER_H

#include <Windows.h>
#include <stdio.h>


LPSTR GetProgramPath()
{
	LPCSTR Buff[1024];

	DWORD GETCWD = GetCurrentDirectoryA(sizeof(Buff), Buff);

	switch (GETCWD)
	{
	case 0:
		printf("Error Getting CWD.\n Error code: %d\n", GetLastError());
		exit(EXIT_FAILURE);
		break;
	default:
		printf("Getting CWD was successful. Path: %s\n", Buff);
		break;
	}
	return Buff;
}

extern void Execute(int hidden, LPCWSTR Params)
{
	int HidVal;

	LPCSTR ExePath = GetProgramPath();

	LPCWSTR ExecutableFileName = L"MyScreen.exe";

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi, sizeof(pi));

	switch (hidden)
	{
	case 0:
		HidVal = SW_HIDE;
		break;
	default:
		HidVal = SW_SHOW;
	}
	
	HINSTANCE CreateProc = ShellExecute(0, L"open", ExecutableFileName, Params, ExePath, HidVal);
	if (32 < CreateProc)
	{
		printf("Successfully started new proccess of MyScreen.exe\n");
		system("cls");
	}
	else
	{
		printf("Failed to start new proccess of MyScreen.exe.\n Error Code: %d\n", CreateProc);
		system("cls");
		exit(EXIT_FAILURE);
	}

}

#endif