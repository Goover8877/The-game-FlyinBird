#include "openglprogram.h"

OpenGLProgram::OpenGLProgram()
{
	for (int i = 0; i < 256; i++) {
		keys[i] = false;
	}
}

void OpenGLProgram::keyDown(char code)
{
	keys[code] = true;
}

void OpenGLProgram::keyUp(char code)
{
	keys[code] = false;
}

bool OpenGLProgram::isKeyDown(char code)
{
	return keys[code];
}
