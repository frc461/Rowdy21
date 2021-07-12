#include "Limelight.h"

Limelight::Limelight(Control *control, DriveTrain *driveTrain) {
    this->control = control;
    drTrain = driveTrain;

    auto instance = nt::NetworkTableInstance::GetDefault();
    table = instance.GetTable("limelight");
    table->PutNumber("ledMode", 1);
    
    output = 0;

    outputPID = new PID(-0.03, -0.00175, 0.19, "LL aim");
}

void Limelight::Periodic() {
    if(control->LimelightAiming()){
        drTrain->driveMode = drTrain->DriveMode::Disabled;
        SetLimelightLight(1);
        LimelightAiming();
    }
    else if(control->LimelightLightActivate()){
        SetLimelightLight(1);
        outputPID->ResetSum();
    }
    else {
        SetLimelightLight(0);
        outputPID->ResetSum();
    }
    SetLimelightLight(1);
}

void Limelight::LimelightReset(){
    outputPID->ResetSum();
}

void Limelight::AutoLimelight(){
    SetLimelightLight(1);
    LimelightAiming();
    drTrain->driveTrain->ArcadeDrive(0, output);
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
    ty = table->GetNumber("ty", 0.0);

    if (fabs(tx) > 0.5) {
        drTrain->driveTrain->ArcadeDrive(0, outputPID->OutputPID(tx, 0.0));
    }
}

void Limelight::SetLimelightLight(bool state) {
    if(state) { // On
        table->PutNumber("ledMode", 3);
        table->PutNumber("camMode", 0);
    } else {    // Off
        table->PutNumber("ledMode", 1);
        table->PutNumber("camMode", 1);
    }
}