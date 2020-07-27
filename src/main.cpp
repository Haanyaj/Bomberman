/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** main
*/

#include <ctime>

#include "Bomberman.hpp"

int main() {
  srand(time(NULL));
  std::string finish = "";
  irr::IrrlichtDevice *device = nullptr;
  Bomberman *bomberman = nullptr;

  while (finish != "end") {
    device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080));
    bomberman = new Bomberman(*device);
    finish = bomberman->launch();
    delete bomberman;
    device->closeDevice();
    delete device;
  }
  return (0);
}
