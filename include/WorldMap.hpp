/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** WorldMap
*/

#ifndef WORLDMAP_HPP_
#define WORLDMAP_HPP_

#include <irrlicht/irrlicht.h>
#include <vector>

#include "EventHandler.hpp"
#include "Crate.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "Jukebox.hpp"
#include "PowerUp.hpp"

const size_t MAX_CRATES = 75;

class WorldMap {
  std::vector<irr::core::vector3df> _pillars = {};
  std::vector<irr::core::vector3df> _positions = {
    irr::core::vector3df(-15, 0, 25),
    irr::core::vector3df(-10, 0, 25),
    irr::core::vector3df(-5, 0, 25),
    irr::core::vector3df(0, 0, 25),
    irr::core::vector3df(5, 0, 25),
    irr::core::vector3df(10, 0, 25),
    irr::core::vector3df(15, 0, 25),
    irr::core::vector3df(-20, 0, 20),
    irr::core::vector3df(-10, 0, 20),
    irr::core::vector3df(0, 0, 20),
    irr::core::vector3df(10, 0, 20),
    irr::core::vector3df(20, 0, 20),
    irr::core::vector3df(-25, 0, 15),
    irr::core::vector3df(-20, 0, 15),
    irr::core::vector3df(-15, 0, 15),
    irr::core::vector3df(-10, 0, 15),
    irr::core::vector3df(-5, 0, 15),
    irr::core::vector3df(0, 0, 15),
    irr::core::vector3df(5, 0, 15),
    irr::core::vector3df(10, 0, 15),
    irr::core::vector3df(15, 0, 15),
    irr::core::vector3df(20, 0, 15),
    irr::core::vector3df(25, 0, 15),
    irr::core::vector3df(-30, 0, 10),
    irr::core::vector3df(-20, 0, 10),
    irr::core::vector3df(-10, 0, 10),
    irr::core::vector3df(0, 0, 10),
    irr::core::vector3df(10, 0, 10),
    irr::core::vector3df(20, 0, 10),
    irr::core::vector3df(30, 0, 10),
    irr::core::vector3df(-30, 0, 5),
    irr::core::vector3df(-25, 0, 5),
    irr::core::vector3df(-20, 0, 5),
    irr::core::vector3df(-15, 0, 5),
    irr::core::vector3df(-10, 0, 5),
    irr::core::vector3df(-5, 0, 5),
    irr::core::vector3df(-0, 0, 5),
    irr::core::vector3df(5, 0, 5),
    irr::core::vector3df(10, 0, 5),
    irr::core::vector3df(15, 0, 5),
    irr::core::vector3df(20, 0, 5),
    irr::core::vector3df(25, 0, 5),
    irr::core::vector3df(30, 0, 5),
    irr::core::vector3df(-30, 0, 0),
    irr::core::vector3df(-20, 0, 0),
    irr::core::vector3df(-10, 0, 0),
    irr::core::vector3df(0, 0, 0),
    irr::core::vector3df(10, 0, 0),
    irr::core::vector3df(20, 0, 0),
    irr::core::vector3df(30, 0, 0),
    irr::core::vector3df(-30, 0, -5),
    irr::core::vector3df(-25, 0, -5),
    irr::core::vector3df(-20, 0, -5),
    irr::core::vector3df(-15, 0, -5),
    irr::core::vector3df(-10, 0, -5),
    irr::core::vector3df(-5, 0, -5),
    irr::core::vector3df(0, 0, -5),
    irr::core::vector3df(5, 0, -5),
    irr::core::vector3df(10, 0, -5),
    irr::core::vector3df(15, 0, -5),
    irr::core::vector3df(20, 0, -5),
    irr::core::vector3df(25, 0, -5),
    irr::core::vector3df(30, 0, -5),
    irr::core::vector3df(-30, 0, -10),
    irr::core::vector3df(-20, 0, -10),
    irr::core::vector3df(-10, 0, -10),
    irr::core::vector3df(0, 0, -10),
    irr::core::vector3df(10, 0, -10),
    irr::core::vector3df(20, 0, -10),
    irr::core::vector3df(30, 0, -10),
    irr::core::vector3df(-25, 0, -15),
    irr::core::vector3df(-20, 0, -15),
    irr::core::vector3df(-15, 0, -15),
    irr::core::vector3df(-10, 0, -15),
    irr::core::vector3df(-5, 0, -15),
    irr::core::vector3df(0, 0, -15),
    irr::core::vector3df(5, 0, -15),
    irr::core::vector3df(10, 0, -15),
    irr::core::vector3df(15, 0, -15),
    irr::core::vector3df(20, 0, -15),
    irr::core::vector3df(25, 0, -15),
    irr::core::vector3df(-20, 0, -20),
    irr::core::vector3df(-10, 0, -20),
    irr::core::vector3df(0, 0, -20),
    irr::core::vector3df(10, 0, -20),
    irr::core::vector3df(20, 0, -20),
    irr::core::vector3df(-15, 0, -25),
    irr::core::vector3df(-10, 0, -25),
    irr::core::vector3df(-5, 0, -25),
    irr::core::vector3df(0, 0, -25),
    irr::core::vector3df(5, 0, -25),
    irr::core::vector3df(10, 0, -25),
    irr::core::vector3df(15, 0, -25)
  };

  public:
  WorldMap(irr::scene::ISceneManager &, int, Jukebox &);
  WorldMap(irr::scene::ISceneManager &);
  WorldMap(const WorldMap &);
  ~WorldMap();
  WorldMap &operator=(const WorldMap &);
  irr::scene::IAnimatedMeshSceneNode *getModel() const { return (_worldMap); };
  std::vector<Crate> getCrates() const { return (_crates); };
  std::vector<Player *> getPlayers() const { return (_players); };
  void rotatePowerUps(const irr::f32);
  bool isOnPowerUp(Player*, PowerUp*);
  void takePowerUp();
  void handlePlayers(EventHandler &, const irr::f32);
  bool isGameFinished();
  void SetupPowerUp();
  void setAllPU();
  std::vector<std::vector<int>> getCurrentGameTable();
  std::vector<std::vector<int>> getCurrentCollisionTable();

  private:
  irr::scene::IAnimatedMeshSceneNode *_worldMap;
  std::vector<Crate> _crates;
  std::vector<Player *> _players;
  Jukebox _jb;
  std::vector<PowerUp*> _powerups;
  irr::scene::ISceneManager &m;
  void explodeBomb(Bomb *);
  std::vector<irr::core::vector3df> calculateExplosion(Bomb *);
  void calculateLine(Bomb *, std::vector<irr::core::vector3df> *, std::string);
  bool ableToMove(irr::core::vector3df, const Player&);
};

#endif /* !WORLDMAP_HPP_ */
