#include "CCharacter.h"
using namespace glm;
#include "stb_images.h"

float verticesCharacter[] = {
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
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

CCharacter::CCharacter()
{
    playerPositionX = -1.5f;
    playerPositionY = -0.5f;

    theifPositionX = 1.5f;
    theifPositionY = -0.5f;

}

void CCharacter::playerDraw(GLuint program, unsigned int VAO[], unsigned int VBO[])
{


    glUseProgram(program);

    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &VBO[0]);

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCharacter), verticesCharacter, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);



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


        glUniform1i(glGetUniformLocation(program, "texture1"), 0); // 流立 汲沥


        textureLoad = true;
    }




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

    // Set the position
    mat4 model = mat4(1.0f);
    model = translate(model, vec3(playerPositionX, playerPositionY, 0.0));
    //model = scale(model, vec3(1.8, 4.0, 1.8));
    model = scale(model, vec3(0.36, 0.8, 0.36));
    int modelLoc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Send global pointer to the objects
    face.sendGlobalPtr(pGlobal);
    leftArm.sendGlobalPtr(pGlobal);
    rightArm.sendGlobalPtr(pGlobal);
    leftThigh.sendGlobalPtr(pGlobal);
    rightThigh.sendGlobalPtr(pGlobal);

    face.drawPlayer(program, playerPositionX, playerPositionY, VAO[1], VBO[1]);
    leftArm.playerDraw(program, VAO[2], VBO[2], VAO[3], VBO[3], LEFT, playerPositionX, playerPositionY);
    rightArm.playerDraw(program, VAO[4], VBO[4], VAO[5], VBO[5], RIGHT, playerPositionX, playerPositionY);
    leftThigh.playerDraw(program, VAO[6], VBO[6], VAO[7], VBO[7], LEFT, playerPositionX, playerPositionY);
    rightThigh.playerDraw(program, VAO[8], VBO[8], VAO[9], VBO[9], RIGHT, playerPositionX, playerPositionY);


}

void CCharacter::thiefDraw(GLuint program, unsigned int VAO[], unsigned int VBO[])
{
    glUseProgram(program);
    glGenVertexArrays(1, &VAO[10]);
    glGenBuffers(1, &VBO[10]);

    glBindVertexArray(VAO[10]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[10]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCharacter), verticesCharacter, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);




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


        glUniform1i(glGetUniformLocation(program, "texture1"), 0); // 流立 汲沥


        textureLoad = true;
    }




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

    mat4 model = mat4(1.0f);
    model = translate(model, vec3(1.25, theifPositionY, 0.0));
    //model = scale(model, vec3(1.8, 4.0, 1.8));
    model = scale(model, vec3(0.36, 0.8, 0.36));
    int modelLoc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

    glBindVertexArray(VAO[10]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Send global pointer to the objects
    face.sendGlobalPtr(pGlobal);
    leftArm.sendGlobalPtr(pGlobal);
    rightArm.sendGlobalPtr(pGlobal);
    leftThigh.sendGlobalPtr(pGlobal);
    rightThigh.sendGlobalPtr(pGlobal);


    face.drawThief(program, theifPositionY, VAO[11], VBO[11]);
    leftArm.thiefDraw(program, VAO[12], VBO[12], VAO[13], VBO[13], LEFT, theifPositionY);
    rightArm.thiefDraw(program, VAO[14], VBO[14], VAO[15], VBO[15], RIGHT, theifPositionY);
    leftThigh.thiefDraw(program, VAO[16], VBO[16], VAO[17], VBO[17], LEFT, theifPositionY);
    rightThigh.thiefDraw(program, VAO[18], VBO[18], VAO[19], VBO[19], RIGHT, theifPositionY);

}

void CCharacter::setPlayerPose(int pose)
{
    this->playerPose = pose;
    leftArm.setMotion(pose);
    rightArm.setMotion(pose);
}

void CCharacter::setPlayerPositionX(float positionX)
{
    this->playerPositionX = positionX;
}

void CCharacter::setPlayerPositionY(float positionY)
{
    this->playerPositionY = positionY;

}

float CCharacter::getPlayerPositionX()
{
    return this->playerPositionX;
}

float CCharacter::getPlayerPositionY()
{
    return this->playerPositionY;
}


int CCharacter::getPlayerPose()
{
    return this->playerPose;
}

void CCharacter::setThiefPositionX(float positionX)
{
    this->theifPositionX = positionX;
}

void CCharacter::setThiefPositionY(float positionY)
{
    this->theifPositionY = positionY;
}

float CCharacter::getThiefPositionX()
{
    return this->theifPositionX;
}

float CCharacter::getThiefPositionY()
{
    return this->theifPositionY;
}

void CCharacter::setThiefPose(int pose)
{
    this->theifPose = pose;
    leftArm.setTMotion(pose);
    rightArm.setTMotion(pose);
}

int CCharacter::getThiefPose()
{
    return this->theifPose;
}

void CCharacter::sendGlobalPtr(CGlobal* pGlobal)
{
    this->pGlobal = pGlobal;
}

