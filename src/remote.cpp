#include "remote.hpp"
#include "IRremote.hpp"
#include <Arduino.h>

bool has_begun = false;

String getButtonName(REMOTE_BUTTON_CODES code)
{
    switch (code)
    {
    case CHANEL_MINUS:
        return "CHANEL_MINUS";
    case CHANNEL:
        return "CHANNEL ";
    case CHANEL_PLUS:
        return "CHANEL_PLUS ";
    case PREV:
        return "PREV";
    case NEXT:
        return "NEXT";
    case PLAY_PAUSE:
        return "PLAY_PAUSE";
    case VOL_MINUS:
        return "VOL_MINUS";
    case VOL_PLUS:
        return "VOL_PLUS";
    case EQUALIZER:
        return "EQUALIZER";
    case N_0:
        return "N_0";
    case N_100_PLUS:
        return "N_100_PLUS";
    case N_200_PLUS:
        return "N_200_PLUS";
    case N_1:
        return "N_1";
    case N_2:
        return "N_2";
    case N_3:
        return "N_3";
    case N_4:
        return "N_4";
    case N_5:
        return "N_5";
    case N_6:
        return "N_6";
    case N_7:
        return "N_7";
    case N_8:
        return "N_8";
    case N_9:
        return "N_9";
    default:
        return "INVALID_CODE";
    };
}

void initRemote(int receiver_pin)
{
    if (has_begun) {
        Serial.println("Remote has already been begun");
    }
    IrReceiver.begin(receiver_pin);
    has_begun = true;
}

bool getCodeFromRemote(REMOTE_BUTTON_CODES &out_code)
{
    if (!IrReceiver.decode())
    {
        return false;
    }
    out_code = (REMOTE_BUTTON_CODES)IrReceiver.decodedIRData.command;
    IrReceiver.resume();
    return true;
}

void initTelecommande()
{
    initRemote(4);
}

long getCodeRecu()
{
    REMOTE_BUTTON_CODES code;
    bool success = getCodeFromRemote(code);
    return success ? code : -1;
}