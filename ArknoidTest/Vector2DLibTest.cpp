#include "gtest/gtest.h"
#include "../ArknoidECS/physics.h"
#include "SFML/Graphics.hpp"

TEST(Vector2DLibTest, CrossProductWithSameVectorIsZero) {
	float result = Vector2DLib::crossProduct(sf::Vector2f(1, 1), sf::Vector2f(1, 1));
	EXPECT_EQ(0, result);
}

TEST(Vector2DLibTest, CrossProductWithDifferentVectorIsNotZero) {
	float result = Vector2DLib::crossProduct(sf::Vector2f(1, 0), sf::Vector2f(1, 1));
	EXPECT_EQ(1, result);
}


TEST(Vector2DLibTest, RayCastOnEdgeWithIntersection) {
	/*
		ray(0, 2)     edge(2, 2)
				 .     .     
					. <---------- Intersection at 0,5 (50% of the ray)
				 .     . 
		edge(0, 0)     ray(2, 0)
	*/
	
	sf::Vector2f edgeStart(0, 0);
	sf::Vector2f edgeEnd(2, 2);
	sf::Vector2f rayStart(0, 2);
	sf::Vector2f rayEnd(2, 0);

	float result = Vector2DLib::rayCastOnEdge(edgeStart, edgeEnd, rayStart, rayEnd);
	EXPECT_EQ(0.5f, result);
}

TEST(Vector2DLibTest, RayCastOnEdgeWithoutIntersection) {
	/*
		ray(0, 2)       edge(2, 2)
				 .     .
				 .	   . 
				 .     .
	    ray(0, 0)       edge(2, 0)
	*/

	sf::Vector2f edgeStart(2, 0);
	sf::Vector2f edgeEnd(2, 2);
	sf::Vector2f rayStart(0, 0);
	sf::Vector2f rayEnd(0, 2);

	float result = Vector2DLib::rayCastOnEdge(edgeStart, edgeEnd, rayStart, rayEnd);
	EXPECT_EQ(std::numeric_limits<float>::max(), result);
}

TEST(Vector2DLibTest, RayCastOnEdgeWithIntersectionBug) {
	/*
		          edge(2, 2)     ray(4, 1) 
 				       .       .
					   .
			  .        .       
				       .
					   .
		ray(0, 0)    edge(2, -2)
	*/

	sf::Vector2f edgeStart(2, 2);
	sf::Vector2f edgeEnd(2, -2);
	sf::Vector2f rayStart(0, 0);
	sf::Vector2f rayEnd(4, 1);

	float result = Vector2DLib::rayCastOnEdge(edgeStart, edgeEnd, rayStart, rayEnd);
	EXPECT_EQ(0.5f, result);
}

TEST(Vector2DLibTest, DotProdAndCosOrelation) {
	//180°
	sf::Vector2f v1(2, 0);
	sf::Vector2f v2(-2, 0);
	float dot = Vector2DLib::dotProduct(v1, v2);
	float cos = Vector2DLib::cosO(v1, v2);
	EXPECT_EQ(-4, dot);
	EXPECT_EQ(-1, cos);

	//90°
	v1 = { 2, 0 };
	v2 = { 0, 2 };
	dot = Vector2DLib::dotProduct(v1, v2);
	cos = Vector2DLib::cosO(v1, v2);
	EXPECT_EQ(0, dot);
	EXPECT_EQ(0, cos);

	//45°
	v1 = { 2, 0 };
	v2 = { 2, 2 };
	dot = Vector2DLib::dotProduct(v1, v2);
	cos = Vector2DLib::cosO(v1, v2);
	EXPECT_EQ(4, dot);
	//EXPECT_EQ(0.707107, cos);

	//0°
	v1 = { 2, 0 };
	v2 = { 3, 0 };
	dot = Vector2DLib::dotProduct(v1, v2);
	cos = Vector2DLib::cosO(v1, v2);
	EXPECT_EQ(6, dot);
	EXPECT_EQ(1, cos);
}

TEST(Vector2DLibTest, cosOonOppositeVectors) {
	// v1 --->       <--- v2
	sf::Vector2f v1(0, -1);
	sf::Vector2f v2(0, 1);
	float dot = Vector2DLib::dotProduct(v1, v2);
	float cos = Vector2DLib::cosO(v1, v2);
	EXPECT_EQ(-1, dot);
	EXPECT_EQ(-1, cos);
}

TEST(Vector2DLibTest, reflectToOppositeNormal) {
	// v --->       <--- n
	sf::Vector2f v(5, 0);
	sf::Vector2f n(-1, 0);
	
	sf::Vector2f r = Vector2DLib::reflect(v, n);
	EXPECT_EQ(-5, r.x);
	EXPECT_EQ(0, r.y);


}

