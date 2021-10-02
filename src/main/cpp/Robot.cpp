#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#include "cameraserver/CameraServer.h"

void Robot::RobotInit() {
    control = new Control();

    driveTrain = new DriveTrain(control);
    intake = new Intake(control);
    limelight = new Limelight(control, driveTrain);
    shooter = new Shooter(control);
    conveyor = new Conveyor(control);
    climber = new Climber(control);
    djSpinner = new DJ_Spinner(control);
    //arduino = new Arduino();

    driveTrain->ResetGyro();
    driveTrain->ResetEncoders();

    climber->ClimberBrakeOn();

    drivePID = new PID(0.0003, 0.0, 0.0, "dpid");
    turnPID = new PID(0.085, 0.0, 0.0, "tpid");

    frc::SmartDashboard::PutBoolean("AUTO_VISION_TRACK", true);
}

void Robot::RobotPeriodic() {}

void Robot::DisabledInit() {
    counter = 0;
}

bool Robot::Go(int inches, int dir) {
    double l = std::min(0.7, drivePID->OutputPID(abs(driveTrain->GetEncoderValueL()), inches*ENCODER_INCH));
    double r = std::min(0.7, drivePID->OutputPID(abs(driveTrain->GetEncoderValueR()), inches*ENCODER_INCH));
    driveTrain->driveTrain->TankDrive(dir*l,dir*r);

    sumGo += abs(driveTrain->GetEncoderValueR());
    nGo++;
    int avg = sumGo / nGo;
    //std::cout << avg << " " << abs(inches*ENCODER_INCH) << std::endl;

    return (abs(abs(inches*ENCODER_INCH) - avg) < 100);
}

bool Robot::Turn(double degs) {
    double p = std::min(1.0, turnPID->OutputPID(driveTrain->GetAngle(), degs));
    //std::cout << driveTrain->GetAngle() << " " << degs << std::endl;
    driveTrain->driveTrain->TankDrive(p, -p);

    sumTurn += abs(driveTrain->GetAngle());
    nTurn++;
    double avg = sumTurn / nTurn;
    //std::cout<<abs(degs)<<" "<< avg << std::endl;
    return (abs(abs(degs) - avg) < 3);
}

void Robot::StartCounter() {
    while (!finished) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        counter++;
    }
}

void Robot::AutonomousInit() {
    timer = new frc::Timer();
    driveTrain->ResetGyro();
    driveTrain->ResetEncoders();

    counter = sumGo = nGo = sumTurn = nTurn = 0;
    shot = true;
    secondShoot = false;
    step1 = true;
    setAngle = false;
    shooterSpeed = 10000;
    
    driveTrain->EnableBreakMode();

    sCount = true;
    finished = false;
    comeBack = false;
    turnedOnce = false;
    s= true;
    reset = false;
}

//( ͡° ͜ʖ ͡°)
void Robot::AutonomousPeriodic() {
    if (!shot){
        /*if (frc::SmartDashboard::GetBoolean("AUTO_VISION_TRACK", true)) {
            std::cout << "TRACC ON" << std::endl;
            //limelight->SetLimelightLight(1);
            //limelight->LimelightAiming();
        }*/

        if (step1) {
            shooter->tilt->ZeroAlign();
            step1 = false;
        }
        else {
            if (!setAngle) encVal = shooter->tilt->GetEncoder();
            setAngle = true;

            if (shooter->tilt->GetEncoder() < encVal+720) shooter->tilt->RunSafe(0.7);
            else shooter->tilt->RunSafe(0.0);

            shooter->RunAtVelocity(shooterSpeed);

            if (sCount) { timer->Reset(); timer->Start(); } 
            sCount = false;
            if (timer->Get() >= 3.0 && timer->Get() <= 4.0) {
                conveyor->Up();
            }
            else if (timer->Get() > 4.0) {
                conveyor->No();
                shooter->RunAtVelocity(0);
                shot = sCount = true;
            }
        }
    }
    else if (shot && secondShoot) {
        finished = true;
    }
    else {
        while(!Turn(ROTATE_ANGLE)){}
        
        if (!reset){
            nTurn = 0;
            //intake->AutoRun();
            
            //intake->SetPosition(true);
            
            driveTrain->ResetEncoders();

            timer->Reset();
            timer->Start();

            reset = true;
        }
        std::cout << timer->Get() << std::endl;
        // else if (reset && timer->Get() > 1 && !comeBack) {
        //     if (Go(GO_DISTANCE,-1)) {
        //         nGo = 0;
        //         driveTrain->ResetEncoders();

        //         timer.Reset();
        //         timer.Start();

        //         intake->IntakeOff();
        //         intake->SetPosition(false);

        //         comeBack = true;
        //     }
        // }

        // if (comeBack) {
        //     if(Go(GO_DISTANCE,1) && timer.Get() > 0.5) {
        //         while(driveTrain->GetAngle() > 0){
        //             driveTrain->driveTrain->TankDrive(-0.5,0.5);
        //         }
        //         shot = false;
        //         secondShoot = true;
        //     }
        // }
    }
}

void Robot::TeleopInit() {
    climber->ClimberBrakeOff();
    driveTrain->ResetEncoders();
    driveTrain->ResetGyro();
}

void Robot::TeleopPeriodic() {
    std::cout << driveTrain->GetAngle() << std::endl;
    driveTrain->Periodic();
    intake->Periodic();
    limelight->Periodic();
    shooter->Periodic();
    conveyor->Periodic();
    climber->Periodic();
    djSpinner->Periodic();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif