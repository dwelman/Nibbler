#include <nibbler.hpp>
#include <algorithm>
#include "GameManager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


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

void	libSwitch(int libID, IGUI *&curLib)
{
	try
	{
		void	*handle;
		switch (libID)
		{
			case  1:
			{
				handle = getHandle("libBasicRender.dylib");
				IGUI *newLib = loadLibObject(handle);
				curLib->passWindow(newLib);
				newLib->init();
				newLib->setSize(curLib->getX(), curLib->getY());
				delete(curLib);
				curLib = newLib;
				break;
			}
			case  2:
			{
				handle = getHandle("libSpriteRender.dylib");
				IGUI *newLib = loadLibObject(handle);
				curLib->passWindow(newLib);
				newLib->init();
				newLib->setSize(curLib->getX(), curLib->getY());
				delete(curLib);
				curLib = newLib;
				break;
			}
		}
	}
	catch (std::exception &e)
	{
		std::cerr << "Could not switch basicLib : " << e.what() << std::endl;
	}
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
    StartConfig						config;
    GameData						gameData;
    bool							started = false;

    gameData.highScore = GameManager::Instance().highScore;
	handle = getHandle(startingLib.c_str());
	guiLib = loadLibObject(handle);
	guiLib->init();
	guiLib->setSize(x, y);
	while (is_running)
    {
    	if (!started)
		{
			memset(&keys, 0, sizeof(s_keypress));
			keys.libswitch = guiLib->start(config);
			started = keys.libswitch  == 0;
		}
		if (!isPaused && started)
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
        //    gameData.scores.emplace(std::make_pair(GameManager::Instance().GetSnake()->GetPlayerNumber(), GameManager::Instance().GetSnake()->GetScore()));
        //    gameData.speeds.emplace(std::make_pair(GameManager::Instance().GetSnake()->GetPlayerNumber(), GameManager::Instance().GetSnake()->GetSpeed()));
        	gameData.scores[1] = GameManager::Instance().GetSnake()->GetScore();
			gameData.speeds[1] = GameManager::Instance().GetSnake()->GetSpeed();
            hasMoved = false;
            drawObj = GameManager::Instance().GetDrawableObjects();
            guiLib->drawObjects(drawObj, gameData);
        }
        else if (started)
			guiLib->getInput(keys);
		if (keys.libswitch > 0)
			libSwitch(keys.libswitch, guiLib);
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
    else if (mapWidth > 100)
    {
        std::cout << "Map width too large" << std::endl;
        exit (-1);
    }
    if (mapHeight < 5)
    {
        std::cout << "Map height too small" << std::endl;
        exit (-1);
    }
    else if (mapHeight > 100)
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
    int startingSpeed = 100 - sqrt(mapWidth * mapHeight) + (sqrt(mapWidth * mapHeight) / 1.5f);
    Snake snake(1, mapWidth / 2, mapHeight / 2, SnakeSegment::NORTH, startingSpeed, startingSpeed / 5);
    GameManager::Instance().GiveSnake(snake);
    GameManager::Instance().SetMapHeight(mapHeight);
    GameManager::Instance().SetMapWidth(mapWidth);
	try
    {
        int highScore;
        std::ifstream   iFile("highscore");
        if (iFile.is_open())
        {
            std::string temp;
            getline(iFile, temp);
            highScore = std::stoi(temp);
            iFile.close();
        }
        else
        {
            highScore = 0;
        }
        GameManager::Instance().highScore = highScore;
        gameLoop(startingLib, mapWidth, mapHeight);
        if (GameManager::Instance().GetSnake()->GetScore() > highScore)
        {
            highScore = GameManager::Instance().GetSnake()->GetScore();
        }

        std::ofstream   oFile("highscore");
        oFile << highScore;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return (-1);
	}
}