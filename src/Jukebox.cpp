/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Jukebox
*/

#include "Jukebox.hpp"

Jukebox::Jukebox() :
_bufBackgroundMusic(), _soundBackgroundMusic(),
_bufBombExplosion(), _soundBombExplosion(),
_bufPlayerDeath(), _soundPlayerDeath() {
  _bufBackgroundMusic.loadFromFile("res/audio/background.wav");
  _bufBombExplosion.loadFromFile("res/audio/bomb.wav");
  _bufPlayerDeath.loadFromFile("res/audio/death.wav");
}

Jukebox::~Jukebox() {
  _soundBackgroundMusic.stop();
  _soundBombExplosion.stop();
  _soundPlayerDeath.stop();
  _soundBackgroundMusic.resetBuffer();
  _soundBombExplosion.resetBuffer();
  _soundPlayerDeath.resetBuffer();
}

void Jukebox::playBackgroundMusic() {
  _soundBackgroundMusic.setBuffer(_bufBackgroundMusic);
  _soundBackgroundMusic.setLoop(true);
  _soundBackgroundMusic.setVolume(30);
  _soundBackgroundMusic.play();
}

void Jukebox::playBombExplosion() {
  _soundBombExplosion.setBuffer(_bufBombExplosion);
  _soundBackgroundMusic.setVolume(50);
  _soundBombExplosion.play();
}

void Jukebox::playPlayerDeath() {
  float pitch = static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 2)) + 1;

  _soundPlayerDeath.setBuffer(_bufPlayerDeath);
  _soundPlayerDeath.setPitch(pitch);
  _soundPlayerDeath.play();
}
