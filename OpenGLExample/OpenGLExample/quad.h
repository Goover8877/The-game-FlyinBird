#pragma once

#include "drawable.h"
#include <Windows.h>
#include <gl\gl.h>                                
#include <gl\glu.h>   
#include "stb_image.h"
#include <string>

class Quad : public Drawable {
protected:
	GLuint texture;
	std::string filename;

public:
	void setFilename(const char* fname);
	virtual void init();
	virtual void draw();
	virtual void destroy();
	virtual bool intersection(Quad* other);

};
