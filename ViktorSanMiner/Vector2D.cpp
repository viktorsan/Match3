#include "Vector2D.h"

bool Vector2D::distance(Vector2D* second)
{
	int distance = abs(this->getX()-second->getX()) + abs(this->getY()-second->getY());
	
	if (distance == 1) return true;

	return false;
}