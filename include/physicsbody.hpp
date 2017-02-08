#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP

#include <SDL_rect.h>

class PhysicsBody {
public:
	PhysicsBody();
	PhysicsBody(SDL_Rect rect_);
	PhysicsBody(SDL_Rect rect_, float initPosX, float initPosY);
	~PhysicsBody();

	//worldspace coordinates; origin is upper-left corner
	float pos_x;
	float pos_y;

	//motion per update? per second?
	float vel_x;
	float vel_y;

	bool airborne;
	//float mass; //maybe later

	void updateMotion();
	SDL_Rect& getRect(); //getRect scrub

private:
	//entity size and spritesheet location
	SDL_Rect rect;

};

#endif //PHYSICSBODY_HPP
