#pragma once
#include <data/config/project_config.hpp>

namespace Config {
struct LoadCell_t {
    float calibration;
};

struct WaterConfig_t {
    LoadCell_t loadCell;
};
}  // namespace Config

class WaterConfig : public CustomConfigInterface {
    Config::WaterConfig_t config;
    ProjectConfig& projectConfig;

   public:
    WaterConfig(ProjectConfig& projectConfig);
    void setLoadCellCalibration(float calibration);
    Config::LoadCell_t& getLoadCellCalibration();

    void save() override;
    void load() override;
};
