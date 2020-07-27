/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Screen
*/

#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include <irrlicht/irrlicht.h>

#include "EventHandler.hpp"

class Screen {
public:
  Screen(EventHandler *);
  Screen(const Screen &);
  Screen &operator=(const Screen &);
  ~Screen();
  irr::video::IVideoDriver *getDriver() const { return (_driver); };
  irr::scene::ISceneManager *getSceneManager() const { return (_sceneManager ); };
  irr::scene::ICameraSceneNode *getCamera() const { return (_camera); };
  irr::video::ITexture *getImage() const { return (_image); };
  irr::core::position2d<irr::s32> getPosition0() const { return (_position0); };
  irr::core::position2d<irr::s32> getPosition1() const { return (_position1); };
  irr::core::rect<irr::s32> getRectangle() const { return (_rectangle); };
  void refreshScreen();

private:
  irr::video::IVideoDriver *_driver;
  irr::scene::ISceneManager *_sceneManager;
  irr::scene::ICameraSceneNode *_camera;
  irr::core::dimension2d<irr::u32> _screenSize;
  irr::video::ITexture *_image;
  irr::core::position2d<irr::s32> _position0;
  irr::core::position2d<irr::s32> _position1;
  irr::core::rect<irr::s32> _rectangle;
};

#endif /* !SCREEN_HPP_ */