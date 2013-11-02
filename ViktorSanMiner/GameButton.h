#pragma once
#include <string>

class GameButton
{
public:
	GameButton(std::string ID, int x, int y, int w, int h, void (*callback)());
	~GameButton(void);

	void draw();
	void update();
	void clean() {}

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	button_state m_currentState;

	std::string m_textureID;

	void (*m_callback) ();

	bool m_bReleased;

	int m_x, m_y;
	int m_w, m_h;
};

