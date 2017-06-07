#include <nibbler.hpp>

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

	handle = getHandle(startingLib.c_str());
	guiLib = loadLibObject(handle);
	guiLib->start();
	guiLib->setSize(x, y);
	DrawableObj temp;
	temp.y = 0;
	temp.x = 0;
	drawObj.push_back(temp);
	while (is_running)
	{
		if (guiLib->getInput(keys) > 0)
		{
			std::cout << keys.p1north << " " << keys.p1south << " "
					  << keys.p1west << " " << keys.p1east << std::endl;
			drawObj[0].x -= keys.p1east;
			drawObj[0].x += keys.p1west;
			drawObj[0].y -= keys.p1north;
			drawObj[0].y += keys.p1south;
		}
		guiLib->drawObjects(drawObj);

		//DO something with keys
		if (keys.quit > 0)
			is_running = false;
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