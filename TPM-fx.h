#ifndef TPM_FX_h
#define TPM_FX_h


#include "Arduino.h"
#include <FastLED.h>



typedef enum {
          MIX_REPLACE
          ,MIX_ADD 			
          ,MIX_SUBTRACT		
          ,MIX_MASK			
          ,MIX_OR		
          ,MIX_XOR
          ,MIX_AND
          ,MIX_DIFF
          ,MIX_HARD
          ,MIX_MULTIPLY
          ,MIX_HARD_LIGHT
          ,MIX_OVERLAY
          ,MIX_TADA
          ,MIX_DARKEN
          ,MIX_LIGHTEN
          ,MIX_LINEAR_BURN
          ,MIX_SCREEN
            } MixModeType;
#define HARD_MIX_TRIGGER 128



class tpm_fx
{
  public:
    //fx();
   void noiseSimple(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds  ,uint8_t octaves, uint16_t x, int scale, uint8_t hue_octaves, uint16_t hue_x, int hue_scale,
            uint16_t time) ;

//Create Layer FX
    //these FX allways write a new Layer. So they are mixed onto the output when generating the colors ( to save memory)
    // if you want to reverse / mirror these do it in 2 steps, first export it to a tempCRGBArray and then mix+mirror+reverse it with mixOntoLedArray .
    // 
    void Fire2012WithPalette(CRGB *OutputLedArray, byte heat[], CRGBPalette16 currentPalette,  uint16_t start_led, uint16_t Nr_leds, uint8_t level, uint8_t cooling = 20 , uint8_t sparking = 50, MixModeType mix_mode = MIX_REPLACE);
    void Shimmer(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds, uint16_t xscale = 6 , uint16_t yscale = 5, uint8_t beater = 7, MixModeType mix_mode = MIX_REPLACE  ,uint8_t level =255, TBlendType blend = LINEARBLEND ) ;
    void noise16fromPalette(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds, uint8_t speed = 30, uint16_t scale = 200, uint8_t trip = 8,  MixModeType mix_mode = MIX_REPLACE,  TBlendType blend = LINEARBLEND) ;

    void threeSinPalette(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds  , uint8_t distance , uint8_t bmpWave1 = 0  ,uint8_t bmpWave2 = 1  ,uint8_t bmpWave3 = 2, int lowWave1= 10 ,int hiWave1 = 250 ,int lowWave2 = 40,int hiWave2= 120 ,int lowWave3 = 5 ,int hiWave3 = 128, MixModeType mix_mode = MIX_REPLACE, uint8_t brightness = 255, TBlendType  blend = LINEARBLEND  ) ;

    // Basic Palette Functions
    void PalFill( CRGB *OutputLedArray, CRGBPalette16 currentPalette , uint16_t StartLed, uint16_t numberOfLeds , uint8_t colorIndex, uint8_t indexAddLed, MixModeType mix_mode = MIX_REPLACE, uint8_t brightness = 255, TBlendType blending = LINEARBLEND );
    void PalFillLong(CRGB *OutputLedArray, CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t numberOfLeds , uint16_t colorIndexLong ,uint16_t indexAddLed, MixModeType mix_mode = MIX_REPLACE,  uint8_t brightness = 255, TBlendType blending = LINEARBLEND);



//Modify Layer FX
    // These FX manipulate a CRGB array. They look best if they allways manipulate the same layer 
    // You need to mix the manipulated layer onto your OUTPUT led array.
    // They need a fade in the loop to work or they just go white.
      void AddGlitter(CRGB *OutputLedArray,CRGBPalette16 currentPalette,fract8 chanceOfGlitter, uint16_t start_led, uint16_t nr_leds);

      // Running Dots 
      void DotSine(CRGB *OutputLedArray, uint8_t inputhue, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness = 255, uint8_t Saturation = 255);
      void DotSine(CRGB *OutputLedArray, CRGBPalette16 currentPalette, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness = 255);
      void DotSine(CRGB *OutputLedArray, CRGB inputcolor, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness = 255);

      void DotSaw(CRGB *OutputLedArray, uint8_t inputhue, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness = 255, uint8_t Saturation = 255);
      void DotSaw(CRGB *OutputLedArray, CRGBPalette16 currentPalette, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness = 255 );
      void DotSaw(CRGB *OutputLedArray, CRGB inputcolor, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness = 255);


      // Manipulate Layer
      void fadeLedArray(CRGB *OutputLedArray, uint16_t start_led, uint16_t nr_leds, uint8_t fadyBy);

  // Mixing
      // Mix one led array with another one
      // Mirror takes the 1st half and mirrors it to the second.
      // Reverse 1sit led in iput array becomes the last led in outputArray
      // Mirror + reverse = Like Reverse and then take the Second half and mirror it to the first.
      void mixOntoLedArray(CRGB *InputLedArray, CRGB *OutputLedArray , uint16_t nr_leds, uint16_t start_led = 0, boolean reversed = false, boolean mirror = false ,MixModeType mix_mode = MIX_ADD, uint8_t mix_level = 255);


      // Mix color onto led
      void mixOntoLed(CRGB *OutputLedArray, uint16_t led_nr, CRGB color, MixModeType mode);


  private:
      // Palette Get
    CRGB PalGetFromLongPal(  CRGBPalette16 currentPalette,	uint16_t longIndex,	uint8_t brightness ,	TBlendType blendType) ;
    
};
















#endif