#include <nibbler.hpp>
#include <algorithm>
#include "GameManager.hpp"


void	*getHandle(const char *lib)
{
	void 	*handle;

	handle = dlopen (lib, RTLD_LAZY);
	if (!handle)
		throw (LibLoadFailed(dlerror()));
	return (handle);
}

IGUI	*loadLibObject(void *handle)
{
	void	*make;
	char 	*error;
	IGUI* 	guiObject = nullptr;

	make = dlsym(handle, "make");
	auto my_gui = reinterpret_cast<IGUI *(*)(void)>(make);
	if ((error = dlerror()) != NULL)
	{
		throw (LibLoadFailed(error));
	}
	if (my_gui != nullptr)
		guiObject = my_gui();
	return (guiObject);
}

void	gameLoop(const std::string &startingLib, int x, int y)
{
	bool 							is_running = true;
	s_keypress						keys;
	IGUI							*guiLib;
	void							*handle;
	std::vector<DrawableObj>		drawObj;
    bool                            hasMoved = false;
    bool                            isPaused = false;

	handle = getHandle(startingLib.c_str());
	guiLib = loadLibObject(handle);
	guiLib->start();
	guiLib->setSize(x, y);
	while (is_running)
    {
        if (!isPaused)
        {
            if (guiLib->getInput(keys) > 0)
            {
                if (!hasMoved)
                {
                    if (keys.p1east > 0)
                    {
                        hasMoved = GameManager::Instance().GetSnake()->ChangeSnakeHeadDirection(SnakeSegment::EAST);
                    }
                    else if (keys.p1north)
                    {
                        hasMoved = GameManager::Instance().GetSnake()->ChangeSnakeHeadDirection(SnakeSegment::NORTH);
                    }
                    else if (keys.p1south)
                    {
                        hasMoved = GameManager::Instance().GetSnake()->ChangeSnakeHeadDirection(SnakeSegment::SOUTH);
                    }
                    else if (keys.p1west)
                    {
                        hasMoved = GameManager::Instance().GetSnake()->ChangeSnakeHeadDirection(SnakeSegment::WEST);
                    }
                }
            }
            GameManager::Instance().Update();
            hasMoved = false;
            drawObj = GameManager::Instance().GetDrawableObjects();
            guiLib->drawObjects(drawObj);
        }
        if (keys.quit > 0)
			is_running = false;
        if (keys.pause > 0)
            isPaused = !isPaused;
	}
}

int main(int argc, char **argv)
{
    int         			mapWidth;
    int        				mapHeight;
    std::string 			startingLib;

    if (argc < 3 || argc > 4)
    {
        std::cout << "Usage: nibbler [map_width] [map_height] [optional: starting graphics library]" << std::endl;
        exit (-1);
    }
    try
    {
        mapWidth = std::stoi(argv[1]);
        mapHeight = std::stoi(argv[2]);
    }
    catch (std::exception &e)
    {
        std::cout << "Error with map dimensions: ";
        std::cout << e.what() << std::endl;
        exit (-1);
    }
    if (mapWidth < 5)
    {
        std::cout << "Map width too small" << std::endl;
        exit (-1);
    }
    else if (mapWidth > 50)
    {
        std::cout << "Map width too large" << std::endl;
        exit (-1);
    }
    if (mapHeight < 5)
    {
        std::cout << "Map height too small" << std::endl;
        exit (-1);
    }
    else if (mapHeight > 50)
    {
        std::cout << "Map height too large" << std::endl;
        exit(-1);
    }
    if (argc == 4)
    {
        startingLib = argv[3];
    }
    else
    {
        srand(time(NULL));
    }
    srand(time(NULL));
    Snake snake(mapWidth / 2, mapHeight / 2, SnakeSegment::NORTH, (std::max(mapWidth, mapHeight) * 2) - (std::max(mapWidth, mapHeight) / 2));
    GameManager::Instance().GiveSnake(snake);
    GameManager::Instance().SetMapHeight(mapHeight);
    GameManager::Instance().SetMapWidth(mapWidth);
	try
	{
		gameLoop(startingLib, mapWidth, mapHeight);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return (-1);
	}
}