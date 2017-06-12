#pragma once

/*
 * All GUI's for nibbler should use this interface
 */
#include "dataStructures.hpp"
#include <vector>

class IGUI
{
public:
	virtual 				~IGUI(){};
	virtual void			start(StartConfig &startConf) = 0;
	virtual void 			drawObjects(const std::vector<DrawableObj> &obj, GameData  &gameData) = 0;
	virtual int				getInput(s_keypress &keys) = 0;
	virtual void			setSize(int x, int y) = 0;
};

