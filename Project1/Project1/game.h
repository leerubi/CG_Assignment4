#pragma once
#pragma comment(lib, "winmm")

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CCharacter.h"
#include "CWall.h"
#include <Windows.h>
#include <tchar.h>
#include <mmsystem.h>
#include <ctime>
#include <cmath>
#include <iostream>
#include "CSound.h"
#include "CLight.h"
#include "CGlobal.h"
#include "CGround.h"
CONST TCHAR* lpszClass = _T("Message Box!\n");

GLuint program;
CCharacter player;
CCharacter thief;
vector<CWall> walls;
CWall wall;
CGround ground;
CLight light;
CSound sound;

class CGlobal* pGlobal;

//unsigned int VBO[21], VAO[21];
unsigned int VBO[23], VAO[23];
unsigned int VBO2, VAO2;
//Wall indices
int total = 0;		//Number of walls
int front = 0;		//Index of the leftmost wall
int previous = 0;	//Index of the wall just to the right of player
int now = 0;		//Index of the wall just to the left of theif

//System varables
int passCount = 0;		 //Number of pass
int failCount = 0;		 //Number of fail
int interval = 3000;	 //Wall creation interval
float initVelocity = 0.02f; //Wall initial velocity
float currentVelocity;		//Wall current velocity
float velocity;				//Wall new velocity

//Timer variables
int startTickCount = 0;
int currentTickCount = 0;
int allPassTimer = 0;

//Jump variables
int jumpThiefTimer = 0;
int jumpPlayerTimer = 0;
bool jumpingThief = false;
bool jumpingPlayer = false;

//Player animation variables
bool pass = false;
float playerDistance = 0.01f;
float previousPlayerPosition = 0.0f;

//Light orbital variables
float startTimer = 0.0f;
float currentTimer = 0.0f;
float lightX;
float lightY;
bool rotateDirection = true;
int cnt = 0;


//Cheatcode variables
enum CheatMode
{
	NO,
	ALL_PASS,
	ALL_FAIL
};
CheatMode cheatMode;

//Window variables
int width;
int height;

//Functions
void init();					// Initialize game states
void setObjectColor(int color);	// Set theif or wall pose(color)
void cameraZoomIn();			// Camera zoom-in
void message(bool success);		// End the game and show the message if pass or fail
void playSound();				// Play background or effect sound

//for checking play time
int time1 = 0;


int viewPoint = VP_GLOBAL;
int shadingType = GOURAUD;
bool dayOrNight = true;

mat4 view = mat4(1.0f);
mat4 projection = mat4(1.0f);
