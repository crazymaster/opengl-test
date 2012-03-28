#ifndef PLAYER_H
#define PLAYER_H

#include <cstdio>
#include <cmath>
#include <GL/freeglut.h>
#include "XMesh/XLoader.h"
#include "GLMetaseq/GLMetaseq.h"
#include "Shape.h"


struct Vector3{ double x,y,z; };

class Player{
private:
	Quadrangle quad1, quad2;
	XModel model;
	MQO_MODEL mqoModel;
	Vector3 model_pos,model_vec;
	Vector3 cam_pos,target_pos;
	double ay,dash_charge,cam_angle[2],cam_zoom;
	int model_state,dash_time1;
	unsigned int keyFlag;
	enum eState{Wait,Dash};

public:
	Player();
	~Player();
	void Render3D();
	void Render2D();
	void KeyStateSet(int, bool);
	int KeyStateGet(int);
	void Move();
	void LookpointSet();

};

#endif
