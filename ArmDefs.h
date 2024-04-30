#include "WeELF328P.h"
#ifndef "ARM_DEFS_H"
#define "ARM_DEFS_H" 

// Part Functional Constants

const int magnet;

const WeDCMotor elbowMotor(1);

const WeEncoderMotor wristMotor(PORT_3);
const finWeEncoderMotor shoulderMotor(PORT_4);

// Part Lengths

// Height above board
const double height = 10;

const double handLength = 6;
const double forearmLength = 8;

const double startRow = -1;
const double startColumn = -1;

const double tileSize = 2;

const int milsPerAngle = 100;

const int elbowSpeed = 100;

#endif