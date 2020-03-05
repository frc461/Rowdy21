#include "Shooter.h"


Shooter::Shooter(Control *control) {
    this->control = control;
    shooterMotor1 = new WPI_TalonFX(SHOOTER_MOTOR_1);
    shooterMotor2 = new WPI_TalonFX(SHOOTER_MOTOR_2);
    adjustingMotor = new WPI_VictorSPX(ADJUSTING_MOTOR);

    encoder = new frc::Encoder(0, 1);
    flashlight = new frc::Relay(0);
    limit = new frc::DigitalInput(LIMIT_SW);

    anglePID = new PID(0.002, 0, 0, "anglePID");
    motorValue1 = motorValue2 = joyValue = 0;
    shooterPos = 0;
    shooterSpeed = 0;
    shooterPower = 0;
    frc::SmartDashboard::PutBoolean("Shooter Speed", shooterSpeed);
    frc::SmartDashboard::PutNumber("Shoot RPM", minShootRPM);
    frc::SmartDashboard::PutNumber("shooterPower", shooterPower);

    frc::SmartDashboard::PutNumber("shooterkF", -0.1);
    frc::SmartDashboard::PutNumber("shooterkP", 0);
    frc::SmartDashboard::PutNumber("shooterkI", 0);
    frc::SmartDashboard::PutNumber("shooterkD", 0);

    shooterMotor1->ConfigFactoryDefault();
    shooterMotor2->ConfigFactoryDefault();

    shooterMotor1->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
    shooterMotor2->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
    
    shooterMotor1->SetSensorPhase(true);
    shooterMotor2->SetSensorPhase(true);

    shooterMotor1->ConfigNominalOutputForward(0, 10);
    shooterMotor1->ConfigNominalOutputReverse(0, 10);
    shooterMotor1->ConfigPeakOutputForward(0.8, 10);
    shooterMotor1->ConfigPeakOutputReverse(-0.8, 10);

    shooterMotor2->ConfigNominalOutputForward(0, 10);
    shooterMotor2->ConfigNominalOutputReverse(0, 10);
    shooterMotor2->ConfigPeakOutputForward(0.8, 10);
    shooterMotor2->ConfigPeakOutputReverse(-0.8, 10);

    // shooterMotor1->SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, 10, 10);
    // shooterMotor1->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, 10);

    // shooterMotor2->SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, 10, 10);
    // shooterMotor2->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, 10);

    
    // shooterMotor1->ConfigMotionCruiseVelocity(1500, 10);
    // shooterMotor1->ConfigMotionAcceleration(1500, 10);

    // shooterMotor1->SetSelectedSensorPosition(0,0,10);
    // shooterMotor2->SetSelectedSensorPosition(0,0,10);
}
void Shooter::Rev(double speed){
        shooterMotor1->Set(speed);
        shooterMotor2->Set(-speed);
}
void Shooter::Periodic() {
    shooterMotor1->Config_kF(0, -0.05, 10);
    shooterMotor1->Config_kP(0, -.3, 10);
    shooterMotor1->Config_kI(0, 0, 10);
    shooterMotor1->Config_kD(0, 0, 10);

    shooterMotor2->Config_kF(0, -frc::SmartDashboard::GetNumber("shooterkF", 0), 10);
    shooterMotor2->Config_kP(0, -frc::SmartDashboard::GetNumber("shooterkP", 0), 10);
    shooterMotor2->Config_kI(0, -frc::SmartDashboard::GetNumber("shooterkI", 0), 10);
    shooterMotor2->Config_kD(0, -frc::SmartDashboard::GetNumber("shooterkD", 0), 10);

    frc::SmartDashboard::PutNumber("pitch Val", encoder->Get());
    frc::SmartDashboard::GetNumber("shooterPower", shooterPower);
    // std::cout<<encoder->Get()<<std::endl;
    shooterSpeed = frc::SmartDashboard::GetBoolean("Shooter Speed", shooterSpeed);
    minShootRPM = frc::SmartDashboard::GetNumber("Shoot RPM", minShootRPM);
    if (control->ShooterLoadUp()) {
        //shooterMotor1->Set(ControlMode::PercentOutput, shooterSpeed ? (shooterPower)*-1 : (shooterPower - 0.2)*-1);
        //shooterMotor2->Set(ControlMode::PercentOutput, shooterSpeed ? shooterPower : shooterPower - 0.2);
        flashlight->Set(frc::Relay::Value::kForward);
        // motorValue1 += pid->OutputPID(shooterMotor1->GetSelectedSensorVelocity(), shooterSpeed ? minShootRPM : 0);
        // motorValue2 += pid->OutputPID(shooterMotor2->GetSelectedSensorVelocity(), shooterSpeed ? -minShootRPM : 0);
        //  shooterMotor1->Set(0.8);
        //  shooterMotor2->Set(-0.8);
        // double velocityTarget = 0.25 * 5000 * 1023 / (600 * 3.4);
        double velocityTarget = 16000;
        shooterMotor1->Set(ControlMode::Velocity, -velocityTarget);
        // shooterMotor1->Set(ControlMode::Velocity, -velocityTarget);
        shooterMotor2->Set(ControlMode::Velocity, -velocityTarget);
        _sb.append("\nTarget: ");
        _sb.append(std::to_string(velocityTarget));
        _sb.append(" ");
        _sb.append("Velocity: ");
        _sb.append(std::to_string(shooterMotor1->GetSelectedSensorVelocity()));
        // _sb.append(" ");
        // _sb.append(std::to_string(shooterMotor2->GetSelectedSensorVelocity()));
        // _sb.append("   ");
        _sb.append(" Motor Percent: ");
        _sb.append(std::to_string(shooterMotor1->GetMotorOutputPercent()));
        // _sb.append(" ");
        // _sb.append(std::to_string(shooterMotor2->GetMotorOutputPercent()));
        // _sb.append("\nShooter 1 Native:");
        // _sb.append(std::to_string(shooterMotor1->GetClosedLoopError(0)));
        // _sb.append("\n Shooter 1 Target: ");
        // _sb.append(std::to_string(velocityTarget));
        _sb.append("\n");

        
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

    if(++_loops >= 10) {
        _loops = 0;
        printf("%s\n", _sb.c_str());
        _sb = "";
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