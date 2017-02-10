#include <physicsbody.hpp>
#include "sprite.hpp"

PhysicsBody::PhysicsBody() : vel_x(0), vel_y(0), airborne(false) { }

PhysicsBody::~PhysicsBody() { }

void PhysicsBody::updateMotion(Sprite* sprite) {
	if (airborne && vel_y < 12) {
		//gravity with terminal velocity check
		vel_y += 0.7F;
	}
	sprite->world_coords.x += vel_x;
	sprite->world_coords.y += vel_y;

	for (const SDL_Rect* it : CollisionLayerFG) {
		const SDL_Rect* destination = sprite->&world_coords;
		SDL_Rect* result;
		if (SDL_IntersectRect(destination, it, result)) {
			//collision! undo attempted movement
			//or move to nearest legal position using 'result'
			sprite->world_coords.x -= vel_x;
			sprite->world_coords.y -= vel_y;
			break;
		}
	}
}

void PhysicsBody::RenderLayerToCollisionBounds(std::map<std::string, Sprite> renderLayer) {
	for (auto& it : renderLayer) {
		auto& rect = it.second.world_coords;
		CollisionLayerFG.push_back(rect);
	}
}



