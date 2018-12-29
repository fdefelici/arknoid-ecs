#include "PhysicsSystemLegacy.h"

void PhysicsSystemLegacy::execute(World* aWorld, Engine* engine) {
	for (int i = 0; i < MAX_ENTITY_NUM; i++) {

		float box1_collided = false;

		for (int j = 0; j < MAX_ENTITY_NUM; j++) {
			if (i == j) continue;
			if (!aWorld->has_component(i, COMP__BOX_COLLIDER)) continue;
			if (!aWorld->has_component(j, COMP__BOX_COLLIDER)) continue;

			//std::cout << "Collision" << std::endl;

			BoxCollider& box1 = aWorld->colliders[i];
			Transform& transf1 = aWorld->transforms[i];

			BoxCollider& box2 = aWorld->colliders[j];
			Transform& transf2 = aWorld->transforms[j];

			float box1Left = transf1.position.x;
			float box1Right = transf1.position.x + box1.extent.x;
			float box1Top = transf1.position.y;
			float box1Bottom = transf1.position.y + box1.extent.y;

			float box2Left = transf2.position.x;
			float box2Right = transf2.position.x + box2.extent.x;
			float box2Top = transf2.position.y;
			float box2Bottom = transf2.position.y + box2.extent.y;

			// If one rectangle is on left side of other 
			if (box1Left >= box2Right ||
				box2Left >= box1Right)
				continue;

			// If one rectangle is above other 
			if (box1Bottom <= box2Top ||
				box2Bottom <= box1Top)
				continue;

			//Collision
			float box1CenterX = transf1.position.x + box1.extent.x / 2.f;
			float box1CenterY = transf1.position.y + box1.extent.y / 2.f;
			float box2CenterX = transf2.position.x + box2.extent.x / 2.f;
			float box2CenterY = transf2.position.y + box2.extent.y / 2.f;

			float w = 0.5 * (box1.extent.x + box2.extent.x);
			float h = 0.5 * (box1.extent.y + box2.extent.y);
			float dx = box1CenterX - box2CenterX;
			float dy = box1CenterY - box2CenterY;

			float wy = w * dy;
			float hx = h * dx;

			CollisionSide side;
			if (wy > hx) {
				if (wy > -hx)
					side = CollisionSide::TOP;
				else
					side = CollisionSide::LEFT;
			}
			else {
				if (wy > -hx)
					side = CollisionSide::RIGHT;
				else
					side = CollisionSide::BOTTOM;
			}

			//box1.collision.exists = true;
			box1_collided = true;

			box1.collision.entity = j;
			box1.collision.hitSide = side;
		}

		if (box1_collided) {
			if (aWorld->colliders[i].collision.has_begun) {
				aWorld->colliders[i].collision.has_begun = false;
				aWorld->colliders[i].collision.is_ongoing = true;
			}
			else {
				aWorld->colliders[i].collision.has_begun = true;
				aWorld->colliders[i].collision.is_ongoing = false;
			}
		}
		else {
			aWorld->colliders[i].collision.has_begun = false;
			aWorld->colliders[i].collision.is_ongoing = false;
		}

		/* PHYSICS RESPONSE */
		if (aWorld->has_component(i, COMP__RIGID_BODY) &&
			aWorld->colliders[i].collision.has_begun &&
			!aWorld->rbodies[i].isKinematic) {
			RigidBody& rbody = aWorld->rbodies[i];
			switch (aWorld->colliders[i].collision.hitSide)
			{
			case CollisionSide::TOP: rbody.velocity.y *= -1; break;
			case CollisionSide::BOTTOM: rbody.velocity.y *= -1; break;
			case CollisionSide::LEFT: rbody.velocity.x *= -1; break;
			case CollisionSide::RIGHT: rbody.velocity.x *= -1; break;
			}

			/**/
			Transform& transf1 = aWorld->transforms[i];
			BoxCollider& colli1 = aWorld->colliders[i];

			Transform& transf2 = aWorld->transforms[colli1.collision.entity];
			BoxCollider& colli2 = aWorld->colliders[colli1.collision.entity];

			switch (colli1.collision.hitSide)
			{
				case CollisionSide::BOTTOM: {
					transf1.position.y = transf2.position.y - colli1.extent.y - 1;
					break;
				}
				case CollisionSide::TOP: {
					transf1.position.y = transf2.position.y + colli2.extent.y + 1;
					break;
				}
				case CollisionSide::LEFT: {
					transf1.position.x = transf2.position.x - colli1.extent.x - 1;
					//std::cout << "Collision LEFT" << std::endl;
					break;
				}
				case CollisionSide::RIGHT: {
					transf1.position.x = transf2.position.x + colli2.extent.x + 1;
					break;
				}
			}
			/**/
			
		} else if (aWorld->has_component(i, COMP__RIGID_BODY) &&
			aWorld->colliders[i].collision.has_begun &&
			aWorld->rbodies[i].isKinematic) {
			RigidBody& rbody = aWorld->rbodies[i];
			switch (aWorld->colliders[i].collision.hitSide)
			{
			case CollisionSide::TOP: rbody.velocity.y = 0; break;
			case CollisionSide::BOTTOM: rbody.velocity.y = 0; break;
			case CollisionSide::LEFT: rbody.velocity.x = 0; break;
			case CollisionSide::RIGHT: rbody.velocity.x = 0; break;
			}
		}
		
	}
}
