// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MOVE_STEP .005
#define ANGLE_STEP 0.2
#define PI 3.1416f

float g_x=0.0f;
float g_y=0.0f;
float g_z=10.0f;
float g_roll= 0.0f;
float g_pitch= 0.0f;
float g_yaw= 0.0f;
int g_w;
int g_h;
float g_cubeAngle= 0.f;
bool g_flag8 = false;
bool g_flag2 = false;
bool g_flag4 = false;
bool g_flag6 = false;

bool g_flagLB = false;
bool g_flagRB = false;
int g_tempX = g_x;
int g_tempY = g_y;
int g_temp2X = g_x;
int g_temp2Y = g_y;


void Keyboard(unsigned char key,int x, int y)
{
	//keyboard callback function
	switch (key)
	{
	case '8':	g_x-= MOVE_STEP*sin(g_yaw*PI/180);
				g_z-= MOVE_STEP*cos(g_yaw*PI/180);break;
	case '2':	g_x+= MOVE_STEP*sin(g_yaw*PI/180);
				g_z+= MOVE_STEP*cos(g_yaw*PI/180);break;
	case '6': g_yaw-= ANGLE_STEP; break;
	case '4': g_yaw+= ANGLE_STEP; break;
	case 27: exit(0);
	}
}

void Keyboard2(unsigned char key, int x, int y)
{
	//keyboard callback function
	switch (key)
	{
	case '8':	g_flag8 = true;
				break;
	case '2':	g_flag2 = true;
				break;
	case '6': g_flag6 = true; 
				break;
	case '4': g_flag4 = true; 
				break;
	case 27: exit(0);
	}
}

void KeyboardUp(unsigned char key, int x, int y)
{
	//keyboard callback function
	switch (key)
	{
	case '8':	g_flag8 = false;
		break;
	case '2':	g_flag2 = false;
		break;
	case '6': g_flag6 = false;
		break;
	case '4': g_flag4 = false;
		break;
	case 27: exit(0);
	}
}

void Click(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state== GLUT_DOWN && !g_flagLB){
		g_flagLB = true;
		g_tempX = x;
		g_tempY = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && g_flagLB){
		//Ifs para direccion de camara
		if (g_tempX < x){
			g_yaw += (x - g_tempX)*ANGLE_STEP;
		}
		if (g_tempX > x){
			g_yaw -= (g_tempX - x)*ANGLE_STEP;
		}
		if (g_tempY < y){
			g_yaw += ANGLE_STEP;
		}
		if (g_tempY > y){
			g_yaw -= ANGLE_STEP;
		}

		g_tempX = x;
		g_tempY = y;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		g_flagLB = false;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		g_flagRB = true;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
		g_flagRB = false;
	}
}

void Set3DView()
{
	//set projection matrix
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

	//set modelview matrix
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glRotatef(-g_roll, 0.0, 0.0, 1.0);	
	glRotatef(-g_yaw, 0.0, 1.0, 0.0);
	glRotatef(-g_pitch, 1.0, 0.0, 0.0);	
	glTranslatef(-g_x, -g_y, -g_z);
}

void DrawCube()
{
	glColor3f (0.5, 1.0, 0.5);
	glMatrixMode(GL_MODELVIEW);
	
	glRotatef(g_cubeAngle,1.0,0.0,0.0);
	glutWireCube (1.0);
}

void DrawScene(void)
{
	//clean the backbuffer
	glClear (GL_COLOR_BUFFER_BIT);

	//viewing transformation
	Set3DView();

	//draw the cube
	DrawCube();

}

void Reshape (int w, int h)
{
	//Reshape callback function
	g_h= h;
	g_w= w;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
}

int main(int argc, char** argv)
{

	//INIT GLUT/////////////////////
	////////////////////////////////
	//init window and OpenGL context
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (1024, 768); 
	glutCreateWindow (argv[0]);
	glutSetKeyRepeat(0);

	//glutFullScreen();


	//callback functions
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard2);
	glutKeyboardUpFunc(KeyboardUp);
	glutMouseFunc(Click);




	while (1)
	{
		//UPDATE////////////////////
		////////////////////////////
		//"move" the cube
		g_cubeAngle+= 0.1;
		//queued events?
		glutMainLoopEvent();


		//RENDER////////////////////
		////////////////////////////
		glutPostRedisplay();
		glutSwapBuffers();

		if (g_flag8){
			g_x -= MOVE_STEP*sin(g_yaw*PI / 180);
			g_z -= MOVE_STEP*cos(g_yaw*PI / 180); 
		} 
		if(g_flag2)
		{
			g_x += MOVE_STEP*sin(g_yaw*PI / 180);
			g_z += MOVE_STEP*cos(g_yaw*PI / 180);
		}
		if (g_flag6)
		{
			g_yaw -= ANGLE_STEP;
		}
		if (g_flag4)
		{
			g_yaw += ANGLE_STEP;
		}
		/*
		if (g_flagLB )
		{
			if (g_tempX < x){
				g_yaw += ()*ANGLE_STEP;
			}
			if (g_tempX > x){
				g_yaw -= ANGLE_STEP;
			}			
		}*/
	}
   return 0;
}