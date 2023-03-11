﻿#pragma once
#include <Windows.h>
#include <iostream>
#include "CONSTANT_VALUES.h"

void FixConsoleWindow();

void ChangeConsole();

void DrawTableLine(int numOfCol, wchar_t mainSym, wchar_t subSym, int width);

void GotoXY(int x, int y);

void DrawBoard(int pSize);

void SetColor(int color);

void PrintText(wstring text, int color, int x, int y);

void EraseBox(int x, int y, int width, int height, int color);

void DrawBigText(string filename, int color, int x, int y);

void DrawBigText(string filename, int color, int x, int y, int timer);

void DrawBorder(int x, int y, int width, int height, wchar_t border_type, int color);

void DrawInGameMenuUSING(int pos);

void DrawInGameMenu();

void DrawPlayer();

int ProcessFinish(int pWhoWin);

int AskContinue(int pWhoWin);

void DrawExit();
