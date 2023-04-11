#include "View.h"
#include "CONSTANT_VALUES.h"
#include "CONTROL.h"
#include "MODEL.h"


_POINT _A[BOARD_SIZE][BOARD_SIZE]; //Ma trận bàn cờ
int _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
int _COMMAND; // Biến nhận giá trị phím người dùng nhập
int _X, _Y; //Tọa độ hiện hành trên màn hình bàn cờ
vector<vector<wstring>> number_font; // Vector chứa font số

int main()
{
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
	FixConsoleWindow();
	ChangeConsole();

	int seconds;
	bool validEnter;
	bool inGame = false;
	bool TimeSwitch = false;
	while (true)
	{
		bool inMenu = true;
		int option = -2;
		do
		{
			option = SelectMenu(MainMenu());
			RunMainMenu(inMenu, option);
		} while (inMenu);
		inGame = true;
		if (option == 6||option==-1)
			return 0;
		DrawLoadingScreen();
		StartGame();
		seconds = TIME;
		inGame = true;
		TimeSwitch = false;
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		while (inGame)
		{
			TimeSwitch = false;
			_COMMAND = 0;
			if ((GetAsyncKeyState(VK_RETURN) & (1 << 15)) != 0)
				_COMMAND = 13;
			else if ((GetAsyncKeyState(0x57/*W Keys*/) & (1 << 15)) != 0)
				_COMMAND = 'W';
			else if ((GetAsyncKeyState(0x41/*A Keys*/) & (1 << 15)) != 0)
				_COMMAND = 'A';
			else if ((GetAsyncKeyState(0x44/*D Keys*/) & (1 << 15)) != 0)
				_COMMAND = 'D';
			else if ((GetAsyncKeyState(0x53/*S Keys*/) & (1 << 15)) != 0)
				_COMMAND = 'S';
			else if ((GetAsyncKeyState(VK_ESCAPE) & (1 << 15)) != 0)
				_COMMAND = 27;
			if (option == 2 && _TURN == 1) {
				_POINT ranPoint = randomPoint();
				while (ranPoint.c != 0)
				{
					ranPoint = randomPoint();
					if (ranPoint.c == 0)
						break;
				}
				int x_p = ranPoint.x;
				int y_p = ranPoint.y;
				_X = _A[x_p][y_p].x;
				_Y = _A[x_p][y_p].y;
				GotoXY(_X, _Y);
				_COMMAND = 13;
			}
			//_COMMAND = toupper(_getch());
			if (seconds <= 0) _COMMAND = -1;
			if (_COMMAND == 27) {
				if (!StartInGameMENU()) {
					DrawExit();
					Sleep(100);
					return 0;
				}
				/*ExitGame();
				return 1;*/
				t1 = high_resolution_clock::now();
				while ((GetAsyncKeyState(VK_ESCAPE) & (1 << 15)) != 0) TimeUpdating(t1, seconds);
			}
			else {
				if (_COMMAND == 'A') { MoveLeft(); while ((GetAsyncKeyState(0x41/*A Keys*/) & (1 << 15)) != 0) TimeUpdating(t1, seconds); }
				else if (_COMMAND == 'W') { MoveUp(); while ((GetAsyncKeyState(0x57/*W Keys*/) & (1 << 15)) != 0) TimeUpdating(t1, seconds); }
				else if (_COMMAND == 'S') { MoveDown(); while ((GetAsyncKeyState(0x53/*S Keys*/) & (1 << 15)) != 0) TimeUpdating(t1, seconds); }
				else if (_COMMAND == 'D') { MoveRight(); while ((GetAsyncKeyState(0x44/*D Keys*/) & (1 << 15)) != 0) TimeUpdating(t1, seconds); }
				else if (_COMMAND == 13) {
					switch (CheckBoard(_X, _Y)) {
					case -1:
						validEnter = true;
						SetColor(c_red);
						wcout << X_SYM;
						SetColor(c_def);
						break;
					case 1:
						validEnter = true;
						SetColor(c_green);
						wcout << O_SYM;
						SetColor(c_def);
						break;
					case 0:
						validEnter = false;
					}

					if (validEnter) {
						int winner = ProcessFinish(TestBoard());
						switch (winner)
						{
						case -1:
						case 1:
						case 0:
							char c;
							do
							{
								c = AskContinue(winner);
							} while (c != 'Y' && c != 'N');
							if (c == 'Y') {
								seconds = TIME + 1;
								StartGame();
							}	
							else {
								seconds = TIME;
								inGame = false;
							}
							break;
						default:
							seconds = TIME + 1;
							t1 = high_resolution_clock::now();
							TimeUpdate(seconds);
							TimeSwitch = true;
							break;
						}
					}
				}
				else if (_COMMAND == -1) {
					int winner = -_TURN;
					ProcessFinish(winner);
					switch (winner)
					{
					case -1:
					case 1:
					case 0:
						char c;
						do
						{
							c = AskContinue(winner);
						} while (c != 'Y' && c != 'N');
						if (c == 'Y') {
							seconds = TIME + 1;
							StartGame();
						}
						else {
							inGame = false;
						}
					}
				}
				if (!TimeSwitch)
					TimeUpdating(t1, seconds);
			}
		}
	}
}


