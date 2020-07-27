/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player
*/

#include "Player.hpp"

#include "Explosion.hpp"

Player::Player(irr::scene::ISceneManager &mgr, irr::core::vector3df pos, std::string player, PlayerControls *controls, AI *ai, irr::core::vector3df angle) :
_player(mgr.addAnimatedMeshSceneNode(mgr.getMesh(player.c_str()))),
_controls(controls), _ai(ai), _moveSpeed(10.f), _bombs(std::vector<Bomb *>()), _range(5.f),
m(mgr) , _malus(), _timeMalus(){
  _player->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _player->setPosition(pos);
  _player->setRotation(angle);
  _player->setLoopMode(false);
  _bombs.push_back(new Bomb(mgr, _range));
}

Player::Player(const Player &p) :
_player(p._player), _controls(p._controls), _ai(p._ai), _moveSpeed(p._moveSpeed), _bombs(p._bombs), _range(p._range), m(p.m) , _malus(p._malus), _timeMalus(p._timeMalus){
}

Player::~Player() {
  _bombs.clear();
}

Player &Player::operator=(const Player &p) {
  this->_player = p._player;
  this->_controls = p._controls;
  this->_moveSpeed = p._moveSpeed;
  this->_bombs = p._bombs;
  this->_range = p._range;
  this->_malus = p._malus;
  this->_timeMalus = p._timeMalus;
  return (*this);
}

bool Player::operator==(const Player &p) {
	return (this->_player == p._player
			&& this->_controls == p._controls
			&& this->_moveSpeed == p._moveSpeed
      && this->_bombs == p._bombs
      && this->_range == p._range
      && this->_malus == p._malus
      && this->_timeMalus == p._timeMalus);
}

bool Player::operator!=(const Player &p) {
  return (this->_player == p._player
      || this->_controls == p._controls
      || this->_moveSpeed == p._moveSpeed
      || this->_bombs == p._bombs
      || this->_range == p._range
      || this->_malus == p._malus
      || this->_timeMalus == p._timeMalus);
}

void Player::dropBomb() {
  irr::core::vector3df pos = _player->getPosition();
  int index = -1;

  for (std::size_t i = 0; i < _bombs.size(); ++i) {
    if (!_bombs.at(i)->isPlanted()) {
      index = i;
      break;
    }
  }
  if (index == -1)
    return;
  if (abs(pos.X) <= 2.5f && abs(pos.Z) <= 2.5f) {
    pos.X = 0.f;
    pos.Z = 0.f;
  } else {
    pos.X = (round((pos.X * 6 / 30))) * 5;
    pos.Z = (round((pos.Z * 5 / 25))) * 5;
  }
  if (_player->getPosition().X < 0.f)
    pos.X = ((round((abs(_player->getPosition().X) * 6 / 30))) * 5) * -1;
  if (_player->getPosition().Z < 0.f)
    pos.Z = ((round((abs(_player->getPosition().Z) * 5 / 25))) * 5) * -1;
  for (auto b : _bombs) {
    if (b->getModel()->getPosition() == pos)
      return;
  }
  _bombs.at(index)->getModel()->setPosition(pos);
  _bombs.at(index)->getModel()->setVisible(true);
  _bombs.at(index)->setPlanted(true);
}

bool Player::isOnBomb(const Bomb &b) const {
  float bombSize = 4.5;
  irr::core::vector3df playerPos = this->getModel()->getPosition();
  irr::core::vector3df bombPos = b.getModel()->getPosition();
  return ((bombPos.X + bombSize > playerPos.X && bombPos.X - bombSize < playerPos.X && bombPos.Z + bombSize > playerPos.Z && bombPos.Z - bombSize < playerPos.Z));
}

bool Player::isInBombRange(const Bomb &b) {
  float bombSize = 3.5;
  float padding = 3.5;
  irr::core::vector3df playerPos = this->getModel()->getPosition();
  irr::core::vector3df bombPos = b.getModel()->getPosition();
  return ((playerPos.X <= bombPos.X + bombSize + b.getRange() && playerPos.X >= bombPos.X - bombSize - b.getRange() && playerPos.Z <= bombPos.Z + padding && playerPos.Z >= bombPos.Z - padding)
      || (playerPos.Z <= bombPos.Z + bombSize + b.getRange() && playerPos.Z >= bombPos.Z - bombSize - b.getRange() && playerPos.X <= bombPos.X + padding && playerPos.X >= bombPos.X - padding)
      );
}

void Player::addBomb() {
  _bombs.push_back(new Bomb(m, 5.f));
  for (irr::f32 i = 5; i < _range; i += 5) {
  _bombs.back()->setExplosions();
  }
}

void Player::setMalus(std::string a) {
  _malus = a;
}

std::string Player::getMalus() {
  return (_malus);
}

void Player::setTimeMalus() {
    _malus = "bad_shoe";
    _timeMalus = std::chrono::system_clock::now();
}

std::chrono::_V2::system_clock::time_point Player::getTimeMalus() {
  return (_timeMalus);
}
