#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Vector2D.h"
#include "ITile.h"

class Board {

private:
    std::vector<std::vector<ITile*>> m_map;
    Vector2D m_playerPos = Vector2D(1, 1);

    std::string getTopRow();
    std::string getBottomRow();
    std::string getCurrentRow();

    bool move(const char direction);
    ITile* getField(const Vector2D position);

public:
    Board();
    ~Board();

    void render();
};

