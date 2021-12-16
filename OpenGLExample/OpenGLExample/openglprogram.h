#pragma once

class OpenGLProgram
{

private:
	bool keys[256];

public:
	OpenGLProgram();
	void keyDown(char code);
	void keyUp(char code);
	bool isKeyDown(char code);
	virtual void init() = 0;
	virtual void draw() = 0;

};
