---
title: "Tutorial 2: Arcade Drive"
permalink: /tutorials/2/index.html
---
[PREV]: {{site.baseurl}}/tutorials/1/index.html
[HOME]: {{site.baseurl}}/index.html
[NEXT]: {{site.baseurl}}/tutorials/3/index.html

{% capture baseImagePath %}{{ site.baseurl }}/assets/images/tutorials/2{% endcapture %}

# Tutorial 2: Arcade Drive

Now that we've got a driving tank drive robot, let's try something more interesting: arcade drive!
This exercise will skip over some of the more detailed steps covered in the tank drive tutorial, so you may want to refer to that tutorial if you get stuck.

* TOC
{:toc}

## What is "Arcade Drive"?

![Arcade Control Scheme]({{ baseImagePath }}/Arcade_Control.png)

Arcade drive may be more familiar, because it is the basis of many video games.
One joystick moves the robot forward and backward, and the second joystick turns left and right
To do this, we will make the left joystick set a value for both motors and the right joystick will increase or decrease the motor speeds to turn the robot
This control scheme offers less driver control, but it's easy to learn and many drivers enjoy it.

If you have some experience programming, try implementing this drive control now.  Otherwise, read on for step-by-step instructions.

## Control Design

To make a working arcade drive, we need to implement the following:

```
left_out = left_y + right_x
right_out = left_y - right_x
```

You may notice that we add `right_x` to the left output and subtract from the right output.
This has the effect of increasing the left output and decreasing right output for positive x values, and the opposite for negative x values.
Having a speed difference between the motors causes turning.

Note that we still have to invert the left motor as we discovered in Tank Drive.  We need to make sure we continue to include this inversion.

If you have any ideas on how to do this, try it on your own before following the step-by-step instructions.

## C++

<details markdown="block" open>

### Initial Setup

Just like Tank Drive, we'll start by:
1. Create a new subsystem named `DriveSubsystem`
2. Add left and right motors to `DriveSubsystem`
3. Add an Xbox controller and the drive subsystem to `RobotContainer`

If you've already implemented another drive setup, you can reuse that here and we'll modify.  Otherwise, you can follow the detailed instructions in [Tank Drive]({{site.baseurl}}/tutorials/1/index.html).

### Add Motor Control Logic

1. Let's start by opening `DriveSubsystem.h`
2. Create a new function declaration for the Arcade Drive logic.  We will have two input parameters: one for the forward speed and one for the turning speed.  This will be a public function like in Tank Drive.
   ```cpp
   void ArcadeDrive(const double forwardSpeed, const double turnSpeed);
   ```
3. Now open `DriveSubsystem.cpp` and add a corresponding function definition.
   ```cpp
   void DriveSubsystem::ArcadeDrive(const double forwardSpeed, const double turnSpeed) {

   }
   ```
4. Based on the description of arcade drive in the first section, we'll have to implement this control logic:
   ```
   left_out = forwardSpeed + turnSpeed
   right_out = forwardSpeed - turnSpeed
   ```
5. Let's add this logic to the body of `DriveSubsystem::ArcadeDrive()`
   ```cpp
   void DriveSubsystem::ArcadeDrive(const double forwardSpeed, const double turnSpeed) {
     m_leftDrive.Set(ControlMode::PercentOutput, forwardSpeed + turnSpeed);
     m_rightDrive.Set(ControlMode::PercentOutput, forwardSpeed - turnSpeed);
   }
   ```

### Update Controller Mapping
The basics of this will be the same as [Tank Drive]({{site.baseurl}}/tutorials/1/index.html), but now we're going to use a different drive function and different joystick axes.
1. Open `RobotContainer.cpp`
2. In the constructor, modify the `m_drive.SetDefaultCommand()` call so it uses your new `DriveSubsystem::ArcadeDrive()` function instead of `DriveSubsystem::TankDrive()`.  We need to make sure the y axis is still inverted.
   ```cpp
   m_drive.SetDefaultCommand(frc2::RunCommand(
       [this] {
         m_drive.ArcadeDrive(m_controller.GetRawAxis(static_cast<int>(frc::XboxController::Axis::kLeftY)) * -1,
                             m_controller.GetRawAxis(static_cast<int>(frc::XboxController::Axis::kRightX)));
       },
       {&m_drive}
     ));
   ```

### Try It Out

1. Connect to the WiFi for the robot.
2. Open the FRC Driver Station.  You should see green communication with the robot
![Driver Station]({{ baseImagePath }}/DriverStation.png)
3. Back in VSCode, press <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd> to get your command pallette and select `WPILib: Deploy Robot Code`
![VSCode Deploy]({{ baseImagePath }}/VSCode_Deploy_0.png)
4. Return to the driver station.  Make sure your controller is plugged in, stand clear of the robot, and enable the robot.
5. Try driving the robot.  Make sure to disable whenever you are not holding the controller.

</details>

## LabVIEW

<details markdown="block">

### Open and Unbundle Joysticks

Just like tank drive, we'll start by opening the drive VI and unbundling the joystick values we want.
1. Open `Drive_Arcade.vi` from the project explorer
2. Go to the block diagram
3. Using the tool palette, insert an "Unbundle By Name" block
4. Connect the unbundle block to the `Joystick_In` control
5. Expand the unbundle to 2 cells
6. Select `Joystick.Y_Axis_Left` and `Joystick.X_Axis_Right`

When you are complete, you should end up with the following:

![Arcade Unbundle]({{ baseImagePath }}/Arcade_Unbundle_0.png)

### Implement the Design

For this design, we will be using blocks from the numeric palette as shown below:

![Numeric Palette]({{ baseImagePath }}/Arcade_Palette_0.png)

Note that we'll be inverting the left motor like in Tank Drive.

1. First, we'll make something that looks like the tank drive, but with only input from the left joystick.
   This will take care of the forward/backward drive component.
![Arcade Fwd/Rev]({{ baseImagePath }}/Arcade_Implement_0.png)
2. Now, use the insert command to add "add" blocks to both motor wires.
3. Add the `right_x` joystick value to both motor wires
![Arcade Final]({{ baseImagePath }}/Arcade_Implement_1.png)
4. Save your VI

### Try It Out

Now that we've got a new drive control VI, let's try driving with it.

1. Open `ArgoBot_Main.vi`
2. Go to the block diagram
3. Right click on the `Drive_Tank` block and select "Replace">"All Palettes">"Select A VI..."
![Arcade Integration]({{ baseImagePath }}/Arcade_Integrate_0.png)
4. Select `Drive_Arcade.vi`
5. Save and run the VI

</details>

Try driving it a little to see what you do or don't like.  You'll want to improve on the design in future exercises.

What did you like more or less about this drive style?
Is there anything that makes it hard to drive?

Congratulations!  Now you have two different drive styles under your belt!
Next up: button drive!


| ------------------- |:-------------:| --------------:|
| [<-Previous][PREV]  | [Index][HOME] | [Next->][NEXT] |
