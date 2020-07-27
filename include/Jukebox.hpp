/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Jukebox
*/

#ifndef JUKEBOX_HPP_
#define JUKEBOX_HPP_

#include <SFML/Audio.hpp>

class Jukebox {
public:
  Jukebox();
  ~Jukebox();
  void playBackgroundMusic();
  void playBombExplosion();
  void playPlayerDeath();

private:
  sf::SoundBuffer _bufBackgroundMusic;
  sf::Sound _soundBackgroundMusic;
  sf::SoundBuffer _bufBombExplosion;
  sf::Sound _soundBombExplosion;
  sf::SoundBuffer _bufPlayerDeath;
  sf::Sound _soundPlayerDeath;
};

#endif /* !JUKEBOX_HPP_ */