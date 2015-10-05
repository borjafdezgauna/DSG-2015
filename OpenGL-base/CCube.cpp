#include "stdafx.h"

#include "CCube.h"

CCube::CCube()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->pitch = 0.0f;
	this->roll = 0.0f;
	this->yaw = 0.0f;
	this->r = 0.8f;
	this->g = 0.8f;
	this->b = 0.8f;
	this->scale_x = 1.0f;
	this->scale_y = 1.0f;
	this->scale_z = 1.0f;
	this->h = 1.0f;
}

void CCube::setSize(double h)
{
	this->h = h;
}

void CCube::setPosition(int x, int y, int z)
{
	this->x = (double) x;
	this->y = (double) y;
	this->z = (double) z;
}

void CCube::setRotation(double pitch, double yaw, double roll)
{
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;
}

void CCube::setScale(double x, double y, double z)
{
	this->scale_x = x;
	this->scale_y = y;
	this->scale_z = z;
}

void CCube::setColor(int r, int g, int b)
{
	this->r = r / 255;
	this->g = g / 255;
	this->b = b / 255;
}

void CCube::draw(bool solid)
{
	glColor3d(r, g, b);
	glMatrixMode(GL_MODELVIEW);
	
	if (solid) {
		glPushMatrix();
		glBegin(GL_QUADS);

		// CARA 1 (la del fondo)
		glVertex3d(x, y + h, z);
		glVertex3d(x + h, y + h, z);
		glVertex3d(x + h, y, z);
		glVertex3d(x, y, z);

		// CARA 2 (lade delante del todo)
		glVertex3d(x, y, z - h);
		glVertex3d(x + h, y, z - h);
		glVertex3d(x + h, y + h, z - h);
		glVertex3d(x, y + h, z - h);

		// CARA 3 (la de arriba)
		glVertex3d(x, y + h, z);
		glVertex3d(x, y + h, z - h);
		glVertex3d(x + h, y + h, z - h);
		glVertex3d(x + h, y + h, z);

		// CARA 4 (la del abajo)
		glVertex3d(x + h, y, z);
		glVertex3d(x + h, y, z - h);
		glVertex3d(x, y, z - h);
		glVertex3d(x, y, z);

		// CARA 5 (la de la izquierda)
		glVertex3d(x, y, z);
		glVertex3d(x, y, z - h);
		glVertex3d(x, y + h, z - h);
		glVertex3d(x, y + h, z);

		// CARA 6 (la de la derecha)
		glVertex3d(x + h, y + h, z);
		glVertex3d(x + h, y + h, z - h);
		glVertex3d(x + h, y, z - h);
		glVertex3d(x + h, y, z);

		glEnd();
		glPopMatrix();
	}
	else {
		glPushMatrix();

		// CARA 1 (la del fondo)
		glBegin(GL_LINE_LOOP);
		glVertex3d(x, y + h, z);
		glVertex3d(x + h, y + h, z);
		glVertex3d(x + h, y, z);
		glVertex3d(x, y, z);
		glEnd();

		// CARA 2 (lade delante del todo)
		glBegin(GL_LINE_LOOP);
		glVertex3d(x, y, z - h);
		glVertex3d(x + h, y, z - h);
		glVertex3d(x + h, y + h, z - h);
		glVertex3d(x, y + h, z - h);
		glEnd();

		// CARA 3 (la de arriba)
		glBegin(GL_LINE_LOOP);
		glVertex3d(x, y + h, z);
		glVertex3d(x, y + h, z - h);
		glVertex3d(x + h, y + h, z - h);
		glVertex3d(x + h, y + h, z);
		glEnd();

		// CARA 4 (la del abajo)
		glBegin(GL_LINE_LOOP);
		glVertex3d(x + h, y, z);
		glVertex3d(x + h, y, z - h);
		glVertex3d(x, y, z - h);
		glVertex3d(x, y, z);
		glEnd();

		// CARA 5 (la de la izquierda)
		glBegin(GL_LINE_LOOP);
		glVertex3d(x, y, z);
		glVertex3d(x, y, z - h);
		glVertex3d(x, y + h, z - h);
		glVertex3d(x, y + h, z);
		glEnd();

		// CARA 6 (la de la derecha)
		glBegin(GL_LINE_LOOP);
		glVertex3d(x + h, y + h, z);
		glVertex3d(x + h, y + h, z - h);
		glVertex3d(x + h, y, z - h);
		glVertex3d(x + h, y, z);
		glEnd();

		glPopMatrix();
	}
	
}