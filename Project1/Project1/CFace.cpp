#include "CFace.h"
using namespace glm;
CFace::CFace()
{
    radius = 1.0f;

}

void CFace::drawPlayer(GLuint program, float positionX, float positionY, unsigned VAO, unsigned VBO)
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

    for (int i = 0; i <= 80; i++) {
        float angle = 4.5f * i;
        float angle2 = 4.5f * (i+1);

        //����
        //x, y, z
        vertices.push_back(radius * cos(radians(angle)));
        vertices.push_back(1.0f);
        vertices.push_back(radius * sin(radians(angle)));

        //color
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);
        vertices.push_back(0.0f);

        //color
        vertices.push_back(1.0f);
        vertices.push_back(.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(radius * cos(radians(angle2)));
        vertices.push_back(1.0f);
        vertices.push_back(radius * sin(radians(angle2)));

        //color
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);

        
        //�Ʒ���
        vertices.push_back(radius * cos(radians(angle)));
        vertices.push_back(0.0f);
        vertices.push_back(radius * sin(radians(angle)));

        //color
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);

        //color
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(radius * cos(radians(angle2)));
        vertices.push_back(0.0f);
        vertices.push_back(radius * sin(radians(angle2)));

        //color
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);


     

        //���1
        vertices.push_back(radius * cos(radians(angle2)));
        vertices.push_back(0.0f);
        vertices.push_back(radius * sin(radians(angle2)));

        //color
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(radius * cos(radians(angle2)));
        vertices.push_back(1.0f);
        vertices.push_back(radius * sin(radians(angle2)));

        //color
        vertices.push_back(1.0f);
        vertices.push_back(.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(radius * cos(radians(angle)));
        vertices.push_back(1.0f);
        vertices.push_back(radius * sin(radians(angle)));

        //color
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);

        //���2
        //x y z
        vertices.push_back(radius* cos(radians(angle)));
        vertices.push_back(1.0f);
        vertices.push_back(radius* sin(radians(angle)));

        //color
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(radius* cos(radians(angle)));
        vertices.push_back(0.0f);
        vertices.push_back(radius* sin(radians(angle)));

        //color
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(radius* cos(radians(angle2)));
        vertices.push_back(0.0f);
        vertices.push_back(radius* sin(radians(angle2)));

        //color
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);

    }

    float* verticeArr = &vertices[0];




    glUseProgram(program); //draw 3 vertices as triangles 

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 23328, verticeArr, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO);

    mat4 model = mat4(1.0f);
    model = translate(model, vec3(positionX, positionY + 0.4, 0.0));
    model = scale(model, vec3(0.1, 0.25, 0.1));
    int modelLoc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 960);


}

void CFace::drawThief(GLuint program, float positionY, unsigned VAO, unsigned VBO)
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

    for (int i = 0; i <= 80; i++) {
        float angle = 4.5f * i;
        float angle2 = 4.5f * (i + 1);

        //����
        //x, y, z
        verticesThief.push_back(radius * cos(radians(angle)));
        verticesThief.push_back(1.0f);
        verticesThief.push_back(radius * sin(radians(angle)));

        //color
        verticesThief.push_back(0.0f);
        verticesThief.push_back(0.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(0.0f);
        verticesThief.push_back(1.0f);
        verticesThief.push_back(0.0f);

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(radius * cos(radians(angle2)));
        verticesThief.push_back(1.0f);
        verticesThief.push_back(radius * sin(radians(angle2)));

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);


        //�Ʒ���
        verticesThief.push_back(radius * cos(radians(angle)));
        verticesThief.push_back(0.0f);
        verticesThief.push_back(radius * sin(radians(angle)));

        //color
        verticesThief.push_back(0.0f);
        verticesThief.push_back(0.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(0.0f);
        verticesThief.push_back(0.0f);
        verticesThief.push_back(0.0f);

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(radius * cos(radians(angle2)));
        verticesThief.push_back(0.0f);
        verticesThief.push_back(radius * sin(radians(angle2)));

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);




        //���1
        verticesThief.push_back(radius * cos(radians(angle2)));
        verticesThief.push_back(0.0f);
        verticesThief.push_back(radius * sin(radians(angle2)));

        //color
        verticesThief.push_back(0.0f);
        verticesThief.push_back(0.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(radius * cos(radians(angle2)));
        verticesThief.push_back(1.0f);
        verticesThief.push_back(radius * sin(radians(angle2)));

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(radius * cos(radians(angle)));
        verticesThief.push_back(1.0f);
        verticesThief.push_back(radius * sin(radians(angle)));

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);

        //���2
        //x y z
        verticesThief.push_back(radius * cos(radians(angle)));
        verticesThief.push_back(1.0f);
        verticesThief.push_back(radius * sin(radians(angle)));

        //color
        verticesThief.push_back(0.0f);
        verticesThief.push_back(0.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(radius * cos(radians(angle)));
        verticesThief.push_back(0.0f);
        verticesThief.push_back(radius * sin(radians(angle)));

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(radius * cos(radians(angle2)));
        verticesThief.push_back(0.0f);
        verticesThief.push_back(radius * sin(radians(angle2)));

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);

    }

    float* verticeArr = &verticesThief[0];


    glUseProgram(program); //draw 3 vertices as triangles 

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 23328, verticeArr, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindVertexArray(VAO);


    mat4 model = mat4(1.0f);
    model = translate(model, vec3(1.25, positionY + 0.4, 0.0));
    model = scale(model, vec3(0.1, 0.25, 0.1));
    int modelLoc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 960);
}

void CFace::sendGlobalPtr(CGlobal* pGlobal)
{
    this->pGlobal = pGlobal;
}
