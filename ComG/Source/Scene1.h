#ifndef SCENE_1_H
#define SCENE_1_H

#include "Scene.h"

class Scene1 : public Scene
{
public:
	Scene1();
	~Scene1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		GEO_TRIANGLE_2 = 1, 
		GEO_TRIANGLE_3 = 2, 
		NUM_GEOMETRY,
	};
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;

	unsigned m_vertexArrayID1;
	unsigned m_vertexBuffer1[NUM_GEOMETRY];
	unsigned m_colorBuffer1[NUM_GEOMETRY];
	unsigned m_programID1;

	unsigned m_vertexArrayID2;
	unsigned m_vertexBuffer2[NUM_GEOMETRY];
	unsigned m_colorBuffer2[NUM_GEOMETRY];
	unsigned m_programID2;

};

#endif