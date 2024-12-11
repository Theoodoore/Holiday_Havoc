// scene_level.h

#pragma once

#include "engine.h"
#include "../components/cmp_popup.h"

class LevelScene : public Scene {

public:
  

  void Load() override;

  void UnLoad() override;

  void Update(const double& dt) override;

  void Render() override;
};
