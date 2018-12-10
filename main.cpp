// Main file

// Will fill this out tomarrow

/* TODO/PLAN:
    Initialize SFML window (done)
    Basic manipulation of pixels/particles
    Introduce basic data structures and physics engines
    Create a particle class
    Create a physics engine class
    Create an easy rendering engine to layer over SFML (I am lazy)
*/

// Preprocessor
#include "libs/libs.hpp"
#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 480
#define WINDOW_TITLE "ParticleSimulation"

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
  particles.push_back(new Particle());

  // Initialize physics engine
  Physics physics();

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

    // Rendering
    window.clear();
    window.display();

    // Get the delta time
    deltaTime = deltaClock.restart();
  }

  // Exit gracefully
  return 0;
}
