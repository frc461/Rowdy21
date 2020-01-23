#include "DriveTrain.h"

DriveTrain::DriveTrain(){
    RMotor0 = new WPI_TalonSRX(CanChain::R_Motor0);
    RMotor1 = new WPI_VictorSPX(CanChain::R_Motor1);

    LMotor0 = new WPI_TalonSRX(CanChain::L_Motor0);
    LMotor1 = new WPI_VictorSPX(CanChain::L_Motor1);

    DTLeft = new frc::SpeedControllerGroup(*LMotor0, *LMotor1);
    DTRight = new frc::SpeedControllerGroup(*RMotor0, *RMotor1);

    driveTrain = new frc::DifferentialDrive(*DTLeft, *DTRight);

    table = NetworkTable::GetTable("limelight");

    xbox = new frc::Joystick(0);

    forwardPID = new PID(-0.07, 0.0, 0.0);
    outputPID = new PID(-0.1, 0.0, 0.0);

    fDistance = 0.0f;

    //smartDashboard = new SmartDashboard();
}

void DriveTrain::Periodic() {
    tx = table->GetNumber("tx", 0.0);
    ta = table->GetNumber("ta", 0.0);

    double Output = outputPID->OutputPID(tx, 0.0);

    double Forward = forwardPID->OutputPID(ta, 0.9);

    std::cout << "Forward: " << Forward << std::endl;

    fDistance = (9.68* pow(ta, 2)) - (53.1*ta) + 123;

    frc::SmartDashboard::PutNumber("Distance", fDistance);

    std::cout << "Distance: " << fDistance << "\n";

    if(xbox->GetRawButton(XboxJoystickButton::XboxButtonB)){
        std::cout << "Output: " << Output << std::endl;

        double makeMove = (Forward > 0 && Forward != 0) ? 0.3 : -0.3;
        // if (tx > 0) {
        //     std::cout << "Right" << std::endl;
        //     // Turn Right
        //     driveTrain->TankDrive((-tx)*0.1, tx*0.1);
        //     driveTrain->ArcadeDrive(Forward, Output);

        // } else if (tx < 0) {
        //     std::cout << "Left" << std::endl;
        //     // Turn Left
        //     driveTrain->TankDrive((tx)*0.1, (-tx)*0.1);
        //     driveTrain->ArcadeDrive(Forward, Output);
        // } else {
        //     driveTrain->ArcadeDrive(0, 0);
        // }
        driveTrain->ArcadeDrive(makeMove + Forward, Output);
    } 
    else {
        driveTrain->TankDrive(0,0);
    }
}