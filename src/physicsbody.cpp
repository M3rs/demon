#include <physicsbody.hpp>
#include "sprite.hpp"

PhysicsBody::PhysicsBody() 
	: id(""), vel_x(0), vel_y(0), world_coords(NULL), airborne(false) {}

PhysicsBody::PhysicsBody(std::string id_, Sprite* sprite) 
	: id(""), vel_x(0), vel_y(0), world_coords(NULL), airborne(false) {
	world_coords = &sprite->world_coords;
	id = id_;
}

PhysicsBody::~PhysicsBody() { }

void PhysicsBody::updateInputs(float x_, float y_) {
	//take inputs from entity and store as velocity
	vel_x += x_;
	vel_y += y_;
}



