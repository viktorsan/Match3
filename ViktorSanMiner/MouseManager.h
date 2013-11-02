#pragma once
#include <vector>
#include "Vector2D.h"


enum mouse_buttons
{
	LEFT=0,
	MIDDLE=1,
	RIGHT=2
};

class MouseManager
{
public:

	static MouseManager* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new MouseManager();
		}
		return s_pInstance;
	}

	void update();
	void clean();

	bool getMouseButtonState(int buttonNumber) { return m_mouseButtonStates[buttonNumber]; }

	Vector2D* getMousePosition() { return m_mousePosition;}

private:
	MouseManager(void);
	~MouseManager(void);

	static MouseManager* s_pInstance;

	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;
};

typedef MouseManager MyMouseManager;

