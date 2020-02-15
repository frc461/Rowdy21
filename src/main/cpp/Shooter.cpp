#include "Shooter.h"

Shooter::Shooter(Control *control) {
    this->control = control;
    shooterMotor1 = new WPI_TalonFX(SHOOTER_MOTOR_1);
    shooterMotor2 = new WPI_TalonFX(SHOOTER_MOTOR_2);
    adjustingMotor = new WPI_VictorSPX(ADJUSTING_MOTOR);

    pid = new PID(0.0001, 0, 0);

    motorValue1 = motorValue2 = joyValue = 0;
}

void Shooter::Periodic() {
    if (control->ShooterLoadUp()) {
        shooterMotor1->Set(0.6);
        shooterMotor2->Set(-0.6);
        //motorValue1 += pid->OutputPID(shooterMotor1->GetSelectedSensorVelocity(), 10000);
        //motorValue2 += pid->OutputPID(shooterMotor2->GetSelectedSensorVelocity(), -10000);
    }
    else {
        shooterMotor1->Set(0);
        shooterMotor2->Set(0);
        motorValue1 = motorValue2 = 0;
    }
    VerticalAdjust();
}

void Shooter::VerticalAdjust() {
    adjustingMotor->Set(control->ManualShooterAdjustment()*PITCH_SPEED_CONTROL);
}