#pragma once

#include <string>

class GameManager
{
public:
    ~GameManager();

    GameManager &operator=(GameManager const &gm);

    static GameManager &Instance();
private:
    GameManager();
    GameManager(GameManager const &gm);
    static GameManager *instance;
};