#include "Star.h"


float Star::speed = 1.0f;

Star::Star()
{
	x = std::rand() % (2 * width + 1) - width;   
	y = std::rand() % (2 * height + 1) - height;
	z = std::rand() % width;
	speed = 1;
	pz = z;
}


Star::~Star() {
}

void Star::Update()
{
	pz = z;
	z = z - speed;
	
	if (z < 1)
	{
		z = width;
		x = std::rand() % (2 * width + 1) - width;
		y = std::rand() % (2 * height + 1) - height;
		pz = z;
	}
		
}

float Star::getspeed()
{
	return speed;
}

void Star::setspeed(float s)
{
	speed = s;
}

float Star::getx()
{
	return x;
}

float Star::gety()
{
	return y;
}

float Star::getz()
{
	return z;
}

float Star::getpz()
{
	return pz;
}

