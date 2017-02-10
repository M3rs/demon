#include <physicsbody.hpp>

PhysicsBody::PhysicsBody() : pos_x(100), pos_y(100), vel_x(0), vel_y(0),
airborne(false) {
	/*rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;*/
}

PhysicsBody::PhysicsBody(SDL_Rect* rect_) : pos_x (100), pos_y(100), vel_x(0), vel_y(0),
	airborne(false) { 
	rect = rect_;
}

PhysicsBody::PhysicsBody(SDL_Rect* rect_, float initPosX, float initPosY)
	: vel_x(0), vel_y(0), airborne(false) { 
	rect = rect_;
	pos_x = initPosX;
	pos_y = initPosY;
}

PhysicsBody::~PhysicsBody() { }

void PhysicsBody::updateMotion() {
	if (airborne) {
		//gravity
		vel_y -= 1;
	}
	pos_x += vel_x;
	pos_y += vel_y;

	// update rect... scrub
	rect->x = pos_x;
	rect->y = pos_y;
}

