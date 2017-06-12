//
// Created by Dean DU TOIT on 2017/06/06.
//
#pragma once

#define F_ERR 0

#include <libIncludes.hpp>

#define YRES 720
#define XRES 1024
#define SDL_SetRenderDrawColorRGB(R, C) SDL_SetRenderDrawColor(R, C.r, C.g, C.b, C.a)

class NibblerGUI : public IGUI
{
private:
	SDL_Window							*_window;
	SDL_Renderer						*_ren;
	int 								_x, _y;
	int 								_blockSize;
	std::vector<SDL_Rect>				_blocks;
	std::map<std::string, SDL_Color>	_colmap;
	UIElement							_score;
	UIElement							_highScore;
	TTF_Font							*nokia14;

public:
	NibblerGUI();
	~NibblerGUI();
	NibblerGUI(const NibblerGUI &src);

	NibblerGUI 		&operator=(NibblerGUI const & src);
	void			start(StartConfig &startConf);
	void 			drawObjects(const std::vector<DrawableObj> &obj, GameData  &gameData);
	int				getInput(s_keypress &keys);
	void			setSize(int x, int y);


	class SDLFailed : public std::exception
	{
	private:
		std::string	_err;
	public:
		SDLFailed(const char *err);
		virtual const char	*what() const throw();
	};

};

