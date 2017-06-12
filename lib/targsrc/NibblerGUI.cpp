//
// Created by Dean DU TOIT on 2017/06/06.
//

#include <NibblerGUI.hpp>

NibblerGUI::NibblerGUI() : _window(nullptr), _x(50), _y(50), _blockSize(5)
{ if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw	SDLFailed(SDL_GetError());
	_colmap[std::string("HEAD")] = createColor(7, 77, 27, 255);
	_colmap[std::string("TAIL")] = createColor(11, 105, 36, 255);
	_colmap[std::string("BODY")] = createColor(7, 61, 22, 255);
	TTF_Init();
}

NibblerGUI::~NibblerGUI()
{
	if (_ren != nullptr)
		SDL_DestroyRenderer(_ren);
	if (_window != nullptr)
		SDL_DestroyWindow(_window);
	SDL_Quit();
}

void	NibblerGUI::start(StartConfig &config)
{
	config.gameMode = 0;

	_window = SDL_CreateWindow("Basic Lib", 100, 100, XRES, YRES, SDL_WINDOW_SHOWN);
	if (_window == nullptr)
		throw	SDLFailed(SDL_GetError());
	_ren = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_ren == nullptr)
	{
		SDL_DestroyWindow(_window);
		throw SDLFailed(SDL_GetError());
	}

	nokia14 = TTF_OpenFont("resources/nokiafc22.ttf", 14);
	{
		UIElement	startButton(XRES / 2 - 100, YRES / 2 - 50, 200, 40);
		SDL_Event	event;
		int 		start = 0;
		TTF_Font	*font = TTF_OpenFont("resources/nokiafc22.ttf", 12);

		startButton.setColor(100,100, 100, 100);
		if (font)
		{
			startButton.setText(_ren, "Start" , font, {176, 196, 182, 255});
		}
		startButton.setMouseUp(&onStartMouseUp, start);
		startButton.setMouseDown(&onStartMouseDown, start);
		while (!start)
		{
			SDL_RenderClear(_ren);
			startButton.draw(_ren);
			while (SDL_PollEvent(&event))
			{
				startButton.checkEvent(event);
				if  (event.type == SDL_QUIT)
				{
					exit(-1);
				}
			}
			SDL_RenderPresent(_ren);
		}
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

void 	NibblerGUI::drawObjects(const std::vector<DrawableObj> &obj, GameData  &gameData)
{
	SDL_Color	col;
	SDL_RenderClear(_ren);
	std::string	score("Score : ");

	col = createColor(122, 114, 95, 255);
	score = score + std::to_string(gameData.scores[1]);
	_score.setText(_ren, score.c_str() , nokia14, createColor(176, 196, 182, 255));
	_score.draw(_ren);

	for (auto it = _blocks.begin(), end = _blocks.end();  it != end ; it++)
	{
		SDL_SetRenderDrawColorRGB(_ren, col);
		SDL_RenderFillRect( _ren, &(*it) );
	}
	SDL_SetRenderDrawColor( _ren, 120, 120, 120, 255 );
	for (auto it = obj.begin(), end = obj.end();  it != end ; it++)
	{
		if (_colmap.find(it->type) != _colmap.end())
		{
			SDL_SetRenderDrawColorRGB(_ren, _colmap[it->type]);
		}
		else
			SDL_SetRenderDrawColor( _ren, 30, 99, 66, 0 );
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
					case 112:
					{
						keys.pause = 1;
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

	int scaler = (_x > _y) ? _x : _y;


	_blockSize = YRES / scaler ; //(YRES  - 5) / scaler;
	//sqrt(XRES * YRES) / sqrt(_x * _y);

	SDL_SetRenderDrawColor( _ren, 120, 120, 120, 255 );

	_score = UIElement(x *_blockSize + 10, 5, (XRES - x *_blockSize) / 2, 25);
	_score.setColor(120, 120, 120, 255 );

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
