/*
** EPITECH PROJECT, 2018
** $NAME_OF_THE_PROJECT
** File description:
** Here is coded a super function
*/

#ifndef POWERUP_HPP_
#define POWERUP_HPP_

#include <irrlicht/irrlicht.h>
#include <string>
#include <chrono>

#include "Crate.hpp"

class PowerUp {

public:
  PowerUp(irr::scene::ISceneManager &, irr::core::vector3df, Crate& );
  PowerUp(const PowerUp &);
  ~PowerUp(){};
  PowerUp &operator=(const PowerUp &);
  irr::scene::IAnimatedMeshSceneNode * getModel() const { return (_powerup); };
  std::string setPowerUp();
  Crate *getCrate();
  std::string getType() const { return (_type); };
  bool verifCrate();

private:
  std::string _type;
  irr::scene::IAnimatedMeshSceneNode *_powerup;
  Crate _crate;
};

#endif
