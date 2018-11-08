#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <thread>
#include <experimental/filesystem>
#include <cstdio>
#include <SDL.h>
#include <SDL_mixer.h>

namespace filesys = std::experimental::filesystem;
const uint8_t SUCCESS = 1;
const uint8_t FAILURE = 0;
using ArgList = std::vector<std::string>;

const uint8_t minArgCount = 2;
const uint8_t maxArgCount = 3;

enum class Options {
  SHUFFLE,
  REPEAT,
	HELP,
};

Options options;
const uint8_t optIdx = 1;
const uint8_t cmdIdx = 0;
const std::string SHUFFLE_OPTION = "--shuffle";
const std::string REPEAT_OPTION = "--repeat";
const std::string HELP_OPTION = "--help";
const std::string CMD_NAME = "playmusic";
const std::string CMD_NAME_TMP = "./playmusic";
std::string absolutePath;

// decarations
bool parse(int argc, ArgList argList);
void usage();
void execute();

bool 
parse(int argc, ArgList argList)
{
  if (argList[cmdIdx] != CMD_NAME && argList[cmdIdx] != CMD_NAME_TMP) {
    std::cerr << "Error: Incorrect command name. Command name must be \"playmusic\"" << std::endl;
    usage();
    std::exit(EXIT_FAILURE);
  }

  if (argc < minArgCount || argc > maxArgCount) {
    std::cerr << "Error: Malformed command. Wrong number of arguments provided" << std::endl;
    usage();  
    std::exit(EXIT_FAILURE); // Malformed Command
  } 

  // check for the options
  if (argc == maxArgCount) {
    // switches can either be shuffle or repeat 
    if (argList[optIdx] == SHUFFLE_OPTION) {
      options =  Options::SHUFFLE;
    } else if (argList[optIdx] == REPEAT_OPTION) {
      options = Options::REPEAT;  
    } else {
      std::cerr << "Error: Incorrect switch provided. Command accepts only --shuffle and --repeat" << std::endl;
      usage();
      std::exit(EXIT_FAILURE);
    }
    try {
      const uint8_t pathIdx = 2;
      filesys::path filePath = filesys::path(argList[pathIdx].c_str());
      absolutePath = filesys::canonical(filePath).string();
    } catch (...) {
      std::cerr << "Error: Suspecting path injection attempt. Anyway don't try that in future, provide a path instead" << std::endl;
      usage();
      std::exit(EXIT_FAILURE);
    }
  }

  if (argc == minArgCount) {
		if (argList[optIdx] == HELP_OPTION) {
			usage();
			std::exit(EXIT_SUCCESS);
		} 
   
    try {
      const uint8_t pathIdx = 1;
      filesys::path filePath = filesys::path(argList[pathIdx].c_str());
      absolutePath = filesys::canonical(filePath).string();
    } catch (...) {
      std::cerr << "Error: Suspecting path injection attempt. Anyway don't try that in future, provide a path instead" << std::endl;
      usage();
      std::exit(EXIT_FAILURE);
    }
  
  }

	return SUCCESS;
}

// everything here is context based, parser must have taken care of most of the state
void execute()
{
	SDL_Init(SDL_INIT_AUDIO);
  
	int result = 0;
	int flags = MIX_INIT_MP3;

  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
    std::cerr <<  "Error: " << Mix_GetError() <<  std::endl;
  }

	if (flags != (result = Mix_Init(flags))) {
		printf("Could not initialize mixer (result: %d).\n", result);
		printf("Mix_Init: %s\n", Mix_GetError());
		exit(1);
	}

  Mix_Music* music(Mix_LoadMUS("random.mp3"));
  if (!music) {
    std::cerr << "Error: Could not load music" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  Mix_VolumeMusic( 128 );
  if ( Mix_PlayMusic( music, 1) != 0 ) {
		std::cout << "Error while playing" << std::endl;
    std::exit(EXIT_FAILURE);
  } 
  
  SDL_Delay(1000*20); 
	Mix_FreeMusic(music);
  music = nullptr;
  Mix_CloseAudio();
	Mix_Quit();
  SDL_Quit();
	std::cout << "Hurray !" << std::endl;
}

/*
 * usage: playmusic --shuffle ~/somerandommusicfolder
 *        playmusic --repeat  ~/somerandommusicfolder/randommusic.mp3
 *        playmusic ~/somerandomemusicfolder/
 * 
 * Note: music files are read based on extension, 
 *       current support is limited to mp3 and wav
 */
void usage()
{
  std::cout << " Usage: \n"
            << " playmusic [--help] [--shuffle | --repeat] <path-to-music>" << std::endl;
}

int main(int argc, char** argv)
{
  // safe code - code safe, we don't want to mess with pointers
  
  ArgList argList {argv, argv + argc};
  if (parse(argc, argList)) {
    std::thread playMusic(execute);
    playMusic.join();
  }
  return 0;  
}
