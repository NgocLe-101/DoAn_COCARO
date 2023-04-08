#include "View.h"
#include "CONSTANT_VALUES.h"
#include "CONTROL.h"
#include "MODEL.h"


_POINT _A[BOARD_SIZE][BOARD_SIZE]; //Ma trận bàn cờ
int _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
int _COMMAND; // Biến nhận giá trị phím người dùng nhập
int _X, _Y; //Tọa độ hiện hành trên màn hình bàn cờ

int main()
{
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	FixConsoleWindow();
	ChangeConsole();


	bool validEnter;
	bool inGame = false;
	while (true)
	{
		bool inMenu = true;
		int option;
		do
		{
			option = SelectMenu(MainMenu());
			RunMainMenu(inMenu, option);
		} while (inMenu);
		inGame = true;
		if (option == 6)
			return 0;
		StartGame();
		inGame = true;
		while (inGame)
		{
			_COMMAND = toupper(_getch());
			if (_COMMAND == 27) {
				if (!StartInGameMENU()) {
					DrawExit();
					Sleep(100);
					return 0;
				}
				/*ExitGame();
				return 1;*/
			}
			else {
				if (_COMMAND == 'A') MoveLeft();
				else if (_COMMAND == 'W') MoveUp();
				else if (_COMMAND == 'S') MoveDown();
				else if (_COMMAND == 'D') MoveRight();
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
							if (c == 'Y')
								StartGame();
							else {
								inGame = false;
							}
						}
					}
				}
			}
		}
	}
}


