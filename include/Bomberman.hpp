/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomberman
*/

#ifndef BOMBERMAN_HPP_
#define BOMBERMAN_HPP_

#include <irrlicht/irrlicht.h>

#include "EventHandler.hpp"
#include "Menu.hpp"
#include "Screen.hpp"
#include "Jukebox.hpp"
#include "WorldMap.hpp"

class Bomberman {
public:
  Bomberman(irr::IrrlichtDevice &);
  ~Bomberman();
  Bomberman(const Bomberman &);
  Bomberman &operator=(const Bomberman &);
  std::string launch();

private:
  EventHandler _handler;
  Screen _screen;
  Menu _menu;
  Jukebox _jukebox;
  WorldMap *_map;
};

#endif /* !BOMBERMAN_HPP_ */
