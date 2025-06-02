#include "text.h"
#include "colors.h"

Text::Text()
{
	m_font =  TTF_OpenFont("Sansation.ttf", 50);
}

Text::~Text()
{
	TTF_CloseFont(m_font);
}

void Text::render(SDL_Renderer* renderer, std::string content, int x, int y, int width, int height)
{
	SDL_Color color {WHITE.r, WHITE.g, WHITE.b, WHITE.a};

	// destination_surface = TTF_RenderText_Solid(m_font, content.c_str(), color);
	SDL_Surface* texture_sufrace = TTF_RenderText_Solid(m_font, content.c_str(), color);
	SDL_Texture* texture_text = SDL_CreateTextureFromSurface(renderer, texture_sufrace);
	SDL_FreeSurface(texture_sufrace);

	SDL_Rect rect_text;
	rect_text.x = x;
	rect_text.y = y;
	rect_text.w = width;
	rect_text.h = height;

	SDL_RenderCopy(renderer, texture_text, nullptr ,&rect_text);
	// SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture_text);
}
