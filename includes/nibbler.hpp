//
// Created by Dean DU TOIT on 2017/06/07.
//

#pragma once

#include <iostream>
#include <dlfcn.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../lib/IGUI.hpp"

class LibLoadFailed : public std::exception
{
private:
	std::string _err;
public:

	LibLoadFailed(std::string err) : _err(err)
	{
	}

	virtual const char	*what() const throw()
	{
		std::string _errRet;

		_errRet.append("Library Load Failed : ");
		_errRet.append(_err);
		return (_errRet.c_str());
	}
};
