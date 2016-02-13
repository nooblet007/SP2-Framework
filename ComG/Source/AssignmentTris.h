#ifndef _ASSIGNMENT_TRIS_H
#define _ASSIGNMENT_TRIS_H

#include "Scene.h"

class AssignmentTris : public Scene
{
	enum GEOMETRY_TYPE
	{
		
		GEO_TRIANGLE_1 = 0, //sun
		GEO_TRIANGLE_2 = 1, //grass
		GEO_TRIANGLE_3 = 2, //black square
		GEO_DOOR = 3,
		GEO_SQUARE = 4, //lvl up
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};


	float rotateAngle;
	float translateX;
	float translateY;
	float scaleAll;

public:
	AssignmentTris();
	~AssignmentTris();

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