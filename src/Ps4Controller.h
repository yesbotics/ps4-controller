/*
 *  Created on: 04.07.2019
 *  Author: Albrecht Nitsche und Jens Kabisch
 */
#ifndef PS4CONTROLLER_H
#define PS4CONTROLLER_H

#include <Arduino.h>
#include <PS4BT.h>
#include <PS4USB.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

#include <SPI.h>
#include <PROGMEM_readAnything.h>

#include "Ps4Data.h"

class Ps4Controller {

public:
    typedef void (*ExternalCallbackPointer)(byte buttonId, byte value);
    Ps4Controller(USB *usbPtr, PS4USB *ps4UsbPtr, ExternalCallbackPointer buttonValueChangeCallbackPointer);
    Ps4Controller(USB *usbPtr, PS4BT *ps4BtPtr, ExternalCallbackPointer buttonValueChangeCallbackPointer);
    bool initialize(unsigned long pollingInterval = 50, unsigned int analogValueThreshold = 2, void (*funcOnInit)() = nullptr);
    bool isInitialized();
    bool isConnected();
    bool loop();
    static int8_t convertHatValue(byte value);

    /**
     * Return the battery level of the PS4 controller.
     * @return The battery level in the range 0-255
     */
    uint8_t getBatteryLevel();
    Ps4Data getData();

protected:

private:
    ExternalCallbackPointer valueChangeCallbackPointer = nullptr;
    USB *usbPtr = nullptr;
    PS4USB *ps4UsbPtr = nullptr;
    PS4BT *ps4BtPtr = nullptr;
    PS4Parser *ps4Parser = nullptr;
    unsigned long pollingInterval = 50;
    unsigned int analogValueThreshold = 2;
    bool _isInitialized = false;
    bool _isConnected = false;
    bool isBluetooth;
    unsigned long lastMillis = 0;

    const byte downButtonsLength = ArraySize(downButtons);
    const byte analogHatsLength = ArraySize(analogHats);
    const byte analogButtonsLength = ArraySize(analogButtons);
    ButtonIdToCommandToBoolValue currentBoolButton;
    ButtonIdToCommandToByteValue currentAnalogButton;

    void addPs4Var(bool curValue, bool &oldValue, byte buttonId);
    void addPs4Var(byte curValue, byte &oldValue, byte buttonId);
    void checkPs4ControllerAnalogEvents();
    void checkPs4ControllerDownEvents();
};

#endif
