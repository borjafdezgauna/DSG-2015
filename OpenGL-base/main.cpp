#include "stdafx.h"

#include "CCube.h"

#define MOVE_STEP .004
#define ANGLE_STEP .02
#define PI 3.1416f

// Variables globales
float g_x = 0.0f;
float g_y = 0.0f;
float g_z = 10.0f;
float g_roll = 0.0f;
float g_pitch = 0.0f;
float g_yaw = 0.0f;
int g_w;
int g_h;
float g_cubeAngle = 0.f;

// Variables para el teclado (flags)
bool up_pressed = false;
bool down_pressed = false;
bool left_pressed = false;
bool right_pressed = false;

bool culling_enabled = false;
bool solid_drawing = false;
bool shade_model_smooth = true;

// Variables para el raton
bool mouse_left_clicked = false;
int initialPos = 0;
int mouseXDiff = 0;

// Gestion del raton
void Mouse(int button, int state, int x, int y)
{
	switch (button) 
	{
	case GLUT_LEFT_BUTTON:
		switch (state)
		{
		case GLUT_DOWN:
			mouse_left_clicked = true;
			initialPos = x;
			break;
		case GLUT_UP:
			mouse_left_clicked = false;
			break;
		}		
		break;
	}
}

void MouseMotion(int x, int y)
{
	mouseXDiff = x - initialPos;
}

// Gestion del teclado
void Keyboard(unsigned char key, int x, int y)
{
	printf("Tecla pulsada: %c\n", key);
	switch (key)
	{
	case '8':
		up_pressed = !up_pressed;
		break;
	case '2':
		down_pressed = !down_pressed;
		break;
	case '6':
		right_pressed = !right_pressed;
		break;
	case '4':
		left_pressed = !left_pressed;
		break;
	case 'c':
		culling_enabled = !culling_enabled;
		break;
	case 'm':
		solid_drawing = !solid_drawing;
		break;
	case 's':
		shade_model_smooth = !shade_model_smooth;
		break;
	case 27:
		exit(0);
	}
}

void KeyboardUp(unsigned char key, int x, int y)
{
	printf("Tecla levantada: %c\n", key);
	switch (key)
	{
	case '8':
		up_pressed = !up_pressed;
		break;
	case '2':
		down_pressed = !down_pressed;
		break;
	case '6':
		right_pressed = !right_pressed;
		break;
	case '4':
		left_pressed = !left_pressed;
		break;
	}
}

void Set3DView()
{
	// Establece la matriz de projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

	// Establece la matriz ModelView
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(-g_roll, 0.0, 0.0, 1.0);	
	glRotatef(-g_yaw, 0.0, 1.0, 0.0);
	glRotatef(-g_pitch, 1.0, 0.0, 0.0);	
	glTranslatef(-g_x, -g_y, -g_z);
}

void DrawCube()
{
	glColor3f (0.5, 1.0, 0.5);
	glMatrixMode(GL_MODELVIEW);
	
	glRotatef(g_cubeAngle, 1.0, 0.0, 0.0);
	glutWireCube (1.0);
}

void DrawCCubes()
{
	CCube* cube1 = new CCube();
	CCube* cube2 = new CCube();

	cube1->setSize(2.33);
	cube1->setPosition(-1, -1, -1);
	cube2->setPosition(2, 2, 2);

	cube1->draw(solid_drawing);
	cube2->draw(solid_drawing);
}

void DrawScene(void)
{
	// Limpia el backBuffer
	glClear (GL_COLOR_BUFFER_BIT);
	
	Set3DView();

	// Diferentes parametros controlados mediante teclas
	(culling_enabled) ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
	(shade_model_smooth) ? glShadeModel(GL_SMOOTH) : glShadeModel(GL_FLAT);

	//DrawCube();
	DrawCCubes();
}

void Reshape(int w, int h)
{
	g_h = h;
	g_w = w;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
}

int main(int argc, char** argv)
{
	// --- INIT GLUT -------------------------------------------------
	
	// Inicia la ventana y el contexto de OpenGL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1024, 768); 
	glutCreateWindow(argv[0]);
	//glutFullScreen();
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	// FUNCIONES CALLBACK
	// Se definen que funciones se llamaran para cuando ocurre determianadas operaciones
	// Reciben como parametro la fucncion que se va a llamar
	glutDisplayFunc(DrawScene); // la función para dibujar
	glutReshapeFunc(Reshape); // La funcion para redimensionar la ventana
	glutKeyboardFunc(Keyboard); // La funcion para cuando se pulsan las teclas
	glutKeyboardUpFunc(KeyboardUp); // La funcion para cuando se levantan las teclas
	glutMouseFunc(Mouse); // la fucion para cuando se pulasn los botones del raton
	glutMotionFunc(MouseMotion); // la funcion para cuando se mueve el raton

	while (1) // Bucle principal
	{
		// --- UPDATE ------------------------------------------------

		// Mueve el cubo
		g_cubeAngle += 0.1;

		if (up_pressed)
		{
			g_x -= MOVE_STEP*sin(g_yaw*PI / 180);
			g_z -= MOVE_STEP*cos(g_yaw*PI / 180);
		}

		if (down_pressed)
		{
			g_x += MOVE_STEP*sin(g_yaw*PI / 180);
			g_z += MOVE_STEP*cos(g_yaw*PI / 180);
		}

		if (left_pressed)
		{
			g_yaw -= ANGLE_STEP;
		}

		if (right_pressed)
		{
			g_yaw += ANGLE_STEP;
		}

		if (mouse_left_clicked) {
			g_yaw += mouseXDiff * 0.0001;
		}

		//queued events?
		glutMainLoopEvent();

		//--- RENDER ------------------------------------------------

		glutPostRedisplay();
		glutSwapBuffers();
	}

	return 0;
}