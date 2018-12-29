#ifndef COSTANTS_H_
#define COSTANTS_H_

#define MAX_ENTITY_NUM 100
#define DESTROY_MASK        0
#define COMP__SPRITE_RECT   (1 << 0)
#define COMP__SPRITE_CIRCLE (1 << 1)
#define COMP__SPEED         (1 << 2)
#define COMP__RIGID_BODY    (1 << 3)
#define COMP__BOX_COLLIDER  (1 << 4)
#define COMP__KEYBOARD      (1 << 5)
#define COMP__TRANSFORM     (1 << 6)
#define COMP__RESISTENCE    (1 << 7)
#define COMP__SOUND         (1 << 8)

#define COMPV__BRICK        (1 << 20)
#define COMPV__PADDLE       (1 << 21)
#define COMPV__BALL         (1 << 22)

enum CollisionSide { TOP, RIGHT, BOTTOM, LEFT };

#endif