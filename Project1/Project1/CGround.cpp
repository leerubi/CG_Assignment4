#include "CGround.h"
using namespace glm;

float verticesGround[] = {
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


CGround::CGround()
{
}

void CGround::groundDraw(GLuint program, unsigned int VAO[], unsigned int VBO[])
{
    glUseProgram(program);

    glGenVertexArrays(1, &VAO[21]);
    glGenBuffers(1, &VBO[21]);

    glBindVertexArray(VAO[21]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[21]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesGround), verticesGround, GL_STATIC_DRAW);
   
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



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

    // Get global shading type
    int shadingTypeLoc = glGetUniformLocation(program, "shadingType");
    glUniform1i(shadingTypeLoc, pGlobal->shadingType);



    //vec4 lightPosition = this->lightPosition;
    //int lightPositionLoc = glGetUniformLocation(program, "lightPosition");
    //glUniform4f(lightPositionLoc, lightPosition.x, lightPosition.y, lightPosition.z, 0.0f);

    glBindVertexArray(VAO[21]);

    mat4 model = mat4(1.0f);
    model = translate(model, vec3(0.0, -1.5, 0.0));
    model = scale(model, vec3(10, 0.1, 2));
    //model = scale(model, vec3(1.8, 4.0, 1.8));
    int modelLoc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CGround::sendGlobalPtr(CGlobal* pGlobal)
{
    this->pGlobal = pGlobal;

}
