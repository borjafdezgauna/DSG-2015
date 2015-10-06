#include "stdafx.h"
#include "CCube.h"

CCube::CCube()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_pitch = 0;
	m_yaw = 0;
	m_roll = 0;
	m_r = 0.3;
	m_b = 0.4;
	m_g = 0.7;
	m_scaleX = 1;
	m_scaleY = 1;
	m_scaleZ = 1;
}

CCube::~CCube()
{

}

void CCube::setPosition(int x, int y, int z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

void CCube::setRotation(float pitch, float yaw, float roll)
{
	m_yaw = yaw;
	m_pitch = pitch;
	m_roll = roll;
}

void CCube::setScale(double x, double y, double z)
{
	m_scaleX = x;
	m_scaleY = y;
	m_scaleZ = z;
}

void CCube::setColor(float r, float g, float b)
{
	m_r = r/255;
	m_g = g/255;
	m_b = b/255;
}

void CCube::draw(bool solid)
{
	//Asigno el color del cubo
	glColor3f(m_r, m_g, m_b);
	//Asignamos la matriz de modelview
	glMatrixMode(GL_MODELVIEW);

	if (solid)
	{
		glPushMatrix();
		//Dibujamos las 6 caras del cubo
		glBegin(GL_QUADS);

		//Dibujamos la primera cara ( la del fondo)
		glVertex3i(m_x, m_y, m_z);
		glVertex3i(m_x, m_y + 1, m_z);
		glVertex3i(m_x + 1, m_y + 1, m_z);
		glVertex3i(m_x + 1, m_y, m_z);


		//Dibujamos la segunda cara (la primera)
		glVertex3i(m_x, m_y, m_z - 1);
		glVertex3i(m_x + 1, m_y, m_z - 1);
		glVertex3i(m_x + 1, m_y + 1, m_z - 1);
		glVertex3i(m_x, m_y + 1, m_z - 1);

		//Dibujamos la tercera cara (la de arriba)
		glVertex3i(m_x, m_y + 1, m_z);
		glVertex3i(m_x, m_y + 1, m_z - 1);
		glVertex3i(m_x + 1, m_y + 1, m_z - 1);
		glVertex3i(m_x + 1, m_y + 1, m_z);

		//Dibujamos la cuarta cara (la de abajo)
		glVertex3i(m_x, m_y, m_z);
		glVertex3i(m_x + 1, m_y, m_z);
		glVertex3i(m_x + 1, m_y, m_z - 1);
		glVertex3i(m_x, m_y, m_z - 1);


		//Dibujamos la quinta cara ( la cara de la izquierda)
		glVertex3i(m_x, m_y, m_z);
		glVertex3i(m_x, m_y, m_z - 1);
		glVertex3i(m_x, m_y + 1, m_z - 1);
		glVertex3i(m_x, m_y + 1, m_z);

		//Dibujamos la sexta cara (la cara de la derecha)
		glVertex3i(m_x + 1, m_y, m_z);
		glVertex3i(m_x + 1, m_y + 1, m_z);
		glVertex3i(m_x + 1, m_y + 1, m_z - 1);
		glVertex3i(m_x + 1, m_y, m_z - 1);
		//Para terminar de dibujar las caras
		glEnd();

		glPopMatrix();
	}
	else{
		glPushMatrix();
		//Dibujamos las 6 caras del cubo

		//Dibujamos la primera cara ( la del fondo)
		glBegin(GL_LINE_LOOP);
		glVertex3i(m_x, m_y, m_z);
		glVertex3i(m_x, m_y + 1, m_z);
		glVertex3i(m_x + 1, m_y + 1, m_z);
		glVertex3i(m_x + 1, m_y, m_z);
		glEnd();


		//Dibujamos la segunda cara (la primera)
		glBegin(GL_LINE_LOOP);
		glVertex3i(m_x, m_y, m_z - 1);
		glVertex3i(m_x + 1, m_y, m_z - 1);
		glVertex3i(m_x + 1, m_y + 1, m_z - 1);
		glVertex3i(m_x, m_y + 1, m_z - 1);
		glEnd();

		//Dibujamos la tercera cara (la de arriba)
		glBegin(GL_LINE_LOOP);
		glVertex3i(m_x, m_y + 1, m_z);
		glVertex3i(m_x, m_y + 1, m_z - 1);
		glVertex3i(m_x + 1, m_y + 1, m_z - 1);
		glVertex3i(m_x + 1, m_y + 1, m_z);
		glEnd();

		//Dibujamos la cuarta cara (la de abajo)
		glBegin(GL_LINE_LOOP);
		glVertex3i(m_x, m_y, m_z);
		glVertex3i(m_x + 1, m_y, m_z);
		glVertex3i(m_x + 1, m_y, m_z - 1);
		glVertex3i(m_x, m_y, m_z - 1);
		glEnd();


		//Dibujamos la quinta cara ( la cara de la izquierda)
		glBegin(GL_LINE_LOOP);
		glVertex3i(m_x, m_y, m_z);
		glVertex3i(m_x, m_y, m_z - 1);
		glVertex3i(m_x, m_y + 1, m_z - 1);
		glVertex3i(m_x, m_y + 1, m_z);
		glEnd();

		//Dibujamos la sexta cara (la cara de la derecha)
		glBegin(GL_LINE_LOOP);
		glVertex3i(m_x + 1, m_y, m_z);
		glVertex3i(m_x + 1, m_y + 1, m_z);
		glVertex3i(m_x + 1, m_y + 1, m_z - 1);
		glVertex3i(m_x + 1, m_y, m_z - 1);
		glEnd();

		glPopMatrix();
	}
}