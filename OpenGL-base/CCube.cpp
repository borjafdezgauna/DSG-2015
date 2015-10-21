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
	this->r = 0.0f;
	this->g = 1.0f;
	this->b = 0.0f;
	this->scale_x = 1.0f;
	this->scale_y = 1.0f;
	this->scale_z = 1.0f;
	this->h = 1.0f;
	this->textureID = 0;
}

void CCube::setSize(float h)
{
	this->h = h;
}

void CCube::setPosition(int x, int y, int z)
{
	this->x = (float) x;
	this->y = (float) y;
	this->z = (float) z;
}

void CCube::setRotation(float pitch, float yaw, float roll)
{
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;
}

void CCube::setScale(float x, float y, float z)
{
	this->scale_x = x;
	this->scale_y = y;
	this->scale_z = z;
}

void CCube::setColor(int r, int g, int b)
{
	this->r = (float) r / 255;
	this->g = (float) g / 255;
	this->b = (float) b / 255;
}

void CCube::setTexture(const char* filename)
{
	this->textureID = SOIL_load_OGL_texture("diamond.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	if (this->textureID == 0)
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	else
		printf("Texture ID: %d\n", textureID);
}

void CCube::draw(bool solid)
{
	glColor3d(r, g, b);
	glMatrixMode(GL_MODELVIEW);

	// Propiedades de material del cubo
	GLfloat mat_ambient[] = { 1.0, 0.2, 0.2, 8.0 };
	GLfloat mat_diffuse[] = { 1.0, 0.2, 0.2, 8.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.5 };
	GLfloat low_shininess[] = { 5.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);

	// Propiedades de la textura del cubo
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glPushMatrix();

	if (solid) {
		//glTranslated(x, y, z);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glEnable(GL_BLEND);
		//glBlendFunc(GLEnum srcfactor, GLenum destfactor);
		//glBlendEquation(GLenum mode);

		glBegin(GL_QUADS);

		// CARA 1 (la de delante)
		glColor3f(0.2, 0.3, 0.4);
		GLfloat normal1 [] = { 0, 0, 1 };
		glNormal3fv(normal1);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x - h / 2, y - h / 2, z + h / 2);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x + h / 2, y - h / 2, z + h / 2);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x + h / 2, y + h / 2, z + h / 2);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x - h / 2, y + h / 2, z + h / 2);

		// CARA 2 (la de la derecha)
		glColor3f(0.3, 0.4, 0.5);
		GLfloat normal2 [] = { 1, 0, 0 };
		glNormal3fv(normal2);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + h / 2, y - h / 2, z + h / 2);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x + h / 2, y - h / 2, z - h / 2);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x + h / 2, y + h / 2, z - h / 2);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x + h / 2, y + h / 2, z + h / 2);

		// CARA 3 (la de arriba)
		glColor3f(0.4, 0.5, 0.6);
		GLfloat normal3 [] = { 0, 1, 0 };
		glNormal3fv(normal3);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x + h / 2, y + h / 2, z + h / 2);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x + h / 2, y + h / 2, z - h / 2);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x - h / 2, y + h / 2, z - h / 2);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x - h / 2, y + h / 2, z + h / 2);

		// CARA 4 (la de la izquierda)
		glColor3f(0.5, 0.6, 0.7);
		GLfloat normal4 [] = { -1, 0, 0 };
		glNormal3fv(normal4);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x - h / 2, y + h / 2, z + h / 2);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x - h / 2, y + h / 2, z - h / 2);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x - h / 2, y - h / 2, z - h / 2);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x - h / 2, y - h / 2, z + h / 2);

		// CARA 5 (la de abajo)
		glColor3f(0.6, 0.7, 0.8);
		GLfloat normal5 [] = { 0, -1, 0 };
		glNormal3fv(normal5);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x - h / 2, y - h / 2, z + h / 2);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x - h / 2, y - h / 2, z - h / 2);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x + h / 2, y - h / 2, z - h / 2);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x + h / 2, y - h / 2, z + h / 2);

		// CARA 6 (la del fondo)
		glColor3f(0.7, 0.8, 0.9);
		GLfloat normal6 [] = { 0, 0, -1 };
		glNormal3fv(normal6);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x - h / 2, y - h / 2, z - h / 2);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x - h / 2, y + h / 2, z - h / 2);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x + h / 2, y + h / 2, z - h / 2);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x + h / 2, y - h / 2, z - h / 2);

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		glEnd();
	
	}
	else {
		// CARA 1 (la de delante)
		glBegin(GL_LINE_LOOP);
		glVertex3f(x - h / 2, y - h / 2, z + h / 2);
		glVertex3f(x + h / 2, y - h / 2, z + h / 2);
		glVertex3f(x + h / 2, y + h / 2, z + h / 2);
		glVertex3f(x - h / 2, y + h / 2, z + h / 2);
		glEnd();

		// CARA 2 (la de la derecha)
		glBegin(GL_LINE_LOOP);
		glVertex3f(x + h / 2, y - h / 2, z + h / 2);
		glVertex3f(x + h / 2, y - h / 2, z - h / 2);
		glVertex3f(x + h / 2, y + h / 2, z - h / 2);
		glVertex3f(x + h / 2, y + h / 2, z + h / 2);
		glEnd();

		// CARA 3 (la de arriba)
		glBegin(GL_LINE_LOOP);
		glVertex3f(x + h / 2, y + h / 2, z + h / 2);
		glVertex3f(x + h / 2, y + h / 2, z - h / 2);
		glVertex3f(x - h / 2, y + h / 2, z - h / 2);
		glVertex3f(x - h / 2, y + h / 2, z + h / 2);
		glEnd();

		// CARA 4 (la de la izquierda)
		glBegin(GL_LINE_LOOP);
		glVertex3f(x - h / 2, y + h / 2, z + h / 2);
		glVertex3f(x - h / 2, y + h / 2, z - h / 2);
		glVertex3f(x - h / 2, y - h / 2, z - h / 2);
		glVertex3f(x - h / 2, y - h / 2, z + h / 2);
		glEnd();

		// CARA 5 (la del abajo)
		glBegin(GL_LINE_LOOP);
		glVertex3f(x - h / 2, y - h / 2, z + h / 2);
		glVertex3f(x - h / 2, y - h / 2, z - h / 2);
		glVertex3f(x + h / 2, y - h / 2, z - h / 2);
		glVertex3f(x + h / 2, y - h / 2, z + h / 2);
		glEnd();

		// CARA 6 (la del fondo)
		glBegin(GL_LINE_LOOP);
		glVertex3f(x - h / 2, y - h / 2, z - h / 2);
		glVertex3f(x - h / 2, y + h / 2, z - h / 2);
		glVertex3f(x + h / 2, y + h / 2, z - h / 2);
		glVertex3f(x + h / 2, y - h / 2, z - h / 2);
		glEnd();
	}

	glPopMatrix();
	
}