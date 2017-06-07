//
// Created by Dean DU TOIT on 2017/06/07.
//

#pragma once

#include <string>

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
};