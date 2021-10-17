// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/RunCommand.h>

RobotContainer::RobotContainer()
  : m_drive{2,1}
  , m_controller{0} {
  // Initialize all of your commands and subsystems here
  m_drive.SetDefaultCommand(frc2::RunCommand(
    [this] {
      m_drive.TankDrive(m_controller.GetRawAxis(static_cast<int>(frc::XboxController::Axis::kLeftY)) * -1,
                        m_controller.GetRawAxis(static_cast<int>(frc::XboxController::Axis::kRightY)) * -1);
      // m_drive.ArcadeDrive(m_controller.GetRawAxis(static_cast<int>(frc::XboxController::Axis::kLeftY)) * -1,
      //                     m_controller.GetRawAxis(static_cast<int>(frc::XboxController::Axis::kRightX)));
    },
    {&m_drive}
  ));

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return nullptr;
}
