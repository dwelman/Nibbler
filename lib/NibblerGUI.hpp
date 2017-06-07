//
// Created by Dean DU TOIT on 2017/06/06.
//
#pragma once

#define F_ERR 0

#include <SDL2/SDL.h>
#include "IGUI.hpp"
#include <exception>
#include <string>
#include <iostream>
#include <queue>

#define YRES 480
#define XRES 680

class NibblerGUI : public IGUI
{
private:
	SDL_Window					*_window;
	SDL_Renderer				*_ren;
	std::queue<int>				_events;
	int 						_x, _y;
	int 						_blockSize;
	std::vector<SDL_Rect>		_blocks;

public:
	NibblerGUI();
	~NibblerGUI();

	void			start();
	void 			drawObjects(const std::vector<DrawableObj> &obj);
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
