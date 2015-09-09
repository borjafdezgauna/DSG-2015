// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GLExtensions.h"

#define MOVE_STEP .4
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

void initShaders()
{
	char *vertexProgram[]= {"varying vec3 lightDir,normal;","void main()","{"
		,"normal = normalize(gl_NormalMatrix * gl_Normal);"
		,"lightDir = normalize(vec3(gl_LightSource[0].position));"
		,"gl_TexCoord[0] = gl_MultiTexCoord0;","gl_Position = ftransform();","}"
	};
	char *fragmentProgram[]= {"varying vec3 lightDir,normal;"
		,"uniform sampler2D tex;","void main()","{","vec3 ct,cf;"
		,"vec4 texel;","float intensity,at,af;"
		,"intensity = max(dot(lightDir,normalize(normal)),0.0);"
		,"cf = intensity * (gl_FrontMaterial.diffuse).rgb + gl_FrontMaterial.ambient.rgb;"
		,"af = gl_FrontMaterial.diffuse.a;"
		,"texel = texture2D(tex,gl_TexCoord[0].st);"
		,"ct = texel.rgb;","at = texel.a;","gl_FragColor = vec4(ct * cf, at * af);","}"};


	QueryGLExtFunctionPointers();

	GLenum my_program;
	GLenum my_vertex_shader;
	GLenum my_fragment_shader;
	 
	// Create Shader And Program Objects
	my_program = glCreateProgramObjectARB();
	my_vertex_shader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	my_fragment_shader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	 
	// Load Shader Sources
	glShaderSourceARB(my_vertex_shader, 1, (const GLcharARB**)vertexProgram, NULL);
	glShaderSourceARB(my_fragment_shader, 1, (const GLcharARB**)fragmentProgram, NULL);
	 
	// Compile The Shaders
	glCompileShaderARB(my_vertex_shader);
	glCompileShaderARB(my_fragment_shader);
	
	GLcharARB log[512];
	int logSize;


	// Attach The Shader Objects To The Program Object
	glAttachObjectARB(my_program, my_vertex_shader);
	glAttachObjectARB(my_program, my_fragment_shader);


	glValidateProgramARB(my_vertex_shader);
	glGetInfoLogARB(my_vertex_shader,512,&logSize,log);
	glValidateProgramARB(my_fragment_shader);
	glGetInfoLogARB(my_fragment_shader,512,&logSize,log);
	glValidateProgramARB(my_program);
	glGetInfoLogARB(my_fragment_shader,512,&logSize,log); 	 

	// Link The Program Object
	glLinkProgramARB(my_program);
	

	// Use The Program Object Instead Of Fixed Function OpenGL
	glUseProgramObjectARB(my_program);
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

	initShaders();

	//callback functions
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);


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
	}
   return 0;
}