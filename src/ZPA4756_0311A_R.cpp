#include "ZPA4756_0311A_R.h"

bool ZPA4756_0311A_R::begin(void)
{
    writeReg(CTRL_REG2, 0x04); // SWリセット
    delay(100);
    writeReg(CTRL_REG0, 0x04); // DEVICE_ENABLE=1
    delay(10);                 // Tpup
    writeReg(RES_CONF, _averages);
    writeReg(STBY_REG, _standby);
    if (_contentious_mode)
    {
        writeReg(OPTN_REG, 0x80 | _oversampling); // CM=1
        writeReg(CTRL_REG0, 0x06);                // DEVICE_ENABLE=1 ENABLE_MEAS=1
    }
    else
    {
        writeReg(OPTN_REG, _oversampling); // CM=0
        if (_standby != STBY_0_MS)
        {
            writeReg(CTRL_REG0, 0x01); // ONE-SHOT=1
        }
    }
    return true;
}

void ZPA4756_0311A_R::setAverages(byte average)
{
    _averages = average;
}

void ZPA4756_0311A_R::setOversamplingRate(byte OSR)
{
    _oversampling = OSR;
}

void ZPA4756_0311A_R::setStandbyTime(byte standby)
{
    _standby = standby;
}

void ZPA4756_0311A_R::setContentiousMode(bool flag)
{
    _contentious_mode = flag;
}

bool ZPA4756_0311A_R::readMeasurements(bool blocking)
{
    if (!_contentious_mode)
    {
        if (_standby == STBY_0_MS)
        {
            writeReg(CTRL_REG0, 0x01); // One-Shotモード開始
            blocking = true;
        }
    }
    if (blocking)
    {
        int cnt = 0;
        do
        {
            delay(2);
            if ((readReg(STATUS_REG) & 0x3) == 0x3)
            {
                break;
            }
        } while (cnt++ < 50);
        if (cnt >= 50)
        {
            return false;
        }
    }
    else
    {
        if ((readReg(STATUS_REG) & 0x3) != 0x3)
        {
            return false;
        }
    }

    // 温度を先に読み出す
    uint16_t temp_raw_data = readReg(TEMP_OUT_L) | readReg(TEMP_OUT_H) << 8;
    _temperature = (float)temp_raw_data * (1.0f / 128.0f) - 273.0f;

    // PRESS_OUT_Hを最後に読む
    uint32_t press_raw_data = readReg(PRESS_OUT_XL) | readReg(PRESS_OUT_L) << 8 | readReg(PRESS_OUT_H) << 16;
    int32_t press_data = press_raw_data;
    if (press_raw_data & 0x800000)
    {
        press_data -= 0x1000000;
    }
    _pressure = (float)press_data / 64.0f;

    return true;
}

byte ZPA4756_0311A_R::readReg(byte reg)
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

void ZPA4756_0311A_R::writeReg(byte reg, byte dat)
{
    _wire.beginTransmission(_devaddr); // デバイスとの通信を開始
    _wire.write(reg);                  // レジスタアドレスを送信
    _wire.write(dat);                  // 書き込みデータを送信
    _wire.endTransmission();           // ストップを送信
}
