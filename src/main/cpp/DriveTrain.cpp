#include "DriveTrain.h"

DriveTrain::DriveTrain(){
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

    auto instance = nt::NetworkTableInstance::GetDefault();
    table = instance.GetTable("limelight");
    table->PutNumber("ledMode", 1);

    frc::SmartDashboard::PutNumber("kp", 0);
    frc::SmartDashboard::PutNumber("ki", 0);
    frc::SmartDashboard::PutNumber("kd", 0);

    control = new Control();
    intake = new Intake();

    forwardPID = new PID(-0.07, 0.0, 0.0);
    outputPID = new PID(-1, 0, 0);

    fDistance = 0.0f;
    switchState = 0;
    prevSwitchState = 0;
}

void DriveTrain::Periodic() {
    throttleCap = frc::SmartDashboard::GetNumber("ThrottleCap", 1);
    driveMode = frc::SmartDashboard::GetBoolean("Arcade", false);
    //frc::SmartDashboard::PutNumber("Distance", fDistance);

    if(control->LimelightAiming()){
        table->PutNumber("ledMode", 3);
        tx = table->GetNumber("tx", 0.0);
        ta = table->GetNumber("ta", 0.0);

        outputPID->getPIDvalues();

        //fDistance = (9.68* pow(ta, 2)) - (53.1*ta) + 123;
        double Output = outputPID->OutputPID(tx, 0.0);

        double Forward = forwardPID->OutputPID(ta, 0.9);

        //double makeMove = (Forward > 0 && Forward != 0) ? 0.3 : -0.3;
        driveTrain->ArcadeDrive(/*makeMove + Forward*/0, Output);
    } 
    else if (control->LimelightLightActivate()) {
        table->PutNumber("ledMode", 3);
    }
    else {
        table->PutNumber("ledMode", 1);
        tick++;
        leftSide.SetDouble(left1->GetSelectedSensorPosition());
        rightSide.SetDouble(right1->GetSelectedSensorPosition());
        ntTick.SetDouble(tick);

     /*   if (leftJoystick->GetRawButton(thumbSwitch)) {
            intakeForeward = 1;
        }
        else if (rightJoystick->GetRawButton(thumbSwitch)){
            intakeForeward = 0;
        }
        */
        switchState = control->IntakeForward();
        if (switchState != prevSwitchState && switchState == 1){
            intakeForeward = !intakeForeward;
        }
        prevSwitchState = switchState;

        if (intakeForeward){
            if (!driveMode)
                driveTrain->TankDrive(throttleCap*control->rightJoystickY(), throttleCap*control->leftJoystickY());
            else
                driveTrain->ArcadeDrive(throttleCap*control->rightJoystickY(), throttleCap*control->leftJoystickX());
        }
        else{
            if (!driveMode)
                driveTrain->TankDrive(-throttleCap*control->leftJoystickY(), -throttleCap*control->rightJoystickY());
            else 
                driveTrain->ArcadeDrive(-throttleCap*control->rightJoystickY(), throttleCap*control->leftJoystickX());
        }
        intake->Periodic();
    }
}