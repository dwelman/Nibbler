#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    int     mapWidth;
    int     mapHeight;
    if (argc < 3 || argc > 4)
    {
        std::cout << "Usage: nibbler [map_width] [map_height] [optional: starting graphics library]" << std::endl;
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
        exit (-1);
    }
}