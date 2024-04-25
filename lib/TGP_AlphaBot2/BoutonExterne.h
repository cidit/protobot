#ifndef BoutonExterne_h
#define BoutonExterne_h

#include "BoutonBase.h"

class BoutonExterne : public BoutonBase
{
public:
	BoutonExterne();
	void setNextValue(bool);

protected:
    bool isDetected();

private:
	bool _nextValue;
};

#endif