// This file adds different materials for use with particles
/*struct Material {
  float bounciness;
  float weight;
  float ice;

  float freezingTemp, meltingTemp, vaporTemp;

  bool solid, liquid, gas;

  float R, G, B;
};*/

const Material DEFAULT_MAT = { 0.22f, 1.f, 0.015f, 0.f, 100.f, 255.f, true, true, true, 255, 255, 255 };
const Material SAND_MAT = { 0.1f, 1.f, 0.015f, 50.f, 1000.f, 3000.f, true, true, true, 255, 255, 0 };
const Material AIR_MAT = { 0.1f, -0.1f, 0.02f, -4000.f, -100.f, 0.f, true, true, true, 5, 5, 5 };
