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

  /** Methods to add/remove physics objects */
	PhysicsBody* create_physBody(std::string id, Sprite* sprite);
	void deregister_physBody(PhysicsBody* physBody);

private:
  // collection of physics objects
	std::map<std::string, PhysicsBody> m_physicsList;
  
};

#endif // PHYSICSENGINE_HPP
