#include "View.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);

	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void ChangeConsole() {
	RECT r;
	HWND consoleWindow = GetConsoleWindow();
	HWND hDesktop = GetDesktopWindow();
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitleA("Co Caro");
	SetConsoleTextAttribute(hConsole, c_def);
	GetWindowRect(hDesktop, &r);
	MoveWindow(consoleWindow, r.right/2-WIDTH/2, r.bottom/2-HEIGHT/2, WIDTH, HEIGHT, true);
}

void DrawTableLine(int numOfCol, wchar_t mainSym, wchar_t subSym, int width)
{
	for (int i = 0; i < numOfCol - 1; i++)
	{
		for (int i = 0; i < width; i++) wcout << mainSym;
		wcout << subSym;
	}
	for (int i = 0; i < width; i++) wcout << mainSym;
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
	wcout << TOP_LEFT;
	DrawTableLine(BOARD_SIZE, HORIZONTAL_LINE, TOP_CROSS, B_WIDTH);
	wcout << TOP_RIGHT;

	for (int i = 0; i < (BOARD_SIZE - 1) * (B_HEIGHT + 1); i++)
	{
		GotoXY(LEFT, TOP + i + 1);
		if ((i + 1) % (B_HEIGHT + 1) != 0)
		{
			wcout << VERTICAL_LINE;
			DrawTableLine(BOARD_SIZE, SPACE, VERTICAL_LINE, B_WIDTH);
			wcout << VERTICAL_LINE;
		}
		else
		{
			wcout << LEFT_CROSS;
			DrawTableLine(BOARD_SIZE, HORIZONTAL_LINE, CROSS, B_WIDTH);
			wcout << RIGHT_CROSS;
		}
	}
	for (int i = 0; i < B_HEIGHT; i++)
	{
		GotoXY(iniX - 2, iniY + (BOARD_SIZE - 1) * (B_HEIGHT + 1) + i);
		wcout << VERTICAL_LINE;
		DrawTableLine(BOARD_SIZE, SPACE, VERTICAL_LINE, B_WIDTH);
		wcout << VERTICAL_LINE;
	}

	GotoXY(iniX - 2, iniY + (BOARD_SIZE - 1) * (B_HEIGHT + 1) + B_HEIGHT);
	wcout << BOTTOM_LEFT;
	DrawTableLine(BOARD_SIZE, HORIZONTAL_LINE, BOTTOM_CROSS, B_WIDTH);
	wcout << BOTTOM_RIGHT;
	GotoXY(_X, _Y);
}

void SetColor(int color) {
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void PrintText(wstring text, int color, int x, int y) {
	GotoXY(x, y);
	SetColor(color);
	wcout << text;
	SetColor(c_def);
}

void EraseBox(int x, int y, int width, int height, int color) {
	SetColor(color);
	for (int i = 0; i < height; i++) {
		GotoXY(x, y + i);
		for (int j = 0; j < width; j++) {
			wcout << L" ";
		}
	}
	SetColor(c_def);
}

void DrawBigText(string filename, int color, int x, int y) {
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	wifstream stream(filename.c_str());
	stream.imbue(utf8_locale);
	vector<wstring> line1;
	wstring line;
	int count = 0;
	while (getline(stream, line)) {
		line1.push_back(line);
		++count;
	};
	for (int i = 0; i < count; i++) {
		PrintText(line1[i], color, x, y + i);
	}
}

void DrawBigText(string filename, int color, int x, int y, int timer) {
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	wifstream stream(filename.c_str());
	stream.imbue(utf8_locale);
	vector<wstring> line1;
	wstring line;
	int count = 0;
	while (getline(stream, line)) {
		line1.push_back(line);
		++count;
	};
	for (int i = 0; i < count; i++) {
		PrintText(line1[i], color, x, y + i);
		Sleep(timer);
	}
}

void DrawBorder(int x, int y, int width, int height, wchar_t border_type, int color) {
	if (border_type == DL_T) {
		GotoXY(x, y);
		SetColor(color);
		wcout << DL_T_TOPLEFTCORNER;
		for (int i = 1; i < width - 1; i++) wcout << DL_T_HORIZONTAL;
		wcout << DL_T_TOPRIGHTCORNER;
		for (int i = 1; i < height - 1; i++) {
			GotoXY(x, y + i);
			wcout << DL_T_VERTICAL;
			GotoXY(x + width - 1, y + i);
			wcout << DL_T_VERTICAL;
		}
		GotoXY(x, y + height - 1);
		wcout << DL_T_BOTLEFTCORNER;
		for (int i = 1; i < width - 1; i++) wcout << DL_T_HORIZONTAL;
		wcout << DL_T_BOTRIGHTCORNER;
	}
	else if (border_type == DM_T) {
		GotoXY(x, y);
		SetColor(color);
		wcout << DM_T_CORNER;
		for (int i = 1; i < width - 1; i++) wcout << DM_T_HORIZONTAL;
		wcout << DM_T_CORNER;
		for (int i = 1; i < height - 1; i++) {
			GotoXY(x, y + i);
			wcout << DM_T_VERTICAL;
			GotoXY(x + width - 1, y + i);
			wcout << DM_T_VERTICAL;
		}
		GotoXY(x, y + height - 1);
		wcout << DM_T_CORNER;
		for (int i = 1; i < width - 1; i++) wcout << DM_T_HORIZONTAL;
		wcout << DM_T_CORNER;
	}
	SetColor(c_def);
}

void DrawInGameMenuUSING(int pos) {
	if (pos >= 0) {
		DrawBigText("SAVE.txt", pos == 0 ? c_def : c_gray, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 6, _A[0][BOARD_SIZE - 1].y + 14);
		DrawBigText("MUTE.txt", pos == 1 ? c_def : c_gray, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 6, _A[0][BOARD_SIZE - 1].y + 14 + IM_SPACE);
		DrawBigText("EXIT.txt", pos == 2 ? c_def : c_gray, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 6, _A[0][BOARD_SIZE - 1].y + 14 + IM_SPACE * 2);
	}
	else {
		DrawBigText("SAVE.txt", c_gray, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 6, _A[0][BOARD_SIZE - 1].y + 14);
		DrawBigText("MUTE.txt", c_gray, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 6, _A[0][BOARD_SIZE - 1].y + 14 + IM_SPACE);
		DrawBigText("EXIT.txt", c_gray, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 6, _A[0][BOARD_SIZE - 1].y + 14 + IM_SPACE * 2);
	}
}


void DrawInGameMenu() {
	DrawBigText("IG_TITLE.txt", c_red, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 2, _A[0][BOARD_SIZE - 1].y + 1);
	DrawInGameMenuUSING(-1);
	DrawBorder(_A[0][BOARD_SIZE - 1].x + B_WIDTH * 3 + 2, _A[0][BOARD_SIZE - 1].y + 10, 36, 20, DM_T, c_green);
	GotoXY(_X, _Y);
}

void DrawPlayer() {
	DrawBigText("O_PLAYER.txt", c_lime, LEFT, 0);
	int tempTime = 16;
	TimeUpdate(tempTime);
	DrawBigText("X_PLAYER.txt", c_red, LEFT + B_WIDTH * (BOARD_SIZE + 1) + 5, 0);
	GotoXY(_X, _Y);
}

int ProcessFinish(int pWhoWin) {
	//GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2);
	switch (pWhoWin)
	{
	case -1:
		DrawBigText("X_WIN.txt", 228, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].x - 20, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].y - 20, 80);
		break;
	case 1:
		DrawBigText("O_WIN.txt", 174, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].x - 20, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].y - 20, 80);
		break;
	case 0:
		DrawBigText("DRAW.txt", 158, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].x - 20, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].y - 20, 80);
		break;
	case 2:
		_TURN = -_TURN;
	}
	GotoXY(_X, _Y);
	return pWhoWin;
}

int AskContinue(int pWhoWin) {
	Sleep(400);
	int pos = 0;
	int NAVIGATOR = 0;
	bool change = true;
	do {
		if (change) {
			switch (pos)
			{
			case 0:
				DrawBigText("AGAIN.txt", pWhoWin == -1 ? c_red : (pWhoWin == 1 ? c_lime : c_dblue), _A[BOARD_SIZE / 2][BOARD_SIZE / 2].x - 7, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].y - 5);
				DrawBigText("RETURN_MENU.txt", c_gray, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].x - 4, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].y + 2);
				break;
			case 1:
				DrawBigText("AGAIN.txt", c_gray, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].x - 7, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].y - 5);
				DrawBigText("RETURN_MENU.txt", pWhoWin == -1 ? c_red : (pWhoWin == 1 ? c_lime : c_dblue), _A[BOARD_SIZE / 2][BOARD_SIZE / 2].x - 4, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].y + 2);
			}
			change = false;
		}
		NAVIGATOR = 0;
		if ((GetAsyncKeyState(0x57/*W Keys*/) & (1 << 15)) != 0)
			NAVIGATOR = 'W';
		else if ((GetAsyncKeyState(0x53/*S Keys*/) & (1 << 15)) != 0)
			NAVIGATOR = 'S';
		else if ((GetAsyncKeyState(VK_RETURN) & (1 << 15)) != 0)
			NAVIGATOR = 13;
		if (NAVIGATOR == 'W') { --pos; change = true; while ((GetAsyncKeyState(0x57/*W Keys*/) & (1 << 15)) != 0); }
		else if (NAVIGATOR == 'S') { ++pos; change = true; while ((GetAsyncKeyState(0x53/*S Keys*/) & (1 << 15)) != 0); }
		if (pos > 1) pos = 0;
		else if (pos < 0) pos = 1;
	} while (NAVIGATOR != 13);
	while ((GetAsyncKeyState(VK_RETURN) & (1 << 15)) != 0);
	if (pos == 0) return 'Y';
	return 'N';
	/*return toupper(_getch());*/
}

void DrawExit() {
	DrawBigText("EXITGAME_SCREEN.txt", 225, 0, 0, 50);
}

void ShowHelp()
{
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	string filename = "HELP.txt";
	int x = 0;
	int y = 0;
	wstring line;
	int i = 0;
	wifstream helpFile(filename.c_str());
	helpFile.imbue(utf8_locale);
	/*std::fstream helpFile;
	helpFile.open("Help.txt", std::fstream::in);*/

	system("cls");
	while (getline(helpFile, line))
	{
		PrintText(line, 243, x, y + i);
		i++;
	}
}

void DrawMenuBackGround()
{
	
}

_MENU MainMenu()
{
	_MENU menu;

	menu.options = 6;
	menu.x = X_CENTER - 13;
	menu.y = Y_CENTER + 5;
	menu.cursorColor = 244;

	system("cls");
	DrawBigText("CARO.txt", 252, X_CENTER - 35, 1);
	PrintText(L"***************************", 244, menu.x, menu.y - 3);
	PrintText(L"*Chào mừng các bạn đến với game caro*", 244, menu.x - 5, menu.y - 2);
	PrintText(L"***************************", 244, menu.x, menu.y - 1);
	PrintText(L"         Chơi với người        ", 244, menu.x, menu.y);
	PrintText(L"         Chơi với máy          ", 244, menu.x, menu.y + 1);
	PrintText(L"         Lưu game         ", 244, menu.x, menu.y + 2);
	PrintText(L"         Bảng xếp hạng          ", 244, menu.x, menu.y + 3);
	PrintText(L"         Trợ giúp            ", 244, menu.x, menu.y + 4);
	PrintText(L"         Thoát game         ", 244, menu.x, menu.y + 5);


	return menu;
}

void PrintNumber(int number, int x, int y, int color) {
	GotoXY(x, y);
	if (number >= 10) {
		vector<int> v;
		while (number > 0) {
			v.push_back(number % 10);
			number /= 10;
		}
		for (int j = v.size() - 1; j >= 0; j--) {
			for (int k = 0; k < number_font[v[j]].size(); k++) {
				PrintText(number_font[v[j]][k], color, x + (v.size() - j - 1) * number_font[v[(j == v.size() - 1 ? j : j + 1)]].size() + (v.size() - j - 1) * 1, y + k);
			}
		}
	}
	else {
		int num = number % 10;
		for (int i = 0; i < number_font[0].size(); i++)
			PrintText(number_font[0][i], color, x, y + i);
		for (int i = 0; i < number_font[num].size(); i++)
			PrintText(number_font[num][i], color, x + number_font[0].size() + 2, y + i);
	}
}

void TimeUpdate(int& seconds) {
	--seconds;
	if (seconds < 0) return;
	EraseBox(LEFT + B_WIDTH * (BOARD_SIZE / 2), 1, 20, 3, c_def);
	PrintNumber(0, LEFT + B_WIDTH * (BOARD_SIZE / 2), 1, seconds < 10 ? c_red : c_def);
	EraseBox(LEFT + B_WIDTH * (BOARD_SIZE / 2) + number_font[0][0].size(), 1, number_font[0][0].size() + 1, number_font[0].size(), seconds < 10 ? c_red : c_def);
	DrawBigText("DOUBLE_DOT.txt", (seconds < 10 ? c_red : c_def), LEFT + B_WIDTH * (BOARD_SIZE / 2) + number_font[0][0].size() + 1, 1);
	PrintNumber(seconds, LEFT + B_WIDTH * (BOARD_SIZE / 2) + 7, 1, seconds < 10 ? c_red : c_def);
	GotoXY(_X, _Y);
}