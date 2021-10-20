// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <chrono>

class DriveSubsystem : public frc2::SubsystemBase {
 public:
  DriveSubsystem(const int leftDriveId, const int rightDriveId);

  void TankDrive(const double leftSpeed, const double rightSpeed);
  void ArcadeDrive(const double forwardSpeed, const double turnSpeed);
  void ButtonDrive(const bool forward, const bool right, const bool reverse, const bool left);
  void CheezyDrive(const bool arcadeDrive, const double forwardSpeed, const double turnSpeed);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  TalonSRX m_leftDrive;
  TalonSRX m_rightDrive;

  class SpeedRamp {
    public:
      SpeedRamp(double pctPerSecond);
      double operator()(const double newSample);
    private:
      const double m_pctPerSecond;
      double       m_lastOutput;
      std::chrono::time_point<std::chrono::steady_clock> m_lastUpdateTime;
  };
};
