// scene_level.h

#pragma once
#include "../components/shop_button.h"
#include "../components/shop_system.h"
#include "../components/cmp_texture_render.h"
#include "engine.h"

class LevelScene : public Scene {
private:
    std::shared_ptr<Entity> shopButtonEntity;
    ShopButton* _shopButton;
    bool _shopVisible;
    bool _mouseHeld;

    sf::Sprite _shopTowerSprite; // Sprite for the tower shown in the shop
    sf::Texture _shopTowerTexture; // Texture for the shop tower
    bool _showShopTowerSprite = false; // Toggle to show/hide tower sprite

public:
    void Load() override;
    void UnLoad() override;
    void Update(const double& dt) override;
    void Render() override;
};
