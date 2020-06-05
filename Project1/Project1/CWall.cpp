#include "CWall.h"
using namespace glm;
#include "stb_images.h"

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Get global view matrix and projection matrix
    int viewLoc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(pGlobal->gView));

    int projectionLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(pGlobal->gProjection));


    // Get global shineness
    int shinenessLoc = glGetUniformLocation(program, "shineness");
    glUniform1f(shinenessLoc, pGlobal->shineness);

    //// Directional light
    // Get global light position and light intensity
    int lightPositionLoc = glGetUniformLocation(program, "lightPosition");
    glUniform4f(lightPositionLoc, pGlobal->dirLightPosition.x, pGlobal->dirLightPosition.y, pGlobal->dirLightPosition.z, 0.0f);

    // Get global diffusion product
    int diffuseProductLoc = glGetUniformLocation(program, "diffuseProduct");
    glUniform4f(diffuseProductLoc, pGlobal->diffuseProduct.x, pGlobal->diffuseProduct.y, pGlobal->diffuseProduct.z, pGlobal->diffuseProduct.w);

    // Get global specular product and shineness
    int specularProductLoc = glGetUniformLocation(program, "specularProduct");
    glUniform4f(specularProductLoc, pGlobal->specularProduct.x, pGlobal->specularProduct.y, pGlobal->specularProduct.z, pGlobal->specularProduct.w);

    //// Point lights
    int pointLightPositionsLoc = glGetUniformLocation(program, "p_lightPositions");
    glUniform4fv(pointLightPositionsLoc, 50, value_ptr(pGlobal->pointLightPositions[0]));

    int p_diffuseProductLoc = glGetUniformLocation(program, "p_diffuseProduct");
    glUniform4fv(p_diffuseProductLoc, 50, value_ptr(pGlobal->pointDiffuseProducts[0]));

    int p_specularProductLoc = glGetUniformLocation(program, "p_specularProduct");
    glUniform4fv(p_specularProductLoc, 50, value_ptr(pGlobal->pointSpecularProducts[0]));


    // Get global shading type
    int shadingTypeLoc = glGetUniformLocation(program, "shadingType");
    glUniform1i(shadingTypeLoc, pGlobal->shadingType);


    glBindVertexArray(VAO);




    if (!textureLoad) {

        unsigned int texture1, texture2;
        // texture 1
        // ---------
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        char fileName[15] = "brick_base.jpg";

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);


        glUniform1i(glGetUniformLocation(program, "texture1"), 0); // 직접 설정
        textureLoad = true;
    }









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

    glDrawArrays(GL_TRIANGLES, 0, 36);

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

    verticesSize = 1152;
    this->vertices = vertice.getNormalVertices();

    //switch (pose) {
    //case RED: {//+ 모양 
    //    verticesSize = 5184;
    //    this->vertices = vertice.getRedWallVertices();
    //    break;
    //}
    //case BLUE: { // 1자
    //    verticesSize = 2592;
    //    this->vertices = vertice.getBlueWallVertices();
    //    break;
    //}

    //case YELLOW: {//가운데 뚫린 +
    //    verticesSize = 3456;
    //    this->vertices = vertice.getYellowWallVerticies();

    //    break;
    //}

    //case GREEN: {//ㄹ
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
