#pragma once
class CCube
{

private:
	double m_dx, m_dy, m_dz, m_yaw, m_pitch, m_roll, m_h;
	int m_ix, m_iy, m_iz, m_r, m_g, m_b;

public:
	CCube(double h);
	~CCube();
	void setPosition(int x, int y, int z);
	void setRotation(double pitch, double yaw, double roll);
	void setScale(double x, double y, double z);
	void setColor(int r, int g, int b);
	void draw();

};

