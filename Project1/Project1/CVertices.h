#pragma once
class CVertices
{
private:
	float* vertices;
	int verticesSize;
public:
	CVertices();
	
	//normal
	float* getNormalVertices();

	//red wall
	float* getRedWallVertices();

	//green wall
	float* getGreenWallVertices();

	//blue wall
	float* getBlueWallVertices();

	//yellow wall
	float* getYellowWallVerticies();

	int getVerticesSize();

};

