#pragma once
#include "CONSTANT_VALUES.h"
#include "View.h"

void ResetData();

void GabageCollect();

void ExitGame();

int CheckBoard(int pX, int pY);

void PrintWinner(int whoWin, int color);

void HoverWinner(int x, int y, int i, int WhoWin, int color);

bool CheckWinCondition(int winner);

int CheckWin(int x, int y, int& x_Won, int& y_Won, int& i_Won);

int TestBoard();