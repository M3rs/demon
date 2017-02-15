#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP

#include <SDL_rect.h>
#include <vector>
#include <map>
#include <SDL.h>
#include <string>

struct Sprite;

class PhysicsBody {
public:
	PhysicsBody(std::string id_, Sprite* sprite);
	~PhysicsBody();

	std::string id;

	float vel_x;
	float vel_y;
	SDL_Rect* world_coords;

	bool airborne;
	//float mass; //maybe later

	//modify sprite's worldspace according to vel
	void updateInputs(float x_, float y_);
};

#endif //PHYSICSBODY_HPP
