#pragma once
#include "CONSTANT_VALUES.h"

void ResetData() {
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_A[i][j].x = HORIZONTAL_SPACE * j + LEFT + 2; // Trùng với hoành độ màn hình bàn cờ
			_A[i][j].y = VERTIAL_SPACE * i + TOP + 1; // Trùng với tung độ màn hình bàn cờ
			_A[i][j].c = 0; // 0 nghĩa là chưa ai đánh dấu, nếu đánh dấu phải theo quy 
							//định như sau: -1 là lượt X đánh, 1 là lượt O đánh

		}
	}
	_TURN = -1;
	_COMMAND = -1;
	_X = _A[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1].x; _Y = _A[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1].y;
}

void GabageCollect() {
	// Cleaning resources if needed
}

void ExitGame() {
	system("cls");
	GabageCollect();
}

int CheckBoard(int pX, int pY) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0) {
				if (_TURN==-1) _A[i][j].c = -1;
				else _A[i][j].c = 1;
				return _A[i][j].c;
			}
		}
	}
	return 0;
}

int CheckWin(int x, int y) {
	int dem[4] = { 0,0,0,0 };
	/*
	0: Hang ngang
	1: Hang doc
	2: Hang cheo phai
	3: Hang cheo trai
	*/
	// Check ngang
	for (int i = 0; x + i < BOARD_SIZE && i < 5; i++) {
		dem[0] += _A[x][y + i].c;
		if (abs(dem[0]) == 5)
			break;
	}
	// Check doc
	for (int i = 0; x + i < BOARD_SIZE && i < 5; i++) {
		dem[1] += _A[x+i][y].c;
		if (abs(dem[1]) == 5)
			break;
	}
	// Check cheo phai
	for (int i = 0; x + i < BOARD_SIZE&&y+i<BOARD_SIZE&&i<5; i++) {
		dem[2] += _A[x+i][y + i].c;
		if (abs(dem[2]) == 5)
			break;
	}
	// Check cheo trai
	for (int i = 0; x + i < BOARD_SIZE && y - i >= 0 && i < 5; i++) {
		dem[3] += _A[x+i][y - i].c;
		if (abs(dem[3]) == 5)
			break;
	}
	for (int i = 0; i < 4; i++) {
		if (abs(dem[i]) == 5)
			return dem[i] / 5;
		else if (abs(dem[i]) == 4) {
			switch (i)
			{
			case 0:
				if (y > 0 && y < BOARD_SIZE - 4)
					if (_A[x][y - 1].c == 0 && _A[x][y + 4].c == 0) {
							return dem[i] / 4;
					}
				break;
			case 1:
				if (x > 0 && x < BOARD_SIZE - 4)
					if (_A[x - 1][y].c == 0 && _A[x + 4][y].c == 0) {
							return dem[i] / 4;
					}
				break;
			case 2:
				if (x-1 >= 0 && y - 1 >= 0 && x+4<BOARD_SIZE && y+4<BOARD_SIZE)
					if (_A[x - 1][y - 1].c == 0 && _A[x + 4][y + 4].c == 0) {
							return dem[i] / 4;
					}
				break;
			case 3:
				if (x-1 >= 0 && y+1 < BOARD_SIZE&&x+4<BOARD_SIZE&&y-4>=0)
					if (_A[x - 1][y + 1].c == 0 && _A[x + 4][y - 4].c == 0) {
							return dem[i] / 4;
					}
				break;
			}
		}
	}
	return 0;
}

int TestBoard() {
	int DrawChecker = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].c != 0)
				if (abs(CheckWin(i, j)))
					return CheckWin(i, j);
				else
					DrawChecker++;
		}
	}
	if (DrawChecker == BOARD_SIZE * BOARD_SIZE)
		return 0;
	return 2;
}