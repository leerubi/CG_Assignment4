#pragma once
#include <vector>
#include "CShaderLoader.h" 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include "global.h"
#include "CGlobal.h"


using namespace std;
using namespace glm;

class CLeg
{
private:
	long startTick;
	long currentTick;
	//bool direction;


	bool rightCircuit;
	bool leftCircuit;


	float rightAngle;
	float leftAngle;


	int rightDirection;
	int leftDirection;


	int passCount;

	CGlobal* pGlobal;

	bool textureLoad = false;
	unsigned int texture;
public:
	CLeg();
	void playerDraw(GLuint program, unsigned int VAO, unsigned int VBO, int type,
		float positionX, float positionY, float angle, bool direction);
	void thiefDraw(GLuint program, unsigned int VAO, unsigned int VBO, int type,
		float positionY, float angle, bool direction);
	void setLeftAngle(bool thighDirection, float thighAngle);
	void setRightAngle(bool thighDirection, float thighAngle);

	void sendGlobalPtr(class CGlobal* pGlobal);

};

