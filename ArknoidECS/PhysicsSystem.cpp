#include "PhysicsSystem.h"
#include "physics.h"
#include <iostream>

void PhysicsSystem::execute(World* aWorld, Engine* engine) {
	for (int i = 0; i < MAX_ENTITY_NUM; i++) {
		if (!aWorld->has_component(i, COMP__BOX_COLLIDER)) continue;

		bool collisionDetected = false;
		Transform& transf1 = aWorld->transforms[i];
		RigidBody& rbody1 = aWorld->rbodies[i];
		BoxCollider& box1 = aWorld->colliders[i];
		box1.collision.velocityRatio = 1.f;

		for (int j = 0; j < MAX_ENTITY_NUM; j++) {
			if (i == j) continue;
			if (!aWorld->has_component(j, COMP__BOX_COLLIDER)) continue;
			BoxCollider& box2 = aWorld->colliders[j];
			Transform& transf2 = aWorld->transforms[j];
			sf::Vector2f vel2 = { 0,0 };
			if (aWorld->has_component(j, COMP__RIGID_BODY)) {
				vel2 = aWorld->rbodies[j].velocity;
			}

			float box1Left = transf1.position.x;
			float box1Right = transf1.position.x + box1.extent.x;
			float box1Top = transf1.position.y;
			float box1Bottom = transf1.position.y + box1.extent.y;

			float box2Left = transf2.position.x;
			float box2Right = transf2.position.x + box2.extent.x;
			float box2Top = transf2.position.y;
			float box2Bottom = transf2.position.y + box2.extent.y;

			AABB aabb1({ box1Left, box1Top }, box1.extent);
			AABB aabb2({ box2Left, box2Top }, box2.extent);
			AABB md = aabb1.minkowskiDiff(aabb2);

			//IF Minkowsky Diff Box contains origin (0,0)
			if (md.containsOrigin()) {
				// Then a collision exists, so look for penetration vector
				collisionDetected = true;
				sf::Vector2f penetrationVec = md.shortestVectorToOrigin();
				CollisionSide collSide;
				if (penetrationVec.x > 0) collSide = CollisionSide::RIGHT;
				else if (penetrationVec.x < 0) collSide = CollisionSide::LEFT;
				else if (penetrationVec.y < 0) collSide = CollisionSide::TOP; //inverted for coehrence with view y
				else if (penetrationVec.y > 0) collSide = CollisionSide::BOTTOM; //inverted for coehrence with view y
				else {					
					if (md.bottom() == 0) collSide = CollisionSide::BOTTOM;
					else if (md.top() == 0) collSide = CollisionSide::TOP;
					else if (md.right() == 0) collSide = CollisionSide::RIGHT;
					else if (md.left() == 0) collSide = CollisionSide::LEFT;
				}

				box1.collision.entity = j;
				box1.collision.hitSide = collSide;
				box1.collision.penetration = penetrationVec;
				break;
			}
			else {
				// Dynamic Sweep Test to avoid "Tunneling" effect on obects between frames
				sf::Vector2f relative_motion_vector = (vel2 - rbody1.velocity) * engine->deltaTime;
				sf::Vector2f rayStart = { 0.f, 0.f };
				sf::Vector2f rayEnd = rayStart + relative_motion_vector;
				float current_ratio = md.findIntersectionRatio(rayStart, rayEnd);
				if (current_ratio < std::numeric_limits<float>().max()) {
					box1.collision.velocityRatio = current_ratio;
					break;
				}
			}
		}

		if (collisionDetected) {
			if (!box1.collision.has_begun && !box1.collision.is_ongoing) {
				//Collision begin
				aWorld->colliders[i].collision.has_begun = true;
				aWorld->colliders[i].collision.is_ongoing = false;
			}
			else if (box1.collision.has_begun) {
				//Collision continue
				aWorld->colliders[i].collision.has_begun = false;
				aWorld->colliders[i].collision.is_ongoing = true;
			}
		}
		else if (box1.collision.has_begun || box1.collision.is_ongoing) {
			//Collision ends
			box1.collision.has_begun = false;
			box1.collision.is_ongoing = false;
		}
	}

	// PHYSICS RESPONSE
	for (int i = 0; i < MAX_ENTITY_NUM; i++) {
		if (!aWorld->has_component(i, COMP__RIGID_BODY)) continue;
		Transform& transf = aWorld->transforms[i];
		RigidBody& rbody = aWorld->rbodies[i];
		BoxCollider::Collision& coll = aWorld->colliders[i].collision;

		if ( (coll.has_begun || coll.is_ongoing) && !rbody.isKinematic) {
			transf.position -= (coll.penetration);
			
			int other = coll.entity;
			sf::Vector2f otherSideNormal;
			switch (coll.hitSide)
			{
			case CollisionSide::BOTTOM: otherSideNormal = { 0, -1 }; break; //inverted for coehrence with view y
			case CollisionSide::TOP: otherSideNormal = { 0, 1 }; break;     //inverted for coehrence with view y
			case CollisionSide::LEFT: otherSideNormal = { 1, 0 }; break;
			case CollisionSide::RIGHT: otherSideNormal = { -1, 0 }; break;
			}

			//A possible reflection case:
			//                    <--- other normal of collision side
			// mine ---->    <-------- other velocity
			float cosOmine = Vector2DLib::cosO(rbody.velocity, otherSideNormal);
			float cosOother = Vector2DLib::cosO(aWorld->rbodies[other].velocity, otherSideNormal);
			
			//If object is moving in "opposite" direction to the other
			if (cosOother <= 0 || ( cosOother == 1 & cosOmine <= 0 )) {
				//then change velocity reflecting it
				rbody.velocity = Vector2DLib::reflect(rbody.velocity, otherSideNormal);
			}
			transf.position += rbody.velocity * engine->deltaTime;
		}
		else if ( (coll.has_begun || coll.is_ongoing)  && rbody.isKinematic) {
			//transf.position -= (coll.penetration);
			sf::Vector2f collDir = coll.penetration;
			/*  Case where Minkowsky difference AABB has an edge on 0 axis (x or y).
				The penetration vector would be (0, 0) by the fact this were the
				minimum displacement by the origin.
				So in this case try to calculate explictly the penetration direction.
				(To have a divisor diffent to zero for later cosO calculation)
			*/
			if (coll.penetration.x == 0 && coll.penetration.y == 0) {
				switch (coll.hitSide) {
				case CollisionSide::BOTTOM: collDir = { 0, -1 };  break;
				case CollisionSide::TOP:    collDir = { 0, 1 }; break;
				case CollisionSide::LEFT:   collDir = { 1, 0 }; break;
				case CollisionSide::RIGHT:  collDir = { -1, 0 };  break;
				}
			}

			float cosO = Vector2DLib::cosO(rbody.velocity, collDir);
			//if negative then velocity is "opposite" to the collision direction,
			//so allow the object to move away
			if (cosO < 0) {
				transf.position += (rbody.velocity * engine->deltaTime * coll.velocityRatio);
			}
		}
		else {
			transf.position += (rbody.velocity * engine->deltaTime * coll.velocityRatio);
		}
	}
}
