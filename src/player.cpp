#include <player.hpp>
#include <physicsbody.hpp>
#include <iostream>
#include <SDL_image.h>

Player::Player(Textures &textures, sol::state &lua)
    : m_textures(textures), m_speed(0.05), m_isJumping(false), m_lua(lua),
      m_form("normal") {

  //m_sprite.setTexture(m_textures.get("res/images/garg.gif"));
  //m_sprite.setTextureRect(sf::IntRect(0, 38, 32, 42));
  // m_sprite.setTextureRect(sf::IntRect(0, 32, 32, 50));
  //m_sprite.setPosition(300, 400);
	setup_lua();
}

void Player::initialize(Renderer* renderer) {
	
	sdlRenderer = renderer->getRenderer();

	// HACK: copied temp code from Renderer.initialize()
	// Need a Renderer method that will return the "sprite" that we can store

	SDL_Surface* img;
	img = IMG_Load("res/images/garg.gif");
	if (img == NULL) {
		printf("error loading garg, %s\n", IMG_GetError());
	}
	SDL_SetColorKey(img, 1, SDL_MapRGB(img->format, 17, 13, 42));

	texture = SDL_CreateTextureFromSurface(sdlRenderer, img);
	SDL_FreeSurface(img);

	playerSprite.x = 0;
	playerSprite.y = 38;
	playerSprite.w = 32;
	playerSprite.h = 42;	
	m_physicsBody = PhysicsBody(playerSprite);
}

void Player::setup_lua() {
  m_lua.script_file("res/scripts/player.lua");
  //test
  set_events();

  sol::table player_t = m_lua["player"];
  player_t.set_function("set_texture_rect", &Player::set_texture, this);
  player_t.set_function("change_texture", &Player::change_texture, this);
  player_t.set_function("move_sprite", &Player::move_sprite, this);
  player_t.set_function("set_texture_and_offset", &Player::set_texture_and_offset, this);
}

void Player::set_events() {
  onJump = m_lua["player"][m_form]["onJump"];
  onLand = m_lua["player"][m_form]["onLand"];
}

void Player::handle_event(SDL_Keycode keycode) {

	switch (keycode) {
		case SDLK_SPACE:
			m_isJumping = true;
			//m_force = sf::Vector2f(0, -14);
			//m_force = sf::Vector2f(0, m_lua["player"][m_form]["jump"]);
			onJump();
			break;
		case SDLK_r:
			// reload player script
			std::cout << "Reloading player.lua\n";
			setup_lua();
			break;
		case SDLK_t:
			if (m_form == "normal") {
				m_form = "big";
				set_events();      
			}
			else if (m_form == "big") {
				m_form = "normal";
				set_events();
			}
			m_lua["player"][m_form]["onTransform"]();
			break;
		default:
			break;
    }
}

void Player::update(const Uint8* input) {
  // reset x velocity to 0 (could not and have accel/deccel (more complicated)
	m_physicsBody.vel_x = 0;

  if (isKeyPressed(input, "A")) {
	m_physicsBody.vel_x = m_speed * -1.0F;
  } else if (isKeyPressed(input, "D")) {
	  m_physicsBody.vel_x = m_speed;
  }

  //m_sprite.move(sf::Vector2f(0, 3)); // extra gravity

  if (m_isJumping) {
    //m_force.y += 1;
    // m_sprite.move(sf::Vector2f(0, 3)); // extra gravity
  }

  //TODO: Remove Renderer ref hack, 
  //let these two talk without one containing the other

  m_physicsBody.updateMotion();
  SDL_Rect dest = m_physicsBody.getRect();
  SDL_RenderCopy(sdlRenderer, texture, &playerSprite, &dest);
  SDL_RenderPresent(sdlRenderer);

  /*
  if (m_force.y >= 0) {
  auto aabb = m_sprite.getGlobalBounds();

  // if (m_sprite.getPosition().y >= 400 && m_isJumping) {
  // if ((aabb.top + aabb.height) >= 400 && m_isJumping) {
  if ((aabb.top + aabb.height) >= 400) {
    //m_sprite.setPosition(aabb.left, 400 - aabb.height);
    //m_force.y = 0;
    if (m_isJumping) {
      m_isJumping = false;
      onLand();
    }
  }
  }
  */
}

//const sf::Sprite &Player::sprite() const { return m_sprite; }

void Player::set_texture(int x, int y, int w, int h) {
  //m_sprite.setTextureRect(sf::IntRect(x, y, w, h));
}

void Player::change_texture(const std::string &txname) {
  //m_sprite.setTexture(m_textures.get(txname));
}

void Player::move_sprite(float x, float y) {
  //m_sprite.move(x, y);
}

void Player::set_texture_and_offset(int x, int y, int w, int h) {
	//shortcut for setTexture and moveSprite
	//adjusts so as to keep bottom plane consistent

	//sf::IntRect oldRect;
	//oldRect = m_sprite.getTextureRect();
	//m_sprite.setTextureRect(sf::IntRect(x, y, w, h));
	//m_sprite.move(0, oldRect.height - h);
}

bool Player::isKeyPressed(const Uint8 * input, char * keyName)
{
	return input[SDL_GetScancodeFromName(keyName)] == 1;
}
