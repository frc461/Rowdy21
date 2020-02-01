#pragma once

#include <iostream>

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>

#include "PID.h"
#include "Controls.h"
#include "DriveTrain.h"

class Limelight
{
public:
    Limelight(Control *control, DriveTrain *driveTrain);

    void LimelightAiming();
    void LimelightActivate();

    void Periodic();

    void SetLimelightLight(bool state);

private:
    std::shared_ptr<nt::NetworkTable> table;

    float tx;
    float ta;

    double Output;
    double Forward;

    PID *forwardPID;
    PID *outputPID;

    Control *control;

    DriveTrain *drTrain;
};