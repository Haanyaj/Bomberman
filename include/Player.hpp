/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <irrlicht/irrlicht.h>
#include <vector>
#include <string>

#include "EventHandler.hpp"
#include "PlayerControls.hpp"
#include "Bomb.hpp"
#include "AI.hpp"

static const std::chrono::duration<double> TIMER2(10.0);

class Player {
  public:
    Player(irr::scene::ISceneManager &, irr::core::vector3df = irr::core::vector3df(0, 0, 0), std::string = "res/models/player/bomberman.obj", PlayerControls * = nullptr, AI * = nullptr, irr::core::vector3df = irr::core::vector3df(0, 0, 0));
    Player(const Player &);
    ~Player();
    Player &operator=(const Player &);
    bool operator==(const Player &);
    bool operator!=(const Player &);
    irr::scene::IAnimatedMeshSceneNode *getModel() const { return (_player); };
    PlayerControls *getControls() const { return (_controls); };
    void setControls(PlayerControls *controls) { _controls = controls; };
    irr::f32 getMoveSpeed() const { return (_moveSpeed); };
    void setMoveSpeed(irr::f32 moveSpeed) { _moveSpeed = moveSpeed; };
    std::vector<Bomb *> getBombs() const { return (_bombs); };
    AI *getAi() const { return (_ai);};
    void upRange() {_range += 5;};
    irr::f32 getRange() {return (_range);};
    void dropBomb();
    bool isOnBomb(const Bomb &) const;
    bool isInBombRange(const Bomb &);
    void addBomb();
    void setMalus(std::string);
    void setMalus();
    std::string getMalus();
    void setTimeMalus();
    std::chrono::_V2::system_clock::time_point getTimeMalus();

  private:
    irr::scene::IAnimatedMeshSceneNode *_player;
    PlayerControls *_controls;
    AI *_ai;
    irr::f32 _moveSpeed;
    std::vector<Bomb *> _bombs;
    irr::f32 _range;
    irr::scene::ISceneManager &m;
    std::string _malus;
    std::chrono::_V2::system_clock::time_point _timeMalus;
};

#endif /* !APLAYER_HPP_ */
