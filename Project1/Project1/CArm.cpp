#include "CArm.h"
using namespace glm;
#define STB_IMAGE_IMPLEMENTATION
#include "stb_images.h"
float verticesArm[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
};

CArm::CArm()
{

}

void CArm::playerDraw(GLuint program, unsigned int VAO1, unsigned int VBO1, unsigned int VAO2, unsigned int VBO2, int type, float positionX, float positionY)
{
    // Get global view matrix and projection matrix
    int viewLoc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(pGlobal->gView));

    int projectionLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(pGlobal->gProjection));

    // Get global light position and light intensity
    int lightPositionLoc = glGetUniformLocation(program, "lightPosition");
    glUniform4f(lightPositionLoc, pGlobal->gLightPosition.x, pGlobal->gLightPosition.y, pGlobal->gLightPosition.z, 0.0f);

    // Get global player own color
    int colorLoc = glGetUniformLocation(program, "color");
    glUniform3f(colorLoc, pGlobal->gPlayerColor.x, pGlobal->gPlayerColor.y, pGlobal->gPlayerColor.z);

    // Get global diffusion product
    int diffuseProductLoc = glGetUniformLocation(program, "diffuseProduct");
    glUniform4f(diffuseProductLoc, pGlobal->gDiffuseProduct.x, pGlobal->gDiffuseProduct.y, pGlobal->gDiffuseProduct.z, pGlobal->gDiffuseProduct.w);

    // Get global specular product and shineness
    int specularProductLoc = glGetUniformLocation(program, "specularProduct");
    glUniform4f(specularProductLoc, pGlobal->gSpecularProduct.x, pGlobal->gSpecularProduct.y, pGlobal->gSpecularProduct.z, pGlobal->gSpecularProduct.w);

    int shinenessLoc = glGetUniformLocation(program, "shineness");
    glUniform1f(shinenessLoc, pGlobal->gShineness);

    float pX = positionX;


    glUseProgram(program); //draw 3 vertices as triangles 

    if (leftRotateAngle != leftAngle)
        leftRotateAngle = leftPreviousAngle += (leftAngle - leftPreviousAngle) * 0.1;

    if (rightRotateAngle != rightAngle)
        rightRotateAngle = rightPreviousAngle += (rightAngle - rightPreviousAngle) * 0.1;

    float angle = leftRotateAngle;



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
        glGenVertexArrays(1, &VAO1);
        glGenBuffers(1, &VBO1);

        glBindVertexArray(VAO1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArm), verticesArm, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //texture attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(VAO1);


        mat4 model = mat4(1.0f);
        model = translate(model, vec3(pX, positionY + 0.3, -0.2));
        model = rotate(model, radians(leftRotateAngle), vec3(0.0f, 0.0f, 1.0f));
        //model = scale(model, vec3(0.5, 1.5, 0.5));
        model = scale(model, vec3(0.1, 0.3, 0.1));
        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(VAO1);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Send global pointer to the objects
        leftForeArm.sendGlobalPtr(pGlobal);

        leftForeArm.playerDraw(program, VAO2, VBO2, LEFT, angle, pX, positionY);
    }
    else {
        glGenVertexArrays(1, &VAO1);
        glGenBuffers(1, &VBO1);

        glBindVertexArray(VAO1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArm), verticesArm, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //texture attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);



        mat4 model = mat4(1.0f);
        model = translate(model, vec3(pX, positionY + 0.3, 0.3));
        model = rotate(model, radians(rightRotateAngle), vec3(0.0f, 0.0f, 1.0f));
        //model = scale(model, vec3(0.5, 1.5, 0.5));
        model = scale(model, vec3(0.1, 0.3, 0.1));
        //model = scale(model, vec3(0.0, 0.0, 0.0));

        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(VAO1);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Send global pointer to the objects
        rightForeArm.sendGlobalPtr(pGlobal);

        rightForeArm.playerDraw(program, VAO2, VBO2, RIGHT, angle, pX, positionY);

    }


}

void CArm::thiefDraw(GLuint program, unsigned int VAO1, unsigned int VBO1, unsigned int VAO2,
    unsigned int VBO2, int type, float positionY)
{
    // Get global view matrix and projection matrix
    int viewLoc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(pGlobal->gView));

    int projectionLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(pGlobal->gProjection));

    // Get global light position and light intensity
    int lightPositionLoc = glGetUniformLocation(program, "lightPosition");
    glUniform4f(lightPositionLoc, pGlobal->gLightPosition.x, pGlobal->gLightPosition.y, pGlobal->gLightPosition.z, 0.0f);

    // Get global thief own color
    int colorLoc = glGetUniformLocation(program, "color");
    glUniform3f(colorLoc, pGlobal->gThiefColor.x, pGlobal->gThiefColor.y, pGlobal->gThiefColor.z);

    // Get global diffusion product
    int diffuseProductLoc = glGetUniformLocation(program, "diffuseProduct");
    glUniform4f(diffuseProductLoc, pGlobal->gDiffuseProduct.x, pGlobal->gDiffuseProduct.y, pGlobal->gDiffuseProduct.z, pGlobal->gDiffuseProduct.w);

    // Get global specular product and shineness
    int specularProductLoc = glGetUniformLocation(program, "specularProduct");
    glUniform4f(specularProductLoc, pGlobal->gSpecularProduct.x, pGlobal->gSpecularProduct.y, pGlobal->gSpecularProduct.z, pGlobal->gSpecularProduct.w);

    int shinenessLoc = glGetUniformLocation(program, "shineness");
    glUniform1f(shinenessLoc, pGlobal->gShineness);

    float pY = positionY;


    glUseProgram(program); //draw 3 vertices as triangles 

    if (leftRotateAngleT != leftAngleT)
        leftRotateAngleT = leftPreviousAngleT += (leftAngleT - leftPreviousAngleT) * 0.1;

    if (rightRotateAngleT != rightAngleT)
        rightRotateAngleT = rightPreviousAngleT += (rightAngleT - rightPreviousAngleT) * 0.1;

    float angle = leftRotateAngleT;


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
        glGenVertexArrays(1, &VAO1);
        glGenBuffers(1, &VBO1);

        glBindVertexArray(VAO1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArm), verticesArm, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //texture attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(VAO1);

        mat4 model = mat4(1.0f);
        model = translate(model, vec3(1.25, pY + 0.3, -.2));
        model = rotate(model, radians(leftRotateAngleT), vec3(0.0f, 0.0f, 1.0f));
        //        model = scale(model, vec3(0.5, 1.5, 0.5));
        model = scale(model, vec3(0.1, 0.3, 0.1));

        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Send global pointer to the objects
        leftForeArm.sendGlobalPtr(pGlobal);

        leftForeArm.thiefDraw(program, VAO2, VBO2, LEFT, angle, pY);
    }
    else {
        glGenVertexArrays(1, &VAO1);
        glGenBuffers(1, &VBO1);

        glBindVertexArray(VAO1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArm), verticesArm, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //texture attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        mat4 model = mat4(1.0f);
        model = translate(model, vec3(1.25, pY + 0.3, .3));
        model = rotate(model, radians(rightRotateAngleT), vec3(0.0f, 0.0f, 1.0f));
        //model = scale(model, vec3(0.5, 1.5, 0.5));
        model = scale(model, vec3(0.1, 0.3, 0.1));

        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(VAO1);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Send global pointer to the objects
        rightForeArm.sendGlobalPtr(pGlobal);

        rightForeArm.thiefDraw(program, VAO2, VBO2, RIGHT, angle, pY);
    }



}

void CArm::setMotion(int pose)
{
    leftPreviousAngle = leftAngle;
    rightPreviousAngle = rightAngle;
    switch (pose) {


    case RED:
        //왼쪽 0, 오른쪽 0
        leftAngle = 0;
        rightAngle = 0;
        break;
    case BLUE:
        //왼쪽 180, 오른쪽 -180
        leftAngle = 180;
        rightAngle = -180;
        break;
    case GREEN:
        //왼쪽 45, 오른쪽 -45
        leftAngle = 45;
        rightAngle = -45;
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

    leftForeArm.setMotion(pose);
    rightForeArm.setMotion(pose);

}

void CArm::setTMotion(int pose)
{
    leftPreviousAngleT = leftAngleT;
    rightPreviousAngleT = rightAngleT;
    switch (pose) {
    case RED:
        //왼쪽 0, 오른쪽 0
        leftAngleT = 0;
        rightAngleT = 0;
        break;
    case BLUE:
        //왼쪽 180, 오른쪽 90
        leftAngleT = 180;
        rightAngleT = -180;
        break;
    case GREEN:
        //왼쪽 180, 오른쪽 180
        leftAngleT = 45;
        rightAngleT = -45;
        break;
    case YELLOW:
        //왼쪽 90, 오른쪽 -90
        leftAngleT = 90;
        rightAngleT = -90;
        break;
    default:
        //RED
        leftAngleT = 0;
        rightAngleT = 0;
        break;
    }

    leftForeArm.setTMotion(pose);
    rightForeArm.setTMotion(pose);
}

void CArm::sendGlobalPtr(CGlobal* pGlobal)
{
    this->pGlobal = pGlobal;
}