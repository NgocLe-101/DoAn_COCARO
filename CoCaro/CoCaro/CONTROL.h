#pragma once
#include "CONSTANT_VALUES.h"
#include "MODEL.h"
#include "View.h"

void StartGame() {
	system("cls");
	ResetData();
	DrawBoard(BOARD_SIZE);
	DrawInGameMenu();
	DrawPlayer();
}

bool StartInGameMENU() {
	int pos = 0;
	int NAVIGATE;
	while (true) {
		NAVIGATE = toupper(_getch());
		switch (NAVIGATE)
		{
		case 'W':
			--pos;
			break;
		case 'S':
			++pos;
			break;
		case 17:
			if (pos==0) {/*save */}
			else if (pos == 1) {/*mute */}
			else if (pos == 2) { ExitGame(); return 0; }
		}
		if (pos > 2) pos = 1;
		else if (pos < 0) pos = 2;
	}
}

void MoveRight() {
	if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x) {
		_X += HORIZONTAL_SPACE;
		GotoXY(_X, _Y);
	}
}
void MoveLeft() {
	if (_X > _A[0][0].x) {
		_X -= HORIZONTAL_SPACE;
		GotoXY(_X, _Y);
	}
}
void MoveDown() {
	if (_Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y) {
		_Y += VERTIAL_SPACE;
		GotoXY(_X, _Y);
	}
}
void MoveUp() {
	if (_Y > _A[0][0].y) {
		_Y -= VERTIAL_SPACE;
		GotoXY(_X, _Y);
	}
}