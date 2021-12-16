#include "drawable.h"

Drawable::Drawable()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	ax = 0.0f;
	ay = 0.0f;
	az = 0.0f;
	sx = 1.0f;
	sy = 1.0f;
	sz = 1.0f;
}

void Drawable::init()
{
}

void Drawable::draw()
{
}

void Drawable::destroy()
{
}

void Drawable::preDraw()
{
	glPushMatrix();

	glTranslatef(x, y, z);
	glRotatef(ax, 1.0f, 0.0f, 0.0f);
	glRotatef(ay, 0.0f, 1.0f, 0.0f);
	glRotatef(az, 0.0f, 0.0f, 1.0f);
	glScalef(sx, sy, sz);
}

void Drawable::postDraw()
{
	glPopMatrix();
}

void Drawable::setPositionX(float _x)
{
	x = _x;
}

float Drawable::getPositionX()
{
	return x;
}

void Drawable::setPositionY(float _y)
{
	y = _y;
}

float Drawable::getPositionY()
{
	return y;
}

void Drawable::setPositionZ(float _z)
{
	z = _z;
}

float Drawable::getPositionZ()
{
	return z;
}
void Drawable::setScaleX(float _x) {
	sx = _x;
}
float Drawable::getScaleX() {
	return sx;
}
void Drawable::setScaleY(float _y) {
	sy = _y;
}
float Drawable::getScaleY() {
	return sy;
}
void Drawable::setScaleZ(float _z) {
	sz = _z;
}
float Drawable::getScaleZ() {
	return sz;
}
