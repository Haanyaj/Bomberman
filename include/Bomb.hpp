/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

class Player;
#include <irrlicht/irrlicht.h>
#include <chrono>
#include <vector>

#include "Explosion.hpp"

static const std::chrono::duration<double> TIMER(4.0);

class Bomb {
public:
  Bomb(irr::scene::ISceneManager &, irr::f32);
  Bomb(const Bomb &);
  ~Bomb();
  Bomb &operator=(const Bomb &);
  irr::scene::IAnimatedMeshSceneNode *getModel() const { return (_bomb); };
  int getRange() const { return (_range); };
  void setRange(irr::f32 range) { _range = range; };
  bool isPlanted() const { return (_isPlanted); };
  void setPlanted(bool);
  std::chrono::_V2::system_clock::time_point getTimePlanted() const { return (_timePlanted); };
  std::vector<Explosion *> getExplosions() const { return (_explosions); };
  void setExplosions();

private:
  irr::scene::IAnimatedMeshSceneNode *_bomb;
  irr::f32 _range;
  bool _isPlanted;
  std::chrono::_V2::system_clock::time_point _timePlanted;
  std::vector<Explosion *> _explosions;
  irr::scene::ISceneManager &m;
};

#endif /* !BOMB_HPP_ */
