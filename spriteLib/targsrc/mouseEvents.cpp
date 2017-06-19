//
// Created by Dean DU TOIT on 2017/06/12.
//

#include <libIncludes.hpp>

void 		onStartMouseUp(void *d, UIElement *btn)
{
	EventContainer *e = reinterpret_cast<EventContainer*>(d);
	e->start = 1;
	btn->setTexture((*e->texmap)["PLAY"]);
}

void 		onStartMouseDown(void *d, UIElement *btn)
{
	EventContainer *e = reinterpret_cast<EventContainer*>(d);
	d = nullptr;
	btn->setTexture((*e->texmap)["PLAY_PRESS"]);
}


void 		onStartMouseMove(void *d, UIElement *btn)
{
	int rx, ry;

	if (*reinterpret_cast<int*>(d) > 0)
	{
		rx = btn->posX();
		ry = abs(rand()) % YRES;
		ry = (ry + btn->height() > YRES) ? YRES - btn->height() : ry; //- btn->height();
		rx = abs(rand()) % XRES;// - btn->width();
		rx = (rx + btn->width() > XRES) ? XRES - btn->width() : rx; //- btn->height();
		*reinterpret_cast<int *>(d) = *reinterpret_cast<int *>(d) - 1;
		btn->move(rx, ry);
	}
}