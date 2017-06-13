//
// Created by Dean DU TOIT on 2017/06/12.
//

#include <libIncludes.hpp>

void 		onStartMouseUp(void *d, UIElement *btn)
{
	*reinterpret_cast<int*>(d) = 1;
	btn->setColor(176, 196, 182, 255);
}

void 		onStartMouseDown(void *d, UIElement *btn)
{
	d = nullptr;
	btn->setColor(196, 216, 202, 255);
}