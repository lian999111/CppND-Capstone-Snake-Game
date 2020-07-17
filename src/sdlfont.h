#ifndef SDLFONT_H
#define SDLFONT_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

class SDLFont {
public:
  SDLFont(std::string path_to_font, int size);
  ~SDLFont();
  TTF_Font *Get();

  // Move
  SDLFont(SDLFont &&rhs);
  SDLFont &operator=(SDLFont &&rhs);

  // Copy (deleted)
  SDLFont(const SDLFont &rhs) = delete;
  SDLFont &operator=(const SDLFont &rhs) = delete;

private:
  // a pointer to font
  TTF_Font *psdl_font;
};

#endif