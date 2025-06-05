#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <iostream>
#include <windows.h>

int get_height_desktop_resolution();

// //game const variables
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = get_height_desktop_resolution() - 50; // screen height - taskbar
const int COL_SIZE = 14;
const int ROW_SIZE = 8;
const int RIGHT_LIMIT = SCREEN_WIDTH - 40;
const int LEFT_LIMIT = 20;
const int PADDLE_VELOCITY = 10 * 1;
const int COOLDOWN_TO_RESPAWN = 2;
const int BRICKS_AMOUNT = 112;
const int TEXT_SCORE_X = 50;
const int TEXT_SCORE_Y = 100;
const int TEXT_PAUSED_TITLE_Y = 100;
// player const variables
const int P_WIDTH = 50;
const int P_HEIGHT = 25;
const int INITIAL_PLAYER_X = 395;
const int INITIAL_PLAYER_Y = SCREEN_HEIGHT - 60;
const int LIFES = 5;

// ball const variables
const int INITIAL_BALL_Y = SCREEN_HEIGHT - 220;
const int MAX_BAll_VELOCITY = SCREEN_HEIGHT == 720 ? 5 : 7;
const int INITIAL_BAll_VELOCITY = 5;

#endif
