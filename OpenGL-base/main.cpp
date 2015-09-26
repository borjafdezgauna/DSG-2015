// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MOVE_STEP .01
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

bool g_flagLeftDown = false;
float g_xClick = 0.0f;
float g_yClick = 0.0f;


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

void Click( int x, int y )
{
	if (g_xClick > x)
	{
		g_yaw -= 0.85;
	}
	if (g_xClick < x)
	{
		g_yaw += 0.85;
	}

	g_xClick = x;
	g_yClick = y;

}

void Click2(int button, int state, int x, int y)
{
	if (GLUT_LEFT_BUTTON == button && GLUT_DOWN == state)
	{
		g_flagLeftDown = true;
	}
	else
	{
		g_flagLeftDown = false;
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
	glutMotionFunc(Click);
	glutMouseFunc(Click2);


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
		if ( g_flagLeftDown )
		{
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		else
		{
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	}
   return 0;
}