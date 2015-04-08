#include "maze.h"



///////////////////////////////////////////////////////////////////
////                        Maze
///////////////////////////////////////////////////////////////////



// (private) drawing the outer walls of the maze
void Maze::drawOuterWalls(sf::RenderWindow *renderWindow) {
    for (int x = 0; x < 4; x++) {
        renderWindow->draw((OuterWalls[x] ) );
    }
}


// initiating a maze with @param xSize times @param ySize Tiles
Maze::Maze(int xSize, int ySize) {
    sizeX = xSize;
    sizeY = ySize;
    MAP = std::vector<std::vector<Tile> >( (unsigned int) xSize,
            std::vector<Tile>( (unsigned int) ySize) );
    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            Tile tile;
            tile.setSize(i * (tileWidth), j * (tileHeight), tileWidth, tileHeight);
            tile.setIndex(i * xSize + j);
            MAP[i][j] = tile;
        }
    }
    setNeighbourTiles();
    setOuterWalls();
}


// setting or actualizing the outerWalls of the Maze
void Maze::setOuterWalls() {

    sf::RectangleShape temp;
    temp.setFillColor(sf::Color::Magenta);

    temp.setPosition(x - 3, y - 3);

    temp.setSize(sf::Vector2f(sizeX * tileWidth + 6, 3));

    OuterWalls[0] = temp;

    temp.setSize(sf::Vector2f(3, sizeY * tileHeight + 6));

    OuterWalls[3] = temp;

    temp.setPosition(sf::Vector2f(x + 3 + sizeX * tileWidth,
            y + 3 + sizeY * tileWidth));

    temp.setSize(sf::Vector2f(-(sizeX * tileWidth + 6), -3));

    OuterWalls[2] = temp;

    temp.setSize(sf::Vector2f(-3, -(sizeY * tileHeight + 6)));

    OuterWalls[1] = temp;
}


// setting the neighbourTile of each tile in the maze
void Maze::setNeighbourTiles() {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            if (j > 0)
                MAP[i][j].setSurrounding(0, &MAP[i][j - 1]);
            if (i < sizeX - 1)
                MAP[i][j].setSurrounding(1, &MAP[i + 1][j]);
            if (j < sizeY - 1)
                MAP[i][j].setSurrounding(2, &MAP[i][j + 1]);
            if (i > 0)
                MAP[i][j].setSurrounding(3, &MAP[i - 1][j]);
        }
    }
}


// drawing the whole maze (first tiles, then walls, then OuterWalls)
void Maze::drawMaze(sf::RenderWindow *window) {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            MAP[i][j].drawTile(window);
        }
    }
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            MAP[i][j].drawWalls(window);
        }
    }

    for (int k = 0; k < bases.size(); k++)
        bases[k].draw(window);

    drawOuterWalls(window);
}


//moving the whole maze for @param x and @param y pixels
void Maze::move(int x, int y) {
    Maze::x += x;
    Maze::y += y;
    setOuterWalls();
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            MAP[i][j].move(x, y);
        }
    }
}


// doing the tick for every tile
void Maze::doTick() {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            MAP[i][j].doTick();
        }
    }
}


// setting the tile at @param x and y to a Home-tile
void Maze::setHome(int x, int y) {
    setHome(getTile(x, y) );
}


// setting the @param tile to an Home
void Maze::setHome(Tile *tile) {
    if (tile != NULL) {
        std::cout << "changing Home status of: " + std::to_string(tile->getIndex()) << std::endl;
        if (tile->getSpecial() == 1) {
            removeHome(tile);
            tile->setSpecial(0);
        } else {
            antBase home1;
            home1.setPosition(tile);
            bases.push_back(home1);
            for (int i = 0; i < bases.size(); i++)
                bases[i].reloadBase();

            tile->setSpecial(1);
            tile->setBase(&bases[bases.size() - 1]);
        }
    }
}


// setting the specific @param base to the @param tile
void Maze::setHome(antBase base, Tile *tile) {
    bases.push_back(base);
    for (int i = 0; i < bases.size(); i++)
        bases[i].reloadBase();

    tile->setSpecial(1);
    tile->setBase(&bases[bases.size() - 1]);
}


// removing the @param tile from the antBases
void Maze::removeHome(Tile *tile) {
    for (int i = 0; i < bases.size(); i++){
        if (tile == bases[i].getTile() )
            bases.erase(bases.begin() + i);
    }
}


// returns the tile that got clicked on (if there is one)
Tile* Maze::getTileClicked(int x, int y) {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            if (MAP[i][j].isInside(x, y) )
                return &MAP[i][j];
        }
    }
    return NULL;
}


// returns the tile at the @param index
Tile* Maze::getTile(int index) {
    return &MAP[index / sizeX][index % sizeY];
}


// returning the tile at the @param x and @param y coordinates
Tile* Maze::getTile(int x, int y) {
    return &MAP[x][y];
}


// returning the sizeX of the maze
int Maze::getSizeX() {
    return sizeX;
}


// returning the the sizeY of the the maze
int Maze::getSizeY() {
    return sizeY;
}


// returns the xPos of the maze
int Maze::getX() {
    return x;
}


// returns the yPos of the maze
int Maze::getY() {
    return y;
}


// returning the max index of the maze
int Maze::INDEX_MAX() {
    return sizeX * sizeY;
}



