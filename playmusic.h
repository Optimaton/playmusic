#ifndef __PLAY_MUSIC_H__
#define __PLAY_MUSIC_H__

namespace pm {

namespace filesys = std::experimental::filesystem;
const uint8_t SUCCESS = 1;
const uint8_t FAILURE = 0;
using ArgList = std::vector<std::string>;

/* set of options/switches one can specify with the command */
enum class Options {
  SHUFFLE,
  REPEAT,
  HELP,
};

enum class UserError {
  INVALID_CMDNAME,
  INVALID_ARGCOUNT,
  INVALID_SWITCH,
  INVALID_PATH,
};

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

void printError(const UserError& userError)
{
  std::cerr << toString(userError);
}

enum class InternalError {
 SDL_INIT_ERROR,
 MIXER_INIT_ERROR,
 MIXER_OPEN_AUDIO_ERROR,
 MUSIC_LOAD_ERROR,
 MUSIC_PLAY_ERROR,
};

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

void printError(const InternalError& internalError)
{
  std::cerr << toString(internalError);  
}

void handleError(const InternalError& internalError)
{
  printError(internalError);  
  std::cout << " Usage: \n"
            << " playmusic [--help] [--shuffle | --repeat] <path-to-music>" << std::endl;
  std::exit(EXIT_FAILURE);
}

void handleError(const UserError& userError) 
{
  printError(userError);
  std::exit(EXIT_FAILURE);
}

const uint8_t minArgCount = 2;
const uint8_t maxArgCount = 3;
const std::string SHUFFLE_OPTION = "--shuffle"; 
const std::string REPEAT_OPTION = "__repeat";
const std::string HELP_OPTION = "__help";
const std::string CMD_NAME = "playmusic";
const std::string CMD_NAME_TMP = "./playmusic";

class PlayMusic {
public:
  PlayMusic(int argc, char** argv); 
  ~PlayMusic();

  bool parse(); // parse the command
  bool execute(); // execute the command
private:
  PlayMusic(); // don't use, never mind let's keep it private
  void usage(); // print usage
  void setAbsolutePath(uint8_t pathIdx);

  bool isDirectory();
  bool checkExtension(std::string filePath);

  ArgList _argList;
  uint8_t _argCount;
  std::string _absolutePath; 
  Options _options;
  
  // constants - for parsing and abstraction
  };  
}

#endif // __PLAY_MUSIC_H__
