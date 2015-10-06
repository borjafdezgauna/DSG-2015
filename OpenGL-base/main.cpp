// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CCube.h"

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

//Variables para gestionar el teclado
bool ochoPulsado = false;
bool dosPulsado = false;
bool cuatroPulsado = false;
bool seisPulsado = false;
bool solido = false;
bool cullingActivo = false;

//Variables para gestionar el ratón
bool ratonPulsado = false;
int Xpos;
int diferencia;


void Keyboard(unsigned char key,int x, int y)
{
	//keyboard callback function
	switch (key)
	{
	case '8':	ochoPulsado = !ochoPulsado; break;
	case '2':	dosPulsado = !dosPulsado;	break;
	case '6':	seisPulsado = !seisPulsado;	break;
	case '4':	cuatroPulsado = !cuatroPulsado;	break;
	case 'm':	solido = !solido; break;
	case 'c':	cullingActivo = !cullingActivo; break;
	}
}

void KeyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '8':	ochoPulsado = !ochoPulsado; break;
	case '2':	dosPulsado = !dosPulsado;	break;
	case '6':	seisPulsado = !seisPulsado;	break;
	case '4':	cuatroPulsado = !cuatroPulsado;	break;
	case 27: exit(0);
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		switch (state)
		{
		case GLUT_DOWN: 
			if (!ratonPulsado)
			{
				ratonPulsado = true;
				Xpos = x;
			}
			else{
				diferencia = x - Xpos;
			}
			break;
		
		case GLUT_UP:     
			ratonPulsado = false;
			break;
		}
	}
}

void Motion(int x, int y)
{
	diferencia = x - Xpos;
}

void Set3DView()
{
	// Definimos la matriz de proyección
	glMatrixMode (GL_PROJECTION);
	// La inicializamos cargando la matriz de identidad con la siguiente función
	glLoadIdentity ();
	glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

	// Definimos la matriz de visionado
	glMatrixMode (GL_MODELVIEW);
	// También la inicializamos con la matriz identidad
	glLoadIdentity ();
	// Con las siguientes funciones trasladamos y rotamos
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

	if (cullingActivo)
	{
		glEnable(GL_CULL_FACE);
	}
	else{
		glDisable(GL_CULL_FACE);
	}

	//draw the cube
	//DrawCube();
	
	// Creamos dos cubos, seguidamente asignamos una posición al segundo y los dibujamos
	CCube* cubo1 = new CCube();
	CCube* cubo2 = new CCube();

	cubo2->setPosition(4, 4, 4);

	cubo1->draw(solido);
	cubo2->draw(solido);


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
	
	// Con la función init recogemos los parámetros de la línea de comandos
	glutInit(&argc, argv);
	// Con esta función le indicamos al sistema gráfico como queremos renderizar, le asignamos un doble buffer
	// y lectura RGB de los colores
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	// Definimos las medidas de la ventana
	glutInitWindowSize (1024, 768); 
	// Creamos la ventana
	glutCreateWindow (argv[0]);
	glutFullScreen();

	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);


	//callback functions
	// Esta funciones son llamadas cuando el usuario interactua con la apliación
	glutDisplayFunc(DrawScene);  // Función de control del render
	glutReshapeFunc(Reshape);    // Función que controla el cambio en el tamaño de la ventana
	glutKeyboardFunc(Keyboard);  // Función que controla eventos de teclado
	glutKeyboardUpFunc(KeyboardUp);// Función que controla eventos del teclado al dejar de pulsar la tecla
	glutMouseFunc(Mouse);        // Función que controla eventos de teclado
	glutMotionFunc(Motion);      // Función que controla movimiento

	while (1)
	{
		//UPDATE////////////////////
		//"move" the cube
		g_cubeAngle+= 0.1;

		if (ochoPulsado)
		{
			g_x -= MOVE_STEP*sin(g_yaw*PI / 180);
			g_z -= MOVE_STEP*cos(g_yaw*PI / 180);
		}

		if (dosPulsado)
		{
			g_x += MOVE_STEP*sin(g_yaw*PI / 180);
			g_z += MOVE_STEP*cos(g_yaw*PI / 180); 
		}

		if (seisPulsado)
		{
			g_yaw -= ANGLE_STEP; 
		}

		if (cuatroPulsado)
		{
			g_yaw += ANGLE_STEP; 
		}

		if (ratonPulsado)
		{
			g_yaw += diferencia * 0.0001;
		}

		//queued events?
		glutMainLoopEvent();


		//RENDER////////////////////
		glutPostRedisplay();
		glutSwapBuffers();
	}
   return 0;
}