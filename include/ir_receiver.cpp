#include "ir_receiver.hpp"

Infrared *Infrared::instance = nullptr;
int *Infrared::_receive_pin = nullptr;

Infrared::Infrared()
{
}

Infrared* Infrared::getInstance()
{
    if (_receive_pin == nullptr) {
        return nullptr;
    }
    if (instance == nullptr)
    {
        Infrared ii();
        *instance = &ii;
        instance->begin();
    }
    return instance;
}

void Infrared::begin()
{
    IrReceiver.begin(*_receive_pin);
}

bool Infrared::sample(Code &out)
{
    if (!IrReceiver.decode())
    {
        return false;
    }
    auto cmd = IrReceiver.decodedIRData.command;
    IrReceiver.resume();
    return cmd;
}

void Infrared::begin()
{
    IrReceiver.begin(this->_receive_pin);
}

bool Infrared::sample(Code &out)
{
    if (!IrReceiver.decode())
    {
        return false;
    }
    auto cmd = IrReceiver.decodedIRData.command;
    IrReceiver.resume();
    return cmd;
}
