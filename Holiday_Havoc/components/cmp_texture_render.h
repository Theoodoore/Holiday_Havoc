#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>

class TextureRenderComponent : public Component {
protected:
    sf::Texture _texture;
    sf::Sprite _sprite;

public:
    explicit TextureRenderComponent(Entity* p, const std::string& texturePath);
    TextureRenderComponent() = delete;

    void setTexture(const std::string& texturePath);
    void draw(sf::RenderWindow& window) const;

    void render() override;
    void update(double dt) override;
};
