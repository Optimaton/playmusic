#ifndef __PLAY_MUSIC_H__
#define __PLAY_MUSIC_H__

namespace pm {

namespace filesys = std::experimental::filesystem;
const uint8_t SUCCESS = 1;
const uint8_t FAILURE = 0;
using ArgList = std::vector<std::string>;
using FileList = std::vector<std::string>;
/* set of options/switches one can specify with the command */
enum class Options {
  SHUFFLE,
  REPEAT,
  HELP,
};

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
  FileList _fileList;
  uint8_t _argCount;
  std::string _absolutePath; 
  Options _options;
  
  // constants - for parsing and abstraction
  };  
}

#endif // __PLAY_MUSIC_H__
