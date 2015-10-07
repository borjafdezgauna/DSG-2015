#include "stdafx.h"
#include "CCube.h"


CCube::CCube(double h)
{
	m_h = h;
}


CCube::~CCube()
{
}

void CCube::setPosition(int x, int y, int z) {
	m_ix = x;
	m_iy = y;
	m_iz = z;
}

void CCube::setRotation(double pitch, double yaw, double roll) {
	m_pitch = pitch;
	m_yaw = yaw;
	m_roll = roll;
}

void CCube::setScale(double x, double y, double z){
	m_dx = x;
	m_dy = y;
	m_dz = z;
}

void CCube::setColor(int r, int g, int b){
	m_r = r;
	m_g = g;
	m_b = b;
}

void CCube::draw(){

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);

	//glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -7.0f);

	glPushMatrix();
	glBegin(GL_QUADS);

	//front side
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3i(m_ix, m_iy, -m_iz);
	glVertex3i(m_ix + m_h, m_iy, -m_iz);
	glVertex3i(m_ix + m_h, m_iy + m_h, -m_iz);
	glVertex3i(m_ix, m_iy + m_h, -m_iz);

	//back side
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3i(m_ix, m_iy, -m_iz - m_h);
	glVertex3i(m_ix + m_h, m_iy, -m_iz - m_h);
	glVertex3i(m_ix + m_h, m_iy + m_h, -m_iz - m_h);
	glVertex3i(m_ix, m_iy + m_h, -m_iz - m_h);

	//down side
	glColor3f(0.8f, 0.8f, 1.0f);
	glVertex3i(m_ix, m_iy, -m_iz);
	glVertex3i(m_ix + m_h, m_iy, -m_iz);
	glVertex3i(m_ix + m_h, m_iy, -m_iz - m_h);
	glVertex3i(m_ix, m_iy, -m_iz - m_h);

	//up side
	glColor3f(0.2f, 0.8f, 0.2f);
	glVertex3i(m_ix + m_h, m_iy + m_h, -m_iz);
	glVertex3i(m_ix, m_iy + m_h, -m_iz);
	glVertex3i(m_ix, m_iy + m_h, -m_iz - m_h);
	glVertex3i(m_ix + m_h, m_iy + m_h, -m_iz - m_h);
	
	//left side
	glColor3f(0.6f, 0.1f, 0.3f);
	glVertex3i(m_ix, m_iy, -m_iz);
	glVertex3i(m_ix, m_iy + m_h, -m_iz);
	glVertex3i(m_ix, m_iy + m_h, -m_iz - m_h);
	glVertex3i(m_ix, m_iy, -m_iz - m_h);
	

	//right side
	glColor3f(0.2f, 0.7f, 0.7f);
	glVertex3i(m_ix + m_h, m_iy, -m_iz);
	glVertex3i(m_ix + m_h, m_iy + m_h, -m_iz);
	glVertex3i(m_ix + m_h, m_iy + m_h, -m_iz - m_h);
	glVertex3i(m_ix + m_h, m_iy, -m_iz - m_h);
	


	glPopMatrix();
	glEnd();

	
	


}
