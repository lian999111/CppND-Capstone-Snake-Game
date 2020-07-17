#include "sdlfont.h"
#include <iostream>

// SDLFont
SDLFont::SDLFont(std::string path_to_font, int size) {
  // Initialize SDL_TTF
  if (TTF_Init() == -1) {
    std::cerr << "SDL_TTF could not initialize.\n";
    std::cerr << "SDL_TTF Error: " << TTF_GetError() << "\n";
  }
  // TTF_OpenFont() only valid after TTF_Init()
  psdl_font = TTF_OpenFont(path_to_font.c_str(), size);
}

SDLFont::~SDLFont() {
  TTF_CloseFont(psdl_font);
  TTF_Quit();
}

SDLFont::SDLFont(SDLFont &&rhs) : psdl_font(rhs.psdl_font) {
  rhs.psdl_font = nullptr;
}

SDLFont &SDLFont::operator=(SDLFont &&rhs) {
  psdl_font = rhs.psdl_font;
  rhs.psdl_font = nullptr;
}

TTF_Font *SDLFont::Get() { return psdl_font; }
