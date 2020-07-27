/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** AI
*/

#ifndef AI_HPP_
#define AI_HPP_

#include <irrlicht/irrlicht.h>
#include <vector>

class AI
{
public:
  AI(irr::core::vector3df = irr::core::vector3df(0, 0, 0));
  ~AI();
  irr::core::vector3df getDirection(std::vector<std::vector<int>>, std::vector<std::vector<int>>, irr::core::vector3df);
  irr::core::vector3df getLongestWay(std::vector<std::vector<int>>, std::vector<std::vector<int>>, irr::core::vector3df);
  irr::core::vector3df getLastDirection() const { return (_lastDirection); };
  irr::core::vector3df getLastPosition() const { return (_lastPosition); };
  void setDirection(irr::core::vector3df);
  void setPosition(irr::core::vector3df);
  void setCollisionMap(std::vector<std::vector<int>>);
  bool safeToPlant(int, irr::core::vector3df, std::vector<std::vector<int>>);
  bool isAWayOut(std::vector<std::vector<int>>, int, int, int, int);
  bool isNextToAnObjective(std::vector<std::vector<int>>, int, int);

private:
  irr::core::vector3df _lastDirection;
  irr::core::vector3df _lastPosition;
  std::vector<std::vector<int>> _collisionMap;
};

#endif /* !AI_HPP_ */
