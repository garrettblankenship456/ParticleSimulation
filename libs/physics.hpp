// Header file to contain the physics engine class

// Preprocessor
#pragma once

// Class
class Physics {
private:
  // Private variables
  float gravity;
  float resistance;
  float speed;

  std::vector<Particle*> particles;
  std::vector<Material*> materials;
  std::vector<std::string> materialNames;

  // Private functions

public:
  // Constructor
  Physics(std::vector<Particle*> particles, float gravity = 1.f, float resistance = 1.f, float speed = 1.f){
    // Initialize the private variables
    this->particles = particles;
    this->gravity = gravity;
    this->resistance = resistance;
    this->speed = speed;
  }

  // Destructor
  ~Physics(){
    for(int i = 0; i < materials.size(); i++)
      delete materials[i];
  }

  // Modifiers
  inline void setGravity(float gravity){ this->gravity = gravity; }
  inline void setAirResistance(float resistance){ this->resistance = resistance; }
  inline void setSpeed(float speed){ this->speed = speed; }

  // Accessors
  inline float getGravity(){ return this->gravity; }
  inline float getAirResistance(){ return this->resistance; }
  inline float getSpeed(){ return this->speed; }

  // Public functions
  void addParticleCustom(float weight = 1.f, float bounciness = 1.f, float ice = 1.f, bool solid = true, bool liquid = false, bool gas = false, float freezingTemp = 1.f, float meltingTemp = 1.f){
    int index = this->particles.size();
    Material currentMaterial = { bounciness, weight, ice, freezingTemp, meltingTemp, solid, liquid, gas };

    this->particles.push_back(new Particle(&currentMaterial));
  }
  void addParticle(std::string name){
    int index = this->particles.size();
    Material* currentMaterial;

    for(int i = 0; i < this->materials.size(); i++){
      if(this->materialNames[i] == name)
        currentMaterial = this->materials[i];
    }

    this->particles.push_back(new Particle(currentMaterial));
  }
  void update(){
    // Loop through each particle
    for(int i = 0; i < this->particles.size(); i++){
      // Initialize varibles to make positions and stuff easier
      sf::Vector2f particlePos = this->particles[i]->getPos();
      sf::Vector2f particleVel = this->particles[i]->getVel();
      sf::Vector2f particleProj = this->particles[i]->getProjection();
      Material* particleMat = this->particles[i]->getMaterial();

      // Window boundaries
    }
  }
};
