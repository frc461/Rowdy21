#include "Shooter.h"


Shooter::Shooter(Control *control) {
    this->control = control;
    shooterMotor1 = new WPI_TalonFX(SHOOTER_MOTOR_1);
    shooterMotor2 = new WPI_TalonFX(SHOOTER_MOTOR_2);
    adjustingMotor = new WPI_VictorSPX(ADJUSTING_MOTOR);

    encoder = new frc::Encoder(0, 1);
    flashlight = new frc::Relay(0);
    limit = new frc::DigitalInput(LIMIT_SW);

    pid = new PID(0.0001, 0, 0, "Shooter");
    anglePID = new PID(0.002, 0, 0, "anglePID");
    motorValue1 = motorValue2 = joyValue = 0;
    shooterPos = 0;
    shooterSpeed = 0;
    frc::SmartDashboard::PutBoolean("Shooter Speed", shooterSpeed);
}
void Shooter::Rev(double speed){
        shooterMotor1->Set(speed);
        shooterMotor2->Set(-speed);
}
void Shooter::Periodic() {
    shooterSpeed = frc::SmartDashboard::GetBoolean("Shooter Speed", shooterSpeed);
    if (control->ShooterLoadUp()) {
        shooterMotor1->Set(shooterSpeed ? 0.8 : 0.6);
        shooterMotor2->Set(shooterSpeed ? -0.8 : -0.6);
        flashlight->Set(frc::Relay::Value::kReverse);
        //motorValue1 += pid->OutputPID(shooterMotor1->GetSelectedSensorVelocity(), 10000);
        //motorValue2 += pid->OutputPID(shooterMotor2->GetSelectedSensorVelocity(), -10000);
    }
    else {
        flashlight->Set(frc::Relay::Value::kOff);
        shooterMotor1->Set(0);
        shooterMotor2->Set(0);
        motorValue1 = motorValue2 = 0;
    }
    if(control->PresetPosition1()){
        shooterPos = HALF_IN_TRENCH;
    }
    else if(control->PresetPosition2()){
        shooterPos = DISCO;
    }
    else if(control->ShooterReset()){
        ZeroAlign();
    }

    if(abs(control->ManualShooterAdjustment())>0.1){
        VerticalAdjust();
        shooterPos = encoder->Get();
    }
    else{
        Angle(shooterPos);
    }
}

void Shooter::VerticalAdjust() {
    SetAdj(control->ManualShooterAdjustment()*PITCH_SPEED_CONTROL);
    frc::SmartDashboard::PutNumber("pitch Val", encoder->Get());
}
//pee pee
void Shooter::SetAdj(double speed) {
    if (!limit->Get() && speed < 0) {
        adjustingMotor->Set(0);
    }
    else {
        adjustingMotor->Set(speed);
    }
    frc::SmartDashboard::PutNumber("pitch Val", encoder->Get());
}

void Shooter::Angle(double angle){
    adjustingMotor->Set(anglePID->OutputPID(encoder->Get(), angle));
}

bool Shooter::GetLimit() {
    return limit->Get();
}

int Shooter::GetAdj(){
    frc::SmartDashboard::PutNumber("pitch Val", encoder->Get());
    return encoder->Get();
}

void Shooter::ZeroAlign() {
    SetAdj(-0.5);
    double time = frc::Timer::GetFPGATimestamp();
    while(GetLimit() && frc::Timer::GetFPGATimestamp() - time < 5) {
    }
    SetAdj(0);
    encoder->Reset();std::cout << "reset brah" << std::endl;
    frc::SmartDashboard::PutNumber("pitch Val", encoder->Get());

}