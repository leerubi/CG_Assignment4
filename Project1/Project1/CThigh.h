#pragma once
#include <vector>
#include "CShaderLoader.h" 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include "global.h"
#include "CLeg.h"
#include "CGlobal.h"


using namespace std;
using namespace glm;

class CThigh
{
private:

	float angle;
	long startTick;
	long currentTick;
	bool direction;


	CLeg leftLeg;
	CLeg rightLeg;

	CGlobal* pGlobal;
	bool textureLoad = false;
	unsigned int texture;

public:
	CThigh();
	void playerDraw(GLuint program, unsigned int VAO1, unsigned int VBO1,
		unsigned int VAO2, unsigned int VBO2, int type, float positionX, float positionY);
	void thiefDraw(GLuint program, unsigned int VAO1, unsigned int
		VBO1, unsigned int VAO2, unsigned int VBO2, int type, float positionY);
	void sendGlobalPtr(class CGlobal* pGlobal);

};

