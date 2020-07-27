/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Explosion
*/

#ifndef EXPLOSION_HPP_
#define EXPLOSION_HPP_

#include <irrlicht/irrlicht.h>

class Explosion {
public:
  Explosion(irr::scene::ISceneManager &);
  Explosion(const Explosion &);
  ~Explosion();
  Explosion &operator=(const Explosion &);
  irr::scene::IAnimatedMeshSceneNode *getModel() const { return (_explosion); };
  void explode(irr::core::vector3df);

private:
  irr::scene::IAnimatedMeshSceneNode *_explosion;
};

#endif /* !EXPLOSION_HPP_ */
