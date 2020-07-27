/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu(EventHandler *eh, Screen *screen) :
_handler(*eh), _screen(*screen), _env(_handler.getDevice().getGUIEnvironment()) {
  _handler.getDevice().setWindowCaption(L"Bomberman - Menu");
  _handler.getDevice().setResizable(false);
  _env->addImage(_screen.getDriver()->getTexture("./res/images/screen_bomberman.png"), irr::core::position2d<int>(0, 0));
  _env->addButton(irr::core::rect<irr::s32>(800, 1080 / 2 - 150, 1100, 1080 / 2 - 100), 0, GUI_ID_NEW_GAME_1P_BUTTON, L"New Game (1 player)", L"Launch new game with 1 player");
  _env->addButton(irr::core::rect<irr::s32>(800, 1080 / 2 - 50, 1100, 1080 / 2), 0, GUI_ID_NEW_GAME_2P_BUTTON, L"New Game (2 players)", L"Launch new game with 2 players");
  _env->addButton(irr::core::rect<irr::s32>(800, 1080 / 2 + 50, 1100, 1080 / 2 + 100), 0, GUI_ID_LOAD_GAME_BUTTON, L"Load Game", L"Load a saved game");
  _env->addButton(irr::core::rect<irr::s32>(800, 1080 / 2 + 150, 1100, 1080 / 2 + 200), 0, GUI_ID_QUIT_BUTTON, L"Quit", L"Exits Program");
}

Menu::~Menu() {
}

Menu::Menu(const Menu &m) : 
_handler(m._handler), _screen(m._screen), _env(m._env) {
}

Menu &Menu::operator=(const Menu &m) {
  this->_handler = m._handler;
  this->_screen = m._screen;
  this->_env = m._env;
  return (*this);
}

std::string Menu::launch() {
  std::string gameOption = "empty";

  while (_handler.getDevice().run()) {
    if (_handler.getDevice().isWindowActive()) {
      _screen.getDriver()->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
      _env->drawAll();
      _screen.getDriver()->endScene();
      if (!_handler.getGameOption()->empty()) {
        gameOption = *_handler.getGameOption();
        break;
      }
    }
  }
  return (gameOption);
}