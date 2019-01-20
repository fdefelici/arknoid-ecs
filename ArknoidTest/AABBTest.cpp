#include "gtest/gtest.h"
#include "../ArknoidECS/physics.h"
#include "SFML/Graphics.hpp"

TEST(AABBTest, NoContainsOrigin) {
	AABB md(sf::Vector2f(2, 2), sf::Vector2f(1, 1));
	EXPECT_FALSE(md.containsOrigin());
}

/**
	Remember on window coordinates the Y is positive going toward the bottom.
	(growing inverse to the cartesian axis)
**/
/*

	(-1,1)         (2,1)

	(-1,4)         (2,4)
*/
TEST(AABBTest, ContainsOrigin) {
	AABB md(sf::Vector2f(-1, -1), sf::Vector2f(3, 3));
	EXPECT_EQ(-1, md.left());
	EXPECT_EQ(2, md.right());
	EXPECT_EQ(-1, md.top());
	EXPECT_EQ(2, md.bottom());
	EXPECT_TRUE(md.containsOrigin());
}


// Y inverted here in the cartesian axis example
/*
			   |     (2, 2) ..............(8, 2)
			   |        .
			   |        .
	   [0,0] --|----------------->[4 ,0]--------
			   |		.
			   |	    .
					(2, -2)..............(8, -2)
*/
TEST(AABBTest, IntersectionFoundApplyingVelocity) {
	sf::Vector2f rayStart(0, 0);
	sf::Vector2f rayEnd(4, 1);

	AABB md({ 2, -2 }, {6, 4});
	EXPECT_FALSE(md.containsOrigin());
	EXPECT_EQ(0.5f, md.findIntersectionRatio(rayStart, rayEnd));
}

TEST(AABBTest, MinkowskiDiffWithCollision) {
	AABB aabb1({ 2, 2 }, { 3, 2 });
	AABB aabb2({ 0, 0 }, { 2, 2 });

	AABB md = aabb1.minkowskiDiff(aabb2);

	EXPECT_EQ(0.f, md.left());
	EXPECT_EQ(0.f, md.top());
	EXPECT_EQ(4.f, md.bottom());
	EXPECT_EQ(5.f, md.right());

	EXPECT_TRUE(md.containsOrigin());
}

TEST(AABBTest, ShortestVectorBug) {
	AABB aabb1({ -340, -2.38419e-07}, { 100, 100 });
	sf::Vector2f vec = aabb1.shortestVectorToOrigin();
	EXPECT_EQ(0, vec.x);
	EXPECT_TRUE(fabsf(-2.38419e-07 -vec.y) < 0.000001f);
}

