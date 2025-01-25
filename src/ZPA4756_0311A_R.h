#ifndef __ZPA4756_0311A_R_H__
#define __ZPA4756_0311A_R_H__

#include <Wire.h>
#include <SPI.h>
#include "ZPA4756_0311A_R_Reg.h"

#define DEFAULT_ZPA4756_0311A_R_ADDR 0x5c // SA0 L 0x5c H 0x5d

class ZPA4756_0311A_R
{
public:
    class HWInterface
    {
    public:
        virtual void writeReg(byte reg, byte dat) = 0;
        virtual byte readReg(byte reg) = 0;
        virtual ~HWInterface() {}
    };

    class WireInterface : public HWInterface
    {
    public:
        WireInterface(TwoWire &wire, byte devaddr) : _wire(wire), _devaddr(devaddr) {}
        void writeReg(byte reg, byte dat)
        {
            _wire.beginTransmission(_devaddr); // デバイスとの通信を開始
            _wire.write(reg);                  // レジスタアドレスを送信
            _wire.write(dat);                  // 書き込みデータを送信
            _wire.endTransmission();           // ストップを送信
        }
        byte readReg(byte reg)
        {
            _wire.beginTransmission(_devaddr);
            _wire.write(reg);
            _wire.endTransmission(false);
            _wire.requestFrom(_devaddr, 1); // 1バイトを要求
            if (_wire.available())
            {
                return _wire.read(); // 受信したデータを返す
            }
            return 0; // データがない場合は0を返す
        }

    private:
        byte _devaddr;
        TwoWire &_wire;
    };

    class SPIInterface : public HWInterface
    {
    public:
        SPIInterface(SPIClass &spi, int cs, SPISettings settings) : _spi(spi), _cs(cs), _settings(settings) {}
        void writeReg(byte reg, byte dat)
        {
            _spi.beginTransaction(_settings);
            if (_cs >= 0)
            {
                digitalWrite(_cs, LOW);
            }
            _spi.transfer(reg);
            _spi.transfer(dat);
            if (_cs >= 0)
            {
                digitalWrite(_cs, HIGH);
            }
            _spi.endTransaction();
        }
        byte readReg(byte reg)
        {
            _spi.beginTransaction(_settings);
            if (_cs >= 0)
            {
                digitalWrite(_cs, LOW);
            }
            _spi.transfer(reg | 0x80);
            byte dat = _spi.transfer(0);
            if (_cs >= 0)
            {
                digitalWrite(_cs, HIGH);
            }
            _spi.endTransaction();
            return dat;
        }

    private:
        SPISettings _settings;
        SPIClass &_spi;
        int _cs;
    };

    ZPA4756_0311A_R(TwoWire &wire = Wire, byte devaddr = DEFAULT_ZPA4756_0311A_R_ADDR)
        : _hwif(new WireInterface(wire, devaddr)), _averages(AVGP_1 | AVGT_1), _oversampling(OSR_512), _contentious_mode(false), _standby(STBY_0_MS) {}
    ZPA4756_0311A_R(SPIClass &spi, int cs, SPISettings settings = SPISettings(1000000, MSBFIRST, SPI_MODE3))
        : _hwif(new SPIInterface(spi, cs, settings)), _averages(AVGP_1 | AVGT_1), _oversampling(OSR_512), _contentious_mode(false), _standby(STBY_0_MS) {}
    ~ZPA4756_0311A_R() { delete _hwif; }
    bool begin(void);
    void setAverages(byte averages);
    void setOversamplingRate(byte OSR);
    void setStandbyTime(byte standby);
    void setContentiousMode(bool flag);
    bool readMeasurements(bool blocking = true);
    float getPressure(void) { return _pressure; }
    float getTemperature(void) { return _temperature; }

private:
    HWInterface *_hwif;
    byte _averages;
    byte _oversampling;
    bool _contentious_mode;
    byte _standby;
    float _pressure;
    float _temperature;
};

#endif
