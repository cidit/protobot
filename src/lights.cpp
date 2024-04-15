#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 7

const auto howmanypins = 4;

Adafruit_NeoPixel RGB = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);

void initDels()
{
    RGB.begin();
    changeColors(Adafruit_NeoPixel::Color(255, 255, 255));
}

/**
 * DEVIS
*/
void changerCouleur(uint8_t rouge, uint8_t vert, uint8_t bleu)
{
    auto color = Adafruit_NeoPixel::Color(rouge, vert, bleu);
    changeColors(color);
}

void changeColors(int color)
{
    for (auto i = 0; i < howmanypins; i++)
    {
        RGB.setPixelColor(i, color);
    }
    RGB.show();
}