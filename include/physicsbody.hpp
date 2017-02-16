#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP

#include <SDL.h>
#include <SDL_rect.h>
#include <map>
#include <string>
#include <vector>

struct Sprite;

class PhysicsBody {
public:
  PhysicsBody();
  PhysicsBody(std::string id_, Sprite *sprite);
  ~PhysicsBody();

  std::string id;

  float vel_x;
  float vel_y;
  SDL_Rect *world_coords;

  bool airborne;
  // float mass; //maybe later

  // modify sprite's worldspace according to vel
  void updateInputs(float x_, float y_);
  void apply_jump(int force);
};

#endif // PHYSICSBODY_HPP
