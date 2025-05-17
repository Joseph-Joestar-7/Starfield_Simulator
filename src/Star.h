#pragma once
#include <cstdlib>
#include <ctime>

#define width 800
#define height 800
class Star
{
private:
	float x, y, z;
	float pz;
	static float speed;
public:
	Star();
	~Star();
	void Update();
	static float getspeed();
	static void setspeed(float s);
	float getx();
	float gety();
	float getz();
	float getpz();
};

