#ifndef __ZPA4756_0311A_R_REG_H__
#define __ZPA4756_0311A_R_REG_H__

// WHO_AM_I レジスタ（デバイス識別用）
#define WHO_AM_I_3        0x04  // R: Device (module) identifier for tracking OTP value
#define WHO_AM_I_2        0x05  // R: Device (module) identifier for tracking OTP value
#define WHO_AM_I_1        0x06  // R: Device (module) identifier for tracking OTP value
#define WHO_AM_I_0        0x07  // R: Device (module) identifier for tracking OTP value

// Reference Pressure レジスタ（圧力基準値）
#define REF_P_XL          0x08  // R/W: Reference pressure XL subtracted from sensor output
#define REF_P_L           0x09  // R/W: Reference pressure L subtracted from sensor output
#define REF_P_H           0x0A  // R/W: Reference pressure H subtracted from sensor output

// その他の制御レジスタ
#define ARB_CTRL          0x0B  // R/W: Arbitration setting
#define I2C_DEVICE_ID     0x0F  // R: I2C device ID number (Read only)
#define RES_CONF          0x10  // R/W: Configures resolution of pressure/temperature measurements
#define BUFF_CTRL         0x11  // R/W: Read buffer control
#define STBY_REG          0x12  // R/W: Standby time control
#define OPTN_REG          0x13  // R/W: Pressure conversion time & continuous mode enable

// インターフェイスおよび制御レジスタ
#define ITF_CTRL          0x1F  // R/W: Interface control register
#define CTRL_REG0         0x20  // R/W: Measurement mode setting
#define CTRL_REG1         0x21  // R/W: Interrupt mask setting
#define CTRL_REG2         0x22  // R/W: Interrupt pin driver & software reset
#define CTRL_REG3         0x23  // R/W: Controls SPI serial interface mode

// 割り込みおよび閾値レジスタ
#define INT_SOURCEREG     0x24  // R/C: Interrupt status (Read-only, clears on read)
#define THS_P_LOW_REG     0x25  // R/W: Low pressure threshold for interrupt
#define THS_P_HIGH_REG    0x26  // R/W: High pressure threshold for interrupt

// ステータスおよびセンサーデータレジスタ
#define STATUS_REG        0x27  // R: Data availability and read buffer status
#define PRESS_OUT_XL      0x28  // R: Pressure output XL (Least Significant Byte)
#define PRESS_OUT_L       0x29  // R: Pressure output L
#define PRESS_OUT_H       0x2A  // R: Pressure output H (Most Significant Byte)
#define TEMP_OUT_L        0x2B  // R: Temperature output L
#define TEMP_OUT_H        0x2C  // R: Temperature output H

// デフォルト値または詳細コメントが提供された場合
#define DEFAULT_REF_P_XL  0x00  // 初期値: 0x00
#define DEFAULT_REF_P_L   0x00  // 初期値: 0x00
#define DEFAULT_REF_P_H   0x00  // 初期値: 0x00
#define DEFAULT_ARB_CTRL  0x00  // 初期値: 0x00
#define DEFAULT_RES_CONF  0x00  // 初期値: 0x00
#define DEFAULT_BUFF_CTRL 0x00  // 初期値: 0x00
#define DEFAULT_STBY      0x00  // 初期値: 0x00
#define DEFAULT_OPTN_REG  0x87  // 初期値: 0x87
#define DEFAULT_ITF_CTRL  0x03  // 初期値: 0x03
#define DEFAULT_CTRL_REG0 0x00  // 初期値: 0x00
#define DEFAULT_CTRL_REG1 0xFF  // 初期値: 0xFF
#define DEFAULT_CTRL_REG2 0x00  // 初期値: 0x00
#define DEFAULT_CTRL_REG3 0x80  // 初期値: 0x80
#define DEFAULT_THS_P_LOW 0x80  // 初期値: 0x80
#define DEFAULT_THS_P_HIGH 0x7F // 初期値: 0x7F

// 圧力測定のオーバーサンプリング比 (OSR)
// OPTN_REGレジスタのビット[3:0]に設定
#define OSR_512   0x05  // オーバーサンプリング比: 512、変換時間: 1/256秒
#define OSR_640   0x06  // オーバーサンプリング比: 640、変換時間: 1/204.8秒
#define OSR_1024  0x07  // オーバーサンプリング比: 1024、変換時間: 1/128秒
#define OSR_2048  0x08  // オーバーサンプリング比: 2048、変換時間: 1/64秒
#define OSR_4096  0x09  // オーバーサンプリング比: 4096、変換時間: 1/32秒

// 圧力測定の平均化設定 (AVGP[2:0])
// RES_CONFレジスタのビット[2:0]に設定
#define AVGP_1   0x00  // 平均回数: 1回
#define AVGP_2   0x01  // 平均回数: 2回
#define AVGP_4   0x02  // 平均回数: 4回
#define AVGP_8   0x03  // 平均回数: 8回
#define AVGP_16  0x04  // 平均回数: 16回
#define AVGP_32  0x05  // 平均回数: 32回

// 温度測定の平均化設定 (AVGT[2:0])
// RES_CONFレジスタのビット[6:4]に設定
#define AVGT_1   0x00  // 平均回数: 1回
#define AVGT_2   0x10  // 平均回数: 2回
#define AVGT_4   0x20  // 平均回数: 4回

// STBY (スタンバイ時間)設定値
// STBYレジスタ (アドレス: 0x12) のビット[3:0]に対応
#define STBY_0_MS    0x00  // スタンバイ時間: 0 ms
#define STBY_10_MS   0x01  // スタンバイ時間: 10 ms
#define STBY_50_MS   0x02  // スタンバイ時間: 50 ms
#define STBY_100_MS  0x03  // スタンバイ時間: 100 ms
#define STBY_250_MS  0x04  // スタンバイ時間: 250 ms
#define STBY_500_MS  0x05  // スタンバイ時間: 500 ms
#define STBY_750_MS  0x06  // スタンバイ時間: 750 ms
#define STBY_1000_MS 0x07  // スタンバイ時間: 1000 ms
#define STBY_1500_MS 0x08  // スタンバイ時間: 1500 ms
#define STBY_2000_MS 0x09  // スタンバイ時間: 2000 ms
#define STBY_2500_MS 0x0A  // スタンバイ時間: 2500 ms
#define STBY_3000_MS 0x0B  // スタンバイ時間: 3000 ms
#define STBY_3500_MS 0x0C  // スタンバイ時間: 3500 ms
#define STBY_4000_MS 0x0D  // スタンバイ時間: 4000 ms
#define STBY_4500_MS 0x0E  // スタンバイ時間: 4500 ms
#define STBY_5000_MS 0x0F  // スタンバイ時間: 5000 ms

#endif
