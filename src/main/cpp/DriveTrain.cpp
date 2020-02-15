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

    driveTrain = new frc::DifferentialDrive(*left, *right);

    direction = -1;
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
    std::cout << "left en: " << left1->GetSelectedSensorPosition() << std::endl;
    std::cout << "right en: " << right1->GetSelectedSensorPosition() << std::endl;

    throttleCap = 1;
    if(frc::SmartDashboard::GetBoolean("Arcade", false)) {
        driveMode = DriveMode::Arcade;
    } else {
        driveMode = DriveMode::Tank;
    }

    if(driveMode == DriveMode::Tank){
        driveTrain->TankDrive(direction * throttleCap*control->leftJoystickY(), direction * throttleCap*control->rightJoystickY());
    } else if(driveMode == DriveMode::Arcade) {
        driveTrain->ArcadeDrive(direction * throttleCap*control->rightJoystickY(), throttleCap*control->leftJoystickX());
    } else if(driveMode == DriveMode::Disabled){
        driveTrain->TankDrive(0,0);
    }
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