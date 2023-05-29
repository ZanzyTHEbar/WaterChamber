#include "config.hpp"

WaterConfig::WaterConfig(ProjectConfig& projectConfig)
    : projectConfig(projectConfig) {}

void WaterConfig::setLoadCellCalibration(float calibration) {
    this->config.loadCell.calibration = calibration;
}

Config::LoadCell_t& WaterConfig::getLoadCellCalibration() {
    return this->config.loadCell;
}

void WaterConfig::save() {
    projectConfig.putFloat("calibration", config.loadCell.calibration);
}

void WaterConfig::load() {
    config.loadCell.calibration = projectConfig.getFloat("calibration", 0.000f);
}
