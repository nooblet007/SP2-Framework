#ifndef LIGHT_H_
#define LIGHT_H_

#include"Vertex.h"

struct Light
{
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	LIGHT_TYPE type;
	Vector3	spotDirection;
	float cosCutOff;
	float cosInner;
	float exponent;
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	Light()
	{
		position.Set(-60, 60.1, 100);
		color.Set(0, 0, 0);
		power = 1.f;
		kC = kL = kQ = 1;
	}
};



#endif