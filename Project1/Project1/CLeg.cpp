#include "CLeg.h"
using namespace glm;
#include "stb_images.h"

float verticesLeg[] = {
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
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,    0.0f, 1.0f
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
    glUniform4f(lightPositionLoc, pGlobal->dirLightPosition.x, pGlobal->dirLightPosition.y, pGlobal->dirLightPosition.z, 0.0f);

    // Get global player own color
    int colorLoc = glGetUniformLocation(program, "color");
    glUniform3f(colorLoc, pGlobal->gPlayerColor.x, pGlobal->gPlayerColor.y, pGlobal->gPlayerColor.z);

    // Get global diffusion product
    int diffuseProductLoc = glGetUniformLocation(program, "diffuseProduct");
    glUniform4f(diffuseProductLoc, pGlobal->diffuseProduct.x, pGlobal->diffuseProduct.y, pGlobal->diffuseProduct.z, pGlobal->diffuseProduct.w);

    // Get global specular product and shineness
    int specularProductLoc = glGetUniformLocation(program, "specularProduct");
    glUniform4f(specularProductLoc, pGlobal->specularProduct.x, pGlobal->specularProduct.y, pGlobal->specularProduct.z, pGlobal->specularProduct.w);

    int shinenessLoc = glGetUniformLocation(program, "shineness");
    glUniform1f(shinenessLoc, pGlobal->shineness);

    float pX = positionX;
    float pY = positionY;


    glUseProgram(program); //draw 3 vertices as triangles 


    float leftAngle, rightAngle;
    leftAngle = -angle;
    rightAngle = angle;





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

        setLeftAngle(direction, leftAngle);


        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLeg), verticesLeg, GL_STATIC_DRAW);

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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //texture attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);



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
    glUniform4f(lightPositionLoc, pGlobal->dirLightPosition.x, pGlobal->dirLightPosition.y, pGlobal->dirLightPosition.z, 0.0f);

    // Get global thief own color
    int colorLoc = glGetUniformLocation(program, "color");
    glUniform3f(colorLoc, pGlobal->gThiefColor.x, pGlobal->gThiefColor.y, pGlobal->gThiefColor.z);

    // Get global diffusion product
    int diffuseProductLoc = glGetUniformLocation(program, "diffuseProduct");
    glUniform4f(diffuseProductLoc, pGlobal->diffuseProduct.x, pGlobal->diffuseProduct.y, pGlobal->diffuseProduct.z, pGlobal->diffuseProduct.w);

    // Get global specular product and shineness
    int specularProductLoc = glGetUniformLocation(program, "specularProduct");
    glUniform4f(specularProductLoc, pGlobal->specularProduct.x, pGlobal->specularProduct.y, pGlobal->specularProduct.z, pGlobal->specularProduct.w);

    int shinenessLoc = glGetUniformLocation(program, "shineness");
    glUniform1f(shinenessLoc, pGlobal->shineness);


    float pY = positionY;


    glUseProgram(program); //draw 3 vertices as triangles 


    float leftAngle, rightAngle;
    leftAngle = -angle;
    rightAngle = angle;

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

        setLeftAngle(direction, leftAngle);


        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLeg), verticesLeg, GL_STATIC_DRAW);

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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //texture attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        mat4 model2 = mat4(1.0f);
        model2 = translate(model2, vec3(1.25, pY - 0.3, .3));
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
        //중간에서 뒤로 접히는 구간
        //최대로 펴져서 이제 접히기 시작하는 부분
        leftDirection = 1;
    }

    if (thighDirection && thighAngle > 0) {
        //앞에서 중간으로 펴지는 구간
        //중간정도 펴진 상태
        leftDirection = 2;
    }

    if (!thighDirection && thighAngle < 0) {
        //뒤에서 중간으로 접히는 구간
        //중간정도 접힌 상태
        leftDirection = 3;
    }

    if (!thighDirection && thighAngle > 0) {
        //중간에서 앞으로 펴지는 구간
        //최대로 접혀서 이제 펴지기 시작하는 부분.
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
        //중간에서 뒤로 접히는 구간
        //최대로 펴져서 이제 접히기 시작하는 부분
        rightDirection = 1;
    }

    if (thighDirection && thighAngle > 0) {
        //앞에서 중간으로 펴지는 구간
        //중간정도 펴진 상태
        rightDirection = 2;
    }

    if (!thighDirection && thighAngle < 0) {
        //뒤에서 중간으로 접히는 구간
        //중간정도 접힌 상태
        rightDirection = 3;
    }

    if (!thighDirection && thighAngle > 0) {
        //중간에서 앞으로 펴지는 구간
        //최대로 접혀서 이제 펴지기 시작하는 부분.
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

