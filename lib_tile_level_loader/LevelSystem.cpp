// LevelSystem.cpp

#include "LevelSystem.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

std::map<LevelSystem::Tile, sf::Color> LevelSystem::_colours{
    {WALL, sf::Color(139, 0, 0)},  // Dark red color
    {END, sf::Color::Black}          // Red color for END
};

sf::Color LevelSystem::getColor(LevelSystem::Tile t) {
    auto it = _colours.find(t);
    if (it == _colours.end()) {
        _colours[t] = sf::Color(255, 102, 102);

    }
    return _colours[t];
}

void LevelSystem::setColor(LevelSystem::Tile t, sf::Color c) {
    _colours[t] = c;
}

std::unique_ptr<LevelSystem::Tile[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;


sf::Texture LevelSystem::_spriteSheet;
std::map<LevelSystem::Tile, sf::IntRect> LevelSystem::_spriteRects;

float LevelSystem::_tileSize(500.f);
Vector2f LevelSystem::_offset(0.0f, 0.0f);
// Vector2f LevelSystem::_offset(0,0);
vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;
vector<std::unique_ptr<sf::Sprite>> LevelSystem::_spriteTiles;

void LevelSystem::loadLevelFile(const std::string& path, float tileSize) {
    _tileSize = tileSize;
    size_t w = 0, h = 0;
    string buffer;

    if (!_spriteSheet.loadFromFile("res/img/spritesheet.png")) {
        throw std::runtime_error("Failed to load sprite sheet!");
    }

    // Define the texture rectangle for the wall sprite
    _spriteRects[WALL] = sf::IntRect(0, 0, 16, 16);
    _spriteRects[EMPTY] = sf::IntRect(128, 0, 16, 16);
    _spriteRects[END] = sf::IntRect(144, 0, 16, 16);

    // Load in file to buffer
    ifstream f(path);
    if (f.good()) {
        f.seekg(0, std::ios::end);
        buffer.resize(f.tellg());
        f.seekg(0);
        f.read(&buffer[0], buffer.size());
        f.close();
    }
    else {
        throw string("Couldn't open level file: ") + path;
    }

    std::vector<Tile> temp_tiles;
    int widthCheck = 0;
    for (int i = 0; i < buffer.size(); ++i) {
        const char c = buffer[i];
        if (c == '\0') { break; }
        if (c == '\n') { // newline
            if (w == 0) {  // if we haven't written width yet
                w = i;       // set width
            }
            else if (w != (widthCheck - 1)) {
                throw string("non uniform width:" + to_string(h) + " ") + path;
            }
            widthCheck = 0;
            h++; // increment height
        }
        else {
            temp_tiles.push_back((Tile)c);
        }
        ++widthCheck;
    }

    if (temp_tiles.size() != (w * h)) {
        throw string("Can't parse level file") + path;
    }
    _tiles = std::make_unique<Tile[]>(w * h);
    _width = w; // set static class vars
    _height = h;
    std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
    cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;
    buildSprites();
}

void LevelSystem::buildSprites(bool optimise) {
    _sprites.clear();
    _spriteTiles.clear();

    struct tp {
        sf::Vector2f p;
        sf::Vector2f s;
        sf::Color c;
    };
    vector<tp> tps;
    const auto tls = Vector2f(_tileSize, _tileSize);
    for (size_t y = 0; y < _height; ++y) {
        for (size_t x = 0; x < _width; ++x) {
            Tile t = getTile({ x, y });
            auto pos = getTilePosition({ x, y });

            if (t == WALL) {
                // Create a sprite for wall tiles
                auto wallSprite = std::make_unique<sf::Sprite>();
                wallSprite->setTexture(_spriteSheet);                     // Use the loaded texture
                wallSprite->setTextureRect(_spriteRects[WALL]);          // Sub-rectangle for the wall
                wallSprite->setScale(_tileSize / 16.f, _tileSize / 16.f); // Scale to fit tile size
                wallSprite->setPosition(pos);                             // Set position
                _spriteTiles.push_back(move(wallSprite));
            }
            if (t == END) {
                // Create a sprite for wall tiles
                auto wallSprite = std::make_unique<sf::Sprite>();
                wallSprite->setTexture(_spriteSheet);                     // Use the loaded texture
                wallSprite->setTextureRect(_spriteRects[END]);          // Sub-rectangle for the wall
                wallSprite->setScale(_tileSize / 16.f, _tileSize / 16.f); // Scale to fit tile size
                wallSprite->setPosition(pos);                             // Set position
                _spriteTiles.push_back(move(wallSprite));
            }
            if (t == EMPTY || t == START || t == WAYPOINT || t == ENEMY) {
                // Create a sprite for wall tiles
                auto wallSprite = std::make_unique<sf::Sprite>();
                wallSprite->setTexture(_spriteSheet);                     // Use the loaded texture
                wallSprite->setTextureRect(_spriteRects[EMPTY]);          // Sub-rectangle for the wall
                wallSprite->setScale(_tileSize / 16.f, _tileSize / 16.f); // Scale to fit tile size
                wallSprite->setPosition(pos);                             // Set position
                _spriteTiles.push_back(move(wallSprite));

            }
        }
    }
    // optimization block left unchanged for brevity
}

void LevelSystem::render(RenderWindow& window) {
    for (auto& t : _sprites) {
        window.draw(*t);
    }
    for (auto& t : _spriteTiles) {
        window.draw(*t);
    }
}

bool LevelSystem::isWall(const sf::Vector2<size_t>& position) {
    // Ensure the position is within the bounds of the grid
    if (position.x >= _width || position.y >= _height) {
        return false; // Out of bounds is not a wall
    }

    // Check if the tile at the position is a wall
    return getTile(position) == WALL;
}

LevelSystem::Tile LevelSystem::getTile(sf::Vector2<size_t> p) {
    if (p.x > _width || p.y > _height) {
        throw string("Tile out of range: ") + to_string(p.x) + "," +
            to_string(p.y) + ")";
    }
    return _tiles[(p.y * _width) + p.x];
}

size_t LevelSystem::getWidth() { return _width; }

size_t LevelSystem::getHeight() { return _height; }

sf::Vector2f LevelSystem::getTilePosition(sf::Vector2<size_t> p) {
    return (Vector2f(p.x, p.y) * _tileSize) + _offset;
}

std::vector<sf::Vector2<size_t>> LevelSystem::findTiles(LevelSystem::Tile type) {
    auto v = vector<sf::Vector2<size_t>>();
    for (size_t i = 0; i < _width * _height; ++i) {
        if (_tiles[i] == type) {
            v.push_back({ i % _width, i / _width });
        }
    }

    return v;
}

sf::Vector2<size_t> LevelSystem::getTileIndexAt(const sf::Vector2f& position) {
    // Adjust position to account for offset
    auto adjustedPos = position - _offset;

    // Check if the position is out of bounds
    if (adjustedPos.x < 0 || adjustedPos.y < 0 ||
        adjustedPos.x >= _width * _tileSize || adjustedPos.y >= _height * _tileSize) {
        // Log out-of-bounds error
        std::cerr << "Position out of bounds: " << adjustedPos.x << ", " << adjustedPos.y << std::endl;
        return { static_cast<size_t>(-1), static_cast<size_t>(-1) }; // Invalid tile index
    }

    size_t x = static_cast<size_t>(adjustedPos.x / _tileSize);
    size_t y = static_cast<size_t>(adjustedPos.y / _tileSize);

    return { x, y };
}


LevelSystem::Tile LevelSystem::getTileAt(Vector2f v) {
    auto a = v - _offset;
    if (a.x < 0 || a.y < 0) {
        throw string("Tile out of range ");
    }
    return getTile(sf::Vector2<size_t>((v - _offset) / (_tileSize)));
}

bool LevelSystem::isOnGrid(sf::Vector2f v) {
    auto a = v - _offset;
    if (a.x < 0 || a.y < 0) {
        return false;
    }
    auto p = sf::Vector2<size_t>((v - _offset) / (_tileSize));
    if (p.x > _width || p.y > _height) {
        return false;
    }
    return true;
}

void LevelSystem::setOffset(const Vector2f& _offset) {
    LevelSystem::_offset = _offset;
    buildSprites();
}

void LevelSystem::unload() {
    cout << "LevelSystem unloading\n";
    _sprites.clear();
    _tiles.reset();
    _width = 0;
    _height = 0;
    _offset = { 0, 0 };
}

const Vector2f& LevelSystem::getOffset() { return _offset; }

float LevelSystem::getTileSize() { return _tileSize; }
