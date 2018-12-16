#pragma once

class Particle {
private:
  sf::CircleShape* shape;
  sf::Vector2f velocity;
  sf::Vector2f maxVelocity;
  Material material;
  float temp;

public:
  Particle(float size, sf::Vector2f position, Material material){
    this->shape = new sf::CircleShape(size);
    this->material = material;

    this->velocity = sf::Vector2f(0, 0);
    this->maxVelocity = sf::Vector2f(10000, 10000);

    this->temp = 10;

    shape->setPosition(position);
  }
  ~Particle(){
    delete shape;
  }

  void setPosition(sf::Vector2f position){
    shape->setPosition(position);
  }
  void move(sf::Vector2f position){
    shape->move(position);
  }
  void setRotation(float rotation){
    shape->setRotation(rotation);
  }
  void rotate(float rotation){
    shape->rotate(rotation);
  }
  void setVelocity(sf::Vector2f velocity){
    this->velocity = velocity;
  }
  void addVelocity(sf::Vector2f velocity){
    this->velocity += velocity;
  }
  void setColor(float R, float G, float B){
    shape->setFillColor(sf::Color(R, G, B));
  }
  void setTemp(float temp){
    this->temp = temp;
  }

  sf::Vector2f getPosition(){
    return shape->getPosition();
  }
  sf::Vector2f getVelocity(){
    return velocity;
  }
  float getRotation(){
    return shape->getRotation();
  }
  bool touchingGround(){
    if(velocity.y == 0)
      return true;
    else
      return false;
  }
  float getSize(){
    return shape->getRadius();
  }
  Material getMaterial(){
    return material;
  }
  float getTemp(){
    return temp;
  }

  void checkWindowCollision(){
    sf::Vector2f position = shape->getPosition();
    float radius = shape->getRadius();

    if(position.x + velocity.x <= 0 || position.x + (radius * 2) + velocity.x >= WINDOW_WIDTH)
      velocity.x = -velocity.x * material.bounciness;
    if(position.y + velocity.y <= 0 || position.y + (radius * 2) + velocity.y >= WINDOW_HEIGHT)
      velocity.y = -velocity.y * material.bounciness;
  }

  void update(){
    material.R = 255;
    material.G = 255 - temp;
    material.B = 255 - temp;
    std::cout << temp << std::endl;

    shape->move(velocity);
  }
  void draw(sf::RenderWindow& window){
    window.draw(*shape);
  }
};
