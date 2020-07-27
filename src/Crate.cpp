/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Crate
*/

#include "Crate.hpp"

Crate::Crate(irr::scene::ISceneManager &mgr, irr::core::vector3df pos) :
_crate(mgr.addAnimatedMeshSceneNode(mgr.getMesh("res/models/crate/crate.obj"))) {
  _crate->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _crate->setPosition(pos);
}

Crate::Crate(const Crate &c) :
_crate(c._crate){
}

Crate::~Crate() {
}

Crate &Crate::operator=(const Crate &c) {
  this->_crate = c._crate;
  return (*this);
}
