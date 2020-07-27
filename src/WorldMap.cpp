/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** WorldMap
*/

#include "WorldMap.hpp"

WorldMap::WorldMap(irr::scene::ISceneManager &mgr, int nbPlayers, Jukebox &jb) :
  _worldMap(mgr.addAnimatedMeshSceneNode(mgr.getMesh("res/models/worldmap/worldmap.obj"))),
  _crates(), _players(), _jb(jb), _powerups() , m(mgr){
    _worldMap->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _crates.push_back(Crate(mgr, irr::core::vector3df(-20, 0, 25)));
    _crates.push_back(Crate(mgr, irr::core::vector3df(-30, 0, 15)));
    _crates.push_back(Crate(mgr, irr::core::vector3df(20, 0, 25)));
    _crates.push_back(Crate(mgr, irr::core::vector3df(30, 0, 15)));
    _crates.push_back(Crate(mgr, irr::core::vector3df(-20, 0, -25)));
    _crates.push_back(Crate(mgr, irr::core::vector3df(-30, 0, -15)));
    _crates.push_back(Crate(mgr, irr::core::vector3df(20, 0, -25)));
    _crates.push_back(Crate(mgr, irr::core::vector3df(30, 0, -15)));
    for (int i = -25; i < 30; i += 10) {
      for (int j = -20; j < 25; j += 10) {
        _pillars.push_back(irr::core::vector3df(i, 0, j));
      }
    }
    int random = 0;
    for (size_t i = _crates.size(); i < MAX_CRATES; ++i) {
      random = std::rand() % _positions.size();
      _crates.push_back(Crate(mgr, _positions.at(random)));
      _positions.erase(_positions.begin() + random);
    }
    _players.push_back(new Player(mgr, irr::core::vector3df(-30, 0, 25), "res/models/player/player1.x", new PlayerControls(irr::KEY_KEY_Z, irr::KEY_KEY_S, irr::KEY_KEY_Q, irr::KEY_KEY_D, irr::KEY_KEY_A)));
    PlayerControls *pc2 = (nbPlayers == 2) ? new PlayerControls(irr::KEY_UP, irr::KEY_DOWN, irr::KEY_LEFT, irr::KEY_RIGHT, irr::KEY_RCONTROL) : nullptr;
    AI *ai2 = (nbPlayers == 1) ? new AI(irr::core::vector3df(30, 0, 25)) : nullptr;
    _players.push_back(new Player(mgr, irr::core::vector3df(30, 0, 25), "res/models/player/player2.x", pc2, ai2));
    _players.push_back(new Player(mgr, irr::core::vector3df(-30, 0, -25), "res/models/player/player3.x", nullptr, new AI(irr::core::vector3df(-30, 0, -25)), irr::core::vector3df(0, 180, 0)));
    _players.push_back(new Player(mgr, irr::core::vector3df(30, 0, -25), "res/models/player/player4.x", nullptr, new AI(irr::core::vector3df(30, 0, -25)), irr::core::vector3df(0, 180, 0)));
    setAllPU();
}

WorldMap::WorldMap(irr::scene::ISceneManager &mgr) :
  _worldMap(mgr.addAnimatedMeshSceneNode(mgr.getMesh("res/models/worldmap/worldmap.obj"))),
  _crates(), _players(), _jb(), _powerups(), m(mgr) {
}

WorldMap::WorldMap(const WorldMap &w) :
  _worldMap(w._worldMap), _crates(w._crates), _players(w._players), _jb(w._jb) , _powerups(w._powerups), m(w.m) {
}

WorldMap::~WorldMap() {
}

WorldMap &WorldMap::operator=(const WorldMap &w) {
  this->_worldMap = w._worldMap;
  this->_crates = w._crates;
  this->_players = w._players;
  this->_jb = w._jb;
  return (*this);
}

bool WorldMap::isOnPowerUp(Player *player, PowerUp* powerup) {
  irr::core::vector3df pPos = player->getModel()->getPosition();
  irr::core::vector3df puPos = powerup->getModel()->getPosition();
  float puSize = 3.5f;

  return (puPos.X + puSize > pPos.X &&
          puPos.X - puSize < pPos.X &&
          puPos.Z + puSize > pPos.Z &&
          puPos.Z - puSize < pPos.Z);
}

void WorldMap::takePowerUp() {
  for (auto p : _players) {
    for (auto pu = _powerups.begin(); pu != _powerups.end();) {
      if ((*pu)->getModel()->isTrulyVisible() && isOnPowerUp(p, *pu)) {
        std::string type = (*pu)->getType();
        if (type == "bomb_add")
          p->addBomb();
        else if (type == "bomb_power") {
          p->upRange();
          for (auto b : p->getBombs())
            b->setExplosions();
        } else if (type == "shoe")
          p->setMoveSpeed(p->getMoveSpeed() + 5.f);
        else if (type == "bad_shoe") {
          p->setTimeMalus();
          p->setMoveSpeed(p->getMoveSpeed() - 5.f);
        }
        (*pu)->getModel()->remove();
        pu = _powerups.erase(pu);
        break;
      }
      ++pu;
    }
  }
}

void WorldMap::rotatePowerUps(const irr::f32 deltaTime) {
  irr::core::vector3df rot;

  for (auto pu : _powerups) {
    rot = pu->getModel()->getRotation();
    rot.Y += 75 * deltaTime;
    pu->getModel()->setRotation(rot);
  }
}

void WorldMap::handlePlayers(EventHandler &handler, const irr::f32 deltaTime) {
  for (auto p : _players) {
    if (p->getMalus() == "bad_shoe" && std::chrono::system_clock::now() - p->getTimeMalus() > TIMER2) {
      p->setMoveSpeed(p->getMoveSpeed()+ 5.f);
      p->setMalus("");
    }
    if (!p->getControls() && p->getAi()) {
      irr::core::vector3df pos = p->getModel()->getPosition();
      irr::core::vector3df nextPos = pos;
      irr::core::vector3df rot = p->getModel()->getRotation();
      irr::f32 speed = p->getMoveSpeed();
      irr::core::vector3df direction = p->getAi()->getDirection(getCurrentGameTable(), getCurrentCollisionTable(), pos);
      if (direction.X > pos.X) {
        p->getModel()->setLoopMode(true);
        rot.Y = 270;
        if (speed * deltaTime + nextPos.X > direction.X)
          nextPos.X = direction.X;
        else
          nextPos.X += speed * deltaTime;
        if (ableToMove(nextPos, *p))
          pos = nextPos;
      }
      else if (direction.X < pos.X) {
        p->getModel()->setLoopMode(true);
        rot.Y = 90;
        if (nextPos.X - (speed * deltaTime) < direction.X)
          nextPos.X = direction.X;
        else
          nextPos.X -= speed * deltaTime;
        if (ableToMove(nextPos, *p))
          pos = nextPos;
      }
      else if (direction.Z < pos.Z) {
        p->getModel()->setLoopMode(true);
        rot.Y = 0;
        if (nextPos.Z - (speed * deltaTime) < direction.Z)
          nextPos.Z = direction.Z;
        else
          nextPos.Z -= speed * deltaTime;
        if (ableToMove(nextPos, *p))
          pos = nextPos;
      }
      else if (direction.Z > pos.Z) {
        p->getModel()->setLoopMode(true);
        rot.Y = 180;
        if (speed * deltaTime + nextPos.Z > direction.Z)
          nextPos.Z = direction.Z;
        else
          nextPos.Z += speed * deltaTime;
        if (ableToMove(nextPos, *p))
          pos = nextPos;
      } else
        p->getModel()->setLoopMode(false);
      if (p->getModel()->isTrulyVisible()) {
        p->getModel()->setPosition(pos);
        p->getModel()->setRotation(rot);
        if (p->getAi()->safeToPlant(1, pos, getCurrentGameTable()))
          p->dropBomb();
      }
      for (auto b : p->getBombs()) {
        if (b->isPlanted() && std::chrono::system_clock::now() - b->getTimePlanted() > TIMER)
          explodeBomb(b);
      }
      continue;
    }
    irr::core::vector3df pos = p->getModel()->getPosition();
    irr::core::vector3df nextPos = pos;
    irr::core::vector3df rot = p->getModel()->getRotation();
    irr::f32 speed = p->getMoveSpeed();
    if (handler.IsKeyDown(p->getControls()->getMoveUpKey())) {
      p->getModel()->setLoopMode(true);
      nextPos.Z += speed * deltaTime;
      if (ableToMove(nextPos, *p))
        pos = nextPos;
      rot.Y = 180;
    }
    else if (handler.IsKeyDown(p->getControls()->getMoveDownKey())) {
      p->getModel()->setLoopMode(true);
      nextPos.Z -= speed * deltaTime;
      if (ableToMove(nextPos, *p))
        pos = nextPos;
      rot.Y = 0;
    }
    else if (handler.IsKeyDown(p->getControls()->getMoveLeftKey())) {
      p->getModel()->setLoopMode(true);
      nextPos.X -= speed * deltaTime;
      if (ableToMove(nextPos, *p))
        pos = nextPos;
      rot.Y = 90;
    }
    else if (handler.IsKeyDown(p->getControls()->getMoveRightKey())) {
      p->getModel()->setLoopMode(true);
      nextPos.X += speed * deltaTime;
      if (ableToMove(nextPos, *p))
        pos = nextPos;
      rot.Y = 270;
    } else
      p->getModel()->setLoopMode(false);
    if (p->getModel()->isTrulyVisible()) {
      if (handler.IsKeyDown(p->getControls()->getDropBombKey()))
        p->dropBomb();
      p->getModel()->setPosition(pos);
      p->getModel()->setRotation(rot);
    }
    for (auto b : p->getBombs()) {
      if (b->isPlanted() && std::chrono::system_clock::now() - b->getTimePlanted() > TIMER)
        explodeBomb(b);
    }
  }
}

bool WorldMap::ableToMove(irr::core::vector3df nextPos, const Player &player) {
  for (auto p : _players) {
    for (auto b : p->getBombs()) {
      if (!b->isPlanted())
        continue;
      if (player.isOnBomb(*b))
        continue;
      if (nextPos.X > b->getModel()->getPosition().X - 4.5
          && nextPos.X < b->getModel()->getPosition().X + 4.5
          && nextPos.Z > b->getModel()->getPosition().Z - 4.5
          && nextPos.Z < b->getModel()->getPosition().Z + 4.5)
        return (false);
    }
  }
  for (auto c : _crates) {
    if (nextPos.X < -30 || nextPos.X > 30 || nextPos.Z < -25 || nextPos.Z > 25)
      return (false);
    if (nextPos.X > c.getModel()->getPosition().X - 3.5
        && nextPos.X < c.getModel()->getPosition().X + 3.5
        && nextPos.Z > c.getModel()->getPosition().Z - 3.5
        && nextPos.Z < c.getModel()->getPosition().Z + 3.5)
      return (false);
  }
  for (auto c : _pillars) {
    if (nextPos.X > c.X - 3.5
        && nextPos.X < c.X + 3.5
        && nextPos.Z > c.Z - 3.5
        && nextPos.Z < c.Z + 3.5)
      return (false);
  }
  return (true);
}

void WorldMap::explodeBomb(Bomb *b) {
  size_t index = 0;
  std::vector<irr::core::vector3df> epl = calculateExplosion(b);
  _jb.playBombExplosion();
  for (auto e : epl) {
    b->getExplosions().at(index++)->explode(e);
    for (auto pu = _powerups.begin(); pu != _powerups.end(); pu++) {
      if ((*pu)->getModel()->getPosition() == e && (*pu)->getModel()->isTrulyVisible()) {
        (*pu)->getModel()->setVisible(false);
        _powerups.erase(pu);
        if (_powerups.size() != 0)
          pu--;
      }
      if ((*pu)->getCrate()->getModel()->getPosition() == e)
        (*pu)->getModel()->setVisible(true);
    }
    for (auto c = _crates.begin(); c != _crates.end(); c++) {
      if ((*c).getModel()->getPosition() == e) {
        c->getModel()->setVisible(false);
        _crates.erase(c);
        if (_crates.size() != 0)
          c--;
      }
    }
    for (auto pl = _players.begin(); pl != _players.end(); pl++) {
      if ((*pl)->getModel()->isTrulyVisible() && (round(((*pl)->getModel()->getPosition().X * 6 / 30))) * 5 == e.X && (round(((*pl)->getModel()->getPosition().Z * 5 / 25))) * 5 == e.Z) {
        _jb.playPlayerDeath();
        (*pl)->getModel()->setVisible(false);
      }
    }
  }
  b->setPlanted(false);
  b->getModel()->setPosition(irr::core::vector3df(0, -5, 0));
  b->getModel()->setVisible(false);
}

std::vector<irr::core::vector3df> WorldMap::calculateExplosion(Bomb *b) {
  std::vector<irr::core::vector3df> explosionRange;

  explosionRange.push_back(b->getModel()->getPosition());
  calculateLine(b, &explosionRange, "up");
  calculateLine(b, &explosionRange, "down");
  calculateLine(b, &explosionRange, "right");
  calculateLine(b, &explosionRange, "left");
  return (explosionRange);
}

void WorldMap::calculateLine(Bomb *b, std::vector<irr::core::vector3df> *explosionRange, std::string where) {
  irr::core::vector3df nextRange = b->getModel()->getPosition();
  bool touchCrates = false;
  bool touchPillar = false;

  for (irr::f32 r = 5; r <= b->getRange(); r += 5) {
    where == "up" ? nextRange.Z += 5 : 0;
    where == "down" ? nextRange.Z -= 5 : 0;
    where == "right" ? nextRange.X += 5 : 0;
    where == "left" ? nextRange.X -= 5 : 0;
    if (touchPillar || touchCrates)
      break;
    if (nextRange.Z < -25 || nextRange.Z > 25 || nextRange.X < -30 || nextRange.X > 30)
      break;
    for (auto p : _pillars) {
      if (p == nextRange) {
        touchPillar = true;
        break;
      }
    }
    if (touchPillar)
      break;
    for (auto c : _crates) {
      if (c.getModel()->getPosition() == nextRange) {
        touchCrates = true;
        break;
      }
    }
    if (!touchPillar)
      explosionRange->push_back(nextRange);
  }
}

bool WorldMap::isGameFinished() {
  size_t nbPlayersAlive = 0;

  for (auto p : _players) {
    if (p->getModel()->isTrulyVisible())
      ++nbPlayersAlive;
  }
  return (nbPlayersAlive == 1);
}

void WorldMap::setAllPU() {
  int ra = 2;
  for (auto c : _crates) {
    ra = rand()% 4;
    if (ra == 0) {
      _powerups.push_back(new PowerUp(m, c.getModel()->getPosition(), c));
    }
  }
}

std::vector<std::vector<int>> WorldMap::getCurrentGameTable() {
  std::vector<std::vector<int>> gameTable(13, std::vector<int>(11, 0));
  for (int i = 1; i < 13; i += 2)
    for (int j = 1 ; j < 11; j += 2)
      gameTable.at(i).at(j) = 1;
  for (auto c : _crates) {
    irr::core::vector3df cratePos = c.getModel()->getPosition();
    gameTable.at((cratePos.X + 30) / 5).at(10 - ((cratePos.Z + 25) / 5)) = 3;
  }
  for (auto p : _players) {
    irr::core::vector3df pos = p->getModel()->getPosition();
    int player_x = ((round(pos.X * 6 / 30) * 5) + 30) / 5;
    int player_z = 10 - (((round(pos.Z * 5 / 25) * 5) + 25) / 5);
    gameTable.at(player_x).at(player_z) = 4;
    for (auto b : p->getBombs()) {
      if (b->isPlanted()) {
        irr::core::vector3df bombPos = b->getModel()->getPosition();
        int bombRange = b->getRange();
        int i = (bombPos.X + 30) / 5;
        int j = 10 - ((bombPos.Z + 25) / 5);
        gameTable.at(i).at(j) = 2;
        for (int k = 1; k < bombRange && (i + k) < 13 && (gameTable.at(i + k).at(j) == 0 || gameTable.at(i + k).at(j) == 4); k++)
          gameTable.at(i + k).at(j) = 2;
        for (int k = 1; k < bombRange && (i - k) >= 0 && (gameTable.at(i - k).at(j) == 0 || gameTable.at(i - k).at(j) == 4); k++)
          gameTable.at(i - k).at(j) = 2;
        for (int k = 1; k < bombRange && (j + k) < 11 && (gameTable.at(i).at(j + k) == 0 || gameTable.at(i).at(j + k) == 4); k++)
          gameTable.at(i).at(j + k) = 2;
        for (int k = 1; k < bombRange && (j - k) >= 0 && (gameTable.at(i).at(j - k) == 0 || gameTable.at(i).at(j - k) == 4); k++)
          gameTable.at(i).at(j - k) = 2;
      }
    }
  }
  return (gameTable);
}

std::vector<std::vector<int>> WorldMap::getCurrentCollisionTable() {
  std::vector<std::vector<int>> CollisionTable(13, std::vector<int>(11, 0));
  for (int i = 1; i < 13; i += 2)
    for (int j = 1 ; j < 11; j += 2)
      CollisionTable.at(i).at(j) = -1;
  for (auto c : _crates) {
    irr::core::vector3df cratePos = c.getModel()->getPosition();
    CollisionTable.at((cratePos.X + 30) / 5).at(10 - ((cratePos.Z + 25) / 5)) = -1;
  }
  for (auto p : _players) {
    for (auto b : p->getBombs()) {
      if (b->isPlanted()) {
        irr::core::vector3df bombPos = b->getModel()->getPosition();
        int i = (bombPos.X + 30) / 5;
        int j = 10 - ((bombPos.Z + 25) / 5);
        CollisionTable.at(i).at(j) = -1;
      }
    }
  }
  return (CollisionTable);
}
