// Contains easy way to include all the libraries and header files

// Only include once
#pragma once

// Define settings
#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 480
#define WINDOW_TITLE "ParticleSimulation"

// Data structures
struct Material {
  float bounciness;
  float weight;
  float ice;

  float freezingTemp, meltingTemp, vaporTemp;

  bool solid, liquid, gas;

  float R, G, B;
};

// Enumerators
enum stateOfMatter { SOLID, LIQUID, GAS };

// Libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cfloat>
#include <unistd.h>

// Classes
#include "materialPresets.hpp"
#include "particle.hpp"
#include "physics.hpp"
