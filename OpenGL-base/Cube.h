#pragma once
class CCube
{
	float m_x, m_y, m_z;
public:
	CCube();
	~CCube();
	void draw();
	void setPosition(float x, float y, float z);
};

