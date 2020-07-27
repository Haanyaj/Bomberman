/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** EventHandler
*/

#ifndef EVENTHANDLER_HPP_
#define EVENTHANDLER_HPP_

#include <irrlicht/irrlicht.h>
#include <string>

enum buttons {
  GUI_ID_NEW_GAME_1P_BUTTON,
  GUI_ID_NEW_GAME_2P_BUTTON,
  GUI_ID_LOAD_GAME_BUTTON,
  GUI_ID_QUIT_BUTTON
};

class EventHandler : public irr::IEventReceiver {

public:
  EventHandler(irr::IrrlichtDevice &);
  ~EventHandler();
  EventHandler(const EventHandler &);
  EventHandler &operator=(const EventHandler &);
  virtual bool OnEvent(const irr::SEvent& event);
  virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
  irr::IrrlichtDevice &getDevice() const { return (_device); };
  std::string *getGameOption() const { return (_gameOption); };

private:
  irr::IrrlichtDevice &_device;
  bool _keyIsDown[irr::KEY_KEY_CODES_COUNT];
  std::string *_gameOption;
};

#endif /* !EVENTHANDLER_HPP_ */
