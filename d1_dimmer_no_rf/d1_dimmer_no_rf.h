/*
  d1_dimmer_no_rf.h - Sonoff D1 Dimmer support for ESPHome

  Copyright © 2020 Jeff Rescignano

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
  and associated documentation files (the “Software”), to deal in the Software without
  restriction, including without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom
  the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or
  substantial portions of the Software.

  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

  -----

  If modifying this file, in addition to the license above, please ensure to include links back to the original code:
  https://jeffresc.dev/blog/2020-10-10
  https://github.com/JeffResc/Sonoff-D1-Dimmer
  https://github.com/arendst/Tasmota/blob/2d4a6a29ebc7153dbe2717e3615574ac1c84ba1d/tasmota/xdrv_37_sonoff_d1.ino#L119-L131

  -----

  THANK YOU!
  Thanks to the team over at Tasmota for providing the serial codes to control the dimmer!

  View the source: https://github.com/arendst/Tasmota/blob/2d4a6a29ebc7153dbe2717e3615574ac1c84ba1d/tasmota/xdrv_37_sonoff_d1.ino#L119-L131
*/

#include "esphome.h"

class Sonoff_D1_Dimmer : public Component, public LightOutput
{
private:
  bool lastBinary;
  int lastBrightness;

public:
  void setup() override
  {
    // Start a serial connection when the script is setup
    Serial.begin(9600);
  }
  // Set the device's traits
  LightTraits get_traits() override
  {
    auto traits = LightTraits();
    traits.set_supported_color_modes({light::ColorMode::BRIGHTNESS});
    return traits;
  }

  void control_dimmer(const bool & binary, const int & brightness) {
    if (binary != lastBinary || brightness != lastBrightness)
    {
      // Include our basic code from the Tasmota project, thank you again!
      //                     0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16
      uint8_t buffer[17] = {0xAA, 0x55, 0x01, 0x04, 0x00, 0x0A, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00};

      buffer[6] = binary;
      buffer[7] = brightness;

      for (uint32_t i = 0; i < sizeof(buffer); i++)
      {
        if ((i > 1) && (i < sizeof(buffer) - 1))
        {
          buffer[16] += buffer[i];
        }
        Serial.write(buffer[i]);
      }
    }
  }

  void write_state(LightState *state) override
  {
    bool binary;
    float brightness;

    // Fill our variables with the device's current state
    state->current_values_as_binary(&binary);
    state->current_values_as_brightness(&brightness);

    // Convert ESPHome's brightness (0-1) to the device's internal brightness (0-100)
    const int calculatedBrightness = round(brightness * 100);

    ESP_LOGD("custom", "Interpreting brightness %f as %d", brightness, calculatedBrightness);
    control_dimmer(binary, calculatedBrightness);
  }
};