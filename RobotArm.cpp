#include "WeELF328P.h"
#include <Math.h>
#include "ArmDefs.h"

const double elbowAngles[8][4];
const double wristAngles[8][4];
const double shoulderAngles[8][4];

double elbowAngle = 0;

void setup() {
    pinMode(magnet, OUTPUT);
    wristMotor.setPositionOrigin();
    shoulderMotor.setPositionOrigin();

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; i++)
        {
            elbowAngles[i][j] = elbowAngle(i, j);
            wristAngles[i][j] = wristAngle(i, j);
            shoulderAngles[i][j] = shoulderAngle(i, j);
        }
    }
    
}

void loop() {
}

void move(int columnFrom, int rowFrom, int columnTo, int rowTo) {
    goToPosition(columnFrom, rowFrom);
    lowerWrist(columnFrom, rowTo);
    digitalWrite(magnet, HIGH);
    reset();
    goToPosition(columnTo, rowTo);
    lowerWrist(columnTo, rowTo);
    digitalWrite(magnet, LOW);
    reset();
    if (rowFrom-rowTo == 2 || rowTo-rowFrom == -2) {
        move((columnFrom+columnTo)/2, (rowFrom+rowTo)/2, 0, -3);
    }
}

void reset() {
    wristMotor.moveTo(0);
    shoulderAngle.moveTo(0);
    elbowMotor.run(-elbowSpeed);
    delay(elbowAngle*milsPerAngle);
    elbowMotor.run(0);
    elbowAngle = 0;
}

void goToPosition(int column, int row) {
    wristMotor.moveTo(-10);
    shoulderMotor.moveTo(shoulderAngles[row][column/2]);
    newElbowAngle = elbowAngles[row][column/2];
    elbowMotor.run(elbowSpeed);
    delay((newElbowAngle-elbowAngle)*milsPerAngle);
    elbowMotor.run(0);
    elbowAngle = newElbowAngle;
}

void lowerWrist(int column, int row) {
    wristMotor.moveTo(wristAngles[row][column/2]);
}

double wristAngle(int i, int j) {
    int x = j - startColumn;
    int y = i - startRow;

    return Math.acos((handLength*handLength + forearmLength*forearmLength - height*height - x*x - y*y)/2/forearmLength/handLength);
}

double elbowAngle(int i, int j) {
    int x = j - startColumn;
    int y = i - startRow;

    return Math.atan2(Math.sqrt(x*x + y*y), h) + Math.asin(handLength*Math.sin(wristAngles[i][j])/Math.sqrt(x*x + y*y + h*h));
}

double shoulderAngle(int i, int j){
    int x = j - startColumn;
    int y = i - startRow;

    return Math.atan2(y, x);
}