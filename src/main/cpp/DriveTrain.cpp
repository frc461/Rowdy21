#include "DriveTrain.h"

DriveTrain::DriveTrain(Control *control){
    control = this->control;
    frc::SmartDashboard::PutNumber("ThrottleCap", 1);
    frc::SmartDashboard::PutBoolean("Arcade", false);
    
    left1 = new WPI_TalonSRX(1);
    right1 = new WPI_TalonSRX(4);

    left2 = new WPI_VictorSPX(2);
    right2 = new WPI_VictorSPX(5);

    left = new frc::SpeedControllerGroup(*left1, *left2);
    right = new frc::SpeedControllerGroup(*right1, *right2);

    driveTrain = new frc::DifferentialDrive(*left, *right);

    intakeForeward = true;

    frc::SmartDashboard::PutNumber("kp", 0);
    frc::SmartDashboard::PutNumber("ki", 0);
    frc::SmartDashboard::PutNumber("kd", 0);

    intake = new Intake();

    fDistance = 0.0f;
    switchState = 0;
    prevSwitchState = 0;

    direction = 1;
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

    switchState = control->IntakeForward();
    if (switchState != prevSwitchState && switchState == 1){
        ToggleDirection();
    }
    prevSwitchState = switchState;

    if(driveMode == DriveMode::Tank){
        driveTrain->TankDrive(direction * throttleCap*control->rightJoystickY(), direction * throttleCap*control->leftJoystickY());
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