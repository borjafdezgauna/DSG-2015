// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Cube.h"

#define MOVE_STEP .4
#define ANGLE_STEP 0.2
#define PI 3.1416f

float g_pos, g_posDif;
bool  g_fdown = false;
bool g_f2, g_f4, g_f6, g_f8, g_f5;
CCube g_pCube1;
CCube g_pCube2;


float g_x=0.0f;
float g_y=0.0f;
float g_z=10.0f;
float g_roll= 0.0f;
float g_pitch= 0.0f;
float g_yaw= 0.0f;
int g_w;
int g_h;
float g_cubeAngle= 0.f;



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
	switch (key)
	{
	case '8':	g_f8 = true; break;

	case '2':	g_f2 = true; break;

	case '6': g_f6 = true; break;

	case '4': g_f4 = true; break;

	case'c':g_f5 = true; break;
		
	

	case 27: exit(0);
	}
}

void Keyboard3(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '8':	g_f8 = false; break;

	case '2':	g_f2 = false; break;

	case '6': g_f6 = false; break;

	case '4': g_f4 = false; break;

	case'c':g_f5 = false; break;

	case 27: exit(0);

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
	//DrawCube();
	
	g_pCube1.setPosition(0, 0, 0);
	g_pCube1.setPosition(2, 5, 0);
	g_pCube1.draw();
	g_pCube2.draw();

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

void Mouse(int button, int state, int x, int y){

	if (GLUT_LEFT_BUTTON == button && GLUT_DOWN == state)
	{
		g_fdown = true;
		g_pos = x;

	}
	if (GLUT_LEFT_BUTTON != button && GLUT_DOWN != state){
		g_fdown = false;
	}
}

void Movimiento(int x, int y){
	if (g_fdown){
		g_posDif = g_pos - x;
	}
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
	//glutFullScreen();
	

	//callback functions
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	//glutKeyboardFunc(Keyboard);
	glutKeyboardFunc(Keyboard2);
	glutKeyboardUpFunc(Keyboard3);
	glutMouseFunc(Mouse);
	glutMotionFunc(Movimiento);

	

	if (g_f5){
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	while (1)
	{
		//UPDATE////////////////////
		////////////////////////////
		//"move" the cube
		g_cubeAngle+= 0.1;
		//queued events?
		glutMainLoopEvent();

		if (g_f2){
			g_x += MOVE_STEP*sin(g_yaw*PI / 180);
			g_z += MOVE_STEP*cos(g_yaw*PI / 180);
		}
		if (g_f4){
			g_yaw += ANGLE_STEP;
		}
		if (g_f6){
			g_yaw -= ANGLE_STEP;
		}
		if (g_f8){
			g_x -= MOVE_STEP*sin(g_yaw*PI / 180);
			g_z -= MOVE_STEP*cos(g_yaw*PI / 180);
		}

		if (g_fdown){
			g_yaw = g_posDif*0.2;
		}

		//RENDER////////////////////
		////////////////////////////
		glutPostRedisplay();
		glutSwapBuffers();
	}
   return 0;
}