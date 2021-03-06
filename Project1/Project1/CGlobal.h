#pragma once
#include <glm/glm.hpp>
#include "global.h"
using namespace glm;


class CGlobal
{
public:
	mat4 gView;
	mat4 gProjection;

	vec4 dirLightPosition;
	vec4 diffuseProduct;
	vec4 specularProduct;

	vec4 pointLightPositions[50];
	vec4 pointDiffuseProducts[50];
	vec4 pointSpecularProducts[50];

	int shadingType = GOURAUD;

	int diffuseType = DIFFUSEON;

	int normalType = NORMALOFF;

	float shineness;
	vec3 gPlayerColor;
	vec3 gThiefColor;

	CGlobal();
};

