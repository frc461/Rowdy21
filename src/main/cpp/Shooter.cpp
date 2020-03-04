#include "Shooter.h"


Shooter::Shooter(Control *control) {
    this->control = control;
    shooterMotor1 = new WPI_TalonFX(SHOOTER_MOTOR_1);
    shooterMotor2 = new WPI_TalonFX(SHOOTER_MOTOR_2);
    adjustingMotor = new WPI_VictorSPX(ADJUSTING_MOTOR);

    encoder = new frc::Encoder(0, 1);
    flashlight = new frc::Relay(0);
    limit = new frc::DigitalInput(LIMIT_SW);

    pid = new PID(0.000001, 0, 0, "Shooter");
    anglePID = new PID(0.002, 0, 0, "anglePID");
    motorValue1 = motorValue2 = joyValue = 0;
    shooterPos = 0;
    shooterSpeed = 0;
    shooterPower = 0;
    frc::SmartDashboard::PutBoolean("Shooter Speed", shooterSpeed);
    frc::SmartDashboard::PutNumber("Shoot RPM", minShootRPM);
    frc::SmartDashboard::PutNumber("shooterPower", shooterPower);

    shooterMotor1->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
    shooterMotor2->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);

    shooterMotor1->ConfigMotionCruiseVelocity(1500, 10);
    shooterMotor1->ConfigMotionAcceleration(1500, 10);

    shooterMotor1->SetSelectedSensorPosition(0,0,10);
    shooterMotor2->SetSelectedSensorPosition(0,0,10);
}
void Shooter::Rev(double speed){
        shooterMotor1->Set(speed);
        shooterMotor2->Set(-speed);
}
void Shooter::Periodic() {
    frc::SmartDashboard::PutNumber("pitch Val", encoder->Get());
    frc::SmartDashboard::GetNumber("shooterPower", shooterPower);
    pid->getPIDvalues();
    // std::cout<<encoder->Get()<<std::endl;
    shooterSpeed = frc::SmartDashboard::GetBoolean("Shooter Speed", shooterSpeed);
    minShootRPM = frc::SmartDashboard::GetNumber("Shoot RPM", minShootRPM);
    if (control->ShooterLoadUp()) {
        //shooterMotor1->Set(ControlMode::PercentOutput, shooterSpeed ? (shooterPower)*-1 : (shooterPower - 0.2)*-1);
        //shooterMotor2->Set(ControlMode::PercentOutput, shooterSpeed ? shooterPower : shooterPower - 0.2);
        flashlight->Set(frc::Relay::Value::kReverse);
        // motorValue1 += pid->OutputPID(shooterMotor1->GetSelectedSensorVelocity(), shooterSpeed ? minShootRPM : 0);
        // motorValue2 += pid->OutputPID(shooterMotor2->GetSelectedSensorVelocity(), shooterSpeed ? -minShootRPM : 0);
         shooterMotor1->Set(0.8);
         shooterMotor2->Set(-0.8);
    }
    else {
        //frc::SmartDashboard::PutNumber("encoderVal", autoDelay);
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
    else if (control->PresetPosition3()) {
        shooterPos = THIRD_PRESET; // TODO: THIRD PRESET not set to any value rn
    }
    else if(control->ShooterReset()){
        ZeroAlign();
    }

    if(abs(control->ManualShooterAdjustment())>0.1||abs(control->ManualShooterAdjustment() < -0.1)){
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