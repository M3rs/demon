#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP

#include <SDL_rect.h>
#include <vector>
#include <map>
#include <SDL.h>

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

	static void RenderLayerToCollisionBounds(std::map<std::string, Sprite> renderLayer);

private:
	//can separate collision validity by placing entities on different layers,
	//or having an entity check against specific layers while excluding others
	static std::vector<SDL_Rect> CollisionLayerFG;
};

#endif //PHYSICSBODY_HPP
