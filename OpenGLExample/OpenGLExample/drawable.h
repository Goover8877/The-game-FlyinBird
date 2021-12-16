#pragma once

#include <Windows.h>
#include <gl\gl.h>                                
#include <gl\glu.h>  

class Drawable {

protected:
	float x, y, z;
	float ax, ay, az;
	float sx, sy, sz;

public:
	Drawable();
	virtual void init();
	virtual void draw();
	virtual void destroy();

	void preDraw();
	void postDraw();

	virtual void setPositionX(float _x);
	virtual float getPositionX();
	virtual void setPositionY(float _y);
	virtual float getPositionY();
	virtual void setPositionZ(float _z);
	virtual float getPositionZ();
	virtual void setScaleX(float _x);
	virtual float getScaleX();
	virtual void setScaleY(float _y);
	virtual float getScaleY();
	virtual void setScaleZ(float _z);
	virtual float getScaleZ();


};