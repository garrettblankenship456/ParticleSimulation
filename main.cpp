// Main file

// Will fill this out tomarrow

/* TODO/PLAN:
    Initialize SFML window (done)
    Basic manipulation of pixels/particles (done)
    Introduce basic data structures and physics engines (done)
    Create a particle class (done)
    Create a physics engine class (done)
    Create an easy rendering engine to layer over SFML (I am lazy) (done)

    Add physics to be accumulative instead of instant force to set location (done)
    Add physics to have the speeds be more realistic (done just needs more tweaking)
    Add pushing the object back after large acceleration (bounciness implemented, done)
    Make values more appealing (make it 2 instead of 0.000001 gravity for example) (done)
    
    Alot of tweaking needed since the physics are a bit... violent (sort of done)
    Just improve overall physics
    Add other particle collisions
    Refactor code (make it look pretty)
    Tweak delta time
*/

// Preprocessor
#include "libs/libs.hpp"

// Main function
int main(){
  // Initialize SFML window
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);

  // Initialize variables
  sf::Clock deltaClock;
  sf::Time deltaTime;
  sf::Vector2i mousePos;

  // Initialize particles
  std::vector<Particle*> particles;

  // Initialize physics engine
  Physics physics(particles, 1.f, 1.f, 1.f);
  //Physics physics(particles, 0.00001f, 1.f, 1.f);
  for(int i = 0; i < 10; i++)
    physics.addParticleCustom(sf::Vector2f(15 + (5 * i), 15 + (5 * i)));

  // Make a sprite for the particle to use
  sf::Texture texture;
  texture.loadFromFile("textures/particle.png");

  // Keep looping until the window is closed
  while(window.isOpen()){
    // Poll for events
    sf::Event event;
    while(window.pollEvent(event)){
      // If the X was pressed close the window
      if(event.type == sf::Event::Closed)
        window.close();

      // If the mouse was moved update the variable
      if(event.type == sf::Event::MouseMoved)
        mousePos = sf::Mouse::getPosition(window);
    }

    // Update the physics
    physics.update(deltaTime.asSeconds());

    // Rendering
    window.clear();
    physics.drawParticles(&window, texture);
    window.display();

    // Get the delta time
    deltaTime = deltaClock.restart();
  }

  // Exit gracefully
  return 0;
}
