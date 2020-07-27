/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** EventHandler
*/

#include "EventHandler.hpp"

EventHandler::EventHandler(irr::IrrlichtDevice &device) :
_device(device), _keyIsDown(), _gameOption(new std::string("")) {
  for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
    _keyIsDown[i] = false;
}

EventHandler::~EventHandler() {
}

EventHandler::EventHandler(const EventHandler &e) :
_device(e._device), _gameOption(e._gameOption) {
}
EventHandler &EventHandler::operator=(const EventHandler &e) {
  this->_device = e._device;
  this->_gameOption = e._gameOption;
  return (*this);
}

bool EventHandler::OnEvent(const irr::SEvent &event) {
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    _keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
  else if (event.EventType == irr::EET_GUI_EVENT) {
      irr::gui::IGUIEnvironment *env = _device.getGUIEnvironment();
      switch (event.GUIEvent.EventType) {
        case irr::gui::EGET_BUTTON_CLICKED:
          switch (event.GUIEvent.Caller->getID()) {
            case GUI_ID_NEW_GAME_1P_BUTTON:
              _gameOption->assign("new1p");
              return true;
            case GUI_ID_NEW_GAME_2P_BUTTON:
              _gameOption->assign("new2p");
              return true;
            case GUI_ID_LOAD_GAME_BUTTON:
              env->addFileOpenDialog(L"Please choose a file.", true, 0, -1, true);
              return true;
            case GUI_ID_QUIT_BUTTON:
              _device.closeDevice();
              return true;
            default:
              return false;
          }
        break;
        case irr::gui::EGET_FILE_SELECTED: {
          irr::gui::IGUIFileOpenDialog *dialog = (irr::gui::IGUIFileOpenDialog *)event.GUIEvent.Caller;
          std::wstring ws(dialog->getFileName());
          std::string file(ws.begin(), ws.end());
          _gameOption->assign(file);
        }
      default:
        break;
      }
    }
  return (false);
}

bool EventHandler::IsKeyDown(irr::EKEY_CODE keyCode) const {
  return (_keyIsDown[keyCode]);
}
