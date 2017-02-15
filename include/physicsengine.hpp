#ifndef PHYSICSENGINE_HPP
#define PHYSICSENGINE_HPP

#include <string>
#include <map>

//forward decl
class PhysicsBody;
struct Sprite;

class PhysicsEngine {
public:
	PhysicsEngine();

  /** update / step method */
	void update();

  /** Methods to add/remove sprites */
	PhysicsBody* create_physBody(std::string id, Sprite* sprite);
	void deregister_physBody(PhysicsBody* physBody);

private:
  // collection of sprites?
	std::map<std::string, PhysicsBody*> m_physicsList;
  
};

#endif // PHYSICSENGINE_HPP
