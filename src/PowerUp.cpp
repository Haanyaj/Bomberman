/*
 ** EPITECH PROJECT, 2018
 ** $NAME_OF_THE_PROJECT
 ** File description:
 ** Here is coded a super function
 */

#include "PowerUp.hpp"

PowerUp::PowerUp(irr::scene::ISceneManager &mgr, irr::core::vector3df pos, Crate &_c) :
  _type(""), _powerup(mgr.addAnimatedMeshSceneNode(mgr.getMesh(PowerUp::setPowerUp().c_str()))), _crate(_c) {
    _powerup->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _powerup->setPosition(pos);
    _powerup->setVisible(false);
}

PowerUp::PowerUp(const PowerUp &p) :
  _type(p._type), _powerup(p._powerup), _crate(p._crate) {
}

PowerUp &PowerUp::operator=(const PowerUp &p) {
  this->_type = p._type;
  this->_powerup = p._powerup;
  this->_crate = p._crate;
  return (*this);
}

std::string PowerUp::setPowerUp() {
  std::string path = "res/models/power_ups/";
  int choose = rand() % 100;
  if (choose >= 0 && choose <= 29) {
    path += "bomb_add.obj";
    _type = "bomb_add";
  } else if (choose >= 30 && choose <= 60) {
    path += "bomb_power.obj";
    _type = "bomb_power";
  } else if (choose >= 61 && choose <= 89){
    path += "shoe.obj";
    _type = "shoe";
  } else {
    path+= "bad_shoe.obj";
    _type = "bad_shoe";
  }
  return (path);
}

Crate *PowerUp::getCrate()
{
  return (&_crate);
}

bool PowerUp::verifCrate() {
  if (&(this->_crate) == NULL)
    return (true);
  return (false);
}
