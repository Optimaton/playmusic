#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <errorhandler.h>

namespace pm {

std::string
toString(const UserError& userError)
{
  std::string errorMsg;
  switch(userError) {
    case UserError::INVALID_CMDNAME: errorMsg = "Error: Invalid command name.\n"; break;
    case UserError::INVALID_ARGCOUNT: errorMsg = "Error: Invalid argument count.\n"; break;
    case UserError::INVALID_SWITCH: errorMsg = "Error: Invalid switch provided.\n"; break;
    case UserError::INVALID_PATH: errorMsg = "Error: Invalid path provided.\n"; break;
  }

  return errorMsg;
}

void 
printError(const UserError& userError)
{
  std::cerr << toString(userError);
}


std::string
toString(const InternalError& internalError)
{
  std::string errorMsg;
  switch(internalError) {
    case InternalError::SDL_INIT_ERROR: errorMsg = "Error: Could not initialize SDL.\n"; break;
    case InternalError::MIXER_INIT_ERROR: errorMsg = "Error: Could not initialize SDL Mixer.\n"; break;
    case InternalError::MIXER_OPEN_AUDIO_ERROR: errorMsg = "Error: Could not open audio.\n"; break;
    case InternalError::MUSIC_LOAD_ERROR: errorMsg = "Error: Could not load music.\n"; break;
    case InternalError::MUSIC_PLAY_ERROR: errorMsg = "Error: Something happened while playing music.\n"; break;
  }

  return errorMsg;
}

void 
printError(const InternalError& internalError)
{
  std::cerr << toString(internalError);  
}

void 
handleError(const InternalError& internalError)
{
  printError(internalError);  
  std::cout << " Usage: \n"
            << " playmusic [--help] [--shuffle | --repeat] <path-to-music>" << std::endl;
  std::exit(EXIT_FAILURE);
}

void 
handleError(const UserError& userError) 
{
  printError(userError);
  std::exit(EXIT_FAILURE);
}

}
