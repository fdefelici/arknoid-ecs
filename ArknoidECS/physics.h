#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "SFML/Graphics.hpp"
#include "Components.h"


class AABB {

private:
	sf::Vector2f topLeftVertex;
	sf::Vector2f topRightVertex;
	sf::Vector2f bottomLeftVertex;
	sf::Vector2f bottomRightVertex;
	sf::Vector2f extent;

public:
	static AABB from(Transform& transf, BoxCollider& box) {
		float box1Left = transf.position.x;
		float box1Top = transf.position.y;
		return AABB({ box1Left, box1Top }, box.extent);
	}

	AABB(sf::Vector2f topLeft1, sf::Vector2f extent1);
	AABB minkowskiDiff(AABB& other);
	float findIntersectionRatio(sf::Vector2f& rayStart, sf::Vector2f& rayEnd);
	bool containsOrigin();
	sf::Vector2f shortestVectorToOrigin();
	float top() { return topLeftVertex.y;  };
	float left() { return topLeftVertex.x; };
	float right() { return topRightVertex.x; };
	float bottom() { return bottomLeftVertex.y; };
};


class Vector2DLib {
public:
	static float crossProduct(sf::Vector2f& v1, sf::Vector2f& v2) {
		return v1.x * v2.y - v1.y * v2.x;
	}

	static float dotProduct(sf::Vector2f& v1, sf::Vector2f& v2) {
		return v1.x*v2.x + v1.y*v2.y;
	}

	static float magnitude(sf::Vector2f& v) {
		return sqrtf(v.x*v.x + v.y*v.y);
	}

	static sf::Vector2f normalize(sf::Vector2f& v) {
		float mag = Vector2DLib::magnitude(v);
		if (mag > 0) return v / mag; 
		return v;
	}

	static sf::Vector2f tangent(sf::Vector2f& v) {
		return sf::Vector2f(-v.y, v.x);
	}

	/**
		Coseno dell'angolo tra i vettori V1 e V2
		cosO = dot(V1,V2) / mag(V1)*mag(V2)

		range risultato [-1, 1]
		Se cosO < 0 allora i 2 vettori si muovono in direzioni opposte 
		raggiungendo il massimo a -1 (180°)
	**/
	static float cosO(sf::Vector2f& v1, sf::Vector2f& v2) {
		float dotProd = Vector2DLib::dotProduct(v1, v2);
		if (dotProd == 0.f) return 0.f; //Solo per evitare che Mag siano 0 e divido 0 per 0
		float magV1 = Vector2DLib::magnitude(v1);
		float magV2 = Vector2DLib::magnitude(v2);
		return dotProd / (magV1 * magV2);
	}

	static float rayCastOnEdge(sf::Vector2f& edgeStart, sf::Vector2f& edgeEnd, sf::Vector2f& rayStart, sf::Vector2f& rayEnd) {
		sf::Vector2f edgeExt = edgeEnd - edgeStart;
		sf::Vector2f rayExt = rayEnd - rayStart;

		sf::Vector2f startDiff = edgeStart - rayStart;
		float numerator = Vector2DLib::crossProduct(startDiff, rayExt);
		float denominator = Vector2DLib::crossProduct(rayExt, edgeExt);

		if (numerator == 0 && denominator == 0)
		{
			// the lines are co-linear
			// check if they overlap
			// todo: calculate intersection point
			return std::numeric_limits<float>::max();
		}
		if (denominator == 0)
		{
			// lines are parallel
			return std::numeric_limits<float>::max();
		}

		float u = numerator / denominator;
		float t = Vector2DLib::crossProduct(startDiff, edgeExt) / denominator;
		if ((t >= 0) && (t <= 1) && (u >= 0) && (u <= 1))
		{
			return t;
		}
		return std::numeric_limits<float>::max();
	}

	static sf::Vector2f reflect(sf::Vector2f& v, sf::Vector2f& normal) {
		sf::Vector2f deflect = 2.f * Vector2DLib::dotProduct(v, normal) * normal;
		return v - deflect;
	}

private:
	Vector2DLib() {}
};

#endif