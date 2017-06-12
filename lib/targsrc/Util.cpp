//
// Created by Dean DU TOIT on 2017/06/12.
//

#include <libIncludes.hpp>
#include <SDL2/SDL_pixels.h>

SDL_Color	createColor(int r, int g, int b, int a)
{
	SDL_Color ret;

	ret.a = a;
	ret.b = b;
	ret.g = g;
	ret.r = r;
	return (ret);
}

SDL_Texture* LoadImage(std::string file, SDL_Renderer *renderer)
{
	SDL_Surface *loadedImage = nullptr;
	SDL_Texture *texture = nullptr;
	loadedImage = SDL_LoadBMP(file.c_str());

	if (loadedImage != nullptr)
	{
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	else
		std::cout << SDL_GetError() << std::endl;
	return texture;
}