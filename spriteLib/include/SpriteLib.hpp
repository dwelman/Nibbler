//
// Created by Dean DU TOIT on 2017/06/06.
//
#pragma once

#define F_ERR 0

#include <libIncludes.hpp>


#define SDL_SetRenderDrawColorRGB(R, C) SDL_SetRenderDrawColor(R, C.r, C.g, C.b, C.a)


class SpriteLib : public IGUI
{
private:
	SDL_Window							*_window;
	SDL_Renderer						*_ren;
	unsigned  int						_x, _y;
	int 								_blockSize;
	std::vector<UIElement*>				_blocks;
	std::map<std::string, SDL_Texture*>	_texmap;
	UIElement							_score;
	UIElement							_highScore;
	TTF_Font							*nokia14;
	UIElement							floor;
public:
	SpriteLib();
	~SpriteLib();
	SpriteLib(const SpriteLib &src);

	SpriteLib 		&operator=(SpriteLib const & src);
	void			init();
	int				start(StartConfig &startConf);
	void 			drawObjects(const std::vector<DrawableObj> &obj, GameData  &gameData);
	int				getInput(s_keypress &keys);
	void			setSize(int x, int y);
	bool 			clean;
	void			passWindow(IGUI *lib);
	void			setWindow(void *win);
	void			setRenderer(void *ren);
	int 			getX();
	int 			getY();
	void			end(int &end);


	class SDLFailed : public std::exception
	{
	private:
		std::string	_err;
	public:
		SDLFailed(const char *err);
		virtual const char	*what() const throw();
	};

};

