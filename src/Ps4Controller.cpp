#include "Ps4Controller.h"

Ps4Controller::Ps4Controller(
        USB *usbPtr,
        PS4USB *ps4UsbPtr,
        ExternalCallbackPointer valueChangeCallbackPointer
) {
    this->usbPtr = usbPtr;
    this->ps4UsbPtr = ps4UsbPtr;
    this->ps4Parser = ps4UsbPtr;
    this->valueChangeCallbackPointer = valueChangeCallbackPointer;
    this->isBluetooth = false;
}

Ps4Controller::Ps4Controller(
        USB *usbPtr,
        PS4BT *ps4BtPtr,
        ExternalCallbackPointer valueChangeCallbackPointer
) {
    this->usbPtr = usbPtr;
    this->ps4BtPtr = ps4BtPtr;
    this->ps4Parser = ps4BtPtr;
    this->valueChangeCallbackPointer = valueChangeCallbackPointer;
    this->isBluetooth = true;
}

bool Ps4Controller::initialize(unsigned long pollingInterval, unsigned int analogValueThreshold, void (*funcOnInit)()) {
    if (this->_isInitialized) {
        return false;
    }
    this->pollingInterval = pollingInterval;
    this->analogValueThreshold = analogValueThreshold;

    if (this->usbPtr->Init() == -1) {
//        Serial.print(F("USB NOT INITIALIZED"));
        return false;
    }

    if (funcOnInit) {
        if (this->isBluetooth) {
            this->ps4BtPtr->attachOnInit(funcOnInit);
        } else {
            this->ps4UsbPtr->attachOnInit(funcOnInit);
        }
    }

    this->_isInitialized = true;
    return true;
}

// Converts byte value to int8 value: -128..127
int8_t Ps4Controller::convertHatValue(byte value) {
    return value - 127;
}

bool Ps4Controller::isInitialized() {
    return this->_isInitialized;
}

bool Ps4Controller::isConnected() {
    return this->_isConnected;
}

bool Ps4Controller::loop() {

    this->usbPtr->Task();

    if (!this->_isInitialized) {
        return false;
    }

    if (this->isBluetooth) {
        this->_isConnected = this->ps4BtPtr->connected();
    } else {
        this->_isConnected = this->ps4UsbPtr->connected();
    }

    if (!this->_isConnected) {
        return false;
    }

    /**
     * ClickEvents - Müssen bei jedem Loop abgerufen werden
     */
    this->checkPs4ControllerDownEvents();

    /**
     * ChangeEvents - Diese werden nur nach einer gewissen Zeit abgerufen
     */
    unsigned long currentMillis = millis();
    if ((currentMillis - this->lastMillis) >= this->pollingInterval) {
        this->lastMillis = currentMillis;
        this->checkPs4ControllerAnalogEvents();
    }

    return true;
}

uint8_t Ps4Controller::getBatteryLevel() {
    if (this->_isInitialized) {
        return map(this->ps4Parser->getBatteryLevel(), 0, 15, 0, 255);
    } else {
        return 0;
    }
}

void Ps4Controller::checkPs4ControllerDownEvents() {
    /**
     * Down-Buttons
     */
    for (int i = 0; i < downButtonsLength; i++) {
        currentBoolButton = PROGMEM_getAnything(&downButtons[i]);
        this->addPs4Var(
                this->ps4Parser->getButtonPress(static_cast<ButtonEnum>(currentBoolButton.ps4Id)),
                *(currentBoolButton.value),
                currentBoolButton.buttonId
        );
    }
}

void Ps4Controller::checkPs4ControllerAnalogEvents() {
    /**
     * AnalogHats
     */
    for (int i = 0; i < analogHatsLength; i++) {
        currentAnalogButton = PROGMEM_getAnything(&analogHats[i]);
        this->addPs4Var(
                this->ps4Parser->getAnalogHat(static_cast<AnalogHatEnum>(currentAnalogButton.ps4Id)),
                *(currentAnalogButton.value),
                currentAnalogButton.buttonId
        );
    }

    /**
     * AnalogButtons
     */
    for (int i = 0; i < analogButtonsLength; i++) {
        currentAnalogButton = PROGMEM_getAnything(&analogButtons[i]);
        this->addPs4Var(
                this->ps4Parser->getAnalogButton(static_cast<ButtonEnum>(currentAnalogButton.ps4Id)),
                *(currentAnalogButton.value),
                currentAnalogButton.buttonId
        );
    }
}

void Ps4Controller::addPs4Var(byte curValue, byte &oldValue, byte buttonId) {
    byte diff = abs(curValue - oldValue);
    if (diff >= this->analogValueThreshold) {
        oldValue = curValue;
        if (this->valueChangeCallbackPointer != nullptr) {
            this->valueChangeCallbackPointer(buttonId, curValue);
        }
    }
}

void Ps4Controller::addPs4Var(bool curValue, bool &oldValue, byte buttonId) {
    if (curValue != oldValue) {
        oldValue = curValue;
        if (this->valueChangeCallbackPointer != nullptr) {
            this->valueChangeCallbackPointer(buttonId, curValue);
        }
    }
}

Ps4Data Ps4Controller::getData() {
    return ps4Data;
}

