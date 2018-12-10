// Contains easy way to include all the libraries and header files

// Only include once
#pragma once

// Data structures
struct Material {
  float bounciness;
  float weight;
  float ice;

  float freezingTemp;
  float meltingTemp;

  bool solid;
  bool liquid;
  bool gas;
};

// Libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

// Classes
#include "particle.hpp"
#include "physics.hpp"
