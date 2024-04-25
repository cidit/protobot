#include "Touches.h"

Touches::Touches(TwoWire *wire) : gauche(), droite(), haut(), bas(), selection(),
                                  parechocGauche(), parechocDroite()
{
  _currentValue = 0;
  _wire = wire;
}

void Touches::begin()
{
  gauche.setDebounceDelay(2);
  droite.setDebounceDelay(2);
  haut.setDebounceDelay(2);
  bas.setDebounceDelay(2);
  selection.setDebounceDelay(2);
  parechocGauche.setDebounceDelay(2);
  parechocDroite.setDebounceDelay(2);
  parechocGauche.setLongPressInterval(2000);
  parechocDroite.setLongPressInterval(2000);
}

void Touches::refresh()
{
  _currentValue = Touches::read();

  extractAndRefresh(&gauche, GAUCHE_ADDR);
  extractAndRefresh(&droite, DROITE_ADDR);
  extractAndRefresh(&bas, BAS_ADDR);
  extractAndRefresh(&haut, HAUT_ADDR);
  extractAndRefresh(&selection, SELECTION_ADDR);
  extractAndRefresh(&parechocGauche, PARECHOC_GAUCHE_ADDR);
  extractAndRefresh(&parechocDroite, PARECHOC_DROITE_ADDR);
}

uint8_t Touches::getStates()
{
  return _currentValue;
}

bool Touches::extractAndRefresh(BoutonExterne *bouton, uint8_t address)
{
  bouton->setNextValue((_currentValue & address) == 0);
  bouton->refresh();
}

uint8_t Touches::read()
{
  uint8_t data = -1;
  _wire->requestFrom(I2C_ADDR, 1);
  if (_wire->available())
  {
    data = _wire->read();
  }
  return data;
}
