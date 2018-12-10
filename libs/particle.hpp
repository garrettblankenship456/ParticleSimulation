// Header file to contain the particle class

// Preprocessor
#pragma once

// Class
class Particle {
private:
  // Private variables
  Material* material;
  sf::Vector2f position;
  sf::Vector2f velocity;

  // Private functions

public:
  // Constructor
  Particle(Material* material){
    this->material = material;
  }

  // Destructor
  ~Particle(){
    delete material;
  }

  // Accessors
  inline sf::Vector2f getPos(){ return this->position; }
  inline sf::Vector2f getVel(){ return this->velocity; }
  inline sf::Vector2f getProjection(){ return this->position + this->velocity; }
  inline Material* getMaterial(){ return this->material; }

  // Modifiers
  inline void setPos(sf::Vector2f pos){ this->position = pos; }
  inline void setVel(sf::Vector2f vel){ this->velocity = vel; }
  inline void setMaterial(Material* mat){ this->material = material; }

  // Public functions
};
