#include "Assignment2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "Utility.h"

Assignment2::Assignment2()
{
}

Assignment2::~Assignment2()
{
}

void Assignment2::Init()
{
	reachAngle = true;
	reachAngle2 = true;
	reachAngle3 = true;
	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.8f, 0.0f);

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
	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
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

	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;

	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

	//variable to rotate geometry
	rotateAngle = 0;
	planet1RotAngle = moon1RotAngle = 0;
	planet1RevAngle = 30;
	planet2RevAngle = 150;
	wingRotation = 60;
	//Initialize camera settings
	camera.Init(Vector3(0, -5, -170), Vector3(0, 0, 0), Vector3(0, 1, 0));

	meshList[GEO_TREESTEM] = MeshBuilder::GenerateCube("cube", Color(1, 0.5, 0));
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_BODY] = MeshBuilder::GenerateCube("cube", Color(1, 1, 1));
	meshList[GEO_NECK] = MeshBuilder::GenerateCube("cube", Color(1, 1, 1));
	meshList[GEO_BENCH] = MeshBuilder::GenerateCube("cube", Color(1, 0.1, 0));
	meshList[GEO_LAMPOST] = MeshBuilder::GenerateCube("cube", Color(0.5, 0.5, 0.5));
	meshList[GEO_LAMPCONE] = MeshBuilder::GenerateCone("sphere", Color(0.5, 0.5, 0.5), 20);
	meshList[GEO_EYES] = MeshBuilder::GenerateSphere("sphere", Color(0, 0, 1), 20);
	//meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(0, 1, 1), 0.8f, 6);
	meshList[GEO_HAIR] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 0), 10, 20);
	meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 10, 40);
	meshList[GEO_BALL] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 10, 20);
	meshList[GEO_YELLOWBALL] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 0), 10, 20);
	meshList[GEO_REDCONE] = MeshBuilder::GenerateCone("sphere", Color(1, 0, 0), 20);
	meshList[GEO_ARMS] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 10, 20);
	meshList[GEO_HANDS] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 10, 20);
	meshList[GEO_LEGS] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 10, 20);
	meshList[GEO_SKIRT] = MeshBuilder::GenerateCone("cone", Color(1, 1, 0), 20);
	meshList[GEO_SNOWCONE] = MeshBuilder::GenerateCone("cone", Color(1, 1, 1), 20);
	meshList[GEO_LEAF] = MeshBuilder::GenerateCone("cone", Color(0, 1, 0.5), 20);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 10, 20);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.f, 0.f, 0.f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 10, 20);

	/*meshList[GEO_PLANET1] = MeshBuilder::GenerateSphere("planet1", Color(1.0f, 0.0f, 0.0f), 10, 36);
	meshList[GEO_MOON1A] = MeshBuilder::GenerateSphere("moon1a", Color(.8f, 1, .3f), 10, 36);
	meshList[GEO_RING1] = MeshBuilder::GenerateRing("ring1", Color(0.0f, 0.0f, 0.0f), 0.8f, 36);
	meshList[GEO_MERCURY] = MeshBuilder::GenerateSphere("mercury", Color(.9f, 0.5, 0), 10, 36);
	meshList[GEO_URANUS] = MeshBuilder::GenerateSphere("uranus", Color(0.0f, 0.5, 0), 10, 36);*/

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	for (int i = 0; i < 500; i++)
	{
		rainpositionx[i] = rand() % 625 - 312.5;
		rainpositiony[i] = rand() % 350 - 175;
		rainpositionz[i] = rand() % 625 - 312.5;
	}
}

static float LSPEED = 10.f;
static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Assignment2::Update(double dt)
{
	camera.Update(dt);

	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	if (Application::IsKeyPressed('0'))
	{
		meshList[GEO_EYES] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 20);
		meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("sphere", Color(0, 0, 0), 10, 40);
		meshList[GEO_SKIRT] = MeshBuilder::GenerateCone("cone", Color(1, 0, 0), 20);
		meshList[GEO_SNOWCONE] = MeshBuilder::GenerateCone("cone", Color(0, 0, 0), 20);
		meshList[GEO_BODY] = MeshBuilder::GenerateCube("cube", Color(1, 0, 0));
		meshList[GEO_HANDS] = MeshBuilder::GenerateSphere("sphere", Color(0, 0, 0), 10, 20);
		meshList[GEO_LEGS] = MeshBuilder::GenerateSphere("sphere", Color(0, 0, 0), 10, 20);
		meshList[GEO_HAIR] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 10, 20);
		meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(0.05, 0.05, 0.05), 10, 20);
		glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	}
	if (Application::IsKeyPressed('9'))
	{
		meshList[GEO_EYES] = MeshBuilder::GenerateSphere("sphere", Color(0, 0, 1), 20);
		meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 10, 40);
		meshList[GEO_SKIRT] = MeshBuilder::GenerateCone("cone", Color(1, 1, 0), 20);
		meshList[GEO_SNOWCONE] = MeshBuilder::GenerateCone("cone", Color(1, 1, 1), 20);
		meshList[GEO_BODY] = MeshBuilder::GenerateCube("cube", Color(1, 1, 1));
		meshList[GEO_HANDS] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 10, 20);
		meshList[GEO_LEGS] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 10, 20);
		meshList[GEO_HAIR] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 0), 10, 20);
		meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 10, 20);
		glClearColor(0.0f, 0.0f, 0.8f, 0.0f);
	}

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

	//The 2 performing spheres
		planet1RotAngle += (float)(300 * dt);
		//planet1RevAngle += (float)(80 * dt);
		/*planet2RevAngle -= (float)(80 * dt);
		planet2RevAngle += (float)(80 * dt);*/
		
		//Wing Rotation
		if (reachAngle == true)
		{
			wingRotation += (float)(20 * dt);
			if (wingRotation >= 75)
				reachAngle = false;
		}
		if (reachAngle == false)
		{
			wingRotation -= (float)(20 * dt);
			if (wingRotation <= 60)
				reachAngle = true;
		}

		//Hand Rotation
		if (reachAngle2 == true)
		{
			planet1RevAngle += (float)(80 * dt);
			if (planet1RevAngle >= 150)
				reachAngle2 = false;
		}
		if (reachAngle2 == false)
		{
			planet1RevAngle -= (float)(80 * dt);
			if (planet1RevAngle <= 30)
				reachAngle2 = true;
		}

		//Hand Rotation
		if (reachAngle3 == true)
		{
			planet2RevAngle -= (float)(80 * dt);
			if (planet2RevAngle <= 30)
				reachAngle3 = false;
		}
		if (reachAngle3 == false)
		{
			planet2RevAngle += (float)(80 * dt);
			if (planet2RevAngle >= 150)
				reachAngle3 = true;
		}

		//planet2RevAngle -= (float)(80 * dt);
		/*if (reachAngle == false)
		{
			planet2RevAngle += (float)(80 * dt);
			if (planet2RevAngle <= 135)
				reachAngle = true;
		}
		if (reachAngle == true)
		{
			planet2RevAngle -= (float)(80 * dt);
			if (planet2RevAngle >= 45)
				reachAngle = false;
		}*/
		if (Application::IsKeyPressed('T'))
		{
			rotateAngle -= (float)(200 * dt);
		}
		if (Application::IsKeyPressed('Y'))
		{
			rotateAngle += (float)(500 * dt);
		}
	rotateAngle += (float)(100 * dt);
	moon1RotAngle += (float)(50 * dt);

	for (int i = 0; i < 1000; i++)
	{
		rainpositiony[i] -= (float)(50 * dt);
		if (rainpositiony[i] < -175.0f)
		{
			rainpositiony[i] = 175.0f;
			rainpositionx[i] = rand() % 625 - 312.5;
			rainpositionz[i] = rand() % 625 - 312.5;
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

void Assignment2::RenderMesh(Mesh *mesh, bool enablelight)
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
	mesh->Render();
}

void Assignment2::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set view matrix using camera settings
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);

	modelStack.LoadIdentity();

	Mtx44 MVP;

	//new code
	Position lightposition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightposition_cameraspace.x);

	/*RenderMesh(meshList[GEO_AXES], false);*/

	//Environment Codes
	modelStack.PushMatrix();
	modelStack.Translate(0, -30, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_QUAD], false);
	modelStack.PopMatrix();

	//**********************ENVIRONMENT CODES*********************************\\
	
	for (int i = 0; i < 500; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(rainpositionx[i], rainpositiony[i], rainpositionz[i]);
		modelStack.Scale(1.5, 1.5, 1.5);
		RenderMesh(meshList[GEO_HEAD], false);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(-100, 20.1, 100);
	modelStack.Scale(7.5, 120, 7.5);
	RenderMesh(meshList[GEO_LAMPOST], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-80, 80.1, 100);
	modelStack.Scale(50, 7.5, 7.5);
	RenderMesh(meshList[GEO_LAMPOST], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-60, 60.1, 100);
	modelStack.Scale(8,20,8);
	RenderMesh(meshList[GEO_LAMPCONE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 95);
	modelStack.Scale(100, 20, 5);
	RenderMesh(meshList[GEO_TREESTEM], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -10, 80);
	modelStack.Scale(100,5,30);
	RenderMesh(meshList[GEO_TREESTEM], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-50, -20, 65);
	modelStack.Scale(4, 25, 4);
	RenderMesh(meshList[GEO_TREESTEM], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, -20, 65);
	modelStack.Scale(4, 25, 4);
	RenderMesh(meshList[GEO_TREESTEM], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-50, -20, 95);
	modelStack.Scale(4, 25, 4);
	RenderMesh(meshList[GEO_TREESTEM], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, -20, 95);
	modelStack.Scale(4, 25, 4);
	RenderMesh(meshList[GEO_TREESTEM], true);
	modelStack.PopMatrix();

	//Xmas Tree
	modelStack.PushMatrix();
	modelStack.Translate(50, 80, 20);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 70, 20);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_REDCONE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 60, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_LEAF], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 65, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_SNOWCONE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 50, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_LEAF], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 55, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_SNOWCONE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 40, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_LEAF], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 45, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_SNOWCONE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 30, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_LEAF], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 35, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_SNOWCONE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 20, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_LEAF], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 25, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_SNOWCONE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 10, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_LEAF], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 15, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_SNOWCONE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 0, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_LEAF], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 5, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_SNOWCONE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, -10, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_LEAF], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, -5, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_SNOWCONE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, -20, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_LEAF], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, -15, 20);
	modelStack.Scale(15, 10, 15);
	RenderMesh(meshList[GEO_SNOWCONE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 20.1, 20);
	modelStack.Scale(7.5, 100, 7.5);
	RenderMesh(meshList[GEO_TREESTEM], true);
	modelStack.PopMatrix();

	//Rocks
	modelStack.PushMatrix();
	modelStack.Translate(35, -30, 0);
	modelStack.Scale(3.5, 3.5, 3.5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(30, -30, 5);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(55, -30, 0);
	modelStack.Scale(3.5, 3.5, 3.5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, -30, 5);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(-35, -30, 0);
	modelStack.Scale(3.5, 3.5, 3.5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-30, -30, 5);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-55, -30, 0);
	modelStack.Scale(3.5, 3.5, 3.5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-50, -30, 5);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -30, 35);
	modelStack.Scale(3.5, 3.5, 3.5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(5, -30, 35);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -30, 55);
	modelStack.Scale(3.5, 3.5, 3.5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(5, -30, 55);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -30, -35);
	modelStack.Scale(3.5, 3.5, 3.5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(5, -30, -35);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -30, -55);
	modelStack.Scale(3.5, 3.5, 3.5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(5, -30, -55);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-60, 60.1, 100);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	//*******************************MODEL CODES*****************************\\

	modelStack.PushMatrix();
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	modelStack.Scale(5, 20, 10);
	modelStack.Translate(0, -0.5, 0);
	RenderMesh(meshList[GEO_BODY], true);

	//Upper Right Wing
	modelStack.PushMatrix();
	modelStack.Translate(1, 0.4, -0.5);
	modelStack.Rotate(wingRotation, 0, -1, 0.2);
	modelStack.Scale(0.1, 0.45, 1.6);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	//Lower Right Wing
	modelStack.PushMatrix();
	modelStack.Translate(1, 0.1, -0.5);
	modelStack.Rotate(wingRotation, 0, -1, -0.2);
	modelStack.Scale(0.1, 0.45, 1.6);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	//Upper Left Wing
	modelStack.PushMatrix();
	modelStack.Translate(1, 0.4, 0.5);
	modelStack.Rotate(wingRotation, 0, 1, 0.2);
	modelStack.Scale(0.1, 0.45, 1.6);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	//Lower Left Wing
	modelStack.PushMatrix();
	modelStack.Translate(1, 0.1, 0.5);
	modelStack.Rotate(wingRotation, 0, 1, -0.2);
	modelStack.Scale(0.1, 0.45, 1.6);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(0, 1.5, 0);
	modelStack.Scale(0.5, 0.125, 0.25);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 1, 0);
	modelStack.Scale(2, 0.5, 1);
	RenderMesh(meshList[GEO_REDCONE], true);
	modelStack.PopMatrix();


	//Head
	modelStack.PushMatrix();
	modelStack.Scale(1,0.25,0.5);
	modelStack.Translate(0, 3.1, 0);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();

	//Right Eye
	modelStack.PushMatrix();
	modelStack.Scale(0.2, 0.05, 0.1);
	modelStack.Translate(-4, 15.5, 2);
	RenderMesh(meshList[GEO_EYES], true);
	modelStack.PopMatrix();

	//left Eye
	modelStack.PushMatrix();
	modelStack.Scale(0.2, 0.05, 0.1);
	modelStack.Translate(-4, 15.5, -2);
	RenderMesh(meshList[GEO_EYES], true);
	modelStack.PopMatrix();

	//Big Hair
	modelStack.PushMatrix();
	modelStack.Scale(1, 0.25, 0.5);
	modelStack.Translate(0.3, 3.4, 0);
	RenderMesh(meshList[GEO_HAIR], true);
	modelStack.PopMatrix();

	//Small Hair
	modelStack.PushMatrix();
	modelStack.Scale(0.5, 0.125, 0.25);
	modelStack.Translate(2.4, 7.4, 0);
	RenderMesh(meshList[GEO_HAIR], true);
	modelStack.PopMatrix();

	//Neck
	modelStack.PushMatrix();
	modelStack.Scale(0.3, 0.06, 0.2);
	modelStack.Translate(0, 8.8, 0);
	RenderMesh(meshList[GEO_NECK], true);
	modelStack.PopMatrix();

	//Skirt
	modelStack.PushMatrix();
	modelStack.Scale(1.8, 0.42, 1.2);
	modelStack.Translate(0, -1.2, 0);
	RenderMesh(meshList[GEO_SKIRT], true);
	modelStack.PopMatrix();

	//RIGHT SHOULDER
	modelStack.PushMatrix();
	modelStack.Scale(0.5, 0.18, 0.2);
	modelStack.Translate(0, 1.9, 3);
	RenderMesh(meshList[GEO_YELLOWBALL], true);

	//RIGHT ARM
	modelStack.PushMatrix();
	modelStack.Rotate(planet1RevAngle, 0, 0, -1);
	modelStack.Translate(1.5, 0, 0.5);
	modelStack.Scale(1.5, 0.24, 0.8);
	RenderMesh(meshList[GEO_HANDS], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	////RIGHT ARM
	//modelStack.PushMatrix();
	//modelStack.Rotate(45, 0, -1, 1);
	//modelStack.Scale(0.5, 0.12, 0.2);
	//modelStack.Translate(1.7, 1.5, 3);
	//RenderMesh(meshList[GEO_HANDS], true);
	//modelStack.PopMatrix();

	//LEFT SHOULDER
	modelStack.PushMatrix();
	modelStack.Scale(0.5, 0.18, 0.2);
	modelStack.Translate(0, 1.9, -3);
	RenderMesh(meshList[GEO_YELLOWBALL], true);

	modelStack.PushMatrix();
	modelStack.Rotate(planet2RevAngle, 0, 0, -1);
	modelStack.Translate(1.5, 0, -0.5);
	modelStack.Scale(1.5, 0.24, 0.8);
	RenderMesh(meshList[GEO_HANDS], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	////LEFT ARM
	//modelStack.PushMatrix();
	//modelStack.Rotate(45, 0, -0.7, 0.7);
	//modelStack.Scale(0.5, 0.12, 0.2);
	//modelStack.Translate(-0.8, 3, -3.7);
	//RenderMesh(meshList[GEO_HANDS], true);
	//modelStack.PopMatrix();

	//RIGHT LEG
	modelStack.PushMatrix();
	modelStack.Scale(0.3, 0.36, 0.2);
	modelStack.Translate(0, -1.78, -1.8);
	RenderMesh(meshList[GEO_LEGS], true);
	modelStack.PopMatrix();

	//LEFT LEG
	modelStack.PushMatrix();
	modelStack.Rotate(-45, 1, 0, 0);
	modelStack.Scale(0.3, 0.36, 0.2);
	modelStack.Translate(0, -1.78, -0.5);
	RenderMesh(meshList[GEO_LEGS], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	//*************************SPHERE CODES***************************************\\
	//ROTATING SPHERE
	modelStack.PushMatrix();
	modelStack.Rotate(planet1RotAngle, 0, -1, 0);
	modelStack.Scale(4, 4, 4);
	modelStack.Translate(0, 3, 6);
	RenderMesh(meshList[GEO_HEAD], true);

	//Spike 1
	modelStack.PushMatrix();
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Translate(0, 4.9, 0);
	RenderMesh(meshList[GEO_SKIRT], true);
	modelStack.PopMatrix();

	//Spike 2
	modelStack.PushMatrix();
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Translate(0, 4.9, 0);
	RenderMesh(meshList[GEO_SKIRT], true);
	modelStack.PopMatrix();

	//Spike 3
	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Translate(0, 4.9, 0);
	RenderMesh(meshList[GEO_SKIRT], true);
	modelStack.PopMatrix();

	//Spike 4
	modelStack.PushMatrix();
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Translate(0, 4.9, 0);
	RenderMesh(meshList[GEO_SKIRT], true);
	modelStack.PopMatrix();

	//Spike 5
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Translate(0, 4.9, 0);
	RenderMesh(meshList[GEO_SKIRT], true);
	modelStack.PopMatrix();

	//Spike 6
	modelStack.PushMatrix();
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Translate(0, 4.9, 0);
	RenderMesh(meshList[GEO_SKIRT], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	//ROTATING SPHERE
	modelStack.PushMatrix();
	modelStack.Rotate(planet1RotAngle, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	modelStack.Translate(0, -1.5, -6);
	RenderMesh(meshList[GEO_HEAD], true);

	//Spike 1
	modelStack.PushMatrix();
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Translate(0, 4.9, 0);
	RenderMesh(meshList[GEO_SKIRT], true);
	modelStack.PopMatrix();

	//Spike 2
	modelStack.PushMatrix();
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Translate(0, 4.9, 0);
	RenderMesh(meshList[GEO_SKIRT], true);
	modelStack.PopMatrix();

	//Spike 3
	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Translate(0, 4.9, 0);
	RenderMesh(meshList[GEO_SKIRT], true);
	modelStack.PopMatrix();

	//Spike 4
	modelStack.PushMatrix();
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Translate(0, 4.9, 0);
	RenderMesh(meshList[GEO_SKIRT], true);
	modelStack.PopMatrix();

	//Spike 5
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Translate(0, 4.9, 0);
	RenderMesh(meshList[GEO_SKIRT], true);
	modelStack.PopMatrix();

	//Spike 6
	modelStack.PushMatrix();
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Translate(0, 4.9, 0);
	RenderMesh(meshList[GEO_SKIRT], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void Assignment2::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}