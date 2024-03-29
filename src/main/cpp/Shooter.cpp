#include <Shooter.h>

Shooter::Shooter(Control *control) {
    this->control = control;

    motor1 = new WPI_TalonFX(SHOOTER_MOTOR_1);
    motor2 = new WPI_TalonFX(SHOOTER_MOTOR_2);

    flashlight = new frc::Relay(0);

    VelocityTarget = 18000; //Default velocity for shooters

    shooterPos = 0;

    tilt = new Tilt();

    /*
        Initialize shooter motors
    */

    motor1->ConfigFactoryDefault();
    motor2->ConfigFactoryDefault();

    motor1->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
    motor2->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
//lul
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

    angle = new PID(0.01, 0, 0, "anglePID");

    AdjMotor = new WPI_VictorSPX(ADJUSTING_MOTOR);
    baseVal = 2.5;

    /*
        Setup dashboard with values for presets
    */
    frc::SmartDashboard::PutNumber("Shoot V Preset 1", 653);
    frc::SmartDashboard::PutNumber("Shoot V Preset 2", 575);
    frc::SmartDashboard::PutNumber("Shoot V Preset 3", 425);

    zeroMode = true;
}

bool Shooter::Tilt::GetLimit() {
    return limit->Get();
}

/*
    Manually Run the motors, without hurting the robot
    NOTE: Use when PID cannot be trusted/used
*/

void Shooter::Tilt::RunSafe(double speed) {
    if (!GetLimit() && speed < 0) {
        AdjMotor->Set(0);
        encoder->Reset();
    }
    else {
        if((encoder->Get() < ENC_MAX && speed > 0) || speed < 0) {
            AdjMotor->Set(speed);
        } else {
            AdjMotor->Set(0);
        }
    }
}

/*
    Angle the shooter to the given position
    NOTE: Needs to be repeated
*/

bool Shooter::Tilt::SetAngle(double val) {
    if(val <= ENC_MAX && val >= 0) {
        double velocity = angle->OutputPID(encoder->Get(), val);
        // std::cout << velocity << std::endl;
        if(velocity > 1) {
            RunSafe(1);
        } 
        else if(velocity < -1) {
            RunSafe(-1);
        } 
        else {
            if(velocity < 0.1) {
                RunSafe(0);
            } else {
                RunSafe(velocity);
            }         
        }
    }
}

void Shooter::Tilt::ZeroAlign() {
    while(GetLimit()) {
        RunSafe(-0.8);
    }
    RunSafe(0);
}


double Shooter::Tilt::GetEncoder() {
    return encoder->Get();
}

bool Shooter::Tilt::Zeroing() {
    if(GetLimit()) {
        RunSafe(-0.3);
       // std::cout << "run to zero" << std::endl;
    } else {
        encoder->Reset();
        RunSafe(0);
        zeroMode = false;
    }
    return zeroMode;
}

void Shooter::Periodic() {

    //frc::SmartDashboard::PutNumber("Shooter Tilt Val", shooterPos);
    //frc::SmartDashboard::PutNumber("Shooter Speed", VelocityTarget);

    /*
        Control Portion
    */

 
    if(control->ShooterReset()) {
        if(!tilt->zeroMode){
            tilt->zeroMode = true;
        }
    }

    if(control -> ManualShooterAdjustment() < -0.2 && shooterPos < ENC_MAX){
           shooterPos += (-control -> ManualShooterAdjustment() * 10);}

   if(tilt->zeroMode) {
       tilt->Zeroing();
       shooterPos = 0;
   } else {
       if(control->PresetPosition1()) {
            shooterPos = 653;
        } else if (control->PresetPosition2()) {
            shooterPos = 575;
        } else if (control->PresetPosition3()){
            shooterPos = 425;
       } else if(control -> ManualShooterAdjustment() < -0.2 && shooterPos < ENC_MAX){
           shooterPos += (-control -> ManualShooterAdjustment() * 10);
       } else if (control -> ManualShooterAdjustment() > 0.2 && shooterPos > 0){
           shooterPos += (-control -> ManualShooterAdjustment() * 10);
       } else {
           if(shooterPos < 0) {
               shooterPos = 0;
           } else if(shooterPos > ENC_MAX) {
               shooterPos = ENC_MAX;
           }
       }
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