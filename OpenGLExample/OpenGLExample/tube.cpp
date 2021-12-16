#include "tube.h"

void Tube::setTextures(const char* top, const char* bottom)
{
	topQuad.setFilename(top);
	bottomQuad.setFilename(bottom);
}

void Tube::init()
{
	topQuad.init();
	bottomQuad.init();
}

void Tube::draw()
{
	topQuad.draw();
	bottomQuad.draw();
}

void Tube::setGap(float _gap)
{
	gap = _gap;
}

float Tube::getGap()
{
	return gap;
}

bool Tube::intersection(Quad* quad)
{
	// topQuad, bottomQuad
	// quad.intersection(topQuad);
	if (topQuad.intersection(quad)) {
		return true;
	}
	else {
		if (bottomQuad.intersection(quad)) {
			return true;
		}
		else {
			return false;
		}
	}
}

void Tube::refreshQuads() {
	topQuad.setScaleX(sx);
	bottomQuad.setScaleX(sx);
	topQuad.setScaleY(sy / 2.0f);
	bottomQuad.setScaleY(sy / 2.0f);
	topQuad.setScaleZ(sz);
	bottomQuad.setScaleZ(sz);

	topQuad.setPositionZ(z);
	bottomQuad.setPositionZ(z);
	topQuad.setPositionX(x);
	bottomQuad.setPositionX(x);

	topQuad.setPositionY(y + sy / 2.0f + gap);
	bottomQuad.setPositionY(y - sy / 2.0f - gap);
}

void Tube::setPositionX(float _x)
{
	x = _x;
	refreshQuads();
}

void Tube::setPositionY(float _y)
{
	y = _y;
	refreshQuads();
}

void Tube::setPositionZ(float _z)
{
	z = _z;
	refreshQuads();
}

void Tube::setScaleX(float _x) {
	sx = _x;
	refreshQuads();
}
void Tube::setScaleY(float _y) {
	sy = _y;
	refreshQuads();
}
void Tube::setScaleZ(float _z) {
	sz = _z;
	refreshQuads();
}