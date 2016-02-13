#ifndef ASSIGNMENT_2_H
#define ASSIGNMENT_2_H

#include "Scene.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Material.h"

class Assignment2 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_HAIR,
		GEO_HEAD,
		GEO_EYES,
		GEO_NECK,
		GEO_BODY,
		GEO_ARMS,
		GEO_HANDS,
		GEO_FINGERS,
		GEO_SKIRT,
		GEO_LEGS,
		GEO_SHOES,
		GEO_BALL,
		GEO_QUAD,
		GEO_LIGHTBALL,
		GEO_YELLOWBALL,
		GEO_TREESTEM,
		GEO_SNOWCONE,
		GEO_LEAF,
		GEO_REDCONE,
		GEO_BENCH,
		GEO_LAMPOST,
		GEO_LAMPCONE,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_TOTAL,
	};
public:
	Assignment2();
	~Assignment2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	void RenderMesh(Mesh *mesh, bool enablelight);

	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	float rotateAngle;
	float planet1RevAngle, planet1RotAngle, moon1RotAngle, planet2RevAngle, wingRotation;

	bool reachAngle, reachAngle2, reachAngle3;

	Camera2 camera;

	MS modelStack, viewStack, projectionStack;

	Light light[1];

	float rainpositionx[500];
	float rainpositiony[500];
	float rainpositionz[500];
};

#endif