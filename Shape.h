#ifndef SHAPE_H
#define SHAPE_H

#include <cstdio>
#include <GL/freeglut.h>

class Quadrangle3D{
private:
public:
	double xPos,yPos,zPos, xSize, zSize;
	Quadrangle3D();
	Quadrangle3D(double, double);
	void Render();
};

class Quadrangle2D{
private: 
public: 
	double xPos, yPos, xSize, ySize;
	Quadrangle2D();
	Quadrangle2D(double, double);
	void Render();
};

#endif
