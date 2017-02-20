#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP

#include <SDL.h>
#include <SDL_rect.h>
#include <map>
#include <string>
#include <vector>
#include "sprite.hpp"

class PhysicsBody {
public:
  PhysicsBody();
  PhysicsBody(std::string id_, Sprite *sprite);
  PhysicsBody(std::string id_, Sprite *sprite, bool isStationary);
  ~PhysicsBody();

  std::string id;

  float vel_x;
  float vel_y;
  Rect *world_coords;

  bool airborne;
  bool suspend_x; //prevent movement on an axis
  bool suspend_y;
  // float mass; //maybe later

  // modify sprite's worldspace according to vel
  void updateInputs(float x_, float y_);
  void apply_jump(int force);
};

#endif // PHYSICSBODY_HPP
