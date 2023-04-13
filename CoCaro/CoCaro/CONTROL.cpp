#include "CONTROL.h"

void StartGame() {
	system("cls");
	ResetData();
	GetFont();
	DrawBoard(BOARD_SIZE);
	DrawInGameMenu();
	DrawPlayer();
}

bool StartInGameMENU() {
	Sleep(100);
	int pos = 0;
	int NAVIGATE = 0;
	bool change = true;
	while (true) {
		if (change) {
			DrawInGameMenuUSING(pos);
			change = false;
		}
		NAVIGATE = 0;
		if ((GetAsyncKeyState(0x57/*W Keys*/) & (1 << 15)) != 0)
			NAVIGATE = 'W';
		else if ((GetAsyncKeyState(0x53/*S Keys*/) & (1 << 15)) != 0)
			NAVIGATE = 'S';
		else if ((GetAsyncKeyState(VK_RETURN) & (1 << 15)) != 0)
			NAVIGATE = 13;
		else if ((GetAsyncKeyState(VK_ESCAPE) & (1 << 15)) != 0)
			NAVIGATE = 27;
		// NAVIGATE = toupper(_getch());
		switch (NAVIGATE)
		{
		case 'W':
			--pos;
			change = true;
			while ((GetAsyncKeyState(0x57/*W Keys*/) & (1 << 15)) != 0);
			break;
		case 'S':
			++pos;
			change = true;
			while ((GetAsyncKeyState(0x53/*S Keys*/) & (1 << 15)) != 0);
			break;
		case 13:
			if (pos == 0) {/*save */ }
			else if (pos == 1) {/*mute */ }
			else if (pos == 2) { ExitGame(); return 0; }
			change = true;
			while ((GetAsyncKeyState(VK_RETURN) & (1 << 15)) != 0);
			break;
		case 27:
			change = true;
			while ((GetAsyncKeyState(VK_ESCAPE) & (1 << 15)) != 0);
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

int SelectMenu(_MENU menu)
{
	int cursor = 1;
	char key = 0;

	PrintText(L"--->", menu.cursorColor, menu.x - 4, menu.y);

	do
	{
		key = 0;
		if ((GetAsyncKeyState(VK_RETURN) & (1 << 15)) != 0)
			key = 13;
		else if ((GetAsyncKeyState(VK_UP) & (1 << 15)) != 0)
			key = ARROW_UP;
		else if ((GetAsyncKeyState(VK_DOWN) & (1 << 15)) != 0)
			key = ARROW_DOWN;
		else if ((GetAsyncKeyState(VK_ESCAPE) & (1 << 15)) != 0)
			key = 27;
		if (key == ARROW_UP && cursor > 1)
		{
			PrintText(L"    ", menu.cursorColor, menu.x - 4, menu.y + cursor - 1);
			cursor--;
			PrintText(L"--->", menu.cursorColor, menu.x - 4, menu.y + cursor - 1);
			while ((GetAsyncKeyState(VK_UP) & (1 << 15)) != 0);
		}
		else if (key == ARROW_DOWN && cursor < menu.options)
		{
			PrintText(L"    ", menu.cursorColor, menu.x - 4, menu.y + cursor - 1);
			cursor++;
			PrintText(L"--->", menu.cursorColor, menu.x - 4, menu.y + cursor - 1);
			while ((GetAsyncKeyState(VK_DOWN) & (1 << 15)) != 0);
		}
		else if (key == ESC)
		{
			return -1;
		}

		
	} while (key != ENTER);
	return cursor;
}

void RunMainMenu(bool& run, int option)
	{
		int loadOption;
		switch (option)
		{
		case 1:
			/*SetPlayer(_PLAYER1, _PLAYER2);
			StartGame(_A, _PLAYER1, _PLAYER2, _TURN, _COMMAND, _X, _Y);
			RunGame(_A, _PLAYER1, _PLAYER2, _TURN, _COMMAND, _X, _Y);*/
			run = false;
			break;

		case 2:
			// PLAYER VS COMPUTER
			run = false;
			break;
		case 3:
			/*system("cls");
			loadOption = SelectMenu(LoadingMenu());
			if (loadOption == -1) break;
			else
			{
				LoadGame(RunLoadingMenu(loadOption), _A, _PLAYER1, _PLAYER2, _TURN, _COMMAND, _X, _Y);
				RunGame(_A, _PLAYER1, _PLAYER2, _TURN, _COMMAND, _X, _Y);
				break;
			}*/
		case 4:
			/*do
			{
				ShowRank();
			} while (_getch() != ESC);
			break;*/
		case 5:
			ShowHelp();
			while ((GetAsyncKeyState(VK_ESCAPE) & (1 << 15)) == 0);
			break;
		case 6:case -1:
			ExitGame();
			DrawExit();
			Sleep(100);
			run = false;
			break;
		}
	}

