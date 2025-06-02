#pragma once

#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

class Text {
	public:
		Text();
		~Text();

		void render(SDL_Renderer* renderer, std::string content, int x, int y, int width, int height);

	private:
		TTF_Font* 	m_font;
		std::string m_text;
};

#endif