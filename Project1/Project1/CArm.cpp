#include "CArm.h"
using namespace glm;

float verticesArm[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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


    if (type == LEFT) {
        glGenVertexArrays(1, &VAO1);
        glGenBuffers(1, &VBO1);

        glBindVertexArray(VAO1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArm), verticesArm, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(VAO1);
        
        
        mat4 model = mat4(1.0f);
        model = translate(model, vec3(pX, positionY + 0.3, -0.2));
        model = rotate(model, radians(leftRotateAngle), vec3(0.0f, 0.0f,1.0f));
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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);



        mat4 model = mat4(1.0f);
        model = translate(model, vec3(pX, positionY+0.3, 0.3));
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


    if (type == LEFT) {
        glGenVertexArrays(1, &VAO1);
        glGenBuffers(1, &VBO1);

        glBindVertexArray(VAO1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArm), verticesArm, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
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
        //哭率 0, 坷弗率 0
        leftAngle = 0;
        rightAngle = 0;
        break;
    case BLUE:
        //哭率 180, 坷弗率 -180
        leftAngle = 180;
        rightAngle = -180;
        break;
    case GREEN:
        //哭率 45, 坷弗率 -45
        leftAngle = 45;
        rightAngle = -45;
        break;
    case YELLOW:
        //哭率 90, 坷弗率 -90
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
        //哭率 0, 坷弗率 0
        leftAngleT = 0;
        rightAngleT = 0;
        break;
    case BLUE:
        //哭率 180, 坷弗率 90
        leftAngleT = 180;
        rightAngleT = -180;
        break;
    case GREEN:
        //哭率 180, 坷弗率 180
        leftAngleT = 45;
        rightAngleT = -45;
        break;
    case YELLOW:
        //哭率 90, 坷弗率 -90
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