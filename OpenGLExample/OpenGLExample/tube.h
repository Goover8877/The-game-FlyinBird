#pragma once

#include "drawable.h"
#include "quad.h"

class Tube : public Drawable {

protected:
	Quad topQuad;
	Quad bottomQuad;
	float gap = 0.0f;

	void refreshQuads();

public:

	void setTextures(const char* top, const char* bottom);
	virtual void init();
	virtual void draw();
	void setGap(float _gap);
	float getGap();
	bool intersection(Quad* quad);

	virtual void setPositionX(float _x);
	virtual void setPositionY(float _y);
	virtual void setPositionZ(float _z);
	virtual void setScaleX(float _x);
	virtual void setScaleY(float _y);
	virtual void setScaleZ(float _z);

};