#ifndef __ERROR_HANDLER_H__
#define __ERROR_HANDLER_H__

namespace pm {

enum class UserError {
  INVALID_CMDNAME,
  INVALID_ARGCOUNT,
  INVALID_SWITCH,
  INVALID_PATH,
};

std::string toString(const UserError& userError);
void printError(const UserError& userError);
void handleError(const UserError& userError);


enum class InternalError {
 SDL_INIT_ERROR,
 MIXER_INIT_ERROR,
 MIXER_OPEN_AUDIO_ERROR,
 MUSIC_LOAD_ERROR,
 MUSIC_PLAY_ERROR,
};

std::string toString(const InternalError& internalError);
void printError(const InternalError& internalError);
void handleError(const InternalError& internalError);
}

#endif // __ERROR_HANDLER_H__
