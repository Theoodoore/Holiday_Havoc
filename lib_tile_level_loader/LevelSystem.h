// levelsystem.h

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include <map>

#define ls LevelSystem


class LevelSystem {
public:
    static void loadLevelFile(const std::string&, float tileSize = 100.0f);
    static void unload();
    static void render(sf::RenderWindow& window);

    typedef unsigned char Tile;

    enum TILES {
        EMPTY = ' ',
        START = 's',
        END = 'e',
        WALL = 'w',
        ENEMY = 'n',
        WAYPOINT = '+'
    };

    static Tile getTile(sf::Vector2<size_t>);

    static Tile getTileAt(sf::Vector2f);

    static bool isOnGrid(sf::Vector2f);

    static size_t getWidth();

    static size_t getHeight();

    static bool isWall(const sf::Vector2<size_t>& position);

    static sf::Vector2f getTilePosition(sf::Vector2<size_t>);

    static sf::Vector2<size_t> getTileIndexAt(const sf::Vector2f& position);

    static std::vector<sf::Vector2<size_t>> findTiles(Tile);

    static sf::Color getColor(Tile t);

    static void setColor(Tile t, sf::Color c);

    static void setOffset(const sf::Vector2f& _offset);

    static const sf::Vector2f& getOffset();

    static float getTileSize();

    static sf::Texture _spriteSheet;
    static std::map<Tile, sf::IntRect> _spriteRects;


protected:
    static std::unique_ptr<Tile[]> _tiles;
    static size_t _width;
    static size_t _height;
    static sf::Vector2f _offset;

    static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;
    static std::vector<std::unique_ptr<sf::Sprite>> _spriteTiles;

    static void buildSprites(bool optimise = true);

    static float _tileSize; // for rendering
    static std::map<Tile, sf::Color> _colours;

private:
    LevelSystem() = delete;

    ~LevelSystem() = delete;
};
