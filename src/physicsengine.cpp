#include "physicsengine.hpp"
#include "physicsbody.hpp"
#include <string>
#include <iostream>
#include "sprite.hpp"

PhysicsEngine::PhysicsEngine() :
	m_physicsList(std::map<std::string, PhysicsBody>{}) {}

PhysicsBody* PhysicsEngine::create_physBody(std::string id, Sprite* sprite) {
	auto it = m_physicsList.find(id);
	if (it != m_physicsList.end()) {
		std::cout << "PhysicsList has already registered " << id << std::endl;
		return &m_physicsList[id];
	}

	m_physicsList.emplace(id, PhysicsBody(id, sprite));
	return &m_physicsList[id];
}

//TODO(nmg): change to string param to deregister by key; figure out who will use
void PhysicsEngine::deregister_physBody(PhysicsBody* physBody) {
	m_physicsList.erase(physBody->id);
}

void PhysicsEngine::update() {
	for (auto& kv_pair : m_physicsList) {
		PhysicsBody* physBody = &kv_pair.second;

		if (physBody->airborne && physBody->vel_y < 13) {
			//gravity with terminal velocity check
			physBody->vel_y += 0.7F;
		}

		SDL_Rect projectedMovement = *physBody->world_coords;
		projectedMovement.x += physBody->vel_x;
		projectedMovement.y += physBody->vel_y;

		bool collision_x(false), collision_y(false);
		for (auto& kv_pair_colcheck : m_physicsList) {
			PhysicsBody* physBody_colcheck = &kv_pair_colcheck.second;
			//TODO(nmg): 'walk off a cliff' transition to airborne
			SDL_Rect result;
			if (SDL_IntersectRect(&projectedMovement,
				physBody_colcheck->world_coords,
				&result)
				&& physBody->id != physBody_colcheck->id) {
				//collision
				if (physBody->airborne && physBody->vel_y > 0 && result.h > 0) {
					//landing
					physBody->airborne = false;
					collision_y = true;
					physBody->vel_y = 0;
					physBody->world_coords->y = 
						physBody_colcheck->world_coords->y - physBody->world_coords->h;
				}
				if (physBody->airborne && physBody->vel_y < 0 && result.h > 0) {
					//head bumped something above
					collision_y = true;
					physBody->vel_y = 0;
					physBody->world_coords->y =
						physBody_colcheck->world_coords->y + physBody_colcheck->world_coords->h;
				}
				if (result.w > 0) {
					collision_x = true;
				}
				break;
			}
		}

		if (!collision_x) {
			physBody->world_coords->x += physBody->vel_x;
		}
		if (!collision_y) {
			physBody->world_coords->y += physBody->vel_y;
		}

		//hack -- reset velx to 0 for next update
		//do this in lua ideally
		physBody->vel_x = 0;
	}
}

