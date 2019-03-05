#include <Arduino.h>
#include <FastLED.h>
#include <TPM-FX.h>

#define LED_DATA_PIN 18
#define LED_CLK_PIN 5

#define NUM_LEDS    11
#define START_LED   0

#define UPDATES_PER_SECOND 30


CRGB leds[NUM_LEDS];

CRGB TempLedArray[NUM_LEDS];

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

tpm_fx tpm_fx;   // init the TPM_FX

void setup() {
  
  
    delay( 3000 ); // power-up safety delay

   // FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<APA102,LED_DATA_PIN ,  LED_CLK_PIN, BGR,DATA_RATE_MHZ(1 )>  (leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;

}

void loop()
{
    static uint8_t startIndex = 0;  
    
    uint8_t index_add_led = 6; // how much to compress the palette
    
    // lets fill the array with Colors from a Palette. 
    // since we want to mirror it we need to give it a tempLedArray to work with.
    // There are 2 version, one with a TempLedArray, where you can choose to 
    // Mirror, Reverse or Onecolor. 
    // The other version mixes Straight onto the Output Array but you can't mirror/reverse/onecolor.
    
    MixModeType mix_mode = MIX_REPLACE; // We will replace the values in the Output Array.
    boolean mirror = true;
    boolean reversed = false;
    uint8_t mix_level = 255;
    
    tpm_fx.PalFill( leds, TempLedArray, RainbowColors_p, START_LED, NUM_LEDS , startIndex++ ,index_add_led , mix_mode, LINEARBLEND ,  reversed ,mirror, mix_level );
    
    
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}
