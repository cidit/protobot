#include "BoutonExterne.h"

BoutonExterne::BoutonExterne() : BoutonBase()
{
	_nextValue = false;
}

bool BoutonExterne::isDetected(){
    return _nextValue;
}


void BoutonExterne::setNextValue(bool value)
{
	_nextValue = value;
}