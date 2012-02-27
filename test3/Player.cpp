#include "Player.h"

//int型は32bitなので記憶できるキーは32個まで
int g_keys[]= {GLUT_KEY_UP,GLUT_KEY_DOWN,
	GLUT_KEY_LEFT,GLUT_KEY_RIGHT,
	' ','h','j','k','l','u','i','z','x'
};

Player::Player():quad1(6.0,6.0),quad2(6.0,6.0){
	quad2.zPos = -24.0;
	model.Load("XMesh/Models/dosei.x");
//	mqoModel = mqoCreateModel("GLMetaseq/Models/tachikoma.mqo",0.02);
	model_pos.x = 0.0; model_pos.y = 1.0; model_pos.z = 0.0;
	ay = 0.0; dash_charge = 0.0;
	model_state=Wait; keyFlag=0;
	cam_angle[0]=0.0; cam_angle[1]=0.0; cam_zoom=8.0;
	target_pos.x = 0.0; target_pos.y = 0.0; target_pos.z = 0.0;
}

Player::~Player(){
//	mqoDeleteModel(mqoModel);	
}

void Player::Render3D(){
	quad1.Render();
	quad2.Render();

	Move();
	glPushMatrix();
	glTranslated(model_pos.x, model_pos.y, model_pos.z);	//移動
	glRotated(ay,0.0,1.0,0.0);

	//　モデルの描画
	float scale = 2.0f/model.sphere.radius;	//　拡大係数
	model.Render(scale);	//　描画
//	mqoCallModel(mqoModel);

	glPopMatrix();
}

void Player::Render2D(){
}

void Player::KeyStateSet(int key,bool state){
	for(unsigned int i=0;i<sizeof(keyFlag)*8;i++){
		if(key == g_keys[i]){
			if(state) keyFlag |= 1<<i;
			else keyFlag &= ~(1<<i);
		} 
	}
}

int  Player::KeyStateGet(int key){
	for(unsigned int i=0;i<sizeof(keyFlag)*8;i++){
		if(key == g_keys[i]) return keyFlag & 1<<i;
	}
	return false;
}

void Player::Move(){
	if(model_state == Wait){
		if(!(KeyStateGet(' ')) && dash_charge>0.0)
			model_state=Dash;
		model_vec.x = 0.1; model_vec.z = 0.1;
		if( (KeyStateGet(GLUT_KEY_LEFT) && KeyStateGet(GLUT_KEY_UP)) ||
			(KeyStateGet(GLUT_KEY_LEFT) && KeyStateGet(GLUT_KEY_DOWN)) ||
			(KeyStateGet(GLUT_KEY_RIGHT) && KeyStateGet(GLUT_KEY_UP)) ||
			(KeyStateGet(GLUT_KEY_RIGHT) && KeyStateGet(GLUT_KEY_DOWN)) ){
			model_vec.x *= 1/sqrt(2.0);
			model_vec.z *= 1/sqrt(2.0);
		}

		if(KeyStateGet(GLUT_KEY_LEFT)){
			model_pos.x -= model_vec.x;
			if(model_pos.x < -5.0) model_pos.x = -5.0;
		}
		if(KeyStateGet(GLUT_KEY_RIGHT)){
			model_pos.x += model_vec.x;
			if(model_pos.x > 5.0) model_pos.x = 5.0;
		}
		if(KeyStateGet(GLUT_KEY_UP)){
			model_pos.z -= model_vec.z;
			if(model_pos.z < -5.0) model_pos.z = -5.0;
		}
		if(KeyStateGet(GLUT_KEY_DOWN)){
			model_pos.z += model_vec.z;
			if(model_pos.z > 5.0) model_pos.z = 5.0;
		}

		if(KeyStateGet('x')) ay -= 1.0;
		if(KeyStateGet('z')) ay += 1.0;
		if(KeyStateGet(' ')) dash_charge +=0.02;
	}else if(model_state == Dash){
		target_pos.x=model_pos.x;
		target_pos.y=model_pos.y;
		target_pos.z=model_pos.z;
		model_state=Wait; dash_charge=0.0;	
		target_pos.x = 0.0; target_pos.y = 0.0; target_pos.z = 0.0;
	}
}

void Player::LookpointSet(){
	//視点移動
	if(KeyStateGet('h')){
		cam_angle[0] -= M_PI/180.0;
		if(cam_angle[0] < 0) cam_angle[0] += 2*M_PI;
	}if(KeyStateGet('j')){
		cam_angle[1] -= M_PI/180.0;
		if(cam_angle[1] < 0) cam_angle[1] += 2*M_PI;
	}if(KeyStateGet('k')){
		cam_angle[1] += M_PI/180.0;
		if(cam_angle[1] > 2*M_PI) cam_angle[1] -= 2*M_PI;
	}if(KeyStateGet('l')){
		cam_angle[0] += M_PI/180.0;
		if(cam_angle[0] > 2*M_PI) cam_angle[0] -= 2*M_PI;
	}if(KeyStateGet('u')){
		cam_zoom -= 0.05;
	}if(KeyStateGet('i')){
		cam_zoom += 0.05;
	}
	cam_pos.x = model_pos.x + sin(cam_angle[0]) * cos(cam_angle[1]) * cam_zoom;
	cam_pos.y = model_pos.y + sin(cam_angle[1]) * cam_zoom;
	cam_pos.z = model_pos.z + cos(cam_angle[0]) * cos(cam_angle[1]) * cam_zoom;
	target_pos.x=model_pos.x;
	target_pos.y=model_pos.y;
	target_pos.z=model_pos.z;

	//　視点の設定
	gluLookAt(cam_pos.x, cam_pos.y, cam_pos.z,
		target_pos.x, target_pos.y, target_pos.z,
		0.0,1.0,0.0);	
}
