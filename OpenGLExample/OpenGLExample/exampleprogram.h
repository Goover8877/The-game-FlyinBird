#pragma once

#include "openglprogram.h"

#include <Windows.h>
#include <gl\gl.h>                                
#include <gl\glu.h>   
#include "stb_image.h"
#include "quad.h"
#include "tube.h"

#include <ctime>

class ExampleProgram : public OpenGLProgram {

private:
	HWND hWnd = 0;
	bool gameovermessage = false;
	bool game = true;
	bool hit = false;

	float x = 0.0f;
	float a = 360;

	float y = 0.0f;
	float vy = 0.0f;
	int counter = 100;

	float astep = 1;
	float step = 0.02f;
	////////////////////////
	Quad bird;
	Quad fire;
	Quad fallingBird;
	Quad sky;
	Quad hitbox;
	Tube tube;
	const int tubesCount = 5;
	Tube* tubes;
	int score;
	bool* tubesFlag;
	Quad* clouds;
	const int cloudsCount = 10;
	float* cloudVel;
public:
	ExampleProgram();
	~ExampleProgram();
	virtual void init();
	virtual void draw();
	HWND getHandle();
	void setHandle(HWND h);

};

