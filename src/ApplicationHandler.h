#pragma once

#ifndef APPLICATIONHANDLER_H
#define APPLICATIONHANDLER_H

#include <Windows.h>
#include <stdio.h>

LPSTR GetProgramPath();

extern void Execute(int hidden, LPCWSTR Params);

#endif