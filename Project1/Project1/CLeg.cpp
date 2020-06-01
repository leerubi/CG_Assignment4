#include "CLeg.h"
using namespace glm;

float verticesLeg[] = {
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



CLeg::CLeg()
{
    passCount = 1;

    rightDirection = 0;
    leftDirection = 0;

    rightAngle = -45;
    leftAngle = -45;

    startTick = GetTickCount64();

    rightCircuit = false;

}
void CLeg::playerDraw(GLuint program, unsigned int VAO, unsigned int VBO, int type, 
    float positionX, float positionY, float angle, bool direction)
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
    float pY = positionY;


    glUseProgram(program); //draw 3 vertices as triangles 


    float leftAngle, rightAngle;
    leftAngle = -angle;
    rightAngle = angle;

    if (type == LEFT) {

        setLeftAngle(direction, leftAngle);


        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLeg), verticesLeg, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);





        mat4 model2 = mat4(1.0f);
        model2 = translate(model2, vec3(pX, pY - 0.3, -.2));
        model2 = rotate(model2, radians(leftAngle), vec3(0.0f, 0.0f, 1.0f));


        mat4 model = model2;
        model = translate(model, vec3(0.0, -0.3, 0.0));
        model = rotate(model, radians(this->leftAngle), vec3(0.0f, 0.0f, 1.0f));
        //model = scale(model, vec3(0.5, 1.5, 0.5));
        model = scale(model, vec3(0.1, 0.3, 0.1));

        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));


        glBindVertexArray(VAO);



        glDrawArrays(GL_TRIANGLES, 0, 36);

    }
    else {

        setRightAngle(direction, rightAngle);


        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLeg), verticesLeg, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);



        mat4 model2 = mat4(1.0f);
        model2 = translate(model2, vec3(pX, pY - 0.3, .3));
        model2 = rotate(model2, radians(rightAngle), vec3(0.0f, 0.0f, 1.0f));


        mat4 model = model2;
        model = translate(model, vec3(0.0, -0.3, 0.0));
        model = rotate(model, radians(this->rightAngle), vec3(0.0f, 0.0f, 1.0f));
        //model = scale(model, vec3(0.5, 1.5, 0.5));
        model = scale(model, vec3(0.1, 0.3, 0.1));



        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }


}

void CLeg::thiefDraw(GLuint program, unsigned int VAO, unsigned int VBO, int type, 
    float positionY, float angle, bool direction)
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


    float leftAngle, rightAngle;
    leftAngle = -angle;
    rightAngle = angle;






    if (type == LEFT) {

        setLeftAngle(direction, leftAngle);


        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLeg), verticesLeg, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // noraml attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);


   


        mat4 model2 = mat4(1.0f);
        model2 = translate(model2, vec3(1.25, pY - 0.3, -.2));
        model2 = rotate(model2, radians(leftAngle), vec3(0.0f, 0.0f, 1.0f));


        mat4 model = model2;
        model = translate(model, vec3(0.0, -0.3, 0.0));
        model = rotate(model, radians(this->leftAngle), vec3(0.0f, 0.0f, 1.0f));
        //model = scale(model, vec3(0.5, 1.5, 0.5));
        model = scale(model, vec3(0.1, 0.3, 0.1));



        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

    

        glBindVertexArray(VAO);



        glDrawArrays(GL_TRIANGLES, 0, 36);


    }
    else {

        setRightAngle(direction, rightAngle);




        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLeg), verticesLeg, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        mat4 model2 = mat4(1.0f);
        model2 = translate(model2, vec3(1.25, pY-0.3, .3));
        model2 = rotate(model2, radians(rightAngle), vec3(0.0f, 0.0f, 1.0f));


        mat4 model = model2;
        model = translate(model, vec3(0.0, -0.3, 0.0));
        model = rotate(model, radians(this->rightAngle), vec3(0.0f, 0.0f, 1.0f));
        //model = scale(model, vec3(0.5, 1.5, 0.5));
        model = scale(model, vec3(0.1, 0.3, 0.1));


        int modelLoc = glGetUniformLocation(program, "model");
        
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

      

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void CLeg::setLeftAngle(bool thighDirection, float thighAngle)
{
    thighDirection = !thighDirection;

    if (thighDirection && thighAngle < 0) {
        //�߰����� �ڷ� ������ ����
        //�ִ�� ������ ���� ������ �����ϴ� �κ�
        leftDirection = 1;
    }

    if (thighDirection && thighAngle > 0) {
        //�տ��� �߰����� ������ ����
        //�߰����� ���� ����
        leftDirection = 2;
    }

    if (!thighDirection && thighAngle < 0) {
        //�ڿ��� �߰����� ������ ����
        //�߰����� ���� ����
        leftDirection = 3;
    }

    if (!thighDirection && thighAngle > 0) {
        //�߰����� ������ ������ ����
        //�ִ�� ������ ���� ������ �����ϴ� �κ�.
        leftDirection = 4;
    }


    switch (leftDirection) {
    case 1:
        startTick = GetTickCount64();
        leftAngle = -((startTick - currentTick) / (VELORATE - ADJUST * passCount));
        leftCircuit = true;
        break;
    case 2:
        currentTick = GetTickCount64();
        leftAngle = -45 + ((currentTick - startTick) / (VELORATE - ADJUST * passCount));

        break;
    case 3:
        currentTick = GetTickCount64();
        //startTick = GetTickCount64();
        leftAngle = -45 - ((currentTick - startTick) / (VELORATE - ADJUST * passCount));
        break;
    case 4:
        startTick = GetTickCount64();
        leftAngle = -90 + ((startTick - currentTick) / (VELORATE - ADJUST * passCount));
        //leftCircuit = true;
        break;
    default:
        break;
    }
}

void CLeg::setRightAngle(bool thighDirection, float thighAngle)
{
    if (thighDirection && thighAngle < 0) {
        //�߰����� �ڷ� ������ ����
        //�ִ�� ������ ���� ������ �����ϴ� �κ�
        rightDirection = 1;
    }

    if (thighDirection && thighAngle > 0) {
        //�տ��� �߰����� ������ ����
        //�߰����� ���� ����
        rightDirection = 2;
    }

    if (!thighDirection && thighAngle < 0) {
        //�ڿ��� �߰����� ������ ����
        //�߰����� ���� ����
        rightDirection = 3;
    }

    if (!thighDirection && thighAngle > 0) {
        //�߰����� ������ ������ ����
        //�ִ�� ������ ���� ������ �����ϴ� �κ�.
        rightDirection = 4;
    }



    switch (rightDirection) {
    case 1:
        startTick = GetTickCount64();
        rightAngle = -((startTick - currentTick) / (VELORATE - ADJUST * passCount));
        break;
    case 2:
        currentTick = GetTickCount64();
        rightAngle = -45 + ((currentTick - startTick) / (VELORATE - ADJUST * passCount)) - 45 * rightCircuit;

        break;
    case 3:
        startTick = GetTickCount64();
        rightAngle = -((startTick - currentTick) / (VELORATE - ADJUST * passCount));
        break;
    case 4:
        currentTick = GetTickCount64();
        rightAngle = -90 + ((currentTick - startTick) / (VELORATE - ADJUST * passCount));
        rightCircuit = true;
        break;
    default:
        break;
    }
}

void CLeg::sendGlobalPtr(CGlobal* pGlobal)
{
    this->pGlobal = pGlobal;

}

