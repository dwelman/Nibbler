//
// Created by Dean DU TOIT on 2017/06/06.
//

#include <NibblerGUI.hpp>

NibblerGUI::NibblerGUI() : _window(nullptr), _ren(nullptr), _x(50), _y(50), _blockSize(5),
	clean(true)

{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw	SDLFailed(SDL_GetError());
	TTF_Init();
}

NibblerGUI::~NibblerGUI()
{
	if (clean)
	{
		if (_ren != nullptr)
			SDL_DestroyRenderer(_ren);
		if (_window != nullptr)
			SDL_DestroyWindow(_window);
		SDL_Quit();
	}
	for (auto it = _texmap.begin(); it != _texmap.end(); it++)
		SDL_DestroyTexture((*it).second);
}

void			NibblerGUI::init()
{
	if (_window == nullptr)
	{
		_window = SDL_CreateWindow("Basic Lib", 100, 100, XRES, YRES, SDL_WINDOW_SHOWN);
	}
	if (_window == nullptr)
		throw	SDLFailed(SDL_GetError());

	if (_ren == nullptr)
		_ren = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_ren == nullptr)
	{
		SDL_DestroyWindow(_window);
		throw SDLFailed(SDL_GetError());
	}
	nokia14 = TTF_OpenFont("resources/ComicSans.ttf", 14);
	_texmap[std::string("HEAD")] = LoadImage("resources/sprites/snake_head.png", _ren);
	_texmap[std::string("TAIL")] = LoadImage("resources/sprites/snake_tail.png", _ren);
	_texmap[std::string("BODY")] = LoadImage("resources/sprites/snake_body.png", _ren);
	_texmap[std::string("BASIC_FOOD")] = LoadImage("resources/sprites/rat.png", _ren);
	_texmap[std::string("SHRINK_FOOD")] = LoadImage("resources/sprites/weeds.png", _ren);
	_texmap[std::string("SUPER_FOOD")] = LoadImage("resources/sprites/B.png", _ren);
	_texmap[std::string("FLOOR")] = LoadImage("resources/sprites/whitefloor.jpg", _ren);
	_texmap[std::string("PLAY")] = LoadImage("resources/sprites/play_button.png", _ren);
	_texmap[std::string("JUNGLE")] = LoadImage("resources/sprites/jungle.png", _ren);
	_texmap[std::string("CAPTION")] = LoadImage("resources/sprites/snek.png", _ren);

}

int	NibblerGUI::start(StartConfig &config)
{
	config.gameMode = 0;
	{
		SDL_RenderClear(_ren);
		UIElement		startButton(XRES / 2 - 150, YRES / 2 - 100, 300, 200);
		UIElement		backdrop(0, 0 ,XRES, YRES);
		UIElement		caption(XRES / 2 - 250, YRES / 4 - 100, 500, 200);;

		UIGroup			gr;
		SDL_Event		event;
		int				s = 0;
		EventContainer	ev;

		startButton.setColor(100,100, 100, 100);
		ev.ren = _ren;
		ev.start = 0;
		startButton.setTexture(_texmap["PLAY"]);
		backdrop.setTexture(_texmap["JUNGLE"]);
		caption.setTexture(_texmap["CAPTION"]);
		startButton.setMouseUp(&onStartMouseUp, ev);
		startButton.setMouseDown(&onStartMouseDown, ev);
		backdrop.layer = 2;
		startButton.layer = 1;
		caption.layer = 1;
		gr.add(backdrop);
		gr.add(startButton);
		gr.add(caption);
		while (!ev.start)
		{
			if (s)
			{
				s--;
				if (!s)
					ev.start = 1;
			}
			SDL_RenderClear(_ren);
			gr.draw(_ren);
			while (SDL_PollEvent(&event))
			{
				gr.checkEvent(event);
				if  (event.type == SDL_QUIT)
				{
					exit(1);
				}
				if  (event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_RETURN:
						{
							startButton.onMouseDown();
							s = 5;
							break;
						}
						case SDLK_1:
							return 1;
						case SDLK_2:
							return 2;
						case SDLK_3:
							return 3;
						case SDLK_ESCAPE:
							exit(1);
				}
				}
			}
			SDL_RenderPresent(_ren);
		}
	}
	return 0;
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
	std::string	score("    Score : "), hs ("Highscore : ");
	int 		i;

	col = createColor(122, 114, 95, 255);
	score = score + std::to_string(gameData.scores[1]);
	_score.setText(_ren, score.c_str() , nokia14, createColor(176, 196, 182, 255));
	_score.draw(_ren);
	hs = hs + std::to_string(gameData.highScore);
	_highScore.setText(_ren, hs.c_str() , nokia14, createColor(176, 196, 182, 255));
	_highScore.draw(_ren);
	floor.draw(_ren);
	for (auto it = obj.begin(), end = obj.end();  it != end ; it++)
	{
		i = it->y * _x + it->x;
		if (it->y < _y && it->x < _x )
		{
			if (_texmap.find(it->type) != _texmap.end())
			{
				_blocks[i]->setTexture(_texmap[it->type]);
				_blocks[i]->setFlip(SDL_FLIP_NONE);
				_blocks[i]->setRotation(0);
				switch (it->dir)
				{
					case 'N' :
						break;
					case 'S' :
						_blocks[i]->setFlip(SDL_FLIP_VERTICAL);
						break;
					case 'E' :
						_blocks[i]->setRotation(-90.0F);
						break;
					case 'W' :
						_blocks[i]->setRotation(90.0F);
						break;
				}
				_blocks[i]->draw(_ren);
			}
			else
			{
				_blocks[i]->setTexture(nullptr);
			}
		}
	}
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
					case SDLK_p:
					case SDLK_SPACE:
					{
						keys.pause = 1;
						break;
					}
					case SDLK_1:
					{
						keys.libswitch = 1;
						break;
					}
					case SDLK_2:
					{
						keys.libswitch = 2;
						break;
					}
					case SDLK_3:
					{
						keys.libswitch = 3;
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

	_blockSize = YRES / ((_x > _y) ? _x : _y) ;
	SDL_SetRenderDrawColor( _ren, 120, 120, 120, 255 );
	_score = UIElement(x *_blockSize + 10, YRES - 50, (XRES - x *_blockSize) / 2, 25);
	_score.setColor(120, 120, 120, 255 );
	_highScore = UIElement(x *_blockSize + 10, YRES - 25, (XRES - x *_blockSize) / 2, 25);
	_highScore.setColor(120, 120, 120, 255 );
	floor.move(5, 5);
	floor.setTexture(_texmap["FLOOR"]);
	floor.resize(_blockSize * _x, _blockSize * _y);
	floor.active = true;
	floor.visible = true;

	for (unsigned int i = 0; i < _y; i++ )
	{
		int ty = i * _blockSize + 5;
		for (unsigned int j = 0; j < _x; j++ )
		{
			UIElement *r = new UIElement(j * _blockSize + 5, ty, _blockSize, _blockSize);
			_blocks.push_back(r);
		}
	}
}
void			NibblerGUI::setWindow(void *win)
{
	_window = reinterpret_cast<SDL_Window*>(win);
}
void			NibblerGUI::setRenderer(void *ren)
{
	_ren = reinterpret_cast<SDL_Renderer*>(ren);
}

int 			NibblerGUI::getX()
{
	return(_x);
}
int 			NibblerGUI::getY()
{
	return(_y);
}

void			NibblerGUI::passWindow(IGUI *lib)
{
	lib->setWindow(reinterpret_cast<void*>(_window));
	lib->setRenderer(reinterpret_cast<void*>(_ren));
	clean = false;
}
