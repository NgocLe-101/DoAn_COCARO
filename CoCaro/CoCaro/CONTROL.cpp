#include "CONTROL.h"

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
		DrawInGameMenuUSING(pos);
		NAVIGATE = toupper(_getch());
		switch (NAVIGATE)
		{
		case 'W':
			--pos;
			break;
		case 'S':
			++pos;
			break;
		case 13:
			if (pos == 0) {/*save */ }
			else if (pos == 1) {/*mute */ }
			else if (pos == 2) { ExitGame(); return 0; }
			break;
		case 27:
			DrawInGameMenuUSING(-1);
			GotoXY(_X, _Y);
			return 1;
		}
		if (pos > 2) pos = 0;
		else if (pos < 0) pos = 2;
	}
	return 1;
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