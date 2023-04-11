#include "MODEL.h"

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
				if (_TURN == -1) _A[i][j].c = -1;
				else _A[i][j].c = 1;
				return _A[i][j].c;
			}
		}
	}
	return 0;
}

_POINT randomPoint()
{
	int x = rand() % BOARD_SIZE;
	int y = rand() % BOARD_SIZE;
	return { x, y };
}

void PrintWinner(int whoWin, int color) {
	SetColor(color);
	if (whoWin == -1)
		wcout << X_SYM;
	else
		wcout << O_SYM;
	SetColor(c_def);
}

void HoverWinner(int x, int y, int i, int WhoWin, int color) {
	switch (i)
	{
	case 0: // Hang ngang
		for (int i = 0; i < 5; i++)
			if (_A[x][y + i].c == WhoWin) {
				GotoXY(_A[x][y + i].x, _A[x][y + i].y);
				PrintWinner(WhoWin, color);
			}
		break;
	case 1: // Hang doc
		for (int i = 0; i < 5; i++)
			if (_A[x + i][y].c == WhoWin) {
				GotoXY(_A[x + i][y].x, _A[x + i][y].y);
				PrintWinner(WhoWin, color);
			}
		break;
	case 2: // Duong cheo phai
		for (int i = 0; i < 5; i++)
			if (_A[x + i][y + i].c == WhoWin) {
				GotoXY(_A[x + i][y + i].x, _A[x + i][y + i].y);
				PrintWinner(WhoWin, color);
			}
		break;
	case 3: /// Duong cheo trai
		for (int i = 0; i < 5; i++)
			if (_A[x + i][y - i].c == WhoWin) {
				GotoXY(_A[x + i][y - i].x, _A[x + i][y - i].y);
				PrintWinner(WhoWin, color);
			}
		break;
	}
}

bool CheckWinCondition(int winner) {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (_A[i][j].c == -winner) {
				if (_A[i][j + 1].c == -winner && j + 4 < BOARD_SIZE && j - 1 >= 0) {
					int dem = 0;
					for (int k = 0; k < 4; ++k) dem += _A[i][j + k].c;
					if (dem == -winner * 4 && (_A[i][j + 4].c == 0 || _A[i][j - 1].c == 0)) return 0;
				}
				else if (_A[i + 1][j].c == -winner && i + 4 < BOARD_SIZE && i - 1 >= 0) {
					int dem = 0;
					for (int k = 0; k < 4; ++k) dem += _A[i + k][j].c;
					if (dem == -winner * 4 && (_A[i + 4][j].c == 0 || _A[i - 1][j].c == 0)) return 0;
				}
				else if (_A[i + 1][j + 1].c == -winner && i + 4 < BOARD_SIZE && j + 4 < BOARD_SIZE && i - 1 >= 0 && j - 1 >= 0) {
					int dem = 0;
					for (int k = 0; k < 4; ++k) dem += _A[i + k][j + k].c;
					if (dem == -winner * 4 && (_A[i + 4][j + 4].c == 0 || _A[i - 1][j - 1].c == 0)) return 0;
				}
				else if (_A[i + 1][j - 1].c == -winner && i + 4 < BOARD_SIZE && j - 4 >= 0 && i - 1 >= 0 && j + 1 < BOARD_SIZE) {
					int dem = 0;
					for (int k = 0; k < 4; ++k) dem += _A[i + k][j - k].c;
					if (dem == -winner * 4 && (_A[i + 4][j - 4].c == 0 || _A[i - 1][j + 4].c == 0)) return 0;
				}
			}
		}
	}
	return 1;
} // Kiem tra truong hop ko chan hai dau nhung nguoi choi kia da co 4 o

int CheckWin(int x, int y, int& x_Won, int& y_Won, int& i_Won) {
	int dem[4] = { 0,0,0,0 };
	/*
	0: Hang ngang
	1: Hang doc
	2: Hang cheo phai
	3: Hang cheo trai
	*/
	// Check ngang
	for (int i = 0; y + i < BOARD_SIZE && i < 5; i++) {
		dem[0] += _A[x][y + i].c;
	}
	// Check doc
	for (int i = 0; x + i < BOARD_SIZE && i < 5; i++) {
		dem[1] += _A[x + i][y].c;
	}
	// Check cheo phai
	for (int i = 0; x + i < BOARD_SIZE && y + i < BOARD_SIZE && i < 5; i++) {
		dem[2] += _A[x + i][y + i].c;
	}
	// Check cheo trai
	for (int i = 0; x + i < BOARD_SIZE && y - i >= 0 && i < 5; i++) {
		dem[3] += _A[x + i][y - i].c;
	}
	for (int i = 0; i < 4; i++) {
		if (abs(dem[i]) == 5) {
			x_Won = x; y_Won = y; i_Won = i;
			//HoverWinner(x, y, i, dem[i] / 5, (dem[i] / 5 == -1 ? 228 : 234));
			return dem[i] / 5;
		}

		else if (abs(dem[i]) == 4) {
			switch (i)
			{
			case 0:
				if (y > 0 && y < BOARD_SIZE - 4)
					if (_A[x][y - 1].c == 0 && _A[x][y + 4].c == 0) {
						x_Won = x; y_Won = y; i_Won = i;
						///HoverWinner(x, y, i, dem[i] / 4, (dem[i] / 4 == -1 ? 228 : 234));
						return dem[i] / 2;
					}
				break;
			case 1:
				if (x > 0 && x < BOARD_SIZE - 4)
					if (_A[x - 1][y].c == 0 && _A[x + 4][y].c == 0) {
						x_Won = x; y_Won = y; i_Won = i;
						//HoverWinner(x, y, i, dem[i] / 4, (dem[i] / 4 == -1 ? 228 : 234));
						return dem[i] / 2;
					}
				break;
			case 2:
				if (x - 1 >= 0 && y - 1 >= 0 && x + 4 < BOARD_SIZE && y + 4 < BOARD_SIZE)
					if (_A[x - 1][y - 1].c == 0 && _A[x + 4][y + 4].c == 0) {
						x_Won = x; y_Won = y; i_Won = i;
						//HoverWinner(x, y, i, dem[i] / 4, (dem[i] / 4 == -1 ? 228 : 234));
						return dem[i] / 2;
					}
				break;
			case 3:
				if (x - 1 >= 0 && y + 1 < BOARD_SIZE && x + 4 < BOARD_SIZE && y - 4 >= 0)
					if (_A[x - 1][y + 1].c == 0 && _A[x + 4][y - 4].c == 0) {
						x_Won = x; y_Won = y; i_Won = i;
						//HoverWinner(x, y, i, dem[i] / 4, (dem[i] / 4 == -1 ? 228 : 234));
						return dem[i] / 2;
					}
				break;
			}
		}
	}
	return 0;
}

int TestBoard() {
	int DrawChecker = 0;
	int winner, x_won, y_won, i_won;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].c != 0) {
				winner = CheckWin(i, j, x_won, y_won, i_won);
				if (winner == 1 || winner == -1) {
					HoverWinner(x_won, y_won, i_won, winner, winner == -1 ? 228 : 234);
					return winner;
				}

				else if (winner == 2 || winner == -2) {
					if (CheckWinCondition(winner / 2))
					{
						HoverWinner(x_won, y_won, i_won, winner / 2, winner / 2 == -1 ? 228 : 234);
						return winner / 2;
					}
				}
				else
					++DrawChecker;
			}
		}
	}
	if (DrawChecker == BOARD_SIZE * BOARD_SIZE)
		return 0;
	return 2;
}

void TimeUpdating(high_resolution_clock::time_point& iniTime, int& seconds) {
	high_resolution_clock::time_point finalTime = high_resolution_clock::now();
	duration<double> time_span = finalTime - iniTime;
	if (time_span.count() >= 1) {
		iniTime = finalTime;
		TimeUpdate(seconds);
	}
}

void GetFont() {
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	string filename = "NUMBER_FONT.txt";
	wifstream stream(filename.c_str());
	stream.imbue(utf8_locale);
	wstring line;
	vector<wstring> line1;
	int count = 0;
	while (getline(stream, line)) {
		line1.push_back(line);
		++count;
	}
	for (int i = 0; i < line1[0].size(); i++) {
		if (line1[0][i] != ' ' && line1[0][i] != 12288) {
			for (int j = i; j < line1[0].size(); j++) {
				if (line1[0][j] == ' ' || line1[0][j] == 12288) {
					vector<wstring> v;
					for (int k = 0; k < count; k++) {
						v.push_back(line1[k].substr(i, j - i));
					}
					number_font.push_back(v);
					i = j;
					break;
				}
			}
		}
	}
}