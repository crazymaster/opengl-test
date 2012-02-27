#include "Player.h"

#define TIMER_WAIT 33

int WindowPositionX = 100;
int WindowPositionY = 100;
int WindowWidth = 800;
int WindowHeight = 600;
char WindowTitle[] = "test3";
double CurrentTime = 0.0;
double LastTime = 0.0;
double CurrentCount = 0.0;
double LastCount = 0.0;
int FrameCount = 0;
float Fps = 0.0f;
Player *p1;

void Initialize();
void Close();
void Display();
void Idle();
void Reshape(int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void PassiveMotion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void Special(int key, int x, int y);
void SpecialUp(int key, int x, int y);
void Render2D();
void Render3D();
void glutRenderText(void* bitmapfont, char* text);
void glutToggleFullScreen();
void Timer(int value);

//----------------------------------------------------------------------------------------------------
// Name : main()
// Desc : �A�v���P�[�V�����̃G���g���[�|�C���g
//----------------------------------------------------------------------------------------------------
int main( int argc, char **argv ){
	//�@GLUT�R�[���o�b�N�֐��Ȃǂ̐ݒ�
	glutInit(&argc, argv);
	glutInitWindowPosition(WindowPositionX, WindowPositionY);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(WindowTitle);
	glutDisplayFunc(Display);
	glutCloseFunc(Close);	//�E�B���h�E������ꂽ�Ƃ�
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutPassiveMotionFunc(PassiveMotion);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(Special);
	glutSpecialUpFunc(SpecialUp);
	Initialize();	//�@OpenGL������

	glutTimerFunc( TIMER_WAIT, Timer, 0);
//	glutIdleFunc(Idle);
	glutMainLoop();	//�@���C�����[�v

	return 0;
}


//----------------------------------------------------------------------------------------------------
// Name : Initialize()
// Desc : ����������
//----------------------------------------------------------------------------------------------------
void Initialize(){
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *vender = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);

	printf("OpenGL %s\n", version);
	printf("%s\n", vender);
	printf("%s\n", renderer);

	//�@�o�b�N�o�b�t�@���N���A����F�̎w��
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	//�@�[�x�e�X�gON
	glEnable(GL_DEPTH_TEST);
	
	//�@���C�e�B���O
	float pos[4] = { 0.0f, 10.0f, 10.0f, 1.0f };
	float amb[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
	float dif[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float spe[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spe);
	glEnable(GL_NORMALIZE);//�@���̐��K��

	glutIgnoreKeyRepeat(GL_TRUE);//�L�[���s�[�g�𖳎�
	mqoInit();
	p1 = new Player();

	//�@�E�B���h�E��\��
	glutShowWindow();
}

//---------------------------------------------------------------------------------------------------
// Name : Idle()
// Desc : �A�C�h�����O���̏���
//---------------------------------------------------------------------------------------------------
void Idle(){
	//�@�ɂȎ��ɍĕ`��
	glutPostRedisplay();
}
void Timer(int value){
	glutTimerFunc( TIMER_WAIT, Timer, 0);
	Display();	//���t���[���̕`��
}

//---------------------------------------------------------------------------------------------------
// Name : Reshape()
// Desc : �T�C�Y�ύX
//---------------------------------------------------------------------------------------------------
void Reshape(int x, int y){
	//�@�E�B���h�E�T�C�Y��ۑ�
	WindowWidth = x;
	WindowHeight = y;

	//�@�T�C�Y�`�F�b�N
	if ( WindowWidth < 1 ) WindowWidth = 1;
	if ( WindowHeight < 1 ) WindowHeight = 1;

	//�@�r���[�|�[�g�̐ݒ�
	glViewport(0, 0, WindowWidth, WindowHeight);

	//�@�ˉe�s��̐ݒ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)WindowWidth/(double)WindowHeight, 0.1, 1000.0);
}

//--------------------------------------------------------------------------------------------------
// Name : Render2D()
// Desc : 2�����V�[���̕`��
//--------------------------------------------------------------------------------------------------
void Render2D(){
	bool isLighting = false;
	
	//�@���Ԍv����FPS�Z�o
	CurrentCount = glutGet(GLUT_ELAPSED_TIME);
	CurrentTime = (CurrentCount - LastCount)/1000.0;
	FrameCount++;
	if ( (CurrentTime - LastTime )>= 1.0 )
	{
		Fps = FrameCount/(CurrentTime - LastTime);
		printf("%.3f FPS\n", Fps);
		FrameCount = 0;
		LastTime = CurrentTime;
	}	

	//�@3D�@���@2D
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WindowWidth, WindowHeight, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	if ( glIsEnabled(GL_LIGHTING) )
	{
		isLighting = true;
		glDisable(GL_LIGHTING);
	}

	//�@�����̕`��

	p1->Render2D();	
	
	
	if ( !glIsEnabled(GL_LIGHTING) )
	{
		if ( isLighting )
			glEnable(GL_LIGHTING);
	}
	
	//�@2D�@���@3D
	glPopMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


//--------------------------------------------------------------------------------------------------
// Name : Render3D()
// Desc : 3�����V�[���̕`��
//--------------------------------------------------------------------------------------------------
void Render3D(){
	p1->Render3D();
}

//---------------------------------------------------------------------------------------------------
// Name : Display()
// Desc : �E�B���h�E�ւ̕`��
//---------------------------------------------------------------------------------------------------
void Display(){
	
	//�@�o�b�N�o�b�t�@���N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//�@���f���r���[�s��̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//�@���_�̐ݒ�
	p1->LookpointSet();

	//
	glPushMatrix();
	
	//�@3D�V�[���̕`��
	Render3D();	

	//�@2D�V�[���̕`��
	Render2D();

	//
	glPopMatrix();

	//�@�_�u���o�b�t�@
	glutSwapBuffers();
}

//---------------------------------------------------------------------------------------------------
// Name : Mouse()
// Desc : �}�E�X����
//---------------------------------------------------------------------------------------------------
void Mouse(int button, int state, int x, int y){
	switch ( button )
	{
	case GLUT_LEFT_BUTTON:
		switch ( state )
		{
		case GLUT_DOWN:
			break;

		case GLUT_UP:
			break;
		}
		break;

	case GLUT_MIDDLE_BUTTON:
		switch ( state )
		{
		case GLUT_DOWN:
			break;

		case GLUT_UP:
			break;
		}
		break;

	case GLUT_RIGHT_BUTTON:
		switch ( state )
		{
		case GLUT_DOWN:
			break;

		case GLUT_UP:
			break;
		}
		break;

	default:
		break;
	}
	

}

//--------------------------------------------------------------------------------------------------
// Name : Motion()
// Desc : �}�E�X�h���b�O��
//-------------------------------------------------------------------------------------------------
void Motion(int x, int y){
}

//--------------------------------------------------------------------------------------------------
// Name : PassiveMotion()
// Desc : �}�E�X�ړ���
//--------------------------------------------------------------------------------------------------
void PassiveMotion(int x, int y){
}

//--------------------------------------------------------------------------------------------------
// Name : Keyboard()
// Desc : �L�[�{�[�h����
//--------------------------------------------------------------------------------------------------
void Keyboard(unsigned char key, int x, int y){
	p1->KeyStateSet((int)key,true);
	switch ( key )
	{
	case '\033':
		exit(0);
		break;

	default:
		break;
	}
}

void KeyboardUp(unsigned char key,int x,int y){
	p1->KeyStateSet((int)key,false);
}

//--------------------------------------------------------------------------------------------------
// Name : Special()
// Desc : ����L�[����
//--------------------------------------------------------------------------------------------------
void Special(int key, int x, int y){
	p1->KeyStateSet(key,true);
	switch ( key )
	{
	case GLUT_KEY_F1:
		glutToggleFullScreen();
		break;

	case GLUT_KEY_F2:
		break;

	case GLUT_KEY_F3:
		break;

	case GLUT_KEY_F4:
		break;

	case GLUT_KEY_F5:
		break;

	case GLUT_KEY_F6:
		break;

	case GLUT_KEY_F7:
		break;

	case GLUT_KEY_F8:
		break;

	case GLUT_KEY_F9:
		break;

	case GLUT_KEY_F10:
		break;

	case GLUT_KEY_F11:
		break;

	case GLUT_KEY_F12:
		break;

	case GLUT_KEY_LEFT:
		break;

	case GLUT_KEY_RIGHT:
		break;

	case GLUT_KEY_UP:
		break;

	case GLUT_KEY_DOWN:
		break;

	case GLUT_KEY_PAGE_UP:
		break;

	case GLUT_KEY_PAGE_DOWN:
		break;

	case GLUT_KEY_HOME:
		break;

	case GLUT_KEY_END:
		break;

	case GLUT_KEY_INSERT:
		break;
	}
}

void SpecialUp(int key,int x,int y){
	p1->KeyStateSet(key,false);
}

//--------------------------------------------------------------------------------------------------
// Name : Close()
// Desc : ��Еt��
//--------------------------------------------------------------------------------------------------
void Close(){
	delete p1;
	mqoCleanup();
}

//--------------------------------------------------------------------------------------------------
// Name : glutRenderText()
// Desc : ASCII������̕`��
//--------------------------------------------------------------------------------------------------
void glutRenderText(void* bitmapfont, char*text){
	for ( int i=0; i<(int)strlen(text); i++ )
		glutBitmapCharacter(bitmapfont, (int)text[i]);
}

//--------------------------------------------------------------------------------------------------
// Name : glutToggleFullScreen()
// Desc : �t���X�N���[���ƃE�B���h�E���[�h�̐؂�ւ�
//--------------------------------------------------------------------------------------------------
void glutToggleFullScreen(){
	static bool FullScreenMode = false;
	static int beforeWidth = WindowWidth;
	static int beforeHeight = WindowHeight;
	static int beforePositionX = glutGet(GLUT_WINDOW_X);
	static int beforePositionY = glutGet(GLUT_WINDOW_Y);
	FullScreenMode ? FullScreenMode = false : FullScreenMode = true;
	if( FullScreenMode ){
		beforeWidth = WindowWidth;
		beforeHeight = WindowHeight;
		beforePositionX = glutGet(GLUT_WINDOW_X);
		beforePositionY = glutGet(GLUT_WINDOW_Y);
		glutFullScreen();
	}else{
		glutPositionWindow(beforePositionX, beforePositionY);
		glutReshapeWindow(beforeWidth, beforeHeight);
		glutShowWindow();
	}
}
