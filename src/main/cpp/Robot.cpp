#include "Robot.h"

#include <iostream>


void Robot::RobotInit() {
  left1 = new WPI_TalonSRX(3);
  right1 = new WPI_TalonSRX(12);

  left2 = new WPI_VictorSPX(4);
  left3 = new WPI_VictorSPX(5);

  right2 = new WPI_VictorSPX(1);
  right3 = new WPI_VictorSPX(2);

  left = new frc::SpeedControllerGroup(*left1, *left2, *left3);
  right = new frc::SpeedControllerGroup(*right1, *right2, *right3);

  driveTrain = new frc::DifferentialDrive(*left, *right);

  xbox = new frc::Joystick(0);
  leftJoystick = new frc::Joystick(2);
  rightJoystick = new frc::Joystick(3);

  auto table =  nt::NetworkTableInstance::GetDefault().GetTable("auto");

  ntTick = table->GetEntry("tick");
  leftSide = table->GetEntry("left");
  rightSide = table->GetEntry("right");

  straightPID = new PID(0.0004,0,0.00001);

  CSVReader reader("example.csv");

  // arduino = new Arduino();
}

void Robot::RobotPeriodic() {
 
}

void Robot::AutonomousInit() {
}

void Robot::AutonomousPeriodic() {
}

void Robot::TeleopInit() {
  right1->SetSelectedSensorPosition(0,0);
  left1->SetSelectedSensorPosition(0,0);
}

double lastEncoder;

void Robot::TeleopPeriodic() {
  tick++;
  leftSide.SetDouble(left1->GetSelectedSensorPosition());
  rightSide.SetDouble(right1->GetSelectedSensorPosition());
  ntTick.SetDouble(tick);
  if(lastEncoder != right1->GetSelectedSensorPosition()){
    std::cout << "Encoder " << right1->GetSelectedSensorPosition() << std::endl;
    lastEncoder = right1->GetSelectedSensorPosition();
  } 
  if(xbox->GetRawButton(XboxButtonA)){
    double pidpos = -straightPID->OutputPID(right1->GetSelectedSensorPosition(), -3140) + ((pidpos > 0) ? -0.09 : 0.09);
    std::cout << "PID output " << pidpos << std::endl;
    if(pidpos != 0) {
      driveTrain->ArcadeDrive(pidpos, 0);
    } else {
      driveTrain->ArcadeDrive(0,0);
    }
    
  } else {
    driveTrain->ArcadeDrive(-xbox->GetRawAxis(XboxAxisLeftStickY), -xbox->GetRawAxis(XboxAxisRightStickX));
  }
  // std::cout << right1->GetSelectedSensorPosition() << std::endl;
  //driveTrain->TankDrive(leftJoystick->GetRawAxis(yAxisJS), rightJoystick->GetRawAxis(yAxisJS));

  // uint8_t color = arduino->getColor();

  // if (color == arduino->yellow) {
  //   std::cout << "yellow" << std::endl;
  // }
  // else if (color == arduino->red) {
  //   std::cout << "red" << std::endl;
  // }
  // else if (color == arduino->blue) {
  //   std::cout << "blue" << std::endl;
  // }
  // else if (color == arduino->green) {
  //   std::cout << "green" << std::endl;
  // }
  // else if (color == arduino->something) {
  //   std::cout << "something else" << std::endl;
  // }
  // arduino->SendData(0x05);
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
