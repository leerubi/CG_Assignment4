#pragma once
#include <glm/glm.hpp>
using namespace glm;


class CGlobal
{
public:
	mat4 gView;
	mat4 gProjection;

	vec4 gLightPosition;
	vec4 gDiffuseProduct;
	vec4 gSpecularProduct;
	float gShineness;

	vec3 gPlayerColor;
	vec3 gThiefColor;

	CGlobal();
};

