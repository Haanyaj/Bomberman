/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Screen
*/

#include "Screen.hpp"

Screen::Screen(EventHandler *handler) :
_driver(handler->getDevice().getVideoDriver()), _sceneManager(handler->getDevice().getSceneManager()), _camera(_sceneManager->addCameraSceneNodeFPS(0, 0, 0)),
_screenSize(_driver->getScreenSize()), _image(_driver->getTexture("res/images/screen_bomberman.png")), _position0(), _position1(), _rectangle() {
  _position0.X = 0;
  _position0.Y = 0;
  _position1.X = _screenSize.Width;
  _position1.Y = _screenSize.Height;
  _rectangle.UpperLeftCorner = _position0;
  _rectangle.LowerRightCorner = _position1;
}

Screen::~Screen() {
}

void Screen::refreshScreen() {
  _driver->beginScene(true, true, irr::video::SColor(0, 141, 222, 230));
  _driver->draw2DImage(_image, _position0, _rectangle, 0, irr::video::SColor(255,255,255,255), true);
  _sceneManager->drawAll();
  _driver->endScene();
}

Screen::Screen(const Screen &s) :
_driver(s._driver), _sceneManager(s._sceneManager), _camera(s._camera), _screenSize(s._screenSize),
_image(s._image), _position0(s._position0), _position1(s._position1), _rectangle(s._rectangle) {
}

Screen &Screen::operator=(const Screen &s) {
  this->_driver = s._driver;
  this->_sceneManager = s._sceneManager;
  this->_camera = s._camera;
  this->_screenSize = s._screenSize;
  this->_image = s._image;
  this->_position0 = s._position0;
  this->_position1 = s._position1;
  this->_rectangle = s._rectangle;
  return (*this);
}
