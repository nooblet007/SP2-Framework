#include "AssignmentTris.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"

AssignmentTris::AssignmentTris()
{
}

AssignmentTris::~AssignmentTris()
{
}

void AssignmentTris::Init()
{
	// Init VBO here
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.9f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	static const GLfloat vertex_buffer_data[] =
	{
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.1f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	static const GLfloat vertex_buffer_data1[] =
	{
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data1), vertex_buffer_data1, GL_STATIC_DRAW);

	static const GLfloat vertex_buffer_data2[] =
	{
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_DOOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data[] =
	{
		1.0f, 0.0f, 0.0f,
		0.1f, 0.1f, 0.1f,
		1.0f, 0.0f, 0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data1[] =
	{
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data1), color_buffer_data1, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data2[] =
	{
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data3[] =
	{
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_DOOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data3), color_buffer_data3, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data4[] =
	{
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SQUARE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data4), color_buffer_data4, GL_STATIC_DRAW);
	//Load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	glUseProgram(m_programID);
	glEnable(GL_DEPTH_TEST);

	rotateAngle = 0.0f;
	translateX = 1;
	translateY = 30;
	scaleAll = 10;
}

void AssignmentTris::Update(double dt)
{
	rotateAngle += (float)(10 * dt);
	if (rotateAngle > 90)
	{
		rotateAngle = 0;
	}
	translateY -= (float)(100 * dt);
	if (translateY < -30)
	{
		translateY = 30;
	}
	if (Application::IsKeyPressed(VK_SPACE))
	{
		translateX += (float)(10 * dt);
		if (translateX > 40)
		{
			translateX = -40;
		}
		scaleAll += (float)(2 * dt);
		if (scaleAll > 5)
		{
			scaleAll = 2;
		}
	}
}

void AssignmentTris::Render()
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

	//Moon
	for (int numTriangles = 0; numTriangles < 30; numTriangles++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		scale.SetToScale(4, 4, 0);
		rotate.SetToRotation(static_cast<float>(numTriangles)* 12, 0, 0, 1);
		translate.SetToTranslation(0, 25, 0);
		model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
		MVP = projection * view * model; // Remember, matrix multiplication is the other way round
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	//Level Up Cost	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SQUARE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(15, 10, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-40, -30, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Unit 1	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(5, 5, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-24, -29, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Unit 2	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(5, 5, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-12, -29, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Unit 3
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(5, 5, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(0, -29, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Unit 4	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(5, 5, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(12, -29, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Unit 5
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(5, 5, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(24, -29, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Units

	//Grass
	for (int numTriangles = -40; numTriangles < 40; numTriangles++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		scale.SetToScale(3, 3, 0);
		rotate.SetToRotation(rotateAngle, 0, 0, 1);
		translate.SetToTranslation(static_cast<float>(numTriangles), -30, 0);
		model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
		MVP = projection * view * model; // Remember, matrix multiplication is the other way round
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
		glDrawArrays(GL_TRIANGLES, 1, 3);
	}


	////DOOR
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_DOOR]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_DOOR]);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//scale.SetToScale(10, 20, 0);
	//rotate.SetToRotation(0, 0, 0, 1);
	//translate.SetToTranslation(-8, -30, 1);
	//model = translate * rotate * scale;
	//MVP = projection * view * model;
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	//glDrawArrays(GL_TRIANGLES, 0, 6);



	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

void AssignmentTris::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);

}