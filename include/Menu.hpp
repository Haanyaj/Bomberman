/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <irrlicht/irrlicht.h>
#include <string>

#include "EventHandler.hpp"
#include "Screen.hpp"

class Menu {
public:
  Menu(EventHandler *, Screen *);
  ~Menu();
  Menu(const Menu &);
  Menu &operator=(const Menu &);
  std::string launch();

private:
  EventHandler _handler;
  Screen _screen;
  irr::gui::IGUIEnvironment *_env;
};

#endif /* !MENU_HPP_ */
