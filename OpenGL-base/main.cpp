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

CCube* cube1;
CCube* cube2;
GLuint textureID;

// Variables para el teclado (flags)
bool up_pressed = false;
bool down_pressed = false;
bool left_pressed = false;
bool right_pressed = false;

bool culling_enabled = true;
bool solid_drawing = true;
bool shade_model_smooth = true;
bool enable_lighting = true;

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
	printf("Pressed Key: %c\n", key);
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
	case 'l':
		enable_lighting = !enable_lighting;
		break;
	case 27:
		exit(0);
	}
}

void KeyboardUp(unsigned char key, int x, int y)
{
	printf("Released Key: %c\n", key);
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

	// Culling
	if (culling_enabled) 
		glEnable(GL_CULL_FACE);
	else 
		glDisable(GL_CULL_FACE);

	// Shade model
	if (shade_model_smooth)
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);

	// Iluminacion
	if (enable_lighting) {
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0); // Activamos la luz #0
	}
	else {
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0); // Desactivamos la luz #0
	}
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
	cube1->draw(solid_drawing);
	cube2->draw(solid_drawing);
}

void DrawScene(void)
{
	// Limpia el backBuffer
	glClear (GL_COLOR_BUFFER_BIT);
	
	Set3DView();

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

	// Propiedades de la iluminacion para GL_LIGHT0
	GLfloat light_ambient [] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_difuse [] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular [] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_direction [] = { -1.0, -1.0, -1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_difuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);

	// Cargar la textura
	

	// Los cubos para dibujar
	cube1 = new CCube();
	cube2 = new CCube();
	cube1->setSize(2.33f);
	cube1->setPosition(-1, -1, -1);
	cube2->setPosition(2, 2, 2);
	cube1->setTexture("diamond.png");
	cube2->setTexture("diamond.png");


	while (1) // Bucle principal
	{
		// --- UPDATE ------------------------------------------------

		// Mueve el cubo
		g_cubeAngle += 0.1f;

		if (up_pressed)
		{
			g_x -= (float) MOVE_STEP*sin(g_yaw*PI / 180);
			g_z -= (float) MOVE_STEP*cos(g_yaw*PI / 180);
		}

		if (down_pressed)
		{
			g_x += (float) MOVE_STEP*sin(g_yaw*PI / 180);
			g_z += (float) MOVE_STEP*cos(g_yaw*PI / 180);
		}

		if (left_pressed)
		{
			g_yaw -= (float) ANGLE_STEP;
		}

		if (right_pressed)
		{
			g_yaw += (float) ANGLE_STEP;
		}

		if (mouse_left_clicked) {
			g_yaw += mouseXDiff * 0.0001f;
		}

		//queued events?
		glutMainLoopEvent();

		//--- RENDER ------------------------------------------------

		glutPostRedisplay();
		glutSwapBuffers();
	}

	return 0;
}