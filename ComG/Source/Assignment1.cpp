#include "Assignment1.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"

Assignment1::Assignment1()
{
}

Assignment1::~Assignment1()
{
}

void Assignment1::Init()
{
	// Init VBO here
	// Set background color to dark blue
	glClearColor(0.3f, 0.0f, 0.0f, 0.0f);

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
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CLOUD]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);

	static const GLfloat vertex_buffer_data3[] =
	{
		-1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BIRD]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data3), vertex_buffer_data3, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
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
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
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
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BIRD]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data4), color_buffer_data4, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data5[] =
	{
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CLOUD]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data5), color_buffer_data5, GL_STATIC_DRAW);

	for (int i = 0; i < 100; i++)
	{
		rainpositionx[i] = rand() % 80 - 40;
		rainpositiony[i] = rand() % 60 - 30;
	}
	//Load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	glUseProgram(m_programID);
	glEnable(GL_DEPTH_TEST);

	rotateAngle = 0.0f;
	translateX = 1;
	translateX2 = 1;
	translateY = 30;
	scaleAll = 10;
}

void Assignment1::Update(double dt)
{
	//Update rain here
	for (int i = 0; i < 100; i++)
	{
		rainpositiony[i] -= (float)(40 * dt);
		if (rainpositiony[i] < -30.0f)
		{
			rainpositiony[i] = 30.0f;
			rainpositionx[i] = rand() % 80 - 40;
		}
	}

	// all other transforms
	rotateAngle += (float)(10 * dt);
	if (rotateAngle > 90)
	{
		rotateAngle = 0;
	}
	translateY -= (float)(dt);
	if (translateY < -30)
	{
		translateY = 30;
	}
	scaleAll += (float)(2 * dt);
	if (scaleAll > 6)
	{
		scaleAll = 3;
	}
	translateX += (float)(10 * dt);
	if (translateX > 40)
	{
		translateX = -40;
	}
	translateX2 += (float)(20 * dt);
	if (translateX2 > 40)
	{
		translateX2 = -40;
	}
	if (Application::IsKeyPressed(VK_SPACE))
	{
		
	}
}

void Assignment1::Render()
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

	for (int i = 0; i < 100; i++)
	{
		//Blood Rain
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_DOOR]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_DOOR]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		scale.SetToScale(0.2, 1, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(rainpositionx[i], rainpositiony[i], 1);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	//Bird Body
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BIRD]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BIRD]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(3, 3, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX2 + 3, 15, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Bird Beak
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BIRD]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BIRD]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(2, 1, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX2 + 6, 15, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Bird Body 2
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BIRD]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BIRD]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(3, 3, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX2 + 9, 10, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Bird Beak 2
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BIRD]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BIRD]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(2, 1, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX2 + 12, 10, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Moon
	for (int numTriangles = 0; numTriangles < 360; numTriangles++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		scale.SetToScale(scaleAll, scaleAll, 0);
		rotate.SetToRotation(static_cast<float>(numTriangles), 0, 0, 1);
		translate.SetToTranslation(35, 25, 0);
		model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
		MVP = projection * view * model; // Remember, matrix multiplication is the other way round
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	//Cloud
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CLOUD]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CLOUD]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(11, 5, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX - 17, 20, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Cloud 2
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CLOUD]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CLOUD]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(11, 5, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX - 11, 18, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Cloud 3
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CLOUD]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CLOUD]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(11, 5, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX, 20, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Cloud 4
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CLOUD]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CLOUD]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(11, 5, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX + 6, 18, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Cloud 5
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CLOUD]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CLOUD]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(11, 5, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX + 17, 20, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Cloud 6
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CLOUD]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CLOUD]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(11, 5, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX + 23, 18, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Cloud 7
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CLOUD]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CLOUD]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(11, 5, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX + 34, 20, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Cloud 8
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CLOUD]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CLOUD]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(11, 5, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX + 40, 18, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Black Square (Main Body)
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(33, 30, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-20, -30, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Black Rectangle above main body	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(30, 14, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-18, 0, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Black triangle (right)	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(20, 15, 0);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(28, -6, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Black triangle (left)	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(15, 20, 0);
	rotate.SetToRotation(180, 0, 0, 1);
	translate.SetToTranslation(-20, 14, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//small square for roof
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(15, 25, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(10, -30, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//small square (left)
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(15, 25, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-30, -30, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//small square (right)
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(10, 10, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(0, 10, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Black triangle for roof	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(15, 15, 0);
	rotate.SetToRotation(315, 0, 0, 1);
	translate.SetToTranslation(-5.5, 20, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//DOOR
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_DOOR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_DOOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(10, 20, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-8, -30, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Window 1
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_DOOR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_DOOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(3, 3, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-14, -10, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Window 2
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_DOOR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_DOOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(3, 3, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-14, -15, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Window 3
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_DOOR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_DOOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(3, 3, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-19, -15, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Window 4
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_DOOR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_DOOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(3, 3, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-19, -10, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//long window 1
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_DOOR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_DOOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(3, 10, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(5, -20, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//long window 2
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_DOOR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_DOOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(3, 10, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(9, -20, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new mvp
	glDrawArrays(GL_TRIANGLES, 0, 6);

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

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

void Assignment1::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);

}