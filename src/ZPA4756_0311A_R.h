#ifndef __ZPA4756_0311A_R_H__
#define __ZPA4756_0311A_R_H__

#include <Wire.h>
#include "ZPA4756_0311A_R_Reg.h"

#define DEFAULT_ZPA4756_0311A_R_ADDR 0x5c // SA0 L 0x5c H 0x5d

class ZPA4756_0311A_R
{
public:
    ZPA4756_0311A_R(byte devaddr = DEFAULT_ZPA4756_0311A_R_ADDR, TwoWire &wire = Wire)
        : _devaddr(devaddr), _wire(wire), _averages(AVGP_1|AVGT_1), _oversampling(OSR_512), _contentious_mode(false), _standby(STBY_0_MS) {}
    ~ZPA4756_0311A_R() {}
    bool begin(void);
    void setAverages(byte averages);
    void setOversamplingRate(byte OSR);
    void setStandbyTime(byte standby);
    void setContentiousMode(bool flag);
    bool readMeasurements(bool blocking = true);
    float getPressure(void) { return _pressure; }
    float getTemperature(void) { return _temperature; }
    byte readReg(byte reg);
    void writeReg(byte reg, byte dat);

private:
    byte _devaddr;
    TwoWire &_wire;
    byte _averages;
    byte _oversampling;
    bool _contentious_mode;
    byte _standby;
    float _pressure;
    float _temperature;
};

#endif
