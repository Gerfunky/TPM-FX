#ifndef TPM_FX_h
#define TPM_FX_h


#include "Arduino.h"
#include <FastLED.h>



typedef enum {
          
          MIX_ADD =0 			
          ,MIX_SUBTRACT		=1 
          ,MIX_MASK			=2 
          ,MIX_OR		=3
          ,MIX_XOR  =4
          ,MIX_AND  =5
          ,MIX_DIFF =6 
          ,MIX_HARD = 7
          ,MIX_MULTIPLY = 8 
          ,MIX_HARD_LIGHT = 10
          ,MIX_OVERLAY = 11
          ,MIX_TADA = 12 
          ,MIX_DARKEN = 13
          ,MIX_LIGHTEN = 14
          ,MIX_LINEAR_BURN = 15
          ,MIX_SCREEN = 16 
          ,MIX_REPLACE = 17
          ,MIX_SOFT_LIGHT = 18
          ,MIX_COLOR_DODGE = 19
          ,MIX_COLOR_BURN = 20
          ,MIX_LINEAR_DODGE = 21
          ,MIX_EXCLUSION = 22

            } MixModeType;
#define HARD_MIX_TRIGGER 128



class tpm_fx
{
  public:


   
   void noiseSimple(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds  ,uint8_t octaves, uint16_t x, int scale, uint8_t hue_octaves, uint16_t hue_x, int hue_scale,
            uint16_t time) ;

//Create Layer FX
    //these FX allways write a new Layer. So they are mixed onto the output when generating the colors ( to save memory)
    // if you want to  / mirror these do it in 2 steps, first export it to a tempCRGBArray and then mix+mirror+reverse it with mixOntoLedArray .
    // 
    void Fire2012WithPalette(CRGB *OutputLedArray, byte heat[], CRGBPalette16 currentPalette,  uint16_t start_led, uint16_t Nr_leds, uint8_t level, uint8_t cooling = 20 , uint8_t sparking = 50, MixModeType mix_mode = MIX_REPLACE);
    void Fire2012WithPalette(CRGB *OutputLedArray,CRGB *TempLedArray, byte heat[],CRGBPalette16 currentPalette,  uint16_t start_led, uint16_t Nr_leds, uint8_t cooling = 20 , uint8_t sparking = 50, MixModeType mix_mode = MIX_REPLACE , TBlendType blending = LINEARBLEND , boolean reversed = false , boolean mirror = false  , uint8_t mix_level = 255 , boolean onecolor = false ) ;
    
    uint16_t Shimmer(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds, uint16_t dist, uint16_t xscale = 6 , uint16_t yscale = 5, uint8_t beater = 7, MixModeType mix_mode = MIX_REPLACE  ,uint8_t level =255, TBlendType blend = LINEARBLEND ) ;
    void noise16fromPalette(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds, uint8_t speed = 30, uint16_t scale = 200, uint8_t trip = 8,  MixModeType mix_mode = MIX_REPLACE,  TBlendType blend = LINEARBLEND) ;

    void threeSinPalette(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds  , uint8_t distance , uint8_t bmpWave1 = 0  ,uint8_t bmpWave2 = 1  ,uint8_t bmpWave3 = 2, int lowWave1= 10 ,int hiWave1 = 250 ,int lowWave2 = 40,int hiWave2= 120 ,int lowWave3 = 5 ,int hiWave3 = 128, MixModeType mix_mode = MIX_REPLACE, uint8_t brightness = 255, TBlendType  blend = LINEARBLEND  ) ;

    // Basic Palette Functions
    CRGB PalGetFromLongPal(  CRGBPalette16 currentPalette,	uint16_t longIndex,	uint8_t brightness ,	TBlendType blendType) ;
    // 2 version 
    void PalFill( CRGB *OutputLedArray, CRGBPalette16 currentPalette , uint16_t StartLed, uint16_t numberOfLeds , uint8_t colorIndex, uint8_t indexAddLed, MixModeType mix_mode = MIX_REPLACE, uint8_t brightness = 255, TBlendType blending = LINEARBLEND );
    void PalFill( CRGB *OutputLedArray, CRGB *TempLedArray, CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t numberOfLeds , uint16_t colorIndex ,uint16_t indexAddLed, MixModeType mix_mode = MIX_REPLACE, TBlendType blending = LINEARBLEND , boolean reversed = false, boolean mirror = false , uint8_t mix_level = 255 , boolean onecolor = false );
    void PalFillLong(CRGB *OutputLedArray, CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t numberOfLeds , uint16_t colorIndexLong ,uint16_t indexAddLed, MixModeType mix_mode = MIX_REPLACE,  uint8_t brightness = 255, TBlendType blending = LINEARBLEND);
    void PalFillLong(CRGB *OutputLedArray, CRGB *TempLedArray, CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t numberOfLeds , uint16_t colorIndexLong ,uint16_t indexAddLed, MixModeType mix_mode = MIX_REPLACE, TBlendType blending = LINEARBLEND , boolean reversed = false, boolean mirror = false , uint8_t mix_level = 255 , boolean onecolor = false );

    void noise8(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds , uint16_t scale , uint16_t dist,  MixModeType mix_mode = MIX_REPLACE, uint8_t brightness = 255, TBlendType  blend = LINEARBLEND);

    void strobe(CRGB *OutputLedArray, uint16_t StartLed, uint16_t NrLeds, CRGB color , uint16_t on_Frames ,uint16_t off_frames , uint16_t frame_position ,MixModeType mix_mode = MIX_REPLACE, uint8_t brightness = 255);
    void BlinkingEyes(CRGB *OutputLedArray, uint16_t StartLed, uint16_t NrLeds, CRGB color , uint16_t EyeWidth, uint16_t EyeSpace, uint16_t eye_pos, uint16_t on_frames,  uint16_t frame_pos, uint8_t fade_speed,  MixModeType mix_mode = MIX_ADD, uint8_t brightness =255);
    void meteorRain(CRGB *OutputLedArray, uint16_t StartLed, uint16_t NrLeds, CRGB color ,uint16_t frame_pos,  byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay);


//Modify Layer FX
    // These FX manipulate a CRGB array. They look best if they allways manipulate the same layer 
    // You need to mix the manipulated layer onto your OUTPUT led array.
    // They need a fade in the loop to work or they just go white.
      void AddGlitter(CRGB *OutputLedArray,CRGBPalette16 currentPalette,fract8 chanceOfGlitter, uint16_t start_led, uint16_t nr_leds);
      void AddGlitter(CRGB *OutputLedArray,CRGB color,fract8 chanceOfGlitter, uint16_t start_led, uint16_t nr_leds, uint8_t level);

      // Running Dots 
      void DotSine(CRGB *OutputLedArray, uint8_t inputhue, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness = 255, uint8_t Saturation = 255);
      void DotSine(CRGB *OutputLedArray, CRGBPalette16 currentPalette, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness = 255);
      void DotSine(CRGB *OutputLedArray, CRGB inputcolor, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness = 255);

      void DotSaw(CRGB *OutputLedArray, uint8_t inputhue, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness = 255, uint8_t Saturation = 255);
      void DotSaw(CRGB *OutputLedArray, CRGBPalette16 currentPalette, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness = 255 );
      void DotSaw(CRGB *OutputLedArray, CRGB inputcolor, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness = 255);

      void KITT_RightToLeft(CRGB *OutputLedArray, uint16_t StartLed, uint16_t NrLeds, CRGB color ,uint16_t frame_pos, uint8_t EyeSize, MixModeType mix_mode, uint8_t brightness) ;
      void KITT_LeftToRight(CRGB *OutputLedArray, uint16_t StartLed, uint16_t NrLeds, CRGB color ,uint16_t frame_pos, uint8_t EyeSize, MixModeType mix_mode, uint8_t brightness) ;

      // Manipulate Layer
      void fadeLedArray(CRGB *OutputLedArray, uint16_t start_led, uint16_t nr_leds, uint8_t fadeBy);

  // Mixing
      // Mix one led array with another one
      // Mirror takes the 1st half and mirrors it to the second.
      // Reverse 1sit led in iput array becomes the last led in outputArray
      // Mirror + reverse = Like Reverse and then take the Second half and mirror it to the first.
      void mixOntoLedArray(CRGB *InputLedArray, CRGB *OutputLedArray , uint16_t nr_leds, uint16_t start_led = 0, boolean reversed = false, boolean mirror = false ,MixModeType mix_mode = MIX_ADD, uint8_t mix_level = 255 , boolean onecolor = false );
      void mixHistoryOntoLedArray(CRGB *InputLedArray, CRGB *OutputLedArray , uint16_t nr_leds, uint16_t start_led, boolean reversed, boolean mirror ,MixModeType mix_mode, uint8_t mix_level, boolean onecolor, uint16_t offset = 0, uint8_t extend = 0);
      
      //void mixOntoLedArray(CRGB *InputLedArray, CRGB *OutputLedArray , uint16_t nr_leds, uint16_t start_led = 0, boolean reversed = false, boolean mirror = false ,uint8_t mix_mode = 1 , uint8_t mix_level = 255 , boolean onecolor = false );


      // Mix color onto led
      void mixOntoLed(CRGB *OutputLedArray, uint16_t led_nr, CRGB color, MixModeType mode, uint8_t level =255);

    // Modify

     void rotate(CRGB *OutputLedArray , uint16_t nr_leds, uint16_t start_led = 0, uint16_t rotateAmount = 0);
     void rotate(CRGB *OutputLedArray , uint16_t nr_leds, uint16_t start_led, uint16_t framesFullRotation, uint16_t framePos);

  //private:
      // Palette Get
    
    
};
















#endif