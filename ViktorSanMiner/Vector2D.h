#pragma once
#include <vector>

class Vector2D
{
public:
	Vector2D() {}
	~Vector2D() {}

	void setValue(int x, int y) { m_x = x; m_y = y; }
	int getX() {return m_x;}
	int getY() {return m_y;}

	bool distance(Vector2D* second);

private:
	int m_x;
	int m_y;
};