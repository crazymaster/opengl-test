#include "Shape.h"

GLfloat Vertex[4][3] =
	{{-1.0,0.0,-1.0},{1.0,0.0,-1.0},{1.0,0.0,1.0},{-1.0,0.0,1.0}};
GLfloat Color[4][3] =
	{{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,1.0,1.0}};

Quadrangle3D::Quadrangle3D(){
}

Quadrangle3D::Quadrangle3D(double xs,double zs){
	xPos=0.0;
	yPos=0.0;
	zPos=0.0;
	xSize = xs; zSize = zs;
}

//描画
void Quadrangle3D::Render(){
	glPushMatrix();
	glTranslated(xPos, yPos, zPos);	//移動
	glScaled(xSize, 0.0, zSize);
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

GLfloat Vertex2D[4][2] =
	{{-1.0,-1.0},{1.0,-1.0},{1.0,1.0},{-1.0,1.0}};
GLfloat Color2D[4][3] =
	{{1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,1.0,1.0}};

Quadrangle2D::Quadrangle2D(){
}

Quadrangle2D::Quadrangle2D(double xs, double ys){
	xPos = 0.0;
	yPos = 0.0;
	xSize = xs;
	ySize = ys;
}

void Quadrangle2D::Render(){
	glPushMatrix();
	glTranslated(xPos, yPos, 0.0);	//移動
	glScaled(xSize, ySize, 0.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
//	glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	//データの関連付け
	glVertexPointer(2, GL_FLOAT, 0, Vertex2D);//座標
	glColorPointer(2,GL_FLOAT, 0, Color2D);//色
	glNormal3f(0.0, 1.0, 0.0);
	glDrawArrays(GL_QUADS,0,4);
	
	glDisable(GL_COLOR_MATERIAL);
	
	glPopMatrix();
} 

