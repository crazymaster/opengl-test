#include "Shape.h"

GLfloat Vertex[4][3] =
	{{-1.0,0.0,-1.0},{1.0,0.0,-1.0},{1.0,0.0,1.0},{-1.0,0.0,1.0}};
GLfloat Color[4][3] =
	{{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,1.0,1.0}};


Quadrangle::Quadrangle(){
}

Quadrangle::Quadrangle(double xs,double ys){
	xPos=0.0;
	yPos=0.0;
	zPos=0.0;
	xSize = xs; ySize = ys;
}

//描画
void Quadrangle::Render(){
	glPushMatrix();
	glTranslated(xPos, yPos, zPos);	//移動
	glScaled(xSize, 0.0, ySize);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
//	glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	//データの関連付け
	glVertexPointer(3, GL_FLOAT, 0, Vertex);//座標
	glColorPointer(3,GL_FLOAT, 0, Color);//色
	glNormal3f(0.0, 1.0, 0.0);
	glDrawArrays(GL_QUADS,0,4);
	
	glDisable(GL_COLOR_MATERIAL);
	
	glPopMatrix();
}


