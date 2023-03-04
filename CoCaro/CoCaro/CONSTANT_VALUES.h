#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <codecvt>
#include <fstream>
#include <vector>
#include <fcntl.h>
#include <io.h>
using namespace std;
//Constant Values
#define SPACE 32
#define BOARD_SIZE 16
#define LEFT 10
#define TOP 5
#define WIDTH 1100
#define HEIGHT 720
#define HORIZONTAL_LINE (wchar_t)0x2500
#define VERTICAL_LINE (wchar_t)0x2502
#define TOP_CROSS (wchar_t)0x251C
#define TOP_RIGHT (wchar_t)0x2510
#define TOP_LEFT (wchar_t)0x250C
#define BOTTOM_LEFT (wchar_t)0x2514
#define BOTTOM_RIGHT (wchar_t)0x2518
#define TOP_CROSS (wchar_t)0x252C
#define BOTTOM_CROSS (wchar_t)0x2534
#define	LEFT_CROSS (wchar_t)0x251C
#define RIGHT_CROSS (wchar_t)0x2524
#define HORIZONTAL_SPACE 5
#define VERTIAL_SPACE 2
#define CROSS (wchar_t)0x253C
// BOX value
#define B_WIDTH 4
#define B_HEIGHT 1
#define IM_SPACE 4
// Color settings
#define c_red 244
#define c_green 250
#define c_def 240
#define c_cyan 251
#define c_dblue 241
#define c_lblue 243
#define c_blue 249
#define c_yellow 254
#define c_orange 246
#define c_lime 242
#define c_gray 248
#define c_purple 245

// Drawing
#define X_SYM (wchar_t)0x274C
#define O_SYM (wchar_t)0x26AB
#define TIMER (wchar_t)0x23F2
// Box Drawing
#define DL_T 1
#define DL_T_VERTICAL (wchar_t)0x2551
#define DL_T_HORIZONTAL (wchar_t)0x2550
#define DL_T_TOPLEFTCORNER (wchar_t)0x2554
#define DL_T_TOPRIGHTCORNER (wchar_t)0x2557
#define DL_T_BOTLEFTCORNER (wchar_t)0x255A
#define DL_T_BOTRIGHTCORNER (wchar_t)0x255D
struct _POINT {
	int x, y, c;
}; // x: tọa độ dòng, y: tọa độ cột, c: đánh dấu
_POINT _A[BOARD_SIZE][BOARD_SIZE]; //Ma trận bàn cờ
int _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
int _COMMAND; // Biến nhận giá trị phím người dùng nhập
int _X, _Y; //Tọa độ hiện hành trên màn hình bàn cờ