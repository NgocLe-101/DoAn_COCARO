#include "View.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	RECT r;
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
	SetConsoleTitleA("Co Caro");
	SetConsoleTextAttribute(hConsole, 240);
	GetWindowRect(consoleWindow, &r);
	MoveWindow(consoleWindow, 0, 0, WIDTH, HEIGHT, true);
}

void DrawTableLine(int numOfCol, char mainSym, char subSym, int width)
{
	for (int i = 0; i < numOfCol - 1; i++)
	{
		for (int i = 0; i < width; i++) printf("%c", mainSym);
		printf("%c", subSym);
	}
	for (int i = 0; i < width; i++) printf("%c", mainSym);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawBoard(int pSize) {
	int iniX = _A[0][0].x, iniY = _A[0][0].y;
	GotoXY(iniX - 2, iniY - 1);
	printf("%c", TOP_LEFT);
	DrawTableLine(BOARD_SIZE, HORIZONTAL_LINE, TOP_CROSS, B_WIDTH);
	printf("%c", TOP_RIGHT);

	for (int i = 0; i < (BOARD_SIZE - 1) * (B_HEIGHT + 1); i++)
	{
		GotoXY(LEFT, TOP + i + 1);
		if ((i + 1) % (B_HEIGHT + 1) != 0)
		{
			printf("%c", VERTICAL_LINE);
			DrawTableLine(BOARD_SIZE, SPACE, VERTICAL_LINE, B_WIDTH);
			printf("%c", VERTICAL_LINE);
		}
		else
		{
			printf("%c", LEFT_CROSS);
			DrawTableLine(BOARD_SIZE, HORIZONTAL_LINE, CROSS, B_WIDTH);
			printf("%c", RIGHT_CROSS);
		}
	}
	for (int i = 0; i < B_HEIGHT; i++)
	{
		GotoXY(iniX - 2, iniY + (BOARD_SIZE - 1) * (B_HEIGHT + 1) + i);
		printf("%c", VERTICAL_LINE);
		DrawTableLine(BOARD_SIZE, SPACE, VERTICAL_LINE, B_WIDTH);
		printf("%c", VERTICAL_LINE);
	}

	GotoXY(iniX - 2, iniY + (BOARD_SIZE - 1) * (B_HEIGHT + 1) + B_HEIGHT);
	printf("%c", BOTTOM_LEFT);
	DrawTableLine(BOARD_SIZE, HORIZONTAL_LINE, BOTTOM_CROSS, B_WIDTH);
	printf("%c", BOTTOM_RIGHT);
	GotoXY(_X, _Y);
}

int ProcessFinish(int pWhoWin) {
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2);
	switch (pWhoWin)
	{
	case -1:
		printf("Nguoi choi X da thang");
		break;
	case 1:
		printf("Nguoi choi O da thang");
		break;
	case 0:
		printf("HOA");
		break;
	case 2:
		_TURN = -_TURN;
	}
	GotoXY(_X, _Y);
	return pWhoWin;
}

int AskContinue() {
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 4);
	printf("Nhan 'y/n' de tiep tuc/dung: ");
	return toupper(_getch());
}

void SetColor(int color) {
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void PrintText(string text, int color, int x, int y) {
	GotoXY(x, y);
	SetColor(color);
	cout << text;
	SetColor(240);
}

void ShowWinner(int pWhowin) {
	if (pWhowin == -1) {
		int midScrX = HEIGHT / 2, midScrY = WIDTH / 2;
		PrintText("XXXXXXX       XXXXXXX               WWWWWWWW                           WWWWWWWWIIIIIIIIIINNNNNNNN        NNNNNNNN", 11, midScrX, midScrY);
		PrintText("X:::::X       X:::::X               W::::::W                           W::::::WI::::::::IN:::::::N       N::::::N", 11, midScrX, midScrY);
		PrintText("X:::::X       X:::::X               W::::::W                           W::::::WI::::::::IN::::::::N      N::::::N", 11, midScrX, midScrY);
		PrintText("X::::::X     X::::::X               W::::::W                           W::::::WII::::::IIN:::::::::N     N::::::N", 11, midScrX, midScrY);
		PrintText("XXX:::::X   X:::::XXX                W:::::W           WWWWW           W:::::W   I::::I  N::::::::::N    N::::::N", 11, midScrX, midScrY);
		PrintText("   X:::::X X:::::X                    W:::::W         W:::::W         W:::::W    I::::I  N:::::::::::N   N::::::N", 11, midScrX, midScrY);
		PrintText("    X:::::X:::::X                      W:::::W       W:::::::W       W:::::W     I::::I  N:::::::N::::N  N::::::N", 11, midScrX, midScrY);
		PrintText("     X:::::::::X                        W:::::W     W:::::::::W     W:::::W      I::::I  N::::::N N::::N N::::::N", 11, midScrX, midScrY);
		PrintText("     X:::::::::X                         W:::::W   W:::::W:::::W   W:::::W       I::::I  N::::::N  N::::N:::::::N", 11, midScrX, midScrY);
		PrintText("    X:::::X:::::X                         W:::::W W:::::W W:::::W W:::::W        I::::I  N::::::N   N:::::::::::N", 11, midScrX, midScrY);
		PrintText("   X:::::X X:::::X                         W:::::W:::::W   W:::::W:::::W         I::::I  N::::::N    N::::::::::N", 11, midScrX, midScrY);
		PrintText("XXX:::::X   X:::::XXX                       W:::::::::W     W:::::::::W          I::::I  N::::::N     N:::::::::N", 11, midScrX, midScrY);
		PrintText("X::::::X     X::::::X                        W:::::::W       W:::::::W         II::::::IIN::::::N      N::::::::N", 11, midScrX, midScrY);
		PrintText("X:::::X       X:::::X                         W:::::W         W:::::W          I::::::::IN::::::N       N:::::::N", 11, midScrX, midScrY);
		PrintText("X:::::X       X:::::X                          W:::W           W:::W           I::::::::IN::::::N        N::::::N", 11, midScrX, midScrY);
		PrintText("XXXXXXX       XXXXXXX                           WWW             WWW            IIIIIIIIIINNNNNNNN         NNNNNNN", 11, midScrX, midScrY);
	}
}