#ifndef _CCube_
#define _CCube_

class CCube {

private:
	double h; // El tamaño de las aristas del cubo
	double x, y, z; // la posicion del punto más pequeño del cubo
	double yaw, pitch, roll; // valores para la rotacion
	float r, g, b; // El color
	double scale_x, scale_y, scale_z; // La escala

public:
	CCube();
	~CCube();

	 // Metodos
	void setSize(double h);
	void setPosition(int x, int y, int z);
	void setRotation(double pitch, double yaw, double roll);
	void setScale(double x, double y, double z);
	void setColor(int r, int g, int b);
	void draw(bool solid = true);
};

#endif