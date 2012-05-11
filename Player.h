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
	Quadrangle3D quad1, quad2;
	Quadrangle2D charge_bar;
	XModel model;
	MQO_MODEL mqoModel;
	Vector3 model_pos,dash_vec,cam_pos,target_pos;
	double ay,dash_charge,cam_angle[2],cam_zoom;
	char str_charge[32], str_score[32], str_total[32];
	int model_state, dash_time1, total;
	unsigned int keyFlag;
	enum eState{WAIT, DASH, RESET, FLY, CHANGE};

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
