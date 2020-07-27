/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomberman
*/

#include "Bomberman.hpp"

Bomberman::Bomberman(irr::IrrlichtDevice &device) :
_handler(device), _screen(&_handler), _menu(&_handler, &_screen), _jukebox(), _map(nullptr) {
  _handler.getDevice().setEventReceiver(&_handler);
  _screen.getCamera()->setPosition(irr::core::vector3df(0, 65, -20));
  _screen.getCamera()->setTarget(irr::core::vector3df(0, 0, 5));
  _jukebox.playBackgroundMusic();
}

Bomberman::~Bomberman() {
}

Bomberman::Bomberman(const Bomberman &b) : 
_handler(b._handler), _screen(b._screen), _menu(b._menu), _jukebox(b._jukebox), _map(b._map) {
}

Bomberman &Bomberman::operator=(const Bomberman &b) {
  this->_handler = b._handler;
  this->_screen = b._screen;
  this->_menu = b._menu;
  this->_jukebox = b._jukebox;
  this->_map = b._map;
  return (*this);
}

std::string Bomberman::launch() {
  irr::u32 then = 0;
  std::string save = _menu.launch();
  std::string finish = "end";

  if (save.at(0) == '/') {
    irr::scene::ISceneManager *smgr = _screen.getSceneManager();
    smgr->loadScene(save.c_str());
    _map = new WorldMap(*_screen.getSceneManager());
  } else
    _map = new WorldMap(*_screen.getSceneManager(), (save == "new1p" ? 1 : 2), _jukebox);
  _handler.getDevice().getCursorControl()->setVisible(false);
  _handler.getDevice().setWindowCaption(L"Bomberman - Game");
  _handler.getDevice().setResizable(false);
  then = _handler.getDevice().getTimer()->getTime();
  while (_handler.getDevice().run()) {
    if (_handler.IsKeyDown(irr::KEY_ESCAPE))
      break;
    if (_handler.IsKeyDown(irr::KEY_SPACE)) {
      _screen.getSceneManager()->saveScene("./bomberman.bm");
      break;
    }
    if (_map->isGameFinished()) {
      finish = "menu";
      break;
    }
    const irr::u32 now = _handler.getDevice().getTimer()->getTime();
    const irr::f32 frameDeltaTime = static_cast<irr::f32>(now - then) / 1000.f;
    then = now;
    _map->handlePlayers(_handler, frameDeltaTime);
    _map->takePowerUp();
    _map->rotatePowerUps(frameDeltaTime);
    _screen.refreshScreen();
  }
  return (finish);
}
