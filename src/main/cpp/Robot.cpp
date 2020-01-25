#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
    arduino = new Arduino();
    driveTrain = new DriveTrain();
    pdp = new frc::PowerDistributionPanel();

    auto instance = nt::NetworkTableInstance::GetDefault();
    auto table = instance.GetTable("FMSInfo");

    connection = instance.IsConnected();

    colorData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

}

void Robot::RobotPeriodic() {
    if (!connection) arduino->SendData(ON_NO_COM);
    else arduino->SendData(ON_AND_COM);

    if (pdp->GetVoltage() <= 10.0) arduino->SendData(LOW_VOLT);
    //if (pdp->GetTotalCurrent() >= ) arduino->SendData(OVER_CURRENT);
}

void Robot::AutonomousInit() {
}

void Robot::AutonomousPeriodic() {
    arduino->SendData(AUTO);
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
    arduino->SendData(TELEOP);
    driveTrain->Periodic();

    switch (colorData[0]) {
    case 'R':
        arduino->SendData(ARD_RED);
        break;
    case 'G':
        arduino->SendData(ARD_GREEN);
        break;
    case 'B':
        arduino->SendData(ARD_BLUE);
        break;
    case 'Y':
        arduino->SendData(ARD_YELLOW);
        break;
    default:
        break;    
    }


}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
