#include <iostream> 
#include <stdio.h> 
#include <stdlib.h> 
#include <fstream> 
#include <vector>
#include "CShaderLoader.h" 
#include "game.h"
using namespace glm;

MCIDEVICEID mID;

void Init() {
	glEnable(GL_DEPTH_TEST); //load and compile shaders 
	CShaderLoader shaderLoader;
	program = shaderLoader.createProgram("vertex1.glsl", "fragment1.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Send global pointer to the objects
	pGlobal = new CGlobal();
	player.sendGlobalPtr(pGlobal);
	thief.sendGlobalPtr(pGlobal);
	light.sendGlobalPtr(pGlobal);
	ground.sendGlobalPtr(pGlobal);


	// Initialize game variables
	cheatMode = NO;
	velocity = initVelocity;
	currentVelocity = velocity;
	startTickCount = GetTickCount64();
	startTimer = GetTickCount64();
	srand((unsigned int)time(NULL));
	thief.setThiefPose(rand() % 5);

	// Set player and thief own colors
	pGlobal->gPlayerColor =	vec3(0.4f, 0.803922f, 0.666667f);
	pGlobal->gThiefColor = vec3(1.0f, 0.5f, 0.3f);

	// Start the game
	walls.push_back(CWall());
	sound.playsound(BGM);
}

void setObjectColor(int color) {
	switch (color)
	{
	case RED:
		glColor3f(1.0, 0.0, 0.0);
		break;
	case GREEN:
		glColor3f(0.0, 1.0, 0.0);
		break;
	case BLUE:
		glColor3f(0.0, 0.0, 1.0);
		break;
	case YELLOW:
		glColor3f(1.0, 1.0, 0.0);
		break;
	case JUMP:
		glColor3f(0.5, 0.5, 0.5);
		break;
	default:
		glColor3f(0.5, 0.5, 0.5);
		break;
	}
}

void message(bool success) {
	HWND hwnd;
	HINSTANCE hInstance = GetModuleHandle(NULL);
	hwnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	if (success) {
		sound.playsound(WIN);
		cout << "Win" << endl;
		MessageBoxA(hwnd, "Win", "Win", MB_OK);
	}
	else {
		sound.playsound(LOSE);
		cout << "Lose" << endl;
		MessageBoxA(hwnd, "Lose", "Lose", MB_OK);
	}

	exit(0);
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// We can also generate multiple VAOs or buffers at the same time
    glGenVertexArrays(23, VAO); //21
    glGenBuffers(23, VBO); //21

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe polygon mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //solid polygon mode

	// Set 1st viewpoint
	if (viewPoint == VP_PLAYER) {
		
		view = mat4(1.0f);
		view = lookAt(vec3(player.getPlayerPositionX() + 0.1f, player.getPlayerPositionY(), 0.0f),
			vec3(player.getPlayerPositionX() + 1.5, player.getPlayerPositionY(), 0.0f),
			vec3(0.0f, 0.5f, 0.0f));
		projection = mat4(1.0f);
		projection = perspective(radians(120.0f), 1.5f, 0.1f, 20.0f);

		pGlobal->gView = view;
		pGlobal->gProjection = projection;
	}
	// Set 3rd viewpoint
	else {

		view = mat4(1.0f);
		view = lookAt(vec3(-1.0f, 1.0f, 1.0f),
			vec3(1.0f, -2.0f, -1.0f),
			vec3(0.0f, 1.0f, 0.0f));
		projection = mat4(1.0f);
		//projection = ortho(-6.0f, 6.0f, -4.0f, 4.0f, -4.0f, 4.0f);
		projection = ortho(-9.0f, 9.0f, -6.0f, 6.0f, -6.0f, 6.0f);

		pGlobal->gView = view;
		pGlobal->gProjection = projection;
	}
	
	// Calculate light position
	currentTimer = GetTickCount64();
	if (rotateDirection)
	{
		lightX = -2.5f * cos((currentTimer - startTimer) / 2500.0f);
		lightY = 2.5f * sin((currentTimer - startTimer) / 2500.0f);
	}
	else
	{
		lightX = 2.5f * cos((currentTimer - startTimer) / 2500.0f);
		lightY = 2.5f * sin((currentTimer - startTimer) / 2500.0f);
	}

	// Set light rotation direction
	if (currentTimer - startTimer >= 2500 * PI)
	{
		rotateDirection = !rotateDirection;
		startTimer = currentTimer;
		cnt++;
		if (cnt == 2)
		{
			// Toggle day or night
			dayOrNight = !dayOrNight;
			cnt = 0;
		}
	}

	// Set light position
	pGlobal->gLightPosition = vec4(lightX, lightY, 0.0, 0.0);

	// Set diffuse light intensity
	if (dayOrNight)
	{
		// Day light intensity
		glClearColor(0.529412, 0.807843, 0.980392, 1.0); // Background color
		pGlobal->gDiffuseProduct = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	}
	else
	{
		// Night light intensity
		glClearColor(0.098039, 0.098039, 0.439216, 1.0); // Background color
		pGlobal->gDiffuseProduct = vec4(0.15f, 0.15f, 0.15f, 1.0f);
	}

	// Set specular light intensity and shineness
	pGlobal->gSpecularProduct = vec4(0.3f, 0.3f, 0.3f, 1.0f);
	pGlobal->gShineness = 0.4f;


	// Draw objects
    player.playerDraw(program, VAO, VBO);
    thief.thiefDraw(program, VAO, VBO);
	light.lightDraw(program, VAO, VBO);
	ground.groundDraw(program, VAO, VBO);

	currentTickCount = GetTickCount64();
	if (currentTickCount - startTickCount >= interval) {
		walls.push_back(CWall());
		walls[total].setWallPositionX(walls[total].getWallPositionX() + interval / 1000.0 * total);
		walls[total].setWall(DEFAULT);
		walls[total].setWallColor(DEFAULT);
		startTickCount = currentTickCount;
		total++;
	}

	for (int i = front; i < total; i++) {
		walls[i].sendGlobalPtr(pGlobal);
		walls[i].draw(program, VAO[20], VBO[20]);
	}
	   
    glutSwapBuffers();

}


void doSystemCheck() {
	//If the wall and the thief collide ...
	if (walls[now].getWallPositionX() < (thief.getThiefPositionX())) {

		//Wall - change to thief color
		walls[now].setWallColor(thief.getThiefPose());
		walls[now].setWall(thief.getThiefPose());

		//Thief - jump timer start
		if (walls[now].getWallColor() == JUMP) {
			jumpThiefTimer = 0;
			jumpingThief = true;
		}

		//Thief - change to new color
		thief.setThiefPose(rand() % 5);
		sound.playsound(THIEFPASS);
		now++;
	}

	//System - check if pass or fail
	if (walls[previous].getWallPositionX() <= (player.getPlayerPositionX())) {

		switch (cheatMode)
		{
		case NO:
			if (player.getPlayerPose() == walls[previous].getWallColor()) {
				sound.playsound(PLAYERPASS);
				cout << "Pass" << endl;
				velocity += 0.01;
				interval -= 300;
				previousPlayerPosition = player.getPlayerPositionX();
				pass = true;
			}
			else {
				sound.playsound(PLAYERNONPASS);
				cout << "Fail" << endl;
				failCount++;
				if (failCount >= 3)
					message(false);
				pass = false;
			}
			previous++;
			break;

		case ALL_PASS:
			cout << "Pass" << endl;
			sound.playsound(PLAYERPASS);
			velocity += 0.01;
			interval -= 300;
			previousPlayerPosition = player.getPlayerPositionX();
			pass = true;
			previous++;
			break;

		case ALL_FAIL:
			sound.playsound(PLAYERNONPASS);
			cout << "Fail" << endl;
			failCount++;
			if (failCount >= 3)
				message(false);
			pass = false;
			previous++;
			break;
		}
	}

	//System - WIN if the distance between player and thief is less than a "threshold"
	//"threshold" == player.getPlayerSize()
	if (thief.getThiefPositionX() <= player.getPlayerPositionX())
		message(true);

	//System - LOSE after 3 minutes in all pass mode
	if ((cheatMode == ALL_PASS) && (time1 > 60 * 60 * 3))
		message(false);

	//System - LOSE if the player is out of the view
	if (player.getPlayerPositionX() < -3.2)
		message(false);

	glutPostRedisplay();
}

void doAnimation(int value) {
	currentVelocity = velocity;
	time1 += 1;


	//Wall - move wall in "currentVelocity"
	for (int i = 0; i < total; i++) {
		walls[i].setWallPositionX(walls[i].getWallPositionX() - currentVelocity);
		if (walls[i].getWallPositionX() + walls[i].getWallWidth() < -10) {
			walls[i].setWallPositionX(-30);
			front = i;
			//walls[i].~CWall();
		}
	}

	//Thief - jump
	//부동소수점 오차를 무시하면 점프할 때마다 일정 거리만큼 왼쪽으로 가게 됨
	jumpThiefTimer++;
	if (jumpThiefTimer < (initVelocity / currentVelocity * 20) && jumpingThief)
	{
		thief.setThiefPositionX(thief.getThiefPositionX() - currentVelocity / 15.0f);
		thief.setThiefPositionY(thief.getThiefPositionY() + currentVelocity * 4.0f);
	}
	else if (jumpThiefTimer < (initVelocity / currentVelocity * 130) && jumpingThief)
	{
		thief.setThiefPositionX(thief.getThiefPositionX() - currentVelocity / 15.0f);

	}
	else if (jumpThiefTimer < (initVelocity / currentVelocity * 150) && jumpingThief)
	{
		thief.setThiefPositionX(thief.getThiefPositionX() - currentVelocity / 15.0f);
		thief.setThiefPositionY(thief.getThiefPositionY() - currentVelocity * 4.0f);

	}
	else if (jumpingThief)
	{
		thief.setThiefPositionY(-0.5f);
		jumpingThief = false;

	}

	//Player - jump
	//부동소수점 오차를 무시하면 점프할 때마다 일정 거리만큼 왼쪽으로 가게 됨
	jumpPlayerTimer++;
	if (jumpPlayerTimer < (initVelocity / currentVelocity * 20) && jumpingPlayer)
	{
		player.setPlayerPositionX(player.getPlayerPositionX() - currentVelocity / 15.0f);
		player.setPlayerPositionY(player.getPlayerPositionY() + currentVelocity * 4.0f);
	}
	else if (jumpPlayerTimer < (initVelocity / currentVelocity * 130) && jumpingPlayer)
	{
		player.setPlayerPositionX(player.getPlayerPositionX() - currentVelocity / 15.0f);
	}
	else if (jumpPlayerTimer < (initVelocity / currentVelocity * 150) && jumpingPlayer)
	{
		player.setPlayerPositionX(player.getPlayerPositionX() - currentVelocity / 15.0f);
		player.setPlayerPositionY(player.getPlayerPositionY() - currentVelocity * 4.0f);
	}
	else if (jumpingPlayer)
	{
		player.setPlayerPositionY(-0.5f);
		player.setPlayerPose(DEFAULT);
		jumpingPlayer = false;
	}

	//Player - move toward thief with moving animation
	if (pass) {
		player.setPlayerPositionX(player.getPlayerPositionX() + playerDistance);
		if ((player.getPlayerPositionX() - previousPlayerPosition) >= 0.3) {
			previousPlayerPosition = 0.0;
			pass = false;
			//cameraZoomIn();
		}
	}

	glutPostRedisplay();

	glutTimerFunc(1, doAnimation, 1);
}

void selectPose(int key, int x, int y) {
    sound.playsound(CHANGE);
    switch (key) {
    case GLUT_KEY_LEFT: //RED
        player.setPlayerPose(RED);
        break;
    case GLUT_KEY_RIGHT: //GREEN
        player.setPlayerPose(GREEN);
        break;
    case GLUT_KEY_UP: //BLUE
        player.setPlayerPose(BLUE);
        break;
    case GLUT_KEY_DOWN: //YELLOW
        player.setPlayerPose(YELLOW);
        break;
    }

    glutPostRedisplay();
}

void doKeyboard(unsigned char key, int x, int y) {

	switch (key)
	{
	case 32: // Space bar
		if (!jumpingPlayer)
		{
			//Plaer - jump timer start
			player.setPlayerPose(JUMP);
			jumpPlayerTimer = 0;
			jumpingPlayer = true;
		}
		return;
	}

	switch (key) {
	case 'b': {
		if (viewPoint == VP_GLOBAL) {
			viewPoint = VP_PLAYER;
		}
		else {
			viewPoint = VP_GLOBAL;
		}
		return;
	}
	case 'c':
		if (cheatMode == ALL_PASS)
			cheatMode = NO;
		else
			cheatMode = ALL_PASS;
		break;
	case 'f':
		if (cheatMode == ALL_FAIL)
			cheatMode = NO;
		else
			cheatMode = ALL_FAIL;
		break;
	}

	if (cheatMode == ALL_PASS) {
		cout << "All Pass Mode" << endl;
		allPassTimer = GetTickCount64();
	}
	else if (cheatMode == ALL_FAIL)
		cout << "All Fail Mode" << endl;
	else
		cout << "No Cheat" << endl;

	glutPostRedisplay();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); 
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 800); 
	glutCreateWindow(argv[0]);

	glewInit();


	Init(); // register callbacks 
	glutDisplayFunc(renderScene); 

	glutTimerFunc(0, doAnimation, 1);
	
	glutIdleFunc(doSystemCheck);

	glutKeyboardFunc(doKeyboard);
	glutSpecialFunc(selectPose);

    //glutTimerFunc(0, timerFunc, 1);
	glutMainLoop(); 
	glDeleteProgram(program); 
	return 0; 
}
