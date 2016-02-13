#include "Scene4.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

Scene4::Scene4()
{
}

Scene4::~Scene4()
{
}

void Scene4::Init()
{
	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	// Use our shader
	glUseProgram(m_programID);
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	//variable to rotate geometry
	rotateAngle = 0;
	planet1RotAngle = planet1RevAngle = moon1RotAngle = 0;

	//Initialize camera settings
	camera.Init(Vector3(40, 30, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 0));
	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(1, 0, 1), 20);
	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(0, 1, 1), 0.8f, 6);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 10, 20);
	meshList[GEO_PLANET1] = MeshBuilder::GenerateSphere("planet1", Color(1.0f, 0.0f, 0.0f), 10, 36);
	meshList[GEO_MOON1A] = MeshBuilder::GenerateSphere("moon1a", Color(.8f, 1, .3f), 10, 36);
	meshList[GEO_RING1] = MeshBuilder::GenerateRing("ring1", Color(0.0f, 0.0f, 0.0f), 0.8f, 36);
	meshList[GEO_MERCURY] = MeshBuilder::GenerateSphere("mercury", Color(.9f, 0.5, 0), 10, 36);
	meshList[GEO_URANUS] = MeshBuilder::GenerateSphere("uranus", Color(0.0f, 0.5, 0), 10, 36);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Scene4::Update(double dt)
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

	rotateAngle += (float)(10 * dt);
	planet1RotAngle += (float)(5 * dt);
	planet1RevAngle += (float)(2 * dt);
	moon1RotAngle += (float)(50 * dt);

}

void Scene4::Render()
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

	modelStack.PushMatrix();
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_AXES]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();						//planet1 system

	//modelStack.Rotate(planet1RevAngle, 0, 1, 0);		//revolution about centre
	//modelStack.Translate(0, 0, 0);					//offset from centre

	modelStack.PushMatrix();						//moon
	modelStack.Rotate(moon1RotAngle, 1, 0, 0);	//revolution about planet
	modelStack.Translate(0, 10, 0);					//offset from planet
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_MOON1A]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();						//planet1 itself
	//modelStack.Rotate(planet1RotAngle, 0, 1, 0);	//rotation about its own axis

	modelStack.PushMatrix();
	modelStack.Scale(1, 5, 1);						//planet size
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_PLANET1]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();						//planet1's ring
	modelStack.Scale(7, 7, 7);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_RING1]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(2, 2, 2);
	modelStack.Rotate(moon1RotAngle, 1, 0, 0);
	modelStack.Translate(0, 10, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_MERCURY]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(2, 2, 2);
	modelStack.Rotate(moon1RotAngle, 1, 0, 0);
	modelStack.Translate(0, 15, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_URANUS]->Render();
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void Scene4::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}