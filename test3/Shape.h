#ifndef SHAPE_H
#define SHAPE_H

#include <cstdio>
#include <GL/freeglut.h>

class Quadrangle{
private:
public:
	double xPos,yPos,zPos, xSize, ySize;
	Quadrangle();
	Quadrangle(double, double);
	void Render();
};

#endif
