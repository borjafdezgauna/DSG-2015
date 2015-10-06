class CCube{
private:
	int m_x, m_y, m_z;
	float m_yaw, m_pitch, m_roll;
	float m_r, m_g, m_b;
	double m_scaleX, m_scaleY, m_scaleZ;

public:
	CCube();
	~CCube();
	void setPosition(int x, int y, int z);
	void setRotation(float pitch, float yaw, float roll);
	void setScale(double x, double y, double z);
	void setColor(float r, float g, float b);
	void draw(bool solido);
};