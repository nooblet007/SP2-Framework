#include "Sp2Scene.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "Utility.h"
#include "LoadTGA.h"
#include "LoadOBJ.h"

bool Camera3::test = false;
bool Camera3::test2 = false;
bool Camera3::test3 = false;
bool Sp2Scene::test4 = false;
bool Sp2Scene::test5 = false;

Sp2Scene::Sp2Scene()
{
}

Sp2Scene::~Sp2Scene()
{
}

void Sp2Scene::Init()
{
	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glDisable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutOff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	glUseProgram(m_programID);

	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 2;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutOff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutOff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);



	//variable to rotate geometry
	rotateAngle = 0;
	planet1RotAngle = planet1RevAngle = moon1RotAngle = 0;

	//Initialize camera settings
	camera.Init(Vector3(-170, 5, -230), Vector3(0, 5, 0), Vector3(0, 1, 0));


	meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 10, 40);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 10, 20);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1000, 1000);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//snow_dn.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1000, 1000);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//snow_up.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1000, 1000);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//snow_dn.tga");
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1000, 1000);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//snow_ft.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1000, 1000);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//snow_bk.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1000, 1000);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//snow_lf.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1000, 1000);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//snow_rt.tga");
	meshList[GEO_MODEL1] = MeshBuilder::GenerateOBJ("model1", "OBJ//chair.obj");
	meshList[GEO_MODEL1]->textureID = LoadTGA("Image//chair.tga");
	meshList[GEO_LAND] = MeshBuilder::GenerateOBJ("land", "OBJ//landvehicle.obj");
	meshList[GEO_LAND]->textureID = LoadTGA("Image//landvehicleUV3.tga");
	meshList[GEO_AIR] = MeshBuilder::GenerateOBJ("air", "OBJ//airvehicle.obj");
	meshList[GEO_AIR]->textureID = LoadTGA("Image//uvairvehicletexture.tga");
	meshList[GEO_DEADTREE] = MeshBuilder::GenerateOBJ("deadtree", "OBJ//deadtree.obj");
	meshList[GEO_DEADTREE]->textureID = LoadTGA("Image//deadtree.tga");
	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(1, 1, 0), 20);
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_OBJECT] = MeshBuilder::GenerateOBJ("tricker", "OBJ//Tricker.obj");
	meshList[GEO_OBJECT]->textureID = LoadTGA("Image//trickeruv.tga");

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 2000.0f);
	projectionStack.LoadMatrix(projection);

	for (int i = 0; i < 1000; i++)
	{
		rainpositionx[i] = rand() % 998 - 499;
		rainpositiony[i] = rand() % 998 - 499;
		rainpositionz[i] = rand() % 998 - 499;
	}

	for (int i = 0; i < 50; ++i)
	{
		treex[i] = rand() % 980 - 490;
		treez[i] = rand() % 980 - 490;
	}


	translateY = 0;
	translateX = 0;
	translateX = 0;
}

static float LSPEED = 10.f;
static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Sp2Scene::Update(double dt)
{
	camera.Update(dt);
	for (int i = 0; i < 50; ++i)
	{
		if (camera.checkcollisionwithObject(Vector3(treex[i], 0, treez[i]), 20, 40, 20) == true)
		{
			camera.position = camera.prevPosition;
			meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1000, 1000);
			meshList[GEO_TOP]->textureID = LoadTGA("Image//hell_up.tga");
			meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1000, 1000);
			meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//hell_dn.tga");
			meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1000, 1000);
			meshList[GEO_FRONT]->textureID = LoadTGA("Image//hell_ft.tga");
			meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1000, 1000);
			meshList[GEO_BACK]->textureID = LoadTGA("Image//hell_bk.tga");
			meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1000, 1000);
			meshList[GEO_LEFT]->textureID = LoadTGA("Image//hell_lf.tga");
			meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1000, 1000);
			meshList[GEO_RIGHT]->textureID = LoadTGA("Image//hell_rt.tga");

			meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("sphere", Color(0, 0, 0), 10, 40);
			light[0].color.Set(0, 0, 0);
			for (int i = 0; i < 1000; i++)
			{
				rainpositiony[i] -= (float)(200 * dt);
			}
		}
	}

	if (camera.checkcollisionwithTricker(Vector3(0, 0, -100), 7, 7, 7))
	{
		camera.position = camera.prevPosition;
		meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_TOP]->textureID = LoadTGA("Image//icyhell_up.tga");
		meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//icyhell_dn.tga");
		meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_FRONT]->textureID = LoadTGA("Image//icyhell_ft.tga");
		meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_BACK]->textureID = LoadTGA("Image//icyhell_bk.tga");
		meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_LEFT]->textureID = LoadTGA("Image//icyhell_lf.tga");
		meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_RIGHT]->textureID = LoadTGA("Image//icyhell_rt.tga");
		meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("sphere", Color(0.5, 0.5, 0.5), 10, 40);
		meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(0.5, 0.5, 0.5), 10, 20);
		light[0].color.Set(0.5, 0.5, 0.5);

		meshList[GEO_OBJECT] = MeshBuilder::GenerateOBJ("tricker", "OBJ//sword.obj");
		meshList[GEO_OBJECT]->textureID = LoadTGA("Image//SwordUV.tga");
	}

	if (camera.checkcollisionwithTricker(Vector3(-80, 0, -50), 7, 7, 7))
	{
		camera.position = camera.prevPosition;
		meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_TOP]->textureID = LoadTGA("Image//blood_up.tga");
		meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//blood_dn.tga");
		meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_FRONT]->textureID = LoadTGA("Image//blood_ft.tga");
		meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_BACK]->textureID = LoadTGA("Image//blood_bk.tga");
		meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_LEFT]->textureID = LoadTGA("Image//blood_lf.tga");
		meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_RIGHT]->textureID = LoadTGA("Image//blood_rt.tga");

		meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 10, 40);
		meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 0, 0), 10, 20);

		meshList[GEO_OBJECT] = MeshBuilder::GenerateOBJ("tricker", "OBJ//Rock.obj");
		meshList[GEO_OBJECT]->textureID = LoadTGA("Image//chair.tga");

		light[0].color.Set(1, 0, 0);
		for (int i = 0; i < 1000; i++)
		{
			rainpositiony[i] -= (float)(100 * dt);
		}
		Camera3::test2 = false;
		Camera3::test = false;
		Camera3::test3 = true;
		Sp2Scene::test4 = false;
	}

	if (camera.checkcollisionwithTricker(Vector3(40, 100, 90), 7, 7, 7))
	{
		camera.position = camera.prevPosition;
		meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_TOP]->textureID = LoadTGA("Image//snow_up.tga");
		meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//snow_dn.tga");
		meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_FRONT]->textureID = LoadTGA("Image//snow_ft.tga");
		meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_BACK]->textureID = LoadTGA("Image//snow_bk.tga");
		meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_LEFT]->textureID = LoadTGA("Image//snow_lf.tga");
		meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_RIGHT]->textureID = LoadTGA("Image//snow_rt.tga");

		meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 10, 40);
		light[0].color.Set(0, 0, 0);
		for (int i = 0; i < 1000; i++)
		{
			rainpositiony[i] -= (float)(200 * dt);
		}

		Camera3::test2 = false;
		Camera3::test = false;
		Camera3::test3 = false;
		Sp2Scene::test4 = true;

	}

	if (camera.checkcollisionwithTricker(Vector3(-150, 50, -200), 30, 5, 40))
	{
		Camera3::test2 = false;
		Camera3::test = false;
		Camera3::test3 = false;
		Sp2Scene::test4 = false;
		Sp2Scene::test5 = true;
	}

	if (Application::IsKeyPressed('1')) //enable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);

	if (Application::IsKeyPressed('7'))
	{
		light[0].type = Light::LIGHT_DIRECTIONAL;
	}
	if (Application::IsKeyPressed('8'))
	{
		light[0].type = Light::LIGHT_SPOT;
	}


	if (Application::IsKeyPressed('5'))
	{
		meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_TOP]->textureID = LoadTGA("Image//snow_up.tga");
		meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//snow_dn.tga");
		meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_FRONT]->textureID = LoadTGA("Image//snow_ft.tga");
		meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_BACK]->textureID = LoadTGA("Image//snow_bk.tga");
		meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_LEFT]->textureID = LoadTGA("Image//snow_lf.tga");
		meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_RIGHT]->textureID = LoadTGA("Image//snow_rt.tga");
		meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 10, 40);
		meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 10, 20);
		light[0].color.Set(1, 1, 1);
	}

	if (Application::IsKeyPressed('6'))
	{
		meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_TOP]->textureID = LoadTGA("Image//icyhell_up.tga");
		meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//icyhell_dn.tga");
		meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_FRONT]->textureID = LoadTGA("Image//icyhell_ft.tga");
		meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_BACK]->textureID = LoadTGA("Image//icyhell_bk.tga");
		meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_LEFT]->textureID = LoadTGA("Image//icyhell_lf.tga");
		meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_RIGHT]->textureID = LoadTGA("Image//icyhell_rt.tga");
		meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("sphere", Color(0.5, 0.5, 0.5), 10, 40);
		meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(0.5, 0.5, 0.5), 10, 20);
		light[0].color.Set(0.5, 0.5, 0.5);
	}

	if (Application::IsKeyPressed('9'))
	{
		meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_TOP]->textureID = LoadTGA("Image//blood_up.tga");
		meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//blood_dn.tga");
		meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_FRONT]->textureID = LoadTGA("Image//blood_ft.tga");
		meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_BACK]->textureID = LoadTGA("Image//blood_bk.tga");
		meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_LEFT]->textureID = LoadTGA("Image//blood_lf.tga");
		meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1000, 1000);
		meshList[GEO_RIGHT]->textureID = LoadTGA("Image//blood_rt.tga");

		meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 10, 40);
		meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 0, 0), 10, 20);
		light[0].color.Set(1, 0, 0);
		for (int i = 0; i < 1000; i++)
		{
			rainpositiony[i] -= (float)(100 * dt);
		}
	}

	rotateAngle += (float)(10 * dt);
	planet1RotAngle += (float)(5 * dt);
	planet1RevAngle += (float)(2 * dt);
	moon1RotAngle += (float)(50 * dt);

	framerate = 1 / dt;

	for (int i = 0; i < 1000; i++)
	{
		rainpositiony[i] -= (float)(50 * dt);
		if (rainpositiony[i] < -499.0f)
		{
			rainpositiony[i] = 499.0f;
			rainpositionx[i] = rand() % 998 - 499;
			rainpositionz[i] = rand() % 998 - 499;
		}
		if (Application::IsKeyPressed(VK_SPACE))
		{
			rainpositiony[i] -= (float)(150 * dt);
		}
		if (Application::IsKeyPressed('Q'))
		{
			rainpositiony[i] += (float)(150 * dt);
		}
		if (Application::IsKeyPressed('E'))
		{
			rainpositiony[i] += (float)(50 * dt);
		}
		if (Application::IsKeyPressed('G'))
		{
			rainpositionx[i] -= (float)(150 * dt);
		}
		if (Application::IsKeyPressed('H'))
		{
			rainpositionx[i] += (float)(150 * dt);
		}
	}
}

void Sp2Scene::RenderSkybox()
{
	//bottom
	modelStack.PushMatrix();
	modelStack.Translate(0, -499, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Scale(-1, 1, 1);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	//top
	modelStack.PushMatrix();
	modelStack.Translate(0, 499, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Scale(1, -1, 1);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	//left
	modelStack.PushMatrix();
	modelStack.Translate(499, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Rotate(-90, 0, 0, 1);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	//right
	modelStack.PushMatrix();
	modelStack.Translate(-499, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	//back
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 499);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	//Front
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -499);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();
}

void Sp2Scene::RenderText(Mesh * mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);

	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);


}

void Sp2Scene::RenderTextOnScreen(Mesh * mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);

	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void Sp2Scene::RenderMesh(Mesh *mesh, bool enablelight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enablelight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}

	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}



void Sp2Scene::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Mtx44 perspective;
	//perspective.SetToPerspective()
	//Set view matrix using camera settings
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);

	modelStack.LoadIdentity();

	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_CameraSpace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_CameraSpace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else // POINT LIGHT
	{
		Position lightposition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightposition_cameraspace.x);
	}

	//RenderMesh(meshList[GEO_AXES], false);


	modelStack.PushMatrix();
	RenderSkybox();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 499, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_LIGHTBALL], true);
	modelStack.PopMatrix();


	if (Sp2Scene::test5 == true)
	{
		for (int i = 0; i < 1000; i++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(rainpositionx[i], rainpositiony[i], rainpositionz[i]);
			modelStack.Scale(1, 6, 1);
			RenderMesh(meshList[GEO_HEAD], false);
			modelStack.PopMatrix();
		}
	}

	for (int i = 0; i < 50; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(treex[i], translateY, treez[i]);
		modelStack.Scale(10, 30, 10);
		RenderMesh(meshList[GEO_DEADTREE], true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(0, -50, 0);
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Scale(-1, 1, 1);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-150, 50, -200);
	modelStack.Scale(10, 10, 10);
	RenderText(meshList[GEO_TEXT], "HIT ME FOR CHANGE OF WEATHER", Color(1, 0, 0));
	modelStack.PopMatrix();

	if (Camera3::test == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-80, 0, -50);
		modelStack.Scale(5, 5, 5);
		modelStack.Rotate(180, 0, 1, 0);
		RenderMesh(meshList[GEO_OBJECT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Find Tricker", Color(1, 0, 0), 0, 0, 0);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Find Sword", Color(1, 0, 0), 3.5, 7, 12);
		modelStack.PopMatrix();

	}

	//to test if player walk into tree
	if (Camera3::test2 == true)
	{
		Camera3::test = false;

		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "GAME OVER, YOU DIED", Color(1, 0, 0), 3.5, 3.5, 10);
		modelStack.PopMatrix();
	}

	if (Camera3::test3 == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(40, 100, 90);
		modelStack.Scale(5, 5, 5);
		modelStack.Rotate(180, 0, 1, 0);
		RenderMesh(meshList[GEO_OBJECT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Find Stone", Color(1, 0, 0), 3.5, 7, 10);
		modelStack.PopMatrix();
	}

	if (Sp2Scene::test4 == true)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Congratulations", Color(1, 0, 0), 3.5, 4, 10);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "YOU WIN", Color(1, 0, 0), 3.5, 4, 8);
		modelStack.PopMatrix();
	}

	else
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 0, -100);
		modelStack.Scale(5, 5, 5);
		modelStack.Rotate(180, 0, 1, 0);
		RenderMesh(meshList[GEO_OBJECT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Find Tricker", Color(1, 0, 0), 3.5, 7, 15);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	RenderTextOnScreen(meshList[GEO_TEXT], "framerate: " + std::to_string(framerate), Color(1, 0, 0), 2, 1, 1);
	modelStack.PopMatrix();
}

void Sp2Scene::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}