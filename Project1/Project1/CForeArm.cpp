#include "CForeArm.h"
using namespace glm;
#include "stb_images.h"

float verticesForeArm[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,   0.0f, 1.0f
};

CForeArm::CForeArm()
{
    leftAngle = 90;
    rightAngle = 90;

    leftPreviousAngle = 0;
    rightPreviousAngle = 0;

    leftRotateAngle = 0;
    rightRotateAngle = 0;



    leftAngleT = 90;
    rightAngleT = 90;

    leftPreviousAngleT = 0;
    rightPreviousAngleT = 0;

    leftRotateAngleT = 0;
    rightRotateAngleT = 0;
}

void CForeArm::playerDraw(GLuint program, unsigned int VAO, unsigned int VBO, int type,
    float angle, float positionX, float positionY)
{

    // Get global view matrix and projection matrix
    int viewLoc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(pGlobal->gView));

    int projectionLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(pGlobal->gProjection));

    // Get global surface color
    int colorLoc = glGetUniformLocation(program, "color");
    glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f);

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

    float pX = positionX;
    float pY = positionY;


    glUseProgram(program); //draw 3 vertices as triangles 


    if (leftRotateAngle != this->leftAngle)
        leftRotateAngle = leftPreviousAngle += (this->leftAngle - leftPreviousAngle) * 0.1;

    if (rightRotateAngle != this->rightAngle)
        rightRotateAngle = rightPreviousAngle += (this->rightAngle - rightPreviousAngle) * 0.1;

    float leftAngle, rightAngle;
    leftAngle = angle;
    rightAngle = -angle;



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







    if (type == LEFT) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesForeArm), verticesForeArm, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //texture attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);


        mat4 model2 = mat4(1.0f);
        model2 = translate(model2, vec3(pX, pY + 0.3, .3));
        model2 = rotate(model2, radians(rightAngle), vec3(0.0f, 0.0f, 1.0f));


        mat4 model = model2;

        model = translate(model, vec3(0.1, -0.2, 0.0));
        model = rotate(model, radians(rightRotateAngle), vec3(0.0f, 0.0f, 1.0f));
        model = scale(model, vec3(0.1, 0.3, 0.1));
        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);

    }
    else {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesForeArm), verticesForeArm, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //texture attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);



        mat4 model2 = mat4(1.0f);
        model2 = translate(model2, vec3(positionX, positionY + 0.3, 0.3));
        model2 = rotate(model2, radians(rightAngle), vec3(0.0f, 0.0f, 1.0f));

        mat4 model = model2;

        model = translate(model, vec3(0.1, -0.2, 0.0));
        model = rotate(model, radians(rightRotateAngle), vec3(0.0f, 0.0f, 1.0f));
        model = scale(model, vec3(0.1, 0.3, 0.1));

        //mat4 model2 = mat4(1.0f);
        //model2 = translate(model2, vec3(pX, pY + 0.3, .3));
        //model2 = rotate(model2, radians(rightAngle), vec3(0.0f, 0.0f, 1.0f));


        //mat4 model = model2;

        //model = translate(model, vec3(0.0, -0.3, 0.0));
        //model = rotate(model, radians(rightRotateAngle), vec3(0.0f, 0.0f, 1.0f));
        ////model = scale(model, vec3(0.5, 1.5, 0.5));
        //model = scale(model, vec3(0.0, 0.0, 0.0));



        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));


        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void CForeArm::thiefDraw(GLuint program, unsigned int VAO, unsigned int VBO, int type, float angle, float positionY)
{

    // Get global view matrix and projection matrix
    int viewLoc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(pGlobal->gView));

    int projectionLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(pGlobal->gProjection));

    // Get global surface color
    int colorLoc = glGetUniformLocation(program, "color");
    glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f);

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


    float pY = positionY;

    glUseProgram(program); //draw 3 vertices as triangles 

    float armAngle = angle;

    if (leftRotateAngleT != leftAngleT)
        leftRotateAngleT = leftPreviousAngleT += (leftAngleT - leftPreviousAngleT) * 0.1;

    if (rightRotateAngleT != rightAngleT)
        rightRotateAngleT = rightPreviousAngleT += (rightAngleT - rightPreviousAngleT) * 0.1;

    float leftAngle, rightAngle;
    leftAngle = angle;
    rightAngle = -angle;



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















    if (type == LEFT) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesForeArm), verticesForeArm, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //texture attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        mat4 model2 = mat4(1.0f);
        model2 = translate(model2, vec3(1.25, pY + 0.3, -.2));
        model2 = rotate(model2, radians(leftAngle), vec3(0.0f, 0.0f, 1.0f));


        mat4 model = model2;

        model = translate(model, vec3(0.0, -0.3, 0.0));
        model = rotate(model, radians(leftRotateAngleT), vec3(0.0f, 0.0f, 1.0f));
        //model = scale(model, vec3(0.5, 1.5, 0.5));
        model = scale(model, vec3(0.1, 0.3, 0.1));


        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);


    }
    else {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesForeArm), verticesForeArm, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //texture attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);


        mat4 model2 = mat4(1.0f);
        model2 = translate(model2, vec3(1.25, pY + 0.3, 0.3));
        model2 = rotate(model2, radians(rightAngle), vec3(0.0f, 0.0f, 1.0f));


        mat4 model = model2;
        model = translate(model, vec3(0.0, -0.3, 0.0));
        model = rotate(model, radians(rightRotateAngleT), vec3(0.0f, 0.0f, 1.0f));
        //model = scale(model, vec3(0.5, 1.5, 0.5));
        model = scale(model, vec3(0.1, 0.3, 0.1));


        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));



        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }




}

void CForeArm::setMotion(int pose)
{
    leftPreviousAngle = leftAngle;
    rightPreviousAngle = rightAngle;

    switch (pose) {
    case RED:
        //왼쪽 90, 오른쪽 90
        leftAngle = 90;
        rightAngle = 90;
        break;
    case BLUE:
        //왼쪽 180, 오른쪽 90
        leftAngle = 0;
        rightAngle = 0;
        break;
    case GREEN:
        //왼쪽 180, 오른쪽 180
        leftAngle = -45;
        rightAngle = 45;
        break;
    case YELLOW:
        //왼쪽 90, 오른쪽 -90
        leftAngle = 90;
        rightAngle = -90;
        break;
    default:
        //RED
        leftAngle = 0;
        rightAngle = 0;
        break;
    }



}

void CForeArm::setTMotion(int pose)
{
    leftPreviousAngleT = leftAngleT;
    rightPreviousAngleT = rightAngleT;

    switch (pose) {
    case RED:
        //왼쪽 90, 오른쪽 90
        leftAngleT = 90;
        rightAngleT = 90;
        break;
    case BLUE:
        //왼쪽 180, 오른쪽 90
        leftAngleT = 0;
        rightAngleT = 0;
        break;
    case GREEN:
        //왼쪽 180, 오른쪽 180
        leftAngleT = -45;
        rightAngleT = 45;
        break;
    case YELLOW:
        //왼쪽 90, 오른쪽 -90
        leftAngleT = 90;
        rightAngleT = -90;
        break;
    default:
        //RED
        leftAngle = 0;
        rightAngle = 0;
        break;
    }

}

void CForeArm::sendGlobalPtr(CGlobal* pGlobal)
{
    this->pGlobal = pGlobal;
}
