#include "physicsengine.hpp"
#include "physicsbody.hpp"
#include "sprite.hpp"
#include <iostream>
#include <string>

PhysicsEngine::PhysicsEngine()
    : m_physicsList(std::map<std::string, PhysicsBody>{}) {}

PhysicsBody *PhysicsEngine::create_physBody(std::string id, Sprite *sprite, 
	bool isStationary) {
  auto it = m_physicsList.find(id);
  if (it != m_physicsList.end()) {
    std::cout << "PhysicsList has already registered " << id << std::endl;
    return &m_physicsList[id];
  }

  m_physicsList.emplace(id, PhysicsBody(id, sprite, isStationary));
  return &m_physicsList[id];
}

// TODO(nmg): change to string param to deregister by key; figure out who will
// use
void PhysicsEngine::deregister_physBody(PhysicsBody *physBody) {
  m_physicsList.erase(physBody->id);
}

void PhysicsEngine::update() {
  for (auto &kv_pair : m_physicsList) {
    PhysicsBody *pb = &kv_pair.second;


	//if entity can move, update/validate movements
	if (!pb->suspend_x && !pb->suspend_y) {
		bool willFall; //if a grounded entity becomes airborne; decided by boxcast
		pb->airborne ? willFall = false : willFall = true;

		if (pb->airborne && pb->vel_y < 13) {
			// gravity with terminal velocity check
			pb->vel_y += 0.7F;
		}

		//TODO: int coordinates in SDL_Rect are causing rounding errors
		//player moves faster to the left than to the right by 1 unit
		SDL_Rect projectedMovement = *pb->world_coords->to_sdl_rect();
		projectedMovement.x += pb->vel_x;
		projectedMovement.y += pb->vel_y;

		
		bool collision_x(false), collision_y(false);
		for (auto &kv_pair_colcheck : m_physicsList) {
			PhysicsBody *pb_col = &kv_pair_colcheck.second;
			
			SDL_Rect result;
			if (SDL_IntersectRect(&projectedMovement, 
				pb_col->world_coords->to_sdl_rect(), &result) &&
				pb->id != pb_col->id) {
				// collision
				//physBody->id

				if (pb->airborne && pb->vel_y > 0 && result.h > 0) {
					// landing event
					pb->airborne = false;
					collision_y = true;
					pb->vel_y = 0;
					pb->world_coords->y =
						pb_col->world_coords->y - pb->world_coords->h;
				}
				if (pb->airborne && pb->vel_y < 0 && result.h > 0) {
					// head bumped something above
					collision_y = true;
					pb->vel_y = 0;
					pb->world_coords->y = pb_col->world_coords->y +
						pb_col->world_coords->h;
				}
				if (result.w > 0) {
					collision_x = true;
				}
			}

			//walk off a platform check
			if (!pb->airborne && willFall) {
				//create a thin 'groundcheck' rect directly below the sprite
				SDL_Rect boxcast;
				boxcast.x = pb->world_coords->x;
				boxcast.y = pb->world_coords->y + pb->world_coords->h + 1;
				boxcast.h = 2;
				boxcast.w = pb->world_coords->w; //scale to less than 100%?
				SDL_Rect result;
				if (SDL_IntersectRect(pb_col->world_coords->to_sdl_rect(), 
					&boxcast, &result)) {
					willFall = false;
				}
			}
		}

		if (!collision_x) {
			pb->world_coords->x += pb->vel_x;
		}
		if (!collision_y) {
			pb->world_coords->y += pb->vel_y;
		}
		if (willFall) {
			pb->airborne = true;
		}

		// hack -- reset velx to 0 for next update
		// do this in lua ideally
		pb->vel_x = 0;
	}   
  }
}
