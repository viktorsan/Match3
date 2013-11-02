#pragma once
#include <vector>
#include "Vector2D.h"
#include "TextureManager.h"

class Fuse
{
public:
	Fuse(Uint32 totalTime, Uint32 sections, std::vector<Vector2D> positions);
	~Fuse(void);

	void update(Uint32 tiempo);
	void draw();

private:
	int m_iPosX, m_iPosY;

	Uint32 m_iTotalTime;
	Uint32 m_iSections;

	std::vector<Vector2D> m_fusePath;
};

