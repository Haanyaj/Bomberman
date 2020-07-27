/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Explosion
*/

#include "Explosion.hpp"

Explosion::Explosion(irr::scene::ISceneManager &mgr)
: _explosion(mgr.addAnimatedMeshSceneNode(mgr.getMesh("res/models/bomb/explosion.x"))) {
  _explosion->setLoopMode(false);
  _explosion->setPosition(irr::core::vector3df(0, -10, 0));
  _explosion->setVisible(false);
  _explosion->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

Explosion::Explosion(const Explosion &e)
: _explosion(e._explosion) {
}

Explosion::~Explosion() {
}

Explosion &Explosion::operator=(const Explosion &e) {
  this->_explosion = e._explosion;
  return (*this);
}

void Explosion::explode(irr::core::vector3df pos) {
  _explosion->setPosition(pos);
  _explosion->setVisible(true);
  _explosion->setFrameLoop(0, 23);
  _explosion->setAnimationSpeed(40);
}
