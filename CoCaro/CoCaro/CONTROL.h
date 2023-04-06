#pragma once
#include "CONSTANT_VALUES.h"
#include "MODEL.h"
#include "View.h"

void StartGame();

bool StartInGameMENU();

void MoveRight();
void MoveLeft();
void MoveDown();
void MoveUp();

int SelectMenu(_MENU menu);
void RunMainMenu(bool& run, int option);
