#ifndef SP2SCENE_H
#define SP2SCENE_H

#include "Scene.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"



class Sp2Scene : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_RING,
		GEO_SPHERE,
		GEO_PLANETS,
		GEO_MOONIA,
		GEO_PLANET1,
		GEO_MOON1A,
		GEO_RING1,
		GEO_LIGHTBALL,
		GEO_MERCURY,
		GEO_URANUS,
		GEO_HEMISHERE,
		GEO_CONE,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_MODEL1,
		GEO_LAND,
		GEO_AIR,
		GEO_TEXT,
		GEO_DEADTREE,
		GEO_HEAD,
		GEO_ICY_LEFT,
		GEO_ICY_RIGHT,
		GEO_ICY_TOP,
		GEO_ICY_BOTTOM,
		GEO_ICY_FRONT,
		GEO_ICY_BACK,
		GEO_ICYHELL_LEFT,
		GEO_ICYHELL_RIGHT,
		GEO_ICYHELL_TOP,
		GEO_ICYHELL_BOTTOM,
		GEO_ICYHELL_FRONT,
		GEO_ICYHELL_BACK,
		GEO_BLOODY_LEFT,
		GEO_BLOODY_RIGHT,
		GEO_BLOODY_TOP,
		GEO_BLOODY_BOTTOM,
		GEO_BLOODY_FRONT,
		GEO_BLOODY_BACK,
		GEO_OBJECT,
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
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
public:
	Sp2Scene();
	~Sp2Scene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	void RenderMesh(Mesh *mesh, bool enablelight);
	void RenderSkybox();
	void RenderText(Mesh * mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh * mesh, std::string text, Color color, float size, float x, float y);

	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	float rotateAngle;
	float planet1RevAngle, planet1RotAngle, moon1RotAngle;
	int framerate;

	float rainpositionx[1000];
	float rainpositiony[1000];
	float rainpositionz[1000];

	int treex[50];
	int treez[50];

	int tempx[50];
	int tempz[50];

	float translateY;
	float translateX;
	float translateZ;

	static bool test4;
	static bool test5;

	Vector3 treeposition[150];


	Camera3 camera;

	MS modelStack, viewStack, projectionStack;

	Light light[1];
};

#endif