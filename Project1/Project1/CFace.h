#pragma once
#include <vector>
#include "CShaderLoader.h" 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include "CGlobal.h"

using namespace std;
using namespace glm;
class CFace
{
private:
	float radius;
	vector<float> vertices;
	vector<float> verticesThief;
	CGlobal* pGlobal;

	float* verticeArr, * verticeArrT;
	bool textureLoad = false;

	unsigned int texture;

public:
	CFace();
	void drawPlayer(GLuint program, float positionX, float positionY,
		unsigned VAO, unsigned VBO);
	void drawThief(GLuint program, float positionY,
		unsigned VAO, unsigned VBO);

	void sendGlobalPtr(class CGlobal* pGlobal);
	void renderFaces();

};

