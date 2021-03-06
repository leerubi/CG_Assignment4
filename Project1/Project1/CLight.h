#pragma once
#include <iostream> 
#include <stdio.h> 
#include <stdlib.h> 
#include <fstream> 
#include <vector>
#include "CShaderLoader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "global.h"
#include "CGlobal.h"
#include <stack>

using namespace std;
using namespace glm;

class CLight
{
private:

	CGlobal* pGlobal;
	int start;
	int current;
	
	bool textureLoad = false;
	unsigned int texture;

public:
	CLight();
	void lightDraw(GLuint program, unsigned int VAO[], unsigned int VBO[]);
	void sendGlobalPtr(class CGlobal* pGlobal);

};

