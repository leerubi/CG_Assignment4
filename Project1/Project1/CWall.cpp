#include "CWall.h"
using namespace glm;
CWall::CWall()
{
	positionX = 10;
	positionY = 1;
	color = DEFAULT;
	width = 0.5;
	height = 2;
	front = 0;
    vertices = nullptr;
    verticesSize = 0;

}

CWall::~CWall()
{
}

void CWall::setWallPositionX(float positionX)
{
	this->positionX = positionX;
}

float CWall::getWallPositionX()
{
	return positionX;
}

void CWall::setWallPositionY(float positionY)
{
	this->positionY = positionY;
}

float CWall::getWallPositionY()
{
	return positionY;
}

void CWall::setWallColor(int color)
{
	this->color = color;
}

int CWall::getWallColor()
{
	return color;
}

float CWall::getWallWidth()
{
	return width;
}

float CWall::getWallHeight()
{
	return height;
}

void CWall::setFront(int front)
{
	this->front = front;
}

int CWall::getFront()
{
	return front;
}

void CWall::draw(GLuint program, unsigned int VAO, unsigned int VBO)
{
 
    glUseProgram(program); //draw 3 vertices as triangles 

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, getVertices(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // Get global view matrix and projection matrix
    int viewLoc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(pGlobal->gView));

    int projectionLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(pGlobal->gProjection));

    // Get global light position and light intensity
    int lightPositionLoc = glGetUniformLocation(program, "lightPosition");
    glUniform4f(lightPositionLoc, pGlobal->gLightPosition.x, pGlobal->gLightPosition.y, pGlobal->gLightPosition.z, 0.0f);

    // Get global diffusion product
    int diffuseProductLoc = glGetUniformLocation(program, "diffuseProduct");
    glUniform4f(diffuseProductLoc, pGlobal->gDiffuseProduct.x, pGlobal->gDiffuseProduct.y, pGlobal->gDiffuseProduct.z, pGlobal->gDiffuseProduct.w);

    // Get global specular product and shineness
    int specularProductLoc = glGetUniformLocation(program, "specularProduct");
    glUniform4f(specularProductLoc, pGlobal->gSpecularProduct.x, pGlobal->gSpecularProduct.y, pGlobal->gSpecularProduct.z, pGlobal->gSpecularProduct.w);

    int shinenessLoc = glGetUniformLocation(program, "shineness");
    glUniform1f(shinenessLoc, pGlobal->gShineness);

    glBindVertexArray(VAO);


    vec3 objColor;
    mat4 model = mat4(1.0f);
    if (color == DEFAULT || color == JUMP) {
        model = translate(model, vec3(positionX, -0.6f, 0.0f));
        //model = scale(model, vec3(1.8, 8.0, 6.8));
        model = scale(model, vec3(0.36, 1.6, 1.36));
        objColor = vec3(1.0f, 1.0f, 1.0f);

    }
    else if (color == RED)
    {
        model = translate(model, vec3(positionX, -0.6f, 0.0f));
        //model = scale(model, vec3(1.8, 8.0, 6.8));
        model = scale(model, vec3(0.36, 1.6, 0.68));
        objColor = vec3(1.0f, 0.0f, 0.0f);
    }
    else if (color == GREEN)
    {
        model = translate(model, vec3(positionX, -0.6f, 0.0f));
        //model = scale(model, vec3(1.8, 8.0, 6.8));
        model = scale(model, vec3(0.36, 1.6, 0.68));
        objColor = vec3(0.0f, 1.0f, 0.0f);
    }
    else if (color == BLUE)
    {
        model = translate(model, vec3(positionX, -0.6f, 0.0f));
        //model = scale(model, vec3(1.8, 8.0, 6.8));
        model = scale(model, vec3(0.36, 1.6, 0.68));
        objColor = vec3(0.0f, 0.0f, 1.0f);
    }
    else if (color == YELLOW)
    {
        model = translate(model, vec3(positionX, -0.6f, 0.0f));
        //model = scale(model, vec3(1.8, 8.0, 6.8));
        model = scale(model, vec3(0.36, 1.6, 0.68));
        objColor = vec3(1.0f, 1.0f, 0.0f);
    }

    int modelLoc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

    int colorLoc = glGetUniformLocation(program, "color");
    glUniform3f(colorLoc, objColor.x, objColor.y, objColor.z);

    glDrawArrays(GL_TRIANGLES, 0, verticesSize/24);

}

void CWall::setVertices(int size)
{
}

float* CWall::getVertices()
{
    return this->vertices;
}

void CWall::setWall(int pose)
{
    if (vertices != nullptr)
        delete vertices;

    verticesSize = 864;
    this->vertices = vertice.getNormalVertices();

    //switch (pose) {
    //case RED: {//+ ��� 
    //    verticesSize = 5184;
    //    this->vertices = vertice.getRedWallVertices();
    //    break;
    //}
    //case BLUE: { // 1��
    //    verticesSize = 2592;
    //    this->vertices = vertice.getBlueWallVertices();
    //    break;
    //}

    //case YELLOW: {//��� �ո� +
    //    verticesSize = 3456;
    //    this->vertices = vertice.getYellowWallVerticies();

    //    break;
    //}

    //case GREEN: {//��
    //    verticesSize = 4320;
    //    this->vertices = vertice.getGreenWallVertices();
    //    break;
    //}

    //default: {
    //    verticesSize = 864;
    //    this->vertices = vertice.getNormalVertices();
    //    break;
    //}
    //}
}

void CWall::sendGlobalPtr(CGlobal* pGlobal)
{
    this->pGlobal = pGlobal;
}