#include "sprite.hpp"
#include <physicsbody.hpp>

PhysicsBody::PhysicsBody()
    : id(""), vel_x(0), vel_y(0), world_coords(NULL), airborne(false), 
	suspend_x(false), suspend_y(false) {}

PhysicsBody::PhysicsBody(std::string id_, Sprite *sprite)
    : id(""), vel_x(0), vel_y(0), world_coords(NULL), airborne(false),
	suspend_x(false), suspend_y(false) {
  world_coords = &sprite->world_coords;
  id = id_;
}

PhysicsBody::PhysicsBody(std::string id_, Sprite *sprite, bool isStationary)
	: id(""), vel_x(0), vel_y(0), world_coords(NULL), airborne(false),
	suspend_x(false), suspend_y(false) {
	world_coords = &sprite->world_coords;
	id = id_;
	if (isStationary) {
		suspend_x = true;
		suspend_y = true;
	}
}

PhysicsBody::~PhysicsBody() {}

void PhysicsBody::updateInputs(float x_, float y_) {
  // take inputs from entity and store as velocity
  vel_x += x_;
  vel_y += y_;
}

void PhysicsBody::apply_jump(int force) {
  vel_y = force;
  airborne = true;
}
