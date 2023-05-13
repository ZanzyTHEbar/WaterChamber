#include "load_cell.hpp"

LoadCell::LoadCell(TwoWire& pWire, uint8_t addr)
    : _pWire(pWire),
      _address(addr),
      pFlag(0),
      _offset(0),
      _calibration(2236.0f) {}

LoadCell::~LoadCell() {}

bool LoadCell::begin() {
    Wire.begin();
    log_d("\r\n");
    Wire.beginTransmission(_address);
    _pWire.write(REG_DATA_INIT_SENSOR);
    _pWire.write(REG_CLEAR_REG_STATE);
    if (Wire.endTransmission() == 0) {
        log_d("\r\n");
        _offset = average(10);
        return true;
    }
    log_d("IIC ");
    return false;
}

double LoadCell::readSensor(uint8_t times) {
    //* Read the sensor
    long value = average(times);
    uint8_t ppFlag = peelFlag();
    if (ppFlag == 1) {
        _offset = average(times);
        log_d("[LoadCell]: _offset %d", _offset);
    } else if (ppFlag == 2) {
        _calibration = getCalibrationValue();
        log_d("[LoadCell]: _calibration %d", _calibration);
    }
    log_d("[LoadCell]: value %d", value);
    return (((float)value - _offset) / _calibration);
}

bool LoadCell::getCalFlag() {
    uint8_t ppFlag = peelFlag();
    return (ppFlag == 2);
}

void LoadCell::enableCalibration() {
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

float LoadCell::getCalibrationValue() {
    uint8_t data[4];
    uint32_t value = 0;
    readReg(REG_DATA_GET_CALIBRATION, data, 4);

    value = data[0];
    value = (value << 8) | data[1];
    value = (value << 8) | data[2];
    value = (value << 8) | data[3];
    log_d("[LoadCell]: value %d", value);
    float* cal = (float*)&value;
    return *cal;
}

uint8_t LoadCell::peelFlag() {
    uint8_t data = 0;
    readReg(REG_DATA_GET_PEEL_FLAG, &data, 1);
    return data;
}

long LoadCell::getValue() {
    uint8_t data[4] = {0};
    long value = 0;
    readReg(REG_DATA_GET_RAM_DATA, data, 4);
    if (data[0] != 0x12) {
        log_e("data[0] != 0x12");
        return 0;
    }
    value = (long)data[1];
    value = (long)((value << 8) | data[2]);
    value = (long)((value << 8) | data[3]);
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
    _pWire.beginTransmission(_address);
    _pWire.write(reg);
    _pWire.endTransmission();
    delay(22);

    _pWire.requestFrom(_address, size);

    for (uint8_t i = 0; i < size; i++) {
        data[i] = _pWire.read();
        log_d("data[%d] = %d", i, data[i]);
    }

    return 1;
}

uint8_t LoadCell::writeReg(uint8_t reg, const void* data, size_t size) {
    if (data == NULL) {
        log_e("pBuf ERROR!! : null pointer");
    }
    uint8_t* _pBuf = (uint8_t*)data;
    _pWire.beginTransmission(_address);
    _pWire.write(reg);
    for (uint8_t i = 0; i < size; i++) {
        _pWire.write(_pBuf[i]);
    }
    _pWire.endTransmission();
    return 1;
}