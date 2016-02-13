#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
	// Init VBO here
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	glGenVertexArrays(1, &m_vertexArrayID1);
	glBindVertexArray(m_vertexArrayID1);
	glGenVertexArrays(1, &m_vertexArrayID2);
	glBindVertexArray(m_vertexArrayID2);

	// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer1[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer1[0]);
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer2[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer2[0]);

	// GEO_TRIANGLE_1
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data[] =
	{
		0.0f, 0.5f, 0.0f, // vertex 0 of triangle
		-0.5f, -0.5f, 0.0f, // vertex 1 of triangle
		-0.5f, 0.5f, 0.0f, // vertex 2 of triangle
		//-0.5f, 0.5f, 0.0f, // vertex 0 of triangle
		//-0.5f, 0.0f, 0.0f, // vertex 1 of triangle
		//0.0f, 0.5f, 0.0f, // vertex 2 of triangle
		//0.0, 0.0f, 0.0f,
		//0.5f, 0.05f, 0.0f,
		//0.5f, 0.0f, 0.0f,
		//-0.25f, 0.25f, 0.0f,
		//0.0f, 0.5f, 0.0f,
		//0.25f, 0.25f, 0.0f,

		//-0.5f, 0.25f, 0.0f,
		//0.0f, 0.25f, 0.0f,
		//-0.25f, 0.0f, 0.0f,

		//0.5f, 0.25f, 0.0f,
		//0.0f, 0.25f, 0.0f,
		//0.25f, 0.0f, 0.0f,

		//-0.25f, 0.0f, 0.0f,
		//0.0f, 0.25f, 0.0f,
		//0.25f, 0.0f, 0.0f,

		//-0.25f, 0.0f, 0.0f,
		//0.0f, -0.25f, 0.0f,
		//0.25f, 0.0f, 0.0f,

		//-0.25f, 0.0f, 0.0f,
		//-0.35f, -0.35f, 0.0f,
		//0.0f, -0.25f, 0.0f,

		//0.0f, -0.25f, 0.0f,
		//0.35f, -0.35f, 0.0f,
		//0.25f, 0.0f, 0.0f,
	};
	static const GLfloat vertex_buffer_data1[] =
	{
		0.0f, 0.5f, 0.5f, // vertex 0 of triangle
		-0.5f, -0.5f, 0.5f, // vertex 1 of triangle
		-0.5f, 0.5f, 0.5f, // vertex 2 of triangle
	};
	static const GLfloat vertex_buffer_data2[] =
	{
		0.0f, 1.0f, 1.0f, // vertex 0 of triangle
		-1.0f, -1.0f, 1.0f, // vertex 1 of triangle
		-1.0f, 1.0f, 1.0f, // vertex 2 of triangle
	};
	// set the active current buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer1[GEO_TRIANGLE_2]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer2[GEO_TRIANGLE_3]);
	// transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data1), vertex_buffer_data1, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);
	// An array of 3 vectors which represents the colors of the three vertices
	static const GLfloat color_buffer_data[] =
	{
		0.0f, 0.5f, 0.0f, // vertex 0 of triangle
		-0.5f, -0.5f, 0.0f, // vertex 1 of triangle
		-0.5f, 0.5f, 0.0f, // vertex 2 of triangle
		//1.0f, 0.0f, 0.0f, // vertex 0 of triangle
		//1.0f, 0.0f, 0.0f, // vertex 1 of triangle
		//1.0f, 0.0f, 0.0f, // vertex 2 of triangle
		//1.0, 0.0f, 0.0f,
		//1.0f, 0.0f, 0.0f,
		//1.0f, 0.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,

		//1.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,

		//1.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,

		//1.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,

		//1.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,

		//1.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,

		//1.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,
	};
	static const GLfloat color_buffer_data1[] =
	{
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	static const GLfloat color_buffer_data2[] =
	{
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	// set the active current buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer1[GEO_TRIANGLE_2]);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer2[GEO_TRIANGLE_3]);
	// transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data1), color_buffer_data1, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);

	//Load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//SimpleVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");
	m_programID1 = LoadShaders(
		"Shader//SimpleVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");
	m_programID2 = LoadShaders(
		"Shader//SimpleVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");
	glUseProgram(m_programID);
	glUseProgram(m_programID1);
	glUseProgram(m_programID2);

	glEnable(GL_DEPTH_TEST);
}

void Scene1::Update(double dt)
{
}

void Scene1::Render()
{
	// Render VBO here
	// Clear Color buffer & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer1[GEO_TRIANGLE_2]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer2[GEO_TRIANGLE_3]);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer1[GEO_TRIANGLE_2]);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer2[GEO_TRIANGLE_3]);
	glVertexAttribPointer(
		1, 
		3, 
		GL_FLOAT,
		GL_FALSE,
		0,
		0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 1, 3);
	
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

void Scene1::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);

	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer1[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer1[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID1);
	glDeleteProgram(m_programID1);

	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer2[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer2[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID2);
	glDeleteProgram(m_programID2);
	
}
