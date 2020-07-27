/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** PlayerControls
*/

#include "PlayerControls.hpp"

PlayerControls::PlayerControls(irr::EKEY_CODE up, irr::EKEY_CODE down, irr::EKEY_CODE left, irr::EKEY_CODE right, irr::EKEY_CODE bomb) :
_moveUp(up), _moveDown(down), _moveLeft(left), _moveRight(right), _dropBomb(bomb) {
}

PlayerControls::~PlayerControls() {
}
