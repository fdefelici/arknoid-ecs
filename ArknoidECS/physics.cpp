#include "physics.h"
#include <iostream>
#include <cmath> 

AABB::AABB(sf::Vector2f topLeft1, sf::Vector2f extent1)
{
	extent = extent1;

	float box1Left = topLeft1.x;
	float box1Right = topLeft1.x + extent1.x;
	float box1Top = topLeft1.y;
	float box1Bottom = topLeft1.y + extent1.y;

	topLeftVertex = { box1Left, box1Top };
	topRightVertex = { box1Right, box1Top };
	bottomLeftVertex = { box1Left, box1Bottom };
	bottomRightVertex = { box1Right, box1Bottom };
}

AABB AABB::minkowskiDiff(AABB& other) {
	sf::Vector2f topLeft = this->topLeftVertex - other.bottomRightVertex;
	sf::Vector2f extent = this->extent + other.extent;
	return AABB(topLeft, extent);

}


/**
	Find if ray intersect one of the four AABB edge, 
	returning the closest interesection to the ray.

	@param ray segment (start and end vectors)
	@return the shortest interesection found. The intersection value is between [0, 1]
			Basically represent the percentage at which the ray segment hit one of the AABB edges.
			if no intersection is found return MAX_FLOAT_NUM
**/
float AABB::findIntersectionRatio(sf::Vector2f& rayStart, sf::Vector2f& rayEnd) {
	float minRatio;

	float ratio = Vector2DLib::rayCastOnEdge(topLeftVertex, topRightVertex, rayStart, rayEnd);
	minRatio = ratio;
	ratio = Vector2DLib::rayCastOnEdge(topLeftVertex, bottomLeftVertex, rayStart, rayEnd);
	if (ratio < minRatio) minRatio = ratio;
	ratio = Vector2DLib::rayCastOnEdge(topRightVertex, bottomRightVertex, rayStart, rayEnd);
	if (ratio < minRatio) minRatio = ratio;
	ratio = Vector2DLib::rayCastOnEdge(bottomLeftVertex, bottomRightVertex, rayStart, rayEnd);
	if (ratio < minRatio) minRatio = ratio;
	return minRatio;
}

bool AABB::containsOrigin() {
	return this->left() <= 0 && this->right() >= 0 &&
		   this->top() <= 0 && this->bottom() >= 0;
}

sf::Vector2f AABB::shortestVectorToOrigin() {
	sf::Vector2f result;

	float min = std::numeric_limits<float>().max();
	if (abs(this->left()) < min) {
		min = abs(this->left());
		result = sf::Vector2f(this->left(), 0.f);
	}
	if (abs(this->right()) < min) {
		min = abs(this->right());
		result = sf::Vector2f(this->right(), 0.f);
	}
	if (abs(this->top()) < min) {
		min = abs(this->top());
		result = sf::Vector2f(0.f, this->top());
	}
	if (abs(this->bottom()) < min) {
		min = abs(this->bottom());
		result = sf::Vector2f(0.f, this->bottom());
	}
	return result;
}

