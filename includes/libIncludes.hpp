//
// Created by Dean DU TOIT on 2017/06/12.
//

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <IGUI.hpp>
#include <exception>
#include <string>
#include <iostream>
#include <map>
#include <UIGroup.hpp>
#include <sstream>

void 		onStartMouseUp(void *d, UIElement *btn);
void 		onStartMouseDown(void *d, UIElement *btn);
SDL_Color	createColor(int r, int g, int b, int a);
