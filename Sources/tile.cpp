#ifndef TILE_H
#define TILE_H

#include "../Headers/tile.h"

Tile::Tile(QWidget *parent, int x, int y) : QLabel(parent)
{
    this->x = x;
    this->y = y;
    mouseOn = false;
}
#endif
