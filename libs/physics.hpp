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
  void addParticleCustom(sf::Vector2f pos, float weight = 1.f, float bounciness = 500.f, float ice = 1.f, bool solid = true, bool liquid = false, bool gas = false, float freezingTemp = 1.f, float meltingTemp = 1.f, float R = 0.f, float G = 0.f, float B = 0.f){
    int index = this->particles.size();
    Material currentMaterial = { bounciness, weight, ice, freezingTemp, meltingTemp, solid, liquid, gas, R, G, B };

    this->particles.push_back(new Particle(pos, currentMaterial));
  }
  void addParticle(sf::Vector2f pos, std::string name){
    int index = this->particles.size();
    Material currentMaterial;

    for(int i = 0; i < this->materials.size(); i++){
      if(this->materialNames[i] == name)
        currentMaterial = *this->materials[i];
    }

    this->particles.push_back(new Particle(pos, currentMaterial));
  }

    float x = 1.1;
  void update(float deltaTime){
    // Loop through each particle
    for(int i = 0; i < this->particles.size(); i++){
      // Initialize varibles to make positions and stuff easier
      sf::Vector2f particlePos = this->particles[i]->getPos();
      sf::Vector2f particleVel = this->particles[i]->getVel();
      sf::Vector2f particleProj = this->particles[i]->getProjection();
      Material particleMat = this->particles[i]->getMaterial();
      float particleRad = this->particles[i]->getRadius();

      sf::Vector2f newVel = particleVel;

      // Gravity calculations
      float additive = pow(newVel.y + (this->gravity * particleMat.weight), 1.00000001);
      if(std::isnan(additive))
        newVel.y = 0;
      else
        newVel.y = additive;

      x = pow(x, 1.001);
      std::cout << newVel.y << std::endl;

      // Window boundaries
      // X collided left
      if(particleProj.x < 0 + particleRad){
        newVel.x = -newVel.x * particleMat.bounciness;
      }
      // X collided right
      if(particleProj.x > WINDOW_WIDTH - particleRad){
        newVel.x = -newVel.x * particleMat.bounciness;
      }
      // Y collided up
      if(particleProj.y < 0 + particleRad){
        newVel.y = -newVel.y * particleMat.bounciness;
      }
      // Y collided down
      if(particleProj.y > WINDOW_HEIGHT - particleRad){
        newVel.y = -newVel.y * particleMat.bounciness;
      }

      // Move the particle to the new position
      this->particles[i]->setPos(particlePos + newVel);
      this->particles[i]->setVel(newVel);
    }
  }
  void drawParticles(sf::RenderWindow* window, sf::Texture texture){
    for(int i = 0; i < this->particles.size(); i++)
      this->particles[i]->render(window, texture);
  }
};
