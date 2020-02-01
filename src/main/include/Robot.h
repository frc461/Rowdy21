#pragma once

#include <string>

#include <frc/WPILib.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>

#include <ctre/Phoenix.h>

#include "XboxJoystickMap.h"
#include "ThrustMasters.h"
#include "Arduino.h"
#include "PID.h"


class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  WPI_VictorSPX *right2, *right3, *left2, *left3;
  WPI_TalonSRX *right1, *left1;

  frc::SpeedControllerGroup *left;
  frc::SpeedControllerGroup *right;

  frc::DifferentialDrive *driveTrain;

  frc::Joystick *xbox;
  frc::Joystick *leftJoystick;
  frc::Joystick *rightJoystick;

  nt::NetworkTableEntry leftSide;
  nt::NetworkTableEntry rightSide;
  nt::NetworkTableEntry ntTick;
  std::shared_ptr<nt::NetworkTable> table;

  int tick;

  Arduino *arduino;

  PID *straightPID;

  std::vector<std::string> split(std::string toSplit, char delimiter);
};
