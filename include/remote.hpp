#pragma once
#define DECODE_NEC
#include <Arduino.h>

// normalement, j'implementerais un senseur, mais vu que la librairie est bizare et entierement globale, cette implementation est une exception

enum REMOTE_BUTTON_CODES: long {
    CHANEL_MINUS = 69,
    CHANNEL = 70,
    CHANEL_PLUS = 71,
    PREV=68,
    NEXT=64,
    PLAY_PAUSE=67,
    VOL_MINUS=7,
    VOL_PLUS=21,
    EQUALIZER=9,
    N_0=22,
    N_100_PLUS=25,
    N_200_PLUS=13,
    N_1=12,
    N_2=24,
    N_3=94,
    N_4=8,
    N_5=28,
    N_6=90,
    N_7=66,
    N_8=82,
    N_9=74,
};

String getButtonName(REMOTE_BUTTON_CODES code);

void initRemote(int receiver_pin);
bool getCodeFromRemote(REMOTE_BUTTON_CODES &out_code);
