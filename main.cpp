// Main file

/* TODO:
    Tweak Physics
    Add different states of matter
    Fix the particles being able to exit world
    Fix the particles bounding box being to big (done)
*/

// Preprocessor
#include "headers/libs.hpp"

// Main function
int main(){
  // Initialize SFML window
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
  window.setFramerateLimit(60);

  // Setup particles
  Physics physics(10.f, 10.f);
  physics.addParticle(25, sf::Vector2f(50, 200));
  physics.addParticle(25, sf::Vector2f(60, 149));

  // Initialize clock
  float deltaTime = 0.f;
  sf::Clock clock;

  // Keep looping until the window is closed
  while(window.isOpen()){
    // Set delta time
    deltaTime = clock.restart().asSeconds();

    // Poll for events
    sf::Event event;
    while(window.pollEvent(event)){
      // If the X was pressed close the window
      if(event.type == sf::Event::Closed)
        window.close();

      if(event.type == sf::Event::MouseButtonPressed)
        physics.addParticle(10, sf::Vector2f(sf::Mouse::getPosition(window)));
    }

    // Update physics
    physics.update(deltaTime);

    // Rendering
    window.clear();
    physics.drawParticles(window);
    window.display();
  }

  // Exit gracefully
  return 0;
}
