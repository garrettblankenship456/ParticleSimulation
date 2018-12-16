#pragma once

class Physics {
private:
  std::vector<Particle*> particles;
  Material defaultMaterial;
  float gravity;
  float ambient;

public:
  Physics(float gravity, float ambient){
    this->defaultMaterial = { 0.22f, 1.f, 0.015f, 0.f, 100.f, true, false, false, 255, 255, 255 };
    this->gravity = gravity;
    this->ambient = ambient;
  }
  ~Physics(){
    for(int i = 0; i < particles.size(); i++)
      delete particles[i];
  }

  void addParticle(float size, sf::Vector2f position){
    particles.push_back(new Particle(size, position, defaultMaterial));
  }

  void update(float deltaTime){
    //std::cout << deltaTime << std::endl;
    for(int i = 0; i < particles.size(); i++){
      Particle* particle = particles[i];

      float particleTemp = particle->getTemp();
      if(particleTemp > ambient)
        particle->setTemp(particleTemp - 0.01f);
      else if(particleTemp < ambient)
        particle->setTemp(particleTemp + 0.001f);

      particle->setColor(particle->getMaterial().R, particle->getMaterial().G, particle->getMaterial().B);
      particle->addVelocity(sf::Vector2f(0, (gravity * particle->getMaterial().weight)) * deltaTime);
      particle->addVelocity(sf::Vector2f(particle->getVelocity() * -particle->getMaterial().ice));

      for(int k = 0; k < particles.size(); k++){
        if(k != i){
          sf::Vector2f position = particle->getPosition();
          sf::Vector2f velocity = particle->getVelocity();
          float radius = particle->getSize();
          sf::Vector2f otherPosition = particles[k]->getPosition();
          sf::Vector2f otherVelocity = particles[k]->getVelocity();
          float otherRadius = particles[k]->getSize();

          sf::Vector2f distance(
            position.x - otherPosition.x,
            position.y - otherPosition.y
          );

          if((position.x + radius) + velocity.x + radius >= (otherPosition.x + otherRadius) + otherVelocity.x - otherRadius && (position.x + radius) + velocity.x - radius <= (otherPosition.x + otherRadius) + velocity.x + otherRadius
          && (position.y + radius) + velocity.y + radius >= otherPosition.y + (otherVelocity.y + otherRadius) - otherRadius && (position.y + radius) + velocity.y - radius <= (otherPosition.y + otherRadius) + velocity.y + otherRadius){
            particle->addVelocity(sf::Vector2f((-velocity.x + (distance.x / 4)) * particle->getMaterial().bounciness, (-velocity.y + (distance.y / 4)) * particle->getMaterial().bounciness));
            particle->move(sf::Vector2f(velocity.x, velocity.y));
            particle->setTemp(particleTemp + 1);
          }
        }
      }

      particle->checkWindowCollision();

      particle->update();
    }
  }
  void drawParticles(sf::RenderWindow& window){
    for(int i = 0; i < particles.size(); i++)
      particles[i]->draw(window);
  }
};
