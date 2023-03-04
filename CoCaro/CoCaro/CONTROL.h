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