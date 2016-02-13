#include "Scene2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"

Scene2::Scene2()
{
}

Scene2::~Scene2()
{
}

void Scene2::Init()
{
	// Init VBO here
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	static const GLfloat vertex_buffer_data[] =
	{
		-1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data[] =
	{
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 1.5f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	//Load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	glUseProgram(m_programID);
	glEnable(GL_DEPTH_TEST);

	rotateAngle = 45.0f;
	translateX = 1
		;
	scaleAll = 10;
}

void Scene2::Update(double dt)
{
	if (Application::IsKeyPressed(VK_SPACE))
	{
		rotateAngle += (float)(10 * dt);
		translateX += (float)(10 * dt);
		scaleAll += (float)(2 * dt);
	}
}

void Scene2::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity(); //no need camera for now, set it at World's origin
	projection.SetToOrtho(-40, 40, -30, 30, -10, 10); //Our world is a cube defined by these boundaries
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	////Triangle 1
	//scale.SetToScale(25, 25, 25 );
	//rotate.SetToRotation(45, 0, 0, 1);
	//translate.SetToTranslation(5, 50, 0);
	//model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	//MVP = projection * view * model; // Remember, matrix multiplication is the other way round
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	//glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	//glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	//Triangle 2 no translation
	scale.SetToScale(5, 10, 5);
	rotate.SetToRotation(45, 0, 0, 1);
	translate.SetToTranslation(translateX, 0, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way round
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Triangle 3 no scaling
	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(45, 0, 0, 1);
	translate.SetToTranslation(5, 0, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way round
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Triangle 4 no rotation
	scale.SetToScale(5, 5, 5);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(5, 5, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way round
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

void Scene2::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}