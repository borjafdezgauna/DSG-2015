// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CCube.h"

#define MOVE_STEP .008
#define ANGLE_STEP 0.05
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

// keyboard btns pressed 
bool eight = false;
bool two = false;
bool six = false;
bool four = false;
bool esc = false;


int m_x = 0;
int m_y = 0;

// mouse rotation
bool mouse_left_clicked  = false;
int mouse_first_position = 0;
int mouse_X_Diff = 0;


CCube * g_pCube1;
CCube * g_pCube2;



void Keyboard(unsigned char key,int x, int y)
{
	//keyboard callback function
	switch (key){
		case '8':	
			eight = true;
			break;
		case '2':	
			two = true;
			break;
		case '6':   
			six = true; 
			break;
		case '4':   
			four = true; 
			break;
		case 27: 
			esc = true;
	}
}

void Keyboard2(unsigned char key, int x, int y)
{
	//keyboard callback function
	switch (key){
		case '8':	
			eight = false; 
			break;
		case '2':	
			two = false; 
			break;
		case '6':   
			six = false; 
			break;
		case '4':   
			four = false; 
			break;
		case 27: 
			esc = false;
	}
}

void Mouse(int button, int state, int x, int y)
{

	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		switch (state)
		{
		case GLUT_DOWN:
			mouse_left_clicked = true;
			mouse_first_position = x;
			break;
		case GLUT_UP:
			mouse_left_clicked = false;
			break;
		}
		break;
	}
}

void MouseMotion(int x, int y){
	
		mouse_X_Diff = x - mouse_first_position;
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
	//glutFullScreen();
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);


	//callback functions
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(Keyboard2);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);


	// cube 
	g_pCube1 = new CCube(0.5);
	g_pCube2 = new CCube(2);

	g_pCube1->setPosition(2, 2, 2);
	g_pCube2->setPosition(3, 3, 3);

	g_pCube1->draw();

	while (1)
	{
		//UPDATE////////////////////
		////////////////////////////
		//"move" the cube
		g_cubeAngle+= 0.1;
		//queued events?
		glutMainLoopEvent();

		g_pCube1->draw();
		
		//Mover cubo si alguna flag es true
		if (eight == true)
		{
			g_x -= MOVE_STEP*sin(g_yaw*PI / 180);
			g_z -= MOVE_STEP*cos(g_yaw*PI / 180);
		}
		if (two == true)
		{
			g_x += MOVE_STEP*sin(g_yaw*PI / 180);
			g_z += MOVE_STEP*cos(g_yaw*PI / 180);
		}
		if (four == true)
		{
			g_yaw += ANGLE_STEP;
		}
		if (six == true)
		{
			g_yaw -= ANGLE_STEP;
		}
		if (esc == true)
		{
			exit(0);
		}

		if (mouse_left_clicked) {
			g_yaw += mouse_X_Diff * 0.00004;
		}

		//RENDER////////////////////
		////////////////////////////
		glutPostRedisplay();
		glutSwapBuffers();
	}

   return 0;
}