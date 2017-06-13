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
	virtual int				start(StartConfig &startConf) = 0;
	virtual void 			init() = 0;
	virtual void 			drawObjects(const std::vector<DrawableObj> &obj, GameData  &gameData) = 0;
	virtual int				getInput(s_keypress &keys) = 0;
	virtual void			setSize(int x, int y) = 0;
	virtual void			passWindow(IGUI *guiLib) = 0;
	virtual	void			setWindow(void *win) = 0;
	virtual	void			setRenderer(void *ren) = 0;
	virtual	int 			getX() = 0;
	virtual	int 			getY() = 0;
};

