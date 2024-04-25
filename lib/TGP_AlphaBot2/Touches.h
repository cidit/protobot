#ifndef Touches_h
#define Touches_h

#include "BoutonExterne.h"
#include <Wire.h>

#define I2C_ADDR  0x20
#define HAUT_ADDR 0b00000001
#define DROITE_ADDR 0b00000010
#define GAUCHE_ADDR 0b00000100
#define BAS_ADDR 0b00001000
#define SELECTION_ADDR 0b00010000
#define BUZZER_ADDR 0b00100000
#define PARECHOC_DROITE_ADDR 0b01000000
#define PARECHOC_GAUCHE_ADDR 0b10000000

/******************************************************************************
 * Definitions
 ******************************************************************************/
class Touches
{
public:
    Touches(TwoWire *);
    void begin();
    void refresh();
    uint8_t getStates();
    
    BoutonExterne gauche, droite, haut, bas, selection;
    BoutonExterne parechocGauche, parechocDroite;
private:
    uint8_t _currentValue;
    bool extractAndRefresh(BoutonExterne *,uint8_t);
    uint8_t read();
    TwoWire * _wire;
};
#endif
