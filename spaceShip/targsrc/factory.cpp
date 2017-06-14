//
// Created by Dean DU TOIT on 2017/06/06.
//

#include <string>
#include "SpriteLib.hpp"

extern "C"
{
	IGUI *make()
	{
		return (new SpriteLib());
	}
}