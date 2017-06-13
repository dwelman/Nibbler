//
// Created by Dean DU TOIT on 2017/06/12.
//

#include <libIncludes.hpp>

void 		onStartMouseUp(void *d, UIElement *btn)
{
	EventContainer *e = reinterpret_cast<EventContainer*>(d);
	e->start = 1;
	btn->setTexture(LoadImage("resources/sprites/play_button.png", e->ren));
}

void 		onStartMouseDown(void *d, UIElement *btn)
{
	EventContainer *e = reinterpret_cast<EventContainer*>(d);
	d = nullptr;
	btn->setTexture(LoadImage("resources/sprites/play_button_clicked.png", e->ren));
}