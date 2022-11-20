#ifndef PS4DATA_H
#define PS4DATA_H

#ifdef ARDUINO_ARCH_AVR
#include <avr/pgmspace.h>
#else
#include <pgmspace.h>
#endif
#include <PS4BT.h>
#include <PS4USB.h>

template<typename T, size_t N>
size_t ArraySize(T (&)[N]) {
    return N;
}

enum ButtonIdEnum : byte {
    BUTTON_LEFTHATX = 1,
    BUTTON_LEFTHATY = 2,
    BUTTON_RIGHTHATX = 3,
    BUTTON_RIGHTHATY = 4,
    BUTTON_ANALOGL2 = 5,
    BUTTON_ANALOGR2 = 6,

    BUTTON_RIGHT = 7,
    BUTTON_DOWN = 8,
    BUTTON_LEFT = 9,
    BUTTON_UP = 10,

    BUTTON_SELECT = 11,
    BUTTON_START = 12,
    BUTTON_L1 = 13,
    BUTTON_R1 = 14,
    BUTTON_L2 = 15,
    BUTTON_R2 = 16,
    BUTTON_L3 = 17,
    BUTTON_R3 = 18,

    BUTTON_TRIANGLE = 19,
    BUTTON_CIRCLE = 20,
    BUTTON_CROSS = 21,
    BUTTON_SQUARE = 22,

    BUTTON_PS = 23,
    BUTTON_SHARE = 24,
    BUTTON_OPTIONS = 25,
    BUTTON_TOUCHPAD = 26,

    // Achtung: Sensoren haben int16 Werte!

//	ACCEL_X = 27,
//	ACCEL_Y = 28,
//	ACCEL_Z = 29,
//	/** GYRO Z-AXIS */
//	GYRO_X = 30,
//	GYRO_Y = 31,
//	GYRO_Z = 32,
//
//	/** ACCELEROMETER X-AXIS */
//	ACCEL_XMOVE = 33,
//	/** ACCELEROMETER Z-AXIS */
//	ACCEL_ZMOVE = 34,
//	/** ACCELEROMETER Y-AXIS */
//	ACCEL_YMOVE = 35,
//
//	/** GYRO X-AXIS */
//	GYRO_XXMOVE = 36,
//	/** GYRO Z-AXIS */
//	GYRO_XZMOVE = 37,
//	/** GYRO Y-AXIS */
//	GYRO_XYMOVE = 38,
//
//	/** TEMPERATURE SENSOR */
//	TEMPMOVE = 39,
//
//	/** MAGNETOMETER X-AXIS */
//	MAGNET_XMOVE = 40,
//	/** MAGNETOMETER Z-AXIS */
//	MAGNET_ZMOVE = 41,
//	/** MAGNETOMETER Y-AXIS */
//	MAGNET_YMOVE = 42,
};

struct Ps4Data {
    byte leftHatX;
    byte leftHatY;
    byte rightHatX;
    byte rightHatY;
    byte analogL2;
    byte analogR2;

    bool downRight;
    bool downDown;
    bool downLeft;
    bool downUp;

    bool downSelect;
    bool downStart;
    bool downL1;
    bool downR1;
    bool downL2;
    bool downR2;
    bool downL3;
    bool downR3;

    bool downTriangle;
    bool downCircle;
    bool downCross;
    bool downSquare;

    bool downPs;
    bool downShare;
    bool downOptions;
    bool downTouchpad;

    // Sensors
    /** Accelerometer values */
//	byte aX;
//	byte aY;
//	byte aZ;
//	/** Gyro z-axis */
//	byte gX;
//	byte gY;
//	byte gZ;
//
//	/** Accelerometer x-axis */
//	byte aXmove;
//	/** Accelerometer z-axis */
//	byte aZmove;
//	/** Accelerometer y-axis */
//	byte aYmove;
//
//	/** Gyro x-axis */
//	byte gXmove;
//	/** Gyro z-axis */
//	byte gZmove;
//	/** Gyro y-axis */
//	byte gYmove;
//
//	/** Temperature sensor */
//	byte tempMove;
//
//	/** Magnetometer x-axis */
//	byte mXmove;
//	/** Magnetometer z-axis */
//	byte mZmove;
//	/** Magnetometer y-axis */
//	byte mYmove;
};

//struct ButtonIdToCommand {
//	ButtonEnum ps4Id;
//	char mspId;
//};

struct ButtonIdToCommandToByteValue {
    byte ps4Id;
    byte buttonId;
    byte *value;
};

//struct AnalogHatIdToCommandToByteValue {
//	byte ps4Id;
//	uint8_t* value;
//};

struct ButtonIdToCommandToBoolValue {
    byte ps4Id;
    byte buttonId;
    bool *value;
};

static Ps4Data ps4Data;

static const PROGMEM ButtonIdToCommandToBoolValue downButtons[] = {
        {L1,       BUTTON_L1,       &(ps4Data.downL1)},
        {L2,       BUTTON_L2,       &(ps4Data.downL2)},
        {L3,       BUTTON_L3,       &(ps4Data.downL3)},
        {R1,       BUTTON_R1,       &(ps4Data.downR1)},
        {R2,       BUTTON_R2,       &(ps4Data.downR2)},
        {R3,       BUTTON_R3,       &(ps4Data.downR3)},
        {TRIANGLE, BUTTON_TRIANGLE, &(ps4Data.downTriangle)},
        {CIRCLE,   BUTTON_CIRCLE,   &(ps4Data.downCircle)},
        {CROSS,    BUTTON_CROSS,    &(ps4Data.downCross)},
        {SQUARE,   BUTTON_SQUARE,   &(ps4Data.downSquare)},
        {UP,       BUTTON_UP,       &(ps4Data.downUp)},
        {RIGHT,    BUTTON_RIGHT,    &(ps4Data.downRight)},
        {DOWN,     BUTTON_DOWN,     &(ps4Data.downDown)},
        {LEFT,     BUTTON_LEFT,     &(ps4Data.downLeft)},
        {PS,       BUTTON_PS,       &(ps4Data.downPs)},
        {SHARE,    BUTTON_SHARE,    &(ps4Data.downShare)},
        {OPTIONS,  BUTTON_OPTIONS,  &(ps4Data.downOptions)},
};

static const PROGMEM ButtonIdToCommandToByteValue analogHats[] = {
        {LeftHatX,  BUTTON_LEFTHATX,  &(ps4Data.leftHatX)},
        {LeftHatY,  BUTTON_LEFTHATY,  &(ps4Data.leftHatY)},
        {RightHatX, BUTTON_RIGHTHATX, &(ps4Data.rightHatX)},
        {RightHatY, BUTTON_RIGHTHATY, &(ps4Data.rightHatY)},
};

static const PROGMEM ButtonIdToCommandToByteValue analogButtons[] = {
        {L2, BUTTON_ANALOGL2, &(ps4Data.analogL2)},
        {R2, BUTTON_ANALOGR2, &(ps4Data.analogR2)},
};

#endif
