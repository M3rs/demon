#include <iostream>

#include "fmod_studio.hpp"
#include <SFML/Graphics.hpp>

#include "oneshot.hpp"

FMOD_RESULT result;
FMOD::Studio::System *studioSystem = NULL;
FMOD::System *lowLevelSystem = NULL;
std::string mediaPath = "media";

FMOD::Studio::EventDescription *evtGhost;
FMOD::Studio::EventDescription *evtThor;
FMOD::Studio::EventDescription *evtSiegeTank;
FMOD::Studio::EventDescription *evtMineralError;
// FMOD::Studio::EventInstance*	instVoidRay;

int initialize() {
  result = FMOD::Studio::System::create(&studioSystem);
  if (result != FMOD_OK) {
    std::cout << "Error: Failed to create FMOD studio system instance."
              << std::endl;
    std::cin.get();
    return 0;
  }

  result = studioSystem->getLowLevelSystem(&lowLevelSystem);
  if (result != FMOD_OK) {
    std::cout << "Error: Could not get low level system." << std::endl;
    std::cin.get();
    return 0;
  }

  result = lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
  if (result != FMOD_OK) {
    std::cout << "Error: Problem setting software format." << std::endl;
    std::cin.get();
    return 0;
  }

  result = studioSystem->initialize(32, FMOD_STUDIO_INIT_NORMAL,
                                    FMOD_INIT_NORMAL, 0);
  if (result != FMOD_OK) {
    std::cout << "Error: Initialization of FMOD studio system instance could "
                 "not be completed."
              << std::endl;
    std::cin.get();
    return 0;
  }

  FMOD::Studio::Bank *masterBank = NULL;
  result = studioSystem->loadBankFile(
      "Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);
  if (result != FMOD_OK) {
    std::cout << "Error: Master Bank file could not be located or loaded."
              << std::endl;
    std::cin.get();
    return 0;
  }

  FMOD::Studio::Bank *stringsBank = NULL;
  result = studioSystem->loadBankFile(
      "Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);
  if (result != FMOD_OK) {
    std::cout << "Error: Strings Bank file could not be located or loaded."
              << std::endl;
    std::cin.get();
    return 0;
  }

  FMOD::Studio::Bank *starcraftBank = NULL;
  result = studioSystem->loadBankFile(
      "starcraft.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &starcraftBank);
  if (result != FMOD_OK) {
    std::cout << "Error: Starcraft bank could not be loaded." << std::endl;
    std::cin.get();
    return 0;
  }

  result = studioSystem->getEvent("event:/ghost", &evtGhost);
  if (result != FMOD_OK) {
    std::cout << "Error: Could not retrieve Ghost FMOD event." << std::endl;
    std::cin.get();
    return 0;
  }

  result = studioSystem->getEvent("event:/thor", &evtThor);
  if (result != FMOD_OK) {
    std::cout << "Error: Could not retrieve Thor FMOD event." << std::endl;
    std::cin.get();
    return 0;
  }

  result = studioSystem->getEvent("event:/siegetank", &evtSiegeTank);
  if (result != FMOD_OK) {
    std::cout << "Error: Could not retrieve Siege Tank FMOD event."
              << std::endl;
    std::cin.get();
    return 0;
  }

  result = studioSystem->getEvent("event:/mineralerror", &evtMineralError);
  if (result != FMOD_OK) {
    std::cout << "Error: Could not retrieve MineralErrorFMOD event."
              << std::endl;
    std::cin.get();
    return 0;
  }

  return 0;
}

int main() {
  initialize();

  sf::RenderWindow window(sf::VideoMode(800, 600), "StarCraft!");

  int minerals = 1000;

  std::cout << "Please press the number of the unit you want to build."
            << std::endl;
  std::cout << "1. Ghost" << std::endl;
  std::cout << "2. Thor" << std::endl;
  std::cout << "3. Siege Tank" << std::endl;
  std::cout << "4. Quit application" << std::endl;

  while (window.isOpen()) {
    int input = 0;
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        case sf::Keyboard::Num1:
          input = 1;
          break;
        case sf::Keyboard::Num2:
          input = 2;
          break;
        case sf::Keyboard::Num3:
          input = 3;
          break;
        case sf::Keyboard::Num4:
          window.close();
          break;
        }
      }
    }

    if (input == 1) {
      if (minerals >= 200) {
        OneShot::Play(evtGhost);
        minerals -= 200;
      } else {
        OneShot::Play(evtMineralError);
      }
    }
    if (input == 2) {
      if (minerals >= 400) {
        OneShot::Play(evtThor);
        minerals -= 400;
      } else {
        OneShot::Play(evtMineralError);
      }
    }
    if (input == 3) {
      if (minerals >= 150) {
        OneShot::Play(evtSiegeTank);
        minerals -= 150;
      } else {
        OneShot::Play(evtMineralError);
      }
    }

    studioSystem->update();

    window.clear();
    window.display();
  }

  return 0;
}
