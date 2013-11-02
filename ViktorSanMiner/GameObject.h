#pragma once
#include <iostream>

class GameObject
{
public:
	GameObject(void) {}
	~GameObject(void) {}

	void init(int x, int y, std::string textureID);
	void draw();
	void drawAtPos(int x, int y, int w, int h);
	void update();
	void clean() {}

	void setValue(int value);
	void setBonus(bool bonus) {m_bBonus = bonus;}
	int getValue();
	int getActualX();
	int getActualY();

	void moveTo(int x, int y);

	bool isMoving() {return moving;}
	bool isBonus() {return m_bBonus;}

protected:

	std::string m_textureID;

	int m_x_now, m_x_end;
	int m_y_now, m_y_end;

	int m_value;
	bool m_bBonus;

	bool moving;
};

