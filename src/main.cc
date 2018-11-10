#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <experimental/filesystem>
#include <cstdio>
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
#include <errorhandler.h>
#include <playmusic.h>

int main(int argc, char** argv)
{
  // safe code - code safe, we don't want to mess with pointers
  using namespace pm;
  PlayMusic playMusic(argc, argv);
  if (playMusic.parse()) {
    playMusic.execute();  
  } 
  return 0;  
}
