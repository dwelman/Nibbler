#include <UIGroup.hpp>

int				UIGroup::next = 1;

UIGroup::UIGroup() : ID(next)
{
	next++;
}

UIGroup::UIGroup(const UIGroup & src) : ID(next)
{
	elem = src.elem;
	next++;
}

UIGroup::~UIGroup()
{
}

UIGroup & UIGroup::operator=(const UIGroup & src)
{
	elem = src.elem;
	return (*this);
}

void UIGroup::hide()
{
	for (auto it = elem.begin(), end = elem.end(); it != end; it++)
	{
		(*it)->hide();
	}
}

void UIGroup::show()
{
	for (auto it = elem.begin(), end = elem.end(); it != end; it++)
	{
		(*it)->show();
	}
}

void UIGroup::enable()
{
	for (auto it = elem.begin(), end = elem.end(); it != end; it++)
	{
		(*it)->enable();
	}
}

void UIGroup::disable()
{
	for (auto it = elem.begin(), end = elem.end(); it != end; it++)
	{
		(*it)->disable();
	}
}

void UIGroup::draw(SDL_Renderer *ren)
{
	for (auto it = elem.begin(), end = elem.end(); it != end; it++)
	{
		(*it)->draw(ren);
	}
}

void UIGroup::add(UIElement &newElem)
{
	if (elem.size() == 0)
		elem.push_back(&newElem);
	else
	{
		auto it = elem.begin();
		while ((*it)->layer > newElem.layer)
			it++;
		elem.insert(it, &newElem);
	}
}

void UIGroup::checkEvent(const SDL_Event & e, bool exec)
{
	for (auto it = elem.begin(), end = elem.end(); it != end; it++)
	{
		(*it)->checkEvent(e, exec);
	}
}
