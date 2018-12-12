// Header file to contain the physics engine class

// Preprocessor
#pragma once

// Data structures
struct Direction {
  bool left;
  bool right;
  bool up;
  bool down;
};

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
  Direction getProjDirection(sf::Vector2f velocity){
    // Make a direction variable and initialize it to false
    Direction dir = { false, false, false, false };

    // Check if the velocity is going right
    if(velocity.x > 0)
      dir.right = true;
    // Check if the velocity is going left
    if(velocity.x < 0)
      dir.left = true;
    // Check if the velocity is going up
    if(velocity.y > 0)
      dir.up = true;
    // Check if the velocity is going down
    if(velocity.y < 0)
      dir.down = true;

    // Return the data to the user
    return dir;
  }

public:
  // Constructor
  Physics(std::vector<Particle*> particles, float gravity = 1.f, float resistance = 1.f, float speed = 1.f){
    // Initialize the private variables
    this->particles = particles;
    this->gravity = gravity + 0.00001f;
    this->resistance = resistance + 0.001f;
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
  void addParticleCustom(sf::Vector2f pos, float weight = 0.5f, float bounciness = 0.15f, float ice = 1.f, bool solid = true, bool liquid = false, bool gas = false, float freezingTemp = 1.f, float meltingTemp = 1.f, float R = 255.f, float G = 255.f, float B = 255.f){
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
  void pushParticle(int id, sf::Vector2f vel){
    this->particles[id]->setVel(vel);
  }
  void update(float deltaTime){
    // Loop through each particle
    for(int i = 0; i < this->particles.size(); i++){
      // Initialize varibles to make positions and stuff easier
      sf::Vector2f particlePos = this->particles[i]->getPos();
      sf::Vector2f particleVel = this->particles[i]->getVel();

      Direction dir = this->getProjDirection(particleVel);
      float leftright = (dir.left == false && dir.right == true) ? 1 : -1;
      float updown = (dir.down == false && dir.up == true) ? 1 : -1;

      sf::Vector2f particleProj(particlePos.x + leftright, particlePos.y + updown);

      Material particleMat = this->particles[i]->getMaterial();
      float particleRad = this->particles[i]->getRadius();

      sf::Vector2f newVel = particleVel;

      // Gravity calculations
      float additive = ((pow(((abs(newVel.y) + 1) + this->gravity) * particleMat.weight, 1.000001) / 10) * 60) * deltaTime; // Make gravity exponential
      if(!std::isnan(additive))
        newVel.y += additive;

      // Window boundaries
      // X collided left
      if(particleProj.x < 0 + particleRad){
        newVel.x = (-newVel.x * particleMat.bounciness) / particleMat.weight;
        particlePos.x = particleRad; // Object remain inside at all times
      }
      // X collided right
      if(particleProj.x > WINDOW_WIDTH - particleRad){
        newVel.x = (-newVel.x * particleMat.bounciness) / particleMat.weight;
        particlePos.x = WINDOW_WIDTH - particleRad;
      }
      // Y collided up
      if(particleProj.y < 0 + particleRad){
        newVel.y = (-newVel.y * particleMat.bounciness) / particleMat.weight;
        particlePos.y = particleRad;
      }
      // Y collided down
      if(particleProj.y > WINDOW_HEIGHT - particleRad){
        newVel.y = (-newVel.y * particleMat.bounciness) / particleMat.weight;
        particlePos.y = WINDOW_HEIGHT - particleRad;
      }

      // Particle-particle collisions (AABB)
      // Loop through every other particle
      for(int k = 0; k < this->particles.size(); k++){
        // Skip if the particle is the same one
        if(k == i)
          continue;

        // Initialize varibles to make positions and stuff easier
        sf::Vector2f particleTargetPos = this->particles[k]->getPos();
        sf::Vector2f particleTargetVel = this->particles[k]->getVel();

        Direction targetDir = this->getProjDirection(particleTargetVel);
        float targetLeftright = (targetDir.left == false && targetDir.right == true) ? 1 : -1;
        float targetUpdown = (targetDir.down == false && targetDir.up == true) ? 1 : -1;

        sf::Vector2f particleTargetProj(particleTargetPos.x + targetLeftright, particleTargetPos.y + targetUpdown);

        Material particleTargetMat = this->particles[k]->getMaterial();
        float particleTargetRad = this->particles[k]->getRadius();

        sf::Vector2f newTargetVel = particleTargetVel;

        // Actually check for the collisions
        Direction sideHit = { false, false, false, false };
        sf::Vector2f distance = sf::Vector2f(abs(particleProj.x - particleTargetProj.x), abs(particleProj.y - particleTargetProj.y));

        // X Collisions
        /*if(particleProj.x <= particleTargetProj.x)
          sideHit.left = true;
        if(particleProj.x >= particleTargetProj.x)
          sideHit.right = true;
        // Y Collisions
        if(particleProj.y <= particleTargetProj.y)
          sideHit.down = true;
        if(particleProj.y >= particleTargetProj.y)
          sideHit.up = true;*/

        // X Collisions
        if(distance.x >= 0 && distance.x <= particleRad)
          sideHit.left = true;
        if(distance.x >= 0 && distance.x <= particleRad)
          sideHit.right = true;
        // Y Collisions
        if(distance.y >= 0 && distance.y <= particleRad)
          sideHit.down = true;
        if(distance.y >= 0 && distance.y <= particleRad)
          sideHit.up = true;

        bool inrange = ((sideHit.up == true && sideHit.down == true) && (sideHit.left == true && sideHit.right == true));

        // If the other particle was actually hit
        if(inrange == true){
          newTargetVel += newVel;
          newVel = -newVel * particleMat.bounciness;
        }

        this->particles[k]->setVel(newTargetVel);
      }

      // Calculate air resistance
      newVel /= this->resistance;

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
