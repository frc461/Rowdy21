#include <Shooter.h>

Shooter::Shooter(Control *control) {
    this->control = control;

    motor1 = new WPI_TalonFX(SHOOTER_MOTOR_1);
    motor2 = new WPI_TalonFX(SHOOTER_MOTOR_2);

    flashlight = new frc::Relay(0);

    VelocityTarget = 16000; //Default velocity for shooters

    shooterPos = 0;

    tilt = new Tilt();

    /*
        Initialize shooter motors
    */

    motor1->ConfigFactoryDefault();
    motor2->ConfigFactoryDefault();

    motor1->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
    motor2->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);

    motor1->SetSensorPhase(true);
    motor2->SetSensorPhase(true);

    motor1->ConfigNominalOutputForward(0, 10);
    motor1->ConfigNominalOutputReverse(0, 10);
    motor1->ConfigPeakOutputForward(0.8, 10);
    motor1->ConfigPeakOutputReverse(-0.8, 10);

    motor2->ConfigNominalOutputForward(0, 10);
    motor2->ConfigNominalOutputReverse(0, 10);
    motor2->ConfigPeakOutputForward(0.8, 10);
    motor2->ConfigPeakOutputReverse(-0.8, 10);

    motor1->Config_kF(0, -0.05, 10);
    motor1->Config_kP(0, -.3, 10);
    motor1->Config_kI(0, 0, 10);
    motor1->Config_kD(0, 0, 10);

    frc::SmartDashboard::PutNumber("shooterkF", -0.1);
    frc::SmartDashboard::PutNumber("shooterkP", 0);
    frc::SmartDashboard::PutNumber("shooterkI", 0);
    frc::SmartDashboard::PutNumber("shooterkD", 0);



    motor2->Config_kF(0, -frc::SmartDashboard::GetNumber("shooterkF", 0), 10);
    motor2->Config_kP(0, -frc::SmartDashboard::GetNumber("shooterkP", 0), 10);
    motor2->Config_kI(0, -frc::SmartDashboard::GetNumber("shooterkI", 0), 10);
    motor2->Config_kD(0, -frc::SmartDashboard::GetNumber("shooterkD", 0), 10);

}

/*
    Simplify the configuration for the relay
*/

void Shooter::SetFlashlight(bool state) {
    if(state) {
        flashlight->Set(frc::Relay::Value::kForward);
    } else {
        flashlight->Set(frc::Relay::Value::kOff);
    }
}

void Shooter::RunAtVelocity(double velocity) {
    motor1->Set(ControlMode::Velocity, -velocity);
    motor2->Set(ControlMode::Velocity, -velocity);
}

void Shooter::RunAtSpeed(double speed) {
    motor1->Set(speed);
    motor2->Set(speed);
}

Shooter::Tilt::Tilt() {
    encoder = new frc::Encoder(0, 1);
    limit = new frc::DigitalInput(LIMIT_SW);

    frc::SmartDashboard::PutNumber("pitch Val", (encoder->Get() - baseVal));

    angle = new PID(8, 0, 0, "anglePID");

    triPot = new frc::AnalogInput(0);

    AdjMotor = new WPI_VictorSPX(ADJUSTING_MOTOR);
    baseVal = 0.327;

    /*
        Setup dashboard with values for presets
    */
    frc::SmartDashboard::PutNumber("Shoot V Preset 1", 16000);
    frc::SmartDashboard::PutNumber("Shoot V Preset 2", 16000);
    frc::SmartDashboard::PutNumber("Shoot V Preset 3", 16000);
}

bool Shooter::Tilt::GetLimit() {
    return limit->Get();
}

double Shooter::Tilt::GetPotVal() {
    return triPot->GetVoltage();
}

/*
    Manually Run the motors, without hurting the robot
    NOTE: Use when PID cannot be trusted/used
*/

void Shooter::Tilt::RunSafe(double speed) {
    if (!GetLimit() && speed < 0) {
        AdjMotor->Set(0);
    }
    else {
        AdjMotor->Set(speed);
    }
    frc::SmartDashboard::PutNumber("pitch Val", (triPot->GetVoltage() - baseVal));
}

/*
    Angle the shooter to the given position
*/

void Shooter::Tilt::SetAngle(double val) {
   RunSafe(angle->OutputPID(triPot->GetVoltage(), (val + baseVal)));
}

void Shooter::Tilt::ZeroAlign() {
    double time = frc::Timer::GetFPGATimestamp();
    while(GetLimit() && frc::Timer::GetFPGATimestamp() - time < 5) {
        RunSafe(-0.3);
    }
    RunSafe(0);
    baseVal = triPot->GetVoltage();
    // encoder->Reset();
    // frc::SmartDashboard::PutNumber("pitch Val", encoder->Get());
}


double Shooter::Tilt::GetEncoder() {
    return encoder->Get();
}

void Shooter::Periodic() {
    /*
        Control Portion
    */

   frc::SmartDashboard::PutNumber("Shooter Angle Tri Pot", tilt->GetPotVal());

   if(control->PresetPosition1()) {
       VelocityTarget = frc::SmartDashboard::GetNumber("Shoot V Preset 1", 16000);
       shooterPos = 0.4;
   } else if (control->PresetPosition2()) {
       VelocityTarget = frc::SmartDashboard::GetNumber("Shooter V Preset 2", 16000);
       shooterPos = DISCO;
   } else if(control->PresetPosition3()) {
       VelocityTarget = frc::SmartDashboard::GetNumber("Shooter V Preset 3", 16000);
       shooterPos = THIRD_PRESET;
   } else if(control->ShooterReset()) {
      tilt->ZeroAlign();
   } else if(fabs(control->ManualShooterAdjustment())>0.1) {
       std::cout << control->ManualShooterAdjustment() << std::endl;
       tilt->RunSafe(control->ManualShooterAdjustment()*PITCH_SPEED_CONTROL);
       shooterPos = tilt->GetPotVal() - tilt->baseVal;
   } else {
        tilt->SetAngle(shooterPos);
   }

   /* 
        Running Shooter Motors
    */

    if(control->ShooterLoadUp()) {
        SetFlashlight(1);
        RunAtVelocity(VelocityTarget);
    } else {
        SetFlashlight(0);
        RunAtSpeed(0);
    }
}