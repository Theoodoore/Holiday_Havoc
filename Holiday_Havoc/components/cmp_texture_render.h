#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>

class TextureRenderComponent : public Component {
protected:
    sf::Texture _texture;
    sf::Sprite _sprite;

public:
    // Updated constructor to accept texture rectangle parameter
    explicit TextureRenderComponent(Entity* p, const std::string& texturePath, const sf::IntRect& textureRect);
    TextureRenderComponent() = delete;

    void setTexture(const std::string& texturePath, const sf::IntRect& textureRect);  // Updated signature
    void draw(sf::RenderWindow& window) const;

    void render() override;
    void update(double dt) override;

    // Method to change opacity (the transparency) of the sprites
    void setOpacity(sf::Uint8 opacity);
};
