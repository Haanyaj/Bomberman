/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** PlayerControls
*/

#ifndef PLAYERCONTROLS_HPP_
#define PLAYERCONTROLS_HPP_

#include <irrlicht/irrlicht.h>

class PlayerControls {
public:
  PlayerControls(irr::EKEY_CODE, irr::EKEY_CODE, irr::EKEY_CODE, irr::EKEY_CODE, irr::EKEY_CODE);
  ~PlayerControls();
  irr::EKEY_CODE getMoveUpKey() const { return (_moveUp); };
  irr::EKEY_CODE getMoveDownKey() const { return (_moveDown); };
  irr::EKEY_CODE getMoveLeftKey() const { return (_moveLeft); };
  irr::EKEY_CODE getMoveRightKey() const { return (_moveRight); };
  irr::EKEY_CODE getDropBombKey() const { return (_dropBomb); };

private:
  irr::EKEY_CODE _moveUp;
  irr::EKEY_CODE _moveDown;
  irr::EKEY_CODE _moveLeft;
  irr::EKEY_CODE _moveRight;
  irr::EKEY_CODE _dropBomb;
};

#endif /* !PLAYERCONTROLS_HPP_ */
