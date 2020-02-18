#include "Limelight.h"

Limelight::Limelight(Control *control, DriveTrain *driveTrain) {
    this->control = control;
    drTrain = driveTrain;

    auto instance = nt::NetworkTableInstance::GetDefault();
    table = instance.GetTable("limelight");
    table->PutNumber("ledMode", 1);

    Output = Forward = 0;

    forwardPID = new PID(-0.07, 0.0, 0.0, "LL fd");
    outputPID = new PID(-0.07, 0.00075, 0, "LL aim");
}

void Limelight::Periodic() {
    if(control->LimelightAiming()){
        drTrain->driveMode = drTrain->DriveMode::Disabled;
        SetLimelightLight(1);
        LimelightAiming();
        drTrain->driveTrain->ArcadeDrive(/*Forward*/0, Output);
    } else if(control->LimelightLightActivate()){
        SetLimelightLight(1);
    }
    else {
        SetLimelightLight(0);
    }
}

void Limelight::LimelightActivate() {
    if(control->LimelightLightActivate()) {
        SetLimelightLight(1);
    } else {
        SetLimelightLight(0);
    }
}

void Limelight::LimelightAiming() {
    tx = table->GetNumber("tx", 0.0);
    ta = table->GetNumber("ta", 0.0);

    outputPID->getPIDvalues();

    //frc::SmartDashboard::PutNumber("Distance", fDistance);
    //fDistance = (9.68* pow(ta, 2)) - (53.1*ta) + 123;
    Output = outputPID->OutputPID(tx, 0.0);

    Forward = forwardPID->OutputPID(ta, 0.9);
}

void Limelight::SetLimelightLight(bool state) {
    if(state) {
        table->PutNumber("ledMode", 3);
    } else {
        table->PutNumber("ledMode", 1);
    }
}