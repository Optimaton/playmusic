#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <experimental/filesystem>
#include <cstdio>
#include <string>
#include <algorithm>
#include <random>
#include <SDL.h>
#include <SDL_mixer.h>
#include <errorhandler.h>
#include <playmusic.h>

namespace pm {

PlayMusic::PlayMusic(int argc, char** argv)
  : _argCount(argc)
{
  // copy the strings in argv to vector for better 
  // uasge 
  std::vector<std::string>(argv, argv + argc).swap(_argList);  
}

PlayMusic::~PlayMusic()
{}

void 
PlayMusic::setAbsolutePath(const uint8_t pathIdx)
{
  try {
    filesys::path filePath = filesys::path(_argList[pathIdx].c_str());
      _absolutePath = filesys::canonical(filePath).string();
  } catch (...) {
      handleError(UserError::INVALID_PATH);
  }
}

bool
PlayMusic::isDirectory()
{
  bool isDir = false;
  try {
    filesys::path filePath = filesys::path(_absolutePath);
    isDir = filesys::is_directory(filePath);
  } catch (...)  {
    handleError(UserError::INVALID_PATH);  
  }

  return isDir;
}

bool
PlayMusic::checkExtension(std::string filePath)
{
  auto const pos = filePath.find_last_of('.');
  if (pos != std::string::npos) {
    if (filePath.substr(pos+1) == "mp3") {
      return true;  
    }  
  }

  return false;
}


/* parse the arguments passed to the command*/
bool
PlayMusic::parse()
{
   // make sure the comand is playmusic. 
   uint8_t cmdIdx = 0;
   if (_argList[cmdIdx] != CMD_NAME && _argList[cmdIdx] != CMD_NAME_TMP) {
     handleError(UserError::INVALID_CMDNAME);
   }

   uint8_t pathIdx;
   uint8_t optIdx = 1;
   switch(_argCount) {
    case minArgCount: // [ --help | pathToFile ]
      if (_argList[optIdx] == HELP_OPTION) {
        usage();
        std::exit(EXIT_SUCCESS);
      } 

      pathIdx = 1;
      setAbsolutePath(pathIdx);
      break;

    case maxArgCount: // [ --shuffle | --repeat ] <pathToFile>
      if (_argList[optIdx] == SHUFFLE_OPTION) {
        _options = Options::SHUFFLE;  
      } else if (_argList[optIdx] == REPEAT_OPTION) {
        _options = Options::REPEAT;  
      } else {
        handleError(UserError::INVALID_SWITCH);
      }
      
      pathIdx = 2;
      setAbsolutePath(pathIdx);
      break;
    default:
        handleError(UserError::INVALID_ARGCOUNT);
   }

   if (isDirectory()) {
    for (auto& file : filesys::directory_iterator(_absolutePath.c_str())) {
      _fileList.emplace_back(file.path().string());
    }
   } else {
    _fileList.emplace_back(_absolutePath);
   }

  return SUCCESS;   
}

// everything here is context based, parser must have taken care of most of the state
bool 
PlayMusic::execute()
{
	SDL_Init(SDL_INIT_AUDIO);
  
	int result = 0;
	int flags = MIX_INIT_MP3;

  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
    handleError(InternalError::MIXER_OPEN_AUDIO_ERROR);
  }

	if (flags != (result = Mix_Init(flags))) {
	  handleError(InternalError::MIXER_INIT_ERROR);
  }

  Mix_Music* music;
  if (isDirectory()) {
    if (_options == Options::SHUFFLE) {
     std::random_device rd;
     std::mt19937 rng(rd());
     std::shuffle(std::begin(_fileList), std::end(_fileList), rng);
    }
    for (auto& fileName : _fileList) {
      if (checkExtension(fileName)) {
        std::cout << "Now Playing: " << fileName << std::endl;
        music = Mix_LoadMUS(fileName.c_str());
        if (!music) {
          handleError(InternalError::MUSIC_LOAD_ERROR);
        }

        if ( Mix_PlayMusic( music, 1) != 0 ) {
          handleError(InternalError::MUSIC_PLAY_ERROR);
        } 

        while (Mix_PlayingMusic()) {
          SDL_Delay(50); 
        }
        Mix_FreeMusic(music);
        music = nullptr;
      }
    }
  } else {
     if (checkExtension(_absolutePath)) {
        std::string fileName = filesys::path(_absolutePath).filename().string();
        std::cout << "Now Playing: " << fileName << std::endl;
        music = Mix_LoadMUS(_absolutePath.c_str());
        if (!music) {
          handleError(InternalError::MUSIC_LOAD_ERROR);
        }

        if ( Mix_PlayMusic( music, 1) != 0 ) {
          handleError(InternalError::MUSIC_PLAY_ERROR);
        } 

        while (Mix_PlayingMusic()) {
          SDL_Delay(50); 
        }
        Mix_FreeMusic(music);
        music = nullptr;
      }
  }
  Mix_CloseAudio();
	Mix_Quit();
  SDL_Quit();
}

/*
 * usage: playmusic --shuffle ~/somerandommusicfolder
 *        playmusic --repeat  ~/somerandommusicfolder/randommusic.mp3
 *        playmusic ~/somerandomemusicfolder/
 * 
 * Note: music files are read based on extension, 
 *       current support is limited to mp3 and wav
 */
void 
PlayMusic::usage()
{
  std::cout << " Usage: \n"
            << " playmusic [--help] [--shuffle | --repeat] <path-to-music>" << std::endl;
}

}


