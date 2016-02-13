#ifndef _ASSIGNMENT_1_H
#define _ASSIGNMENT_1_H

#include "Scene.h"

class Assignment1 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,	
		GEO_TRIANGLE_2 = 1,
		GEO_TRIANGLE_3 = 2,
		GEO_DOOR = 3,
		GEO_BIRD = 4,
		GEO_CLOUD = 5,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};


	float rotateAngle;
	float translateX;
	float translateX2;
	float translateY;
	float scaleAll;
	float rainpositionx[100];
	float rainpositiony[100];

public:
	Assignment1();
	~Assignment1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
};

#endif