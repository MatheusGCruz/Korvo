#ifndef KorvoV11_H
#define KorvoV11_H

// I2C pins Configuration
#define I2C_SDA 19
#define I2C_SCL 32

// WS2812 Led array Configuration
#define WS2812_PIN 33      // GPIO pin connected to WS2812 data
#define WS2812_NUM_LEDS 12     // Number of LEDs in your strip

// Button Array Configuration
#define BUTTON_ARRAY_PIN 39  // Buttons Serial Controller
// Buttons values:
// VOL+ - 305-306
// VOL- - 842-846
// SET  - 1210-1213
// PLAY - 1879-1881
// MODE - 2289-2292
// REC  - 2825-2827

// I2S Pin Configuration
#define I2S_DOUT  25  // Data out
#define I2S_BCLK  26  // Bit clock
#define I2S_LRC   22  // Left-right clock

//MIC ARRAY ES7210 Configuration
#define ES7210_MCLK 	0
#define ES7210_SCLK		27
#define ES7210_LRCK		26
#define ES7210_SDOUT	36
#define ES7210_INT		34

//SD READER Configuration 
#define SD_CLK			5
#define SD_CMD 			18
#define SD_DAT0			21
#define SD_DAT3			23
#define SD_DET			35

//Speaker Codec ES8311 Configuration
#define ES8311_MCLK		0
#define ES8311_SCLK		25
#define ES8311_LRCK		22
#define ES8311_DSDIN	13
#define PA_CTRL			12

//STD IO configuration (ESP to ESP)
#define SDIO_CLK		14
#define SDIO_CMD		15
#define SDIO_DAT0		2
#define SDIO_DAT1		4

//Boot Configuration
#defina ESP_BOOT_IO0	0
#defina ESP_BOOT_IO2	2
#defina ESP_BOOT_EN		EN



#endif