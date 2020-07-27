/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** AI
*/

#include "AI.hpp"
#include <iostream>

AI::AI(irr::core::vector3df pos) :
_lastDirection(pos), _lastPosition(pos), _collisionMap(std::vector<std::vector<int>>(13, std::vector<int>(11, 0))) {
}

AI::~AI() {
}

irr::core::vector3df AI::getDirection(std::vector<std::vector<int>> gameMap, std::vector<std::vector<int>> collisionMap, irr::core::vector3df position) {
  int player_x = ((round(position.X * 6 / 30) * 5) + 30) / 5;
  int player_z = 10 - (((round(position.Z * 5 / 25) * 5) + 25) / 5);
  while (_lastDirection != _lastPosition) {
    setPosition(position);
    return (_lastDirection);
  }
  irr::core::vector3df direction = position;
  if (player_z - 1 >= 0 && collisionMap.at(player_x).at(player_z - 1) != -1)
    collisionMap.at(player_x).at(player_z - 1) = 1;
  if (player_z + 1 < 11 && collisionMap.at(player_x).at(player_z + 1) != -1)
    collisionMap.at(player_x).at(player_z + 1) = 1;
  if (player_x - 1 >= 0 && collisionMap.at(player_x - 1).at(player_z) != -1)
    collisionMap.at(player_x - 1).at(player_z) = 1;
  if (player_x + 1 < 13 && collisionMap.at(player_x + 1).at(player_z) != -1)
    collisionMap.at(player_x + 1).at(player_z) = 1;
  int nb_it = 1;
  while (nb_it < 6) {
    for (int i = 0; i < 13; i++) {
      for (int j = 0; j < 11; j++) {
        if (collisionMap.at(i).at(j) == nb_it) {
          if (j - 1 >= 0 && (collisionMap.at(i).at(j - 1) == 0 || collisionMap.at(i).at(j - 1) > nb_it + 1) && (i != player_x || j - 1 != player_z))
            collisionMap.at(i).at(j - 1) = nb_it + 1;
          if (j + 1 < 11 && (collisionMap.at(i).at(j + 1) == 0 || collisionMap.at(i).at(j + 1) > nb_it + 1) && (i != player_x || j + 1 != player_z))
            collisionMap.at(i).at(j + 1) = nb_it + 1;
          if (i - 1 >= 0 && (collisionMap.at(i - 1).at(j) == 0 || collisionMap.at(i - 1).at(j) > nb_it + 1) && (i - 1 != player_x || j != player_z))
            collisionMap.at(i - 1).at(j) = nb_it + 1;
          if (i + 1 < 13 && (collisionMap.at(i + 1).at(j) == 0 || collisionMap.at(i + 1).at(j) > nb_it + 1) && (i + 1 != player_x || j != player_z))
            collisionMap.at(i + 1).at(j) = nb_it + 1;
        }
      }
    }
    nb_it++;
  }
  setCollisionMap(collisionMap);
  direction = getLongestWay(gameMap, collisionMap, position);
  setDirection(direction);
  setPosition(position);
  return (direction);
}

irr::core::vector3df AI::getLongestWay(std::vector<std::vector<int>> gameMap, std::vector<std::vector<int>> collisionMap, irr::core::vector3df position)
{
  int player_x = ((round(position.X * 6 / 30) * 5) + 30) / 5;
  int player_z = 10 - (((round(position.Z * 5 / 25) * 5) + 25) / 5);
  irr::core::vector3df longestWay = position;
  int max = 0;
  int x_target = player_x;
  int z_target = player_z;
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 11; j++) {
      if (collisionMap.at(i).at(j) > max && gameMap.at(i).at(j) == 0) {
        max = collisionMap.at(i).at(j);
        x_target = i;
        z_target = j;
      }
      else if (isNextToAnObjective(gameMap, i, j) && collisionMap.at(i).at(j) >= 1 && gameMap.at(i).at(j) != 2) {
        max = collisionMap.at(i).at(j);
        x_target = i;
        z_target = j;
        break;
      }
    }
  }
  while (max > 1) {
    if (x_target - 1 >= 0 && collisionMap.at(x_target - 1).at(z_target) == max - 1) {
      max -= 1;
      x_target -= 1;
    }
    else if (x_target + 1 < 13 && collisionMap.at(x_target + 1).at(z_target) == max - 1) {
      max -= 1;
      x_target += 1;
    } 
    else if (z_target - 1 >= 0 && collisionMap.at(x_target).at(z_target - 1) == max - 1) {
      max -= 1;
      z_target -= 1;
    }
    else if (z_target + 1 < 11 && collisionMap.at(x_target).at(z_target + 1) == max - 1) {
      max -= 1;
      z_target += 1;
    }
  }
  longestWay.X = (5 * x_target) - 30;
  longestWay.Z = ((10 - z_target) * 5) - 25;
  return (longestWay);
}

void AI::setDirection(irr::core::vector3df direction) {
  _lastDirection = direction;
}

void AI::setPosition(irr::core::vector3df position) {
  _lastPosition = position;
}

void AI::setCollisionMap(std::vector<std::vector<int>> collisionMap) {
  _collisionMap = collisionMap;
}

bool AI::isNextToAnObjective(std::vector<std::vector<int>> gameMap, int player_x, int player_z) {
  if (player_x - 1 >= 0 && (gameMap.at(player_x - 1).at(player_z) == 3 || gameMap.at(player_x - 1).at(player_z) == 4))
    return (true);
  else if (player_x + 1 < 13 && (gameMap.at(player_x + 1).at(player_z) == 3 || gameMap.at(player_x + 1).at(player_z) == 4))
    return (true);
  else if (player_z - 1 >= 0 && (gameMap.at(player_x).at(player_z - 1) == 3 || gameMap.at(player_x).at(player_z - 1) == 4))
    return (true);
  else if (player_z + 1 < 11 && (gameMap.at(player_x).at(player_z + 1) == 3 || gameMap.at(player_x).at(player_z + 1) == 4))
    return (true);
  return (false);
}

bool AI::isAWayOut(std::vector<std::vector<int>> gameMap, int x, int z, int player_x, int player_z)
{
  if (gameMap.at(x).at(z) == 0)
    return (true);
  else {
    if (x - 1 > 0 && player_x != x - 1) {
      if (gameMap.at(x - 1).at(z) == 0)
        return (true);
    }
    else if (x + 1 < 13 && player_x != x + 1) {
      if (gameMap.at(x + 1).at(z) == 0)
        return (true);
    }
    if (z - 1 > 0 && player_z != z - 1) {
      if (gameMap.at(x).at(z - 1) == 0)
        return (true);
    }
    if (z + 1 < 11 && player_z != z + 1) {
      if (gameMap.at(x).at(z + 1) == 0)
        return (true);
    }
  }
  return (false);
}

bool AI::safeToPlant(int bombPower, irr::core::vector3df pos, std::vector<std::vector<int>> gameMap) {
  int player_x = ((round(pos.X * 6 / 30) * 5) + 30) / 5;
  int player_z = 10 - (((round(pos.Z * 5 / 25) * 5) + 25) / 5);
  if (player_z - 1 >= 0 && _collisionMap.at(player_x).at(player_z - 1) != -1)
    _collisionMap.at(player_x).at(player_z - 1) = 1;
  if (player_z + 1 < 11 && _collisionMap.at(player_x).at(player_z + 1) != -1)
    _collisionMap.at(player_x).at(player_z + 1) = 1;
  if (player_x - 1 >= 0 && _collisionMap.at(player_x - 1).at(player_z) != -1)
    _collisionMap.at(player_x - 1).at(player_z) = 1;
  if (player_x + 1 < 13 && _collisionMap.at(player_x + 1).at(player_z) != -1)
    _collisionMap.at(player_x + 1).at(player_z) = 1;
  int nb_it = 1;
  while (nb_it < 6) {
    for (int i = 0; i < 13; i++) {
      for (int j = 0; j < 11; j++) {
        if (_collisionMap.at(i).at(j) == nb_it) {
          if (j - 1 >= 0 && (_collisionMap.at(i).at(j - 1) == 0 || _collisionMap.at(i).at(j - 1) > nb_it + 1) && (i != player_x || j - 1 != player_z))
            _collisionMap.at(i).at(j - 1) = nb_it + 1;
          if (j + 1 < 11 && (_collisionMap.at(i).at(j + 1) == 0 || _collisionMap.at(i).at(j + 1) > nb_it + 1) && (i != player_x || j + 1 != player_z))
            _collisionMap.at(i).at(j + 1) = nb_it + 1;
          if (i - 1 >= 0 && (_collisionMap.at(i - 1).at(j) == 0 || _collisionMap.at(i - 1).at(j) > nb_it + 1) && (i - 1 != player_x || j != player_z))
            _collisionMap.at(i - 1).at(j) = nb_it + 1;
          if (i + 1 < 13 && (_collisionMap.at(i + 1).at(j) == 0 || _collisionMap.at(i + 1).at(j) > nb_it + 1) && (i + 1 != player_x || j != player_z))
            _collisionMap.at(i + 1).at(j) = nb_it + 1;
        }
      }
    }
    nb_it++;
  }
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 11; j++) {
      if (_collisionMap.at(i).at(j) > bombPower) {
        if (player_x - 1 >= 0 && (gameMap.at(player_x - 1).at(player_z) == 3 || gameMap.at(player_x - 1).at(player_z) == 4))
          return (true);
        if (player_x + 1 < 13 && (gameMap.at(player_x + 1).at(player_z) == 3 || gameMap.at(player_x + 1).at(player_z) == 4))
          return (true);
        if (player_z - 1 >= 0 && (gameMap.at(player_x).at(player_z - 1) == 3 || gameMap.at(player_x).at(player_z - 1) == 4))
          return (true);
        if (player_z + 1 < 11 && (gameMap.at(player_x).at(player_z + 1) == 3 || gameMap.at(player_x).at(player_z + 1) == 4))
          return (true);
      }
    }
  }
  return (false);
}