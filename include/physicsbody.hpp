#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP

#include <SDL_rect.h>

//fwd decl -- am I doing it right?
struct Sprite;

class PhysicsBody {
public:
	PhysicsBody();
	~PhysicsBody();

	//motion per update? per second?
	float vel_x;
	float vel_y;

	bool airborne;
	//float mass; //maybe later

	//modify sprite's worldspace according to vel
	void updateMotion(Sprite* m_sprite); 
};

#endif //PHYSICSBODY_HPP
