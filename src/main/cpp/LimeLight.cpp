#include "Limelight.h"

Limelight::Limelight(Control *control, DriveTrain *driveTrain) {
    this->control = control;
    drTrain = driveTrain;

    auto instance = nt::NetworkTableInstance::GetDefault();
    table = instance.GetTable("limelight");
    table->PutNumber("ledMode", 1);

    Output = Forward = 0;

    forwardPID = new PID(-0.07, 0.0, 0.0, "LL fd");
    outputPID = new PID(-0.071, -0.002, -0.0003, "LL aim");
}

void Limelight::Periodic() {
    if(control->LimelightAiming()){
        drTrain->driveMode = drTrain->DriveMode::Disabled;
        SetLimelightLight(1);
        LimelightAiming();
        drTrain->driveTrain->ArcadeDrive(0, Output);

    } else if(control->LimelightLightActivate()){
        SetLimelightLight(1);
        outputPID->ResetSum();
    }
    else {
        SetLimelightLight(0);
        outputPID->ResetSum();
    }
}

void Limelight::LimelightReset(){
    outputPID->ResetSum();
}

void Limelight::AutoLimelight(){
        SetLimelightLight(1);
        LimelightAiming();
        drTrain->driveTrain->ArcadeDrive(0, Output);
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

    Output = outputPID->OutputPID(tx, 0.0);
    Forward = forwardPID->OutputPID(ta, 0.9);
}

void Limelight::SetLimelightLight(bool state) {
    if(state) {
        table->PutNumber("ledMode", 3);
        table->PutNumber("camMode", 0);
    } else {
        table->PutNumber("ledMode", 1);
        table->PutNumber("camMode", 1);
    }
}