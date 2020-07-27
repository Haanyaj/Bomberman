/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomb
*/

#include "Bomb.hpp"

#include "Player.hpp"

Bomb::Bomb(irr::scene::ISceneManager &mgr, irr::f32 range) :
_bomb(mgr.addAnimatedMeshSceneNode(mgr.getMesh("res/models/bomb/bomb.obj"))),
_range(range), _isPlanted(false), _timePlanted(), _explosions(), m(mgr) {
  _bomb->setPosition(irr::core::vector3df(0, -5, 0));
  _bomb->setVisible(false);
  _bomb->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  for (size_t i = 0; i < 5; ++ i)
    _explosions.push_back(new Explosion(mgr));
}

Bomb::Bomb(const Bomb &b) :
_bomb(b._bomb), _range(b._range), _isPlanted(b._isPlanted), _timePlanted(b._timePlanted), _explosions(b._explosions) , m(b.m){
}

Bomb::~Bomb() {
}

Bomb &Bomb::operator=(const Bomb &b) {
  this->_bomb = b._bomb;
  this->_range = b._range;
  this->_isPlanted = b._isPlanted;
  this->_timePlanted = b._timePlanted;
  this->_explosions = b._explosions;
  this->m = b.m;
  return (*this);
}

void Bomb::setPlanted(bool isPlanted) {
  _isPlanted = isPlanted;
  _timePlanted = std::chrono::system_clock::now();
}

void Bomb::setExplosions() {
  for (size_t i = 0; i < 4; ++ i)
    _explosions.push_back(new Explosion(m));
  _range += 5.f;
}
