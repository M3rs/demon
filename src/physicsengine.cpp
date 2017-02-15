#include "physicsengine.hpp"
#include "physicsbody.hpp"
#include <string>
#include <iostream>

PhysicsEngine::PhysicsEngine() :
	m_physicsList(std::map<std::string, PhysicsBody*>{}) {}

void PhysicsEngine::register_physBody(PhysicsBody* physBody) {
	auto it = m_physicsList.find(physBody->id);
	if (it != m_physicsList.end()) {
		std::cout << "PhysicsList has already registered " << physBody->id << std::endl;
	}
	m_physicsList.emplace(physBody->id, physBody);
}

void PhysicsEngine::deregister_physBody(PhysicsBody* physBody) {
	m_physicsList.erase(physBody->id);
}

void PhysicsEngine::update() {
	for (auto& kv_pair : m_physicsList) {
		auto physBody = kv_pair.second;

		if (physBody->airborne && physBody->vel_y < 13) {
			//gravity with terminal velocity check
			physBody->vel_y += 0.7F;
		}

		SDL_Rect projectedMovement = *physBody->world_coords;
		projectedMovement.x += physBody->vel_x;
		projectedMovement.y += physBody->vel_y;

		bool collision_x(false), collision_y(false);
		for (auto& kv_pair_colcheck : m_physicsList) {
			auto physBody_colcheck = kv_pair_colcheck.second;
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

