#pragma once

class Physics {
private:
  std::vector<Particle*> particles;
  Material defaultMaterial;
  float gravity;
  float ambient;

public:
  Physics(float gravity, float ambient){
    this->defaultMaterial = { 0.22f, 1.f, 0.015f, 0.f, 100.f, 255.f, true, true, true, 255, 255, 255 };
    this->gravity = gravity;
    this->ambient = ambient;
  }
  ~Physics(){
    for(int i = 0; i < particles.size(); i++)
      delete particles[i];
  }

  void addParticle(float size, sf::Vector2f position, Material mat){
    particles.push_back(new Particle(size, position, mat));
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

        particle->checkWindowCollision();

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

          float xDirection = (velocity.x > 0) ? 1 : (velocity.x < 0) ? -1 : 0;
          float yDirection = (velocity.y > 0) ? 1 : (velocity.y < 0) ? -1 : 0;
          sf::Vector2f distance(
            abs(abs(position.x + velocity.x + radius) - abs(otherPosition.x + otherVelocity.x + otherRadius)),
            abs(abs(position.y + velocity.y + radius) - abs(otherPosition.y + otherVelocity.y + otherRadius))
          );
          float absoluteDistance = pow(pow(distance.x, 2) + pow(distance.y, 2), 0.5);
          float absoluteVelocity = pow(pow(velocity.x, 2) + pow(distance.y, 2), 0.5);

          if(absoluteDistance < radius + otherRadius){
            particle->addVelocity(sf::Vector2f((-velocity.x * 3 - distance.x) * (particle->getMaterial().bounciness), (-velocity.y * 3) * (particle->getMaterial().bounciness)));

          }

          /*if((position.x + radius) + velocity.x + radius >= (otherPosition.x + otherRadius) + otherVelocity.x - otherRadius && (position.x + radius) + velocity.x - radius <= (otherPosition.x + otherRadius) + velocity.x + otherRadius
          && (position.y + radius) + velocity.y + radius >= (otherPosition.y + otherRadius) + otherVelocity.y - otherRadius && (position.y + radius) + velocity.y - radius <= (otherPosition.y + otherRadius) + velocity.y + otherRadius){
            particle->setVelocity(sf::Vector2f(0, 0));
            particle->addVelocity(sf::Vector2f(-velocity.x * particle->getMaterial().bounciness, -velocity.y * particle->getMaterial().bounciness));
            particle->setTemp(particleTemp + 0.01f);

            particles[k]->addVelocity(sf::Vector2f(velocity * particles[k]->getMaterial().bounciness));
          }*/
        }
      }

      particle->update();
    }
  }
  void drawParticles(sf::RenderWindow& window){
    for(int i = 0; i < particles.size(); i++)
      particles[i]->draw(window);
  }
};
