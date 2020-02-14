#include "DriveTrain.h"

DriveTrain::DriveTrain(Control *control){
    this->control = control;
    frc::SmartDashboard::PutNumber("ThrottleCap", 1);
    frc::SmartDashboard::PutBoolean("Arcade", false);
    
    left1 = new WPI_TalonSRX(DTL1);
    right1 = new WPI_TalonSRX(DTR1);

    left2 = new WPI_TalonSRX(DTL2);
    right2 = new WPI_TalonSRX(DTR2);

    left = new frc::SpeedControllerGroup(*left1, *left2);
    right = new frc::SpeedControllerGroup(*right1, *right2);

    driveTrain = new frc::DifferentialDrive(*left, *right);

    intakeForeward = true;

    frc::SmartDashboard::PutNumber("kp", 0);
    frc::SmartDashboard::PutNumber("ki", 0);
    frc::SmartDashboard::PutNumber("kd", 0);

    fDistance = 0.0f;
    switchState = 0;
    prevSwitchState = 0;

    direction = -1;
}

void DriveTrain::Periodic() {
    throttleCap = frc::SmartDashboard::GetNumber("ThrottleCap", 1);
    if(frc::SmartDashboard::GetBoolean("Arcade", false)) {
        driveMode = DriveMode::Arcade;
    } else {
        driveMode = DriveMode::Tank;
    }
    // else {
    //     table->PutNumber("ledMode", 1);
    //     tick++;
    //     leftSide.SetDouble(left1->GetSelectedSensorPosition());
    //     rightSide.SetDouble(right1->GetSelectedSensorPosition());
    //     ntTick.SetDouble(tick);

    //     if (intakeForeward){
    //         if (!driveMode)
    //             driveTrain->TankDrive(throttleCap*control->rightJoystickY(), throttleCap*control->leftJoystickY());
    //         else
    //             driveTrain->ArcadeDrive(throttleCap*control->rightJoystickY(), throttleCap*control->leftJoystickX());
    //     }
    //     else{
    //         if (!driveMode)
    //             driveTrain->TankDrive(-throttleCap*control->leftJoystickY(), -throttleCap*control->rightJoystickY());
    //         else 
    //             driveTrain->ArcadeDrive(-throttleCap*control->rightJoystickY(), throttleCap*control->leftJoystickX());
    //     }
    // }

    // switchState = control->IntakeForward();
    // if (switchState != prevSwitchState && switchState == 1){
    //     ToggleDirection();
    // }
    prevSwitchState = switchState;

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

void DriveTrain::ToggleDirection() {
    if(direction == 1) {
        direction = -1;
    } else if(direction == -1) {
        direction = 1;
    }
}