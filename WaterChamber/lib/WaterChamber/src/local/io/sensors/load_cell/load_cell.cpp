#include "load_cell.hpp"

LoadCell::LoadCell(WaterConfig& waterConfig, TwoWire* pWire, uint8_t addr)
    : _address(addr),
      _pFlag(0),
      _offset(0),
      _pWire(pWire),
      _calibration(2236.0f),
      _readings{0},
      _total(0),
      _average(0),
      _index(0),
      waterConfig(waterConfig) {
    _readings.reserve(100);
}

LoadCell::~LoadCell() {
    _readings.clear();
    delete _pWire;
}

bool LoadCell::begin(void) {
    Wire.begin();
    log_v("\r\n");
    Wire.beginTransmission(_address);
    _pWire->write(REG_DATA_INIT_SENSOR);
    _pWire->write(REG_CLEAR_REG_STATE);
    if (Wire.endTransmission() == 0) {
        log_v("\r\n");
        _offset = average(10);

        auto calibration = waterConfig.getLoadCellCalibration();
        log_d("[Load Cell]: Calibration value: %0.3f", calibration.calibration);

        if (calibration.calibration <= 0.0) {
            // Manually set the calibration values
            // loadCell.setCalibration(2236.f);
            //// remove the peel
            // loadCell.peel();
            //  Set the calibration weight when the weight sensor module is
            //  automatically calibrated (g)
            this->setCalWeight(328);
            // Set the trigger threshold (G) for automatic calibration of the
            // weight sensor module. When only the weight of the object on the
            // scale is greater than this value, the module will start the
            // calibration process This value cannot be greater than the
            // calibration weight of the setCalWeight() setting
            this->setThreshold(50);

            delay(2000);
            // Start sensor calibration
            this->enableCal();
            long time1 = millis();
            // Wait for sensor calibration to complete
            while (!this->getCalFlag()) {
                delay(1000);
                if ((millis() - time1) > 7000) {
                    log_i(
                        "[Load Cell ]: Calibration failed, no weight was "
                        "detected "
                        "on the scale");
                    log_i(
                        "[Load Cell]: Please check whether the weight sensor "
                        "module is placed "
                        "correctly on the scale");
                    log_i(
                        "[Load Cell]: Restarting calibration after 2 seconds, "
                        "please wait.");
                    delay(2000);
                }
            }
            // Obtain the calibration value. The accurate calibration value can
            // be obtained after the calibration operation is completed
            log_i(
                "[Load Cell]: The calibration value of the LoadCell is: %0.3f",
                this->getCalibration());
            this->setCalibration(this->getCalibration());
            log_i("[Load Cell]: Weight %0.3f", this->readWeight());
            waterConfig.setLoadCellCalibration(this->getCalibration());
            waterConfig.save();
            delay(1000);
            return true;
        }
        log_d("[Load Cell]: Settings Calibration value");
        this->setCalibration(calibration.calibration);
        log_d("[Load Cell]: We have set the calibration value");
        this->peel();
        log_d("[Load Cell]: We have peeled the load cell");
        return true;
    }
    log_v("[Load Cell]: IIC Failed ");
    return false;
}

float LoadCell::readWeight(uint8_t times) {
    long value = average(times);
    uint8_t p_pFlag = peelFlag();
    if (p_pFlag == 1) {
        // _pFlag = 1;
        _offset = average(times);
        // log_i("_offset");
    } else if (p_pFlag == 2) {
        _calibration = getCalibration();
        // log_i("_calibration");
    }
    // log_i(value);
    return (((float)value - _offset) / _calibration);
}

bool LoadCell::getCalFlag() {
    uint8_t p_pFlag = peelFlag();
    return (p_pFlag == 2);
}
void LoadCell::enableCal() {
    uint8_t data = 0;
    writeReg(REG_CLICK_CAL, &data, 1);
}
void LoadCell::peel() {
    _offset = average();
    uint8_t data = 0;
    writeReg(REG_CLICK_RST, &data, 1);
}
long LoadCell::average(uint8_t times) {
    long sum = 0;
    for (uint8_t i = 0; i < times; i++) {
        sum += getValue();
    }

    return sum / times;
}
float LoadCell::getCalibration() {
    uint8_t data[4];
    uint32_t value = 0;
    readReg(REG_DATA_GET_CALIBRATION, data, 4);

    value = data[0];
    value = (value << 8) | data[1];
    value = (value << 8) | data[2];
    value = (value << 8) | data[3];
    log_v("[Load Cell]: %d", value, HEX);
    // if(value == 0) value ==2234.f;
    float* cal = (float*)&value;

    //_calibration = *cal;
    return *cal;
}
void LoadCell::setCalibration(float value) {
    _calibration = value;
}
uint8_t LoadCell::peelFlag() {
    uint8_t data[1];
    readReg(REG_DATA_GET_PEEL_FLAG, data, 1);
    // log_i(data[0]);
    if (data[0] == 1) {
        log_v("---------------------------------");
        return 1;
    } else if (data[0] == 2) {
        return 2;
    } else {
        return 0;
    }
}
long LoadCell::getValue() {
    uint8_t data[4];
    long value = 0;
    readReg(REG_DATA_GET_RAM_DATA, data, 4);
    if (data[0] == 0x12) {
        value = (long)data[1];
        value = (long)((value << 8) | data[2]);
        value = (long)((value << 8) | data[3]);
    } else {
        log_e("[Load Cell]: DATA ERROR");
    }
    // log_i(sizeof(int),HEX);
    // log_i(value^0x800000);
    return (value ^ 0x800000);
}
void LoadCell::setThreshold(uint16_t threshold) {
    uint8_t txData[2];
    txData[0] = threshold >> 8;
    txData[1] = threshold & 0xFF;
    writeReg(REG_SET_CAL_THRESHOLD, txData, 2);
    delay(50);
}
void LoadCell::setCalWeight(uint16_t triWeight) {
    uint8_t txData[2];
    txData[0] = triWeight >> 8;
    txData[1] = triWeight & 0xFF;
    writeReg(REG_SET_TRIGGER_WEIGHT, txData, 2);
    delay(50);
}
int LoadCell::readReg(uint8_t reg, uint8_t* data, size_t size) {
    _pWire->beginTransmission(_address);
    _pWire->write(reg);
    _pWire->endTransmission();
    delay(22);

    _pWire->requestFrom(_address, size);

    for (uint8_t i = 0; i < size; i++) {
        data[i] = _pWire->read();
        log_v("[Load Cell]: %d", data[i], HEX);
    }

    return 1;
}
uint8_t LoadCell::writeReg(uint8_t reg, const void* data, size_t size) {
    if (data == NULL) {
        log_v("[Load Cell]: pBuf ERROR!! : null pointer");
    }
    uint8_t* _pBuf = (uint8_t*)data;
    _pWire->beginTransmission(_address);
    _pWire->write(reg);
    for (uint8_t i = 0; i < size; i++) {
        _pWire->write(_pBuf[i]);
    }
    _pWire->endTransmission();

    return 1;
}