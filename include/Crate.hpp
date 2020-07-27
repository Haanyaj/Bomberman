/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Crate
*/

#ifndef CRATE_HPP_
#define CRATE_HPP_

#include <irrlicht/irrlicht.h>

class Crate {

public:
  Crate(irr::scene::ISceneManager &, irr::core::vector3df = irr::core::vector3df(0, 0, 0));
  Crate(const Crate &);
  ~Crate();
  Crate &operator=(const Crate &);
  irr::scene::IAnimatedMeshSceneNode *getModel() const { return (_crate); };
  void setModel(irr::scene::IAnimatedMeshSceneNode *p) { _crate = p; };
  irr::scene::ISceneManager &getScene();

private:
  irr::scene::IAnimatedMeshSceneNode *_crate;
};

#endif /* !CRATE_HPP_ */
