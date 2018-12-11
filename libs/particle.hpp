// Header file to contain the particle class

// Preprocessor
#pragma once

// Class
class Particle {
private:
  // Private variables
  Material material;
  sf::Vector2f position;
  sf::Vector2f velocity;
  float radius;

  sf::Sprite* sprite;

  // Private functions

public:
  // Constructor
  Particle(sf::Vector2f pos, Material material, float radius = 4.f){
    this->material = material;
    this->radius = radius;

    this->position = pos;
    this->velocity = sf::Vector2f(0, 0);

    this->sprite = new sf::Sprite;
  }

  // Destructor
  ~Particle(){

  }

  // Accessors
  inline sf::Vector2f getPos(){ return this->position; }
  inline sf::Vector2f getVel(){ return this->velocity; }
  inline sf::Vector2f getProjection(){ return this->position + this->velocity; }
  inline Material getMaterial(){ return this->material; }
  inline float getRadius(){ return this->radius; }

  // Modifiers
  inline void setPos(sf::Vector2f pos){ this->position = pos; }
  inline void setVel(sf::Vector2f vel){ this->velocity = vel; }
  inline void setMaterial(Material mat){ this->material = material; }
  inline void setRadius(float radius){ this->radius = radius; }

  // Public functions
  void render(sf::RenderWindow* window, sf::Texture texture){
    this->sprite->setTexture(texture);
    this->sprite->setPosition(this->position);

    window->draw(*sprite);
  }
};
