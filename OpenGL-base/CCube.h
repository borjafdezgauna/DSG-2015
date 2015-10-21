#ifndef _CCube_
#define _CCube_

class CCube {

private:
	float h; // El tamaño de las aristas del cubo
	float x, y, z; // la posicion del punto más pequeño del cubo
	float yaw, pitch, roll; // valores para la rotacion
	float r, g, b; // El color
	float scale_x, scale_y, scale_z; // La escala
	GLuint textureID; // EL ID de la textura

public:
	CCube();
	~CCube();

	 // Metodos
	void setSize(float h);
	void setPosition(int x, int y, int z);
	void setRotation(float pitch, float yaw, float roll);
	void setScale(float x, float y, float z);
	void setColor(int r, int g, int b);
	void setTexture(const char* filename);
	void draw(bool solid = true);
};

#endif