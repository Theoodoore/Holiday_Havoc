// scene_level.h

#pragma once
#include "../components/Shop_Button.h"
#include "../components/shop_system.h"

#include "engine.h"

class LevelScene : public Scene {
private:
	ShopButton* _shopButton;
	bool _shopVisible;

public:
  void Load() override;

  void UnLoad() override;

  void Update(const double& dt) override;

  void Render() override;
};
