//
// Created by Dean DU TOIT on 2017/06/06.
//

#include "NibblerGUI.hpp"

NibblerGUI::NibblerGUI() : _window(nullptr), _x(50), _y(50), _blockSize(5)
{
}

NibblerGUI::~NibblerGUI()
{
	SDL_Quit();
}

void	NibblerGUI::start()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw	SDLFailed(SDL_GetError());
	_window = SDL_CreateWindow("Basic Lib", 100, 100, XRES, YRES, SDL_WINDOW_SHOWN);
	if (_window == nullptr)
		throw	SDLFailed(SDL_GetError());
	_ren = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_ren == nullptr)
	{
		SDL_DestroyWindow(_window);
		throw SDLFailed(SDL_GetError());
	}
}

NibblerGUI::NibblerGUI(const NibblerGUI &src)
{
	*this = src;
}

NibblerGUI 		&NibblerGUI::operator=(NibblerGUI const & src)
{
	_window = src._window;
	_ren = src._ren;
	_x = src._x;
	_y =  src._y;
	_blockSize = src._blockSize;
	_blocks = src._blocks;
	return (*this);
}

void 	NibblerGUI::drawObjects(const std::vector<DrawableObj> &obj)
{
	// Set render color to blue ( rect will be rendered in this color )
	SDL_RenderClear(_ren);
	for (auto it = _blocks.begin(), end = _blocks.end();  it != end ; it++)
	{
		SDL_SetRenderDrawColor( _ren, 50, 50, 120, 255 );
		SDL_RenderFillRect( _ren, &(*it) );
		SDL_SetRenderDrawColor( _ren, 120, 120, 120, 255 );
	}

	for (auto it = obj.begin(), end = obj.end();  it != end ; it++)
	{
		SDL_SetRenderDrawColor( _ren, 0, 0, 0, 0 );
		if (it->y * _x + it->x < _blocks.size())
			SDL_RenderFillRect( _ren, &_blocks[it->y * _x + it->x] );
		SDL_SetRenderDrawColor( _ren, 120, 120, 120, 255 );
	}
	// Render the rect to the screen
	SDL_RenderPresent(_ren);
}

NibblerGUI::SDLFailed::SDLFailed(const char *err) : _err(err)
{
}

const char *NibblerGUI::SDLFailed::what() const throw()
{
	std::string			_lastErr;

	_lastErr = "SDL error : ";
	_lastErr.append(_err);
	SDL_Quit();
	return (_lastErr.c_str());
}

int			NibblerGUI::getInput(s_keypress &keys)
{
	SDL_Event	event;

	memset(&keys, 0, sizeof(s_keypress));
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN :
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_LEFT :
					{
						if (keys.p1west > 0)
							keys.p1west--;
						else
							keys.p1east++;
						break;
					}
					case SDLK_RIGHT :
					{
						if (keys.p1east > 0)
							keys.p1east--;
						else
							keys.p1west++;
						break;
					}
					case SDLK_UP :
					{
						if (keys.p1south > 0)
							keys.p1south--;
						else
							keys.p1north++;
						break;
					}
					case SDLK_DOWN :
					{
						if (keys.p1north > 0)
							keys.p1north--;
						else
							keys.p1south++;
						break;
					}
					case SDLK_ESCAPE:
					{
						keys.quit = 1;
						break;
					}
				}
				break;
			}
			case SDL_QUIT:
			{
				keys.quit = 1;
			}
		}
	}
	return (keys.p1north + keys.p1south + keys.p1east + keys.p1west);
}

void			NibblerGUI::setSize(int x, int y)
{
	_x = x;
	_y = y;
	_blockSize = (YRES  - 5)/ _y;
	SDL_SetRenderDrawColor( _ren, 120, 120, 120, 255 );

	SDL_Rect r;
	r.x = 5;
	r.y = 5;
	r.w = _blockSize;
	r.h = _blockSize;
	for (int i = 0; i < _y; i++ )
	{
		r.y = i * _blockSize + 5;
		for (int j = 0; j < _x; j++ )
		{
			r.x = j * _blockSize + 5;
			_blocks.push_back(r);
		}
	}
}
