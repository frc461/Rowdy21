#include "DriveTrain.h"

DriveTrain::DriveTrain(Control *control){
    this->control = control;
    frc::SmartDashboard::PutBoolean("Arcade", true);
    
    left1 = new WPI_TalonSRX(DTL1);
    right1 = new WPI_TalonSRX(DTR1);

    left2 = new WPI_TalonSRX(DTL2);
    right2 = new WPI_TalonSRX(DTR2);

    left = new frc::SpeedControllerGroup(*left1, *left2);
    right = new frc::SpeedControllerGroup(*right1, *right2);

    gyro = new frc::ADXRS450_Gyro(frc::SPI::Port::kOnboardCS0);

    driveTrain = new frc::DifferentialDrive(*left, *right);

    autoPIDLeft = new PID(-0.0003, 0, 0, "D: autoTest_L");
    autoPIDRight = new PID(0.0003 , 0, 0, "D: autoTest_R");

    leftPower = rightPower = 0.0;

    ResetEncoders();

    direction = -1;
}

void DriveTrain::EnableBreakMode(){
    left1->SetNeutralMode(NeutralMode::Brake);
    left2->SetNeutralMode(NeutralMode::Brake);
    right1->SetNeutralMode(NeutralMode::Brake);
    right2->SetNeutralMode(NeutralMode::Brake);
}

void DriveTrain::DisableBreakMode() {
    left1->SetNeutralMode(NeutralMode::Coast);
    left2->SetNeutralMode(NeutralMode::Coast);
    right1->SetNeutralMode(NeutralMode::Coast);
    right2->SetNeutralMode(NeutralMode::Coast);
}

void DriveTrain::ResetGyro() {
    gyro->Reset();
}

double DriveTrain::GetAngle() {
    return gyro->GetAngle();
}

void DriveTrain::ResetEncoders() {
    right1->SetSelectedSensorPosition(0, 0);
    left1->SetSelectedSensorPosition(0, 0);
}

double DriveTrain::GetEncoderValueL() {
    return left1->GetSelectedSensorPosition();
}
double DriveTrain::GetEncoderValueR() {
    return right1->GetSelectedSensorPosition();
}

void DriveTrain::Periodic() {
    throttleCap = 1;
    if(frc::SmartDashboard::GetBoolean("Arcade", false)) {
        driveMode = DriveMode::Arcade;
    } else {
        driveMode = DriveMode::Tank;
    }
    if(driveMode == DriveMode::Tank){
        double l = direction * throttleCap*control->leftJoystickY();
        double r =  direction * throttleCap*control->rightJoystickY();
        leftPower = l;
        rightPower = r;
        driveTrain->TankDrive(l,r);
    } else if(driveMode == DriveMode::Arcade) {
        driveTrain->ArcadeDrive(direction * throttleCap*control->rightJoystickY(), throttleCap*control->leftJoystickX());
    } else if(driveMode == DriveMode::Disabled){
        driveTrain->TankDrive(0,0);
    }
}

double DriveTrain::GetLeftPower() {
    return leftPower;
}
double DriveTrain::GetRightPower() {
    return rightPower;
}

void DriveTrain::SetDriveMode(DriveMode mode) {
    if(mode == DriveMode::Arcade){
        driveMode = DriveMode::Arcade;
    } else if(mode == DriveMode::Tank) {
        driveMode = DriveMode::Tank;
    } else if(mode == DriveMode::Disabled){
        driveMode = DriveMode::Disabled;
    }
}

void DriveTrain::ToggleDriveMode() {
    if(driveMode == DriveMode::Tank) {
        driveMode = DriveMode::Arcade;
    } else {
        driveMode = DriveMode::Tank;
    }
}