#include <physicsbody.hpp>
#include "sprite.hpp"

PhysicsBody::PhysicsBody() : vel_x(0), vel_y(0), airborne(false) { }

PhysicsBody::~PhysicsBody() { }

void PhysicsBody::updateMotion(Sprite* sprite) {
	if (airborne) {
		//gravity
		vel_y -= 1;
	}
	sprite->world_coords.x += vel_x;
	sprite->world_coords.y += vel_y;
}

