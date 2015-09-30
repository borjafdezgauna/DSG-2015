#include "stdafx.h"
#include "Cube.h"



CCube::CCube()
{

}


CCube::~CCube()
{
}

void CCube::draw(){

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(m_x, m_y, m_z);
	glBegin(GL_QUADS);
	//cara1
	glColor3f(0.2, 0.3, 0.4);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	//cara2
	glColor3f(0.3, 0.4, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	//cara3
	glColor3f(0.4, 0.5, 0.6);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5,-0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	//cara4
	glColor3f(0.5, 0.6, 0.7);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5,-0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	//cara5
	glColor3f(0.6, 0.7, 0.8);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	//cara6
	glColor3f(0.7,0.8, 0.9);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);

	glEnd();

	glPopMatrix();

}

void CCube::setPosition(float x, float y, float z){
	m_x = x;
	m_y = y;
	m_z = z;
}
