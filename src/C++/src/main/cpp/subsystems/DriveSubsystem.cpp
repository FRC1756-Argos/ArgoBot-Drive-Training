// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/DriveSubsystem.h"

DriveSubsystem::DriveSubsystem(const int leftDriveId, const int rightDriveId)
  : m_leftDrive{leftDriveId}
  , m_rightDrive{rightDriveId} {
  m_leftDrive.SetInverted(true);
}

void DriveSubsystem::TankDrive(const double leftSpeed, const double rightSpeed) {
  wpi::outs() << "Left speed:" << leftSpeed << ", Right speed:" << rightSpeed << '\n';
  m_leftDrive.Set(ControlMode::PercentOutput, leftSpeed);
  m_rightDrive.Set(ControlMode::PercentOutput, rightSpeed);
}

void DriveSubsystem::ArcadeDrive(const double forwardSpeed, const double turnSpeed) {
  m_leftDrive.Set(ControlMode::PercentOutput, forwardSpeed + turnSpeed);
  m_rightDrive.Set(ControlMode::PercentOutput, forwardSpeed - turnSpeed);
}

void DriveSubsystem::ButtonDrive(const bool forward, const bool right, const bool reverse, const bool left) {
  if(forward) {
    ArcadeDrive(0.5, 0);
  } else if(reverse) {
    ArcadeDrive(-0.5, 0);
  } else if(right) {
    ArcadeDrive(0, 0.5);
  } else if(left) {
    ArcadeDrive(0, -0.5);
  } else {
    ArcadeDrive(0, 0);
  }
}

// This method will be called once per scheduler run
void DriveSubsystem::Periodic() {}
