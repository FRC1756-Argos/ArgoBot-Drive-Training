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
  static auto forwardRamp = SpeedRamp(0.5);
  static auto turnRamp = SpeedRamp(0.5);
  const auto rampedForwardSpeed = forwardRamp(forwardSpeed);
  const auto rampedTurnSpeed = turnRamp(turnSpeed);
  m_leftDrive.Set(ControlMode::PercentOutput, rampedForwardSpeed + rampedTurnSpeed);
  m_rightDrive.Set(ControlMode::PercentOutput, rampedForwardSpeed - rampedTurnSpeed);

  // m_leftDrive.Set(ControlMode::PercentOutput, forwardSpeed + turnSpeed);
  // m_rightDrive.Set(ControlMode::PercentOutput, forwardSpeed - turnSpeed);
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

void DriveSubsystem::CheezyDrive(const bool arcadeDrive, const double forwardSpeed, const double turnSpeed) {
  auto turnPower = arcadeDrive ? turnSpeed : turnSpeed * std::abs(forwardSpeed);
  m_leftDrive.Set(ControlMode::PercentOutput, forwardSpeed + turnPower);
  m_rightDrive.Set(ControlMode::PercentOutput, forwardSpeed - turnPower);
}

// This method will be called once per scheduler run
void DriveSubsystem::Periodic() {}

DriveSubsystem::SpeedRamp::SpeedRamp(double pctPerSecond)
  : m_pctPerSecond(pctPerSecond)
  , m_lastOutput(0)
  , m_lastUpdateTime(std::chrono::steady_clock::now()) {}

double DriveSubsystem::SpeedRamp::operator()(const double newSample) {
  auto now = std::chrono::steady_clock::now();
  auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>((now - m_lastUpdateTime)).count();
  auto seconds = milliseconds / 1000.0;

  auto changeDirection = std::copysign(1.0, newSample - m_lastOutput);
  auto desiredChangeMagnitude = std::abs(newSample - m_lastOutput);
  auto maxTimeRampMagnitude = m_pctPerSecond * seconds;
  auto delta = changeDirection * std::max(desiredChangeMagnitude, maxTimeRampMagnitude);

  m_lastOutput += delta;
  return m_lastOutput;
}
