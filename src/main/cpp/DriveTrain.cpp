#include "DriveTrain.h"

DriveTrain::DriveTrain(){
    left1 = new WPI_TalonSRX(1);
    right1 = new WPI_TalonSRX(4);

    left2 = new WPI_VictorSPX(2);

    right2 = new WPI_VictorSPX(5);

    left = new frc::SpeedControllerGroup(*left1, *left2);
    right = new frc::SpeedControllerGroup(*right1, *right2);

    driveTrain = new frc::DifferentialDrive(*left, *right);

    intakeMotor = new WPI_VictorSPX(3);

    leftJoystick = new frc::Joystick(2);
    rightJoystick = new frc::Joystick(3);

    // auto table2 =  nt::NetworkTableInstance::GetDefault().GetTable("auto");

    // ntTick = table->GetEntry("tick");
    // leftSide = table->GetEntry("left");
    // rightSide = table->GetEntry("right");

    tankDrive = true;
    arcadeDrive = false;

    auto instance = nt::NetworkTableInstance::GetDefault();
    table = instance.GetTable("limelight");
    table->PutNumber("ledMode", 1);

    frc::SmartDashboard::PutNumber("kp", 0);
    frc::SmartDashboard::PutNumber("ki", 0);
    frc::SmartDashboard::PutNumber("kd", 0);

    forwardPID = new PID(-0.07, 0.0, 0.0);
    outputPID = new PID(-1, 0, 0);

    fDistance = 0.0f;
}

void DriveTrain::Periodic() {

    frc::SmartDashboard::PutNumber("Distance", fDistance);

    if(rightJoystick->GetRawButton(8)){
        table->PutNumber("ledMode", 3);
        tx = table->GetNumber("tx", 0.0);
        ta = table->GetNumber("ta", 0.0);

        outputPID->getPIDvalues();

        fDistance = (9.68* pow(ta, 2)) - (53.1*ta) + 123;
        double Output = outputPID->OutputPID(tx, 0.0);

        double Forward = forwardPID->OutputPID(ta, 0.9);

        //double makeMove = (Forward > 0 && Forward != 0) ? 0.3 : -0.3;
        driveTrain->ArcadeDrive(/*makeMove + Forward*/0, Output);
    } 
    else if (rightJoystick->GetRawButton(9)) {
        table->PutNumber("ledMode", 3);
    }
    else {
        table->PutNumber("ledMode", 1);
        tick++;
        leftSide.SetDouble(left1->GetSelectedSensorPosition());
        rightSide.SetDouble(right1->GetSelectedSensorPosition());
        ntTick.SetDouble(tick);

        if (leftJoystick->GetRawButton(thumbSwitch) && tankDrive && !arcadeDrive) {
            tankDrive = false;;
            arcadeDrive = true;
        }
        else if (leftJoystick->GetRawButton(thumbSwitch) && !tankDrive && arcadeDrive) {
            arcadeDrive = false;
            tankDrive = true;
        }
        if (tankDrive && !arcadeDrive)
            driveTrain->TankDrive(rightJoystick->GetRawAxis(yAxisJS), leftJoystick->GetRawAxis(yAxisJS));
        else if (arcadeDrive && !tankDrive)
            driveTrain->ArcadeDrive(rightJoystick->GetRawAxis(yAxisJS), leftJoystick->GetRawAxis(xAxisJS));

        if (leftJoystick->GetRawButton(rightButton)) {
            intakeMotor->Set(0.8);
        }
        else if (rightJoystick->GetRawButton(leftButton)) {
            intakeMotor->Set(-0.8);
        }
        else {
            intakeMotor->Set(0);
        }
    }
}