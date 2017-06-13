//
// Created by Dean DU TOIT on 2017/06/07.
//

#pragma once

#include <string>
#include <map>

struct DrawableObj
{
	std::string 		type;
	unsigned int 		x;
	unsigned int 		y;
	int 				layer;
};

struct s_keypress
{
	int p1north;
	int p1south;
	int p1east;
	int p1west;
	int quit;
	int pause;
	int	libswitch;
};

struct StartConfig
{
	int gameMode;
};

struct EventContainer
{
	int start;
	SDL_Renderer	*ren;
};

struct GameData
{
	std::map<int, int> scores;
	std::map<int, int> speeds;
	int 	highScore;
};

struct rgba
{
	rgba();
	rgba(int _r, int _g, int _b, int _a);
	void	set(int _r, int _g, int _b, int _a);
	rgba 		&operator=(rgba const & src);

	int r;
	int g;
	int b;
	int a;
};