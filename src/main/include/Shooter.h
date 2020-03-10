#pragma once

#include <ctre/Phoenix.h>

#include "PID.h"
#include "Controls.h"

#include <frc/DigitalInput.h>
#include <frc/Encoder.h>
#include <frc/Timer.h>
#include <frc/DigitalOutput.h>
#include <frc/AnalogInput.h>
#include <frc/Relay.h>

#define SHOOTER_MOTOR_1 5
#define SHOOTER_MOTOR_2 6
#define ADJUSTING_MOTOR 12

#define PITCH_SPEED_CONTROL 0.5

#define LIMIT_SW 6

#define MAX_ANGLE 0.314

/*
    HERE ARE THE PRESETS!!!!
*/

#define HALF_IN_TRENCH 0.205
#define DISCO 1//angle is shy of target 0.6 power
#define THIRD_PRESET 1




#define ON_INIT_LINE 1012

class Shooter
{
public:
    Shooter(Control *control);

    Control *control;

    WPI_TalonFX *motor1;
    WPI_TalonFX *motor2;

    frc::Relay *flashlight;

    void Periodic();

    void SetFlashlight(bool value);

    void RunAtVelocity(double velocity);
    void RunAtSpeed(double speed);

    double shooterPos;

    class Tilt {
        public:
            Tilt();

            void ZeroAlign();
            void RunSafe(double speed);
            void SetAngle(double speed);

            double GetEncoder();
            double GetPotVal();
            double baseVal;
            WPI_VictorSPX *AdjMotor;
        private:
            frc::Encoder *encoder;
            frc::DigitalInput *limit;
            frc::AnalogInput *triPot;
            PID *angle;

            bool GetLimit();
    };

    Tilt *tilt;

   
private:
    double VelocityTarget;

};