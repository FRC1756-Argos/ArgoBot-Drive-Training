---
title: "Tutorial 1: Tank Drive"
permalink: /tutorials/1/index.html
---
[PREV]: {{site.baseurl}}/tutorials/0/index.html
[HOME]: {{site.baseurl}}/index.html
[NEXT]: {{site.baseurl}}/tutorials/2/index.html

{% capture baseImagePath %}{{ site.baseurl }}/assets/images/tutorials/1{% endcapture %}

# Tutorial 1: Tank Drive

Let's start with one of the most basic drive train controls: tank drive.
In this exercise, you'll get your first hands-on experience with LabVIEW and how it enables you to translate controller inputs to motor outputs.

* TOC
{:toc}

## What is "Tank Drive"?

![Tank Control Scheme]({{ baseImagePath }}/Tank_Control.png)

Tank drive is a direct-drive control where one joystick is used for each side of the drive train.
The left joystick moves the left motor forward and backward, and the right joystick moves the right motor forward and backward.
To turn, you move one joystick forward and the other in reverse.
This control scheme offers the driver complete control, but tends to have a steeper learning curve.

But, this scheme is the easiest to implement in software because of its simplicity!

If you have already used LabVIEW, try implementing this drive control now.  Otherwise, read on for step-by-step instructions.

## Open the Tank Drive Template VI

### ArgoBot V1

1. Open `ArgoBotDriveTraining.lvproj` from the `src/ArgobotV1` folder of the training repository.  This will bring up the project explorer window.
2. From the project explorer window, open `Drive_Tank.vi`
![Tank Control Scheme]({{ baseImagePath }}/Tank_ProjectExplorer.png)
3. You will first encounter the front panel.  On the front panel, you can see a bundle of joystick inputs \(Black\), numeric motor outputs \(Red\), and the VI icon and input/output terminals \(Blue\).
![Tank Front Panel]({{ baseImagePath }}/Tank_FrontPanel.png)
4. Go to the block diagram by pressing Ctrl + E or by clicking "Window">"Show Block Diagram"
5. On the block diagram, you'll see a control \(input\) with the joystick bundle \(Black\) and indicators \(outputs\) for the motors \(Red\).
![Tank Block Diagram]({{ baseImagePath }}/Tank_BlockDiagram_0.png)

### ArgoBot V2

1. Open `ArgoBotV2.lvproj` from the `src/ArgobotV2` folder of the training repository.  This will bring up the project explorer window.
2. From the project explorer window, open `Drive_Tank.vi`
![Tank Control Scheme]({{ baseImagePath }}/Tank_ProjectExplorer_v2.png)
3. You will first encounter the front panel.  On the front panel, you can see a joystick input devref \(Black\), numeric motor outputs \(Red\), and the VI icon and input/output terminals \(Blue\).
![Tank Front Panel]({{ baseImagePath }}/Tank_FrontPanel_v2.png)
4. Go to the block diagram by pressing Ctrl + E or by clicking "Window">"Show Block Diagram"
5. On the block diagram, you'll see a control \(input\) with the joystick input devref \(Black\), some code to process the joystick input \(Blue\), and indicators \(outputs\) for the motors \(Red\).
![Tank Block Diagram]({{ baseImagePath }}/Tank_BlockDiagram_0_v2.png)

## Extract the Joystick Values

### ArgoBot V1

1. In the block diagram, right click on the white space to bring up the tools palette.
  - Most of the tools we need are in the "Programming" palette at the top
2. Open the "Cluster, Class, & Variant" section and select "Unbundle By Name"
![Tank Palette]({{ baseImagePath }}/Tank_Palette_0.png)
3. Place the new block on the right side of the Joystick_In block
4. Connect the output of Joystick_In to the input of the unbundle block with a wire.  Do this by clicking the dot on one block then clicking the dot on the other.
![Tank Unbundle By Name]({{ baseImagePath }}/Tank_Unbundle_0.png)
5. Drag the little blue dot on the bottom of the unbundle block down to make the block two cells high.
6. Select "Joystick">"Y_Axis_Left" and "Joystick">"Y_Axis_Right" by left clicking on each of the two cells when you get the "finger" cursor.
![Tank Unbundle Elements]({{ baseImagePath }}/Tank_Unbundle_1.png)

### ArgoBot V2

1. In the block diagram, right click on the white space to bring up the tools palette.
  - Most of the tools we need are in the "Programming" palette at the top
2. Open the "Cluster, Class, & Variant" section and select "Unbundle By Name"
![Tank Palette]({{ baseImagePath }}/Tank_Palette_0_v2.png)
3. Place the new block on the right side of the Joystick_In block
4. Connect the "Named Axes" output of Joystick Name to the input of the unbundle block with a wire.  Do this by clicking the dot on one block then clicking the dot on the other.
![Tank Unbundle By Name]({{ baseImagePath }}/Tank_Unbundle_0_v2.png)
5. Drag the little blue dot on the bottom of the unbundle block down to make the block two cells high.
6. Select "Left_Y" and "Right_Y" by left clicking on each of the two cells when you get the "finger" cursor.
![Tank Unbundle Elements]({{ baseImagePath }}/Tank_Unbundle_1_v2.png)

## Connect the Joystick Inputs to the Motor Outputs

### ArgoBot V1

1. Wire the "Y_Axis_Left" input to the "Left_Motor_Out" output
2. Wire the "Y_Axis_Right" input to the "Right_Motor_Out" output
![Tank Wiring]({{ baseImagePath }}/Tank_Wire_0.png)
3. Make sure you save your changes by pressing Ctrl + S or clicking "File">"Save"

### ArgoBot V2

1. Wire the "Left_Y" input to the "Left_Motor_Out" output
2. Wire the "Right_Y" input to the "Right_Motor_Out" output
![Tank Wiring]({{ baseImagePath }}/Tank_Wire_0_v2.png)
3. Make sure you save your changes by pressing Ctrl + S or clicking "File">"Save"

## Try It Out

### ArgoBot V1

1. Open the project explorer window
2. Open `ArgoBot_Main.vi`
3. Navigate to the block diagram
4. In the tools palette, choose "Select a VI..."
![Tank Select VI]({{ baseImagePath }}/Tank_Integrate_0.png)
5. Wire the `Read_Joystick` bundle to the `Joystick_In` input
6. Wire the `Left_Motor_Out` output to the `Left Motor` bundle element
7. Wire the `Right_Motor_Out` output to the `Right Motor` bundle element
![Tank Control Scheme]({{ baseImagePath }}/Tank_Integrate_1.png)
8. Go back to the front panel
9. Save the VI
10. Connect the ArgoBot and click the "Run" arrow
![Tank Run]({{ baseImagePath }}/Tank_Integrate_2.png)
11. Try driving the tank drive.
  - Does it work?
  - Is there anything that doesn't do what you were expecting?

### ArgoBot V2

1. Open the project explorer window
2. Open `Teleop.vi`
3. Navigate to the block diagram
4. In the tools palette, choose "Select a VI..."
![Tank Select VI]({{ baseImagePath }}/Tank_Integrate_0_v2.png)
5. Wire the `JoystickDevRef` output of Joystick RefNum Registry Get to the `Joystick_In` input
6. Wire the `Left_Motor_Out` output to the `LeftSpeed` input of RobotDriveMotors
7. Wire the `Right_Motor_Out` output to the `RightSpeed` input of RobotDriveMotors
![Tank Control Scheme]({{ baseImagePath }}/Tank_Integrate_1_v2.png)
8. Save the VI
9. Go back to the project explorer and open `Robot Main.vi`
10. Connect the ArgoBot and click the "Run" arrow.  This will load your code onto the robot.
![Tank Run]({{ baseImagePath }}/Tank_Integrate_2_v2.png)
11. Open the FRC Driver Station program and click "Enable" to run the robot
![Driver Station]({{ baseImagePath }}/DriverStation.png)
11. Try driving the tank drive.
  - Does it work?
  - Is there anything that doesn't do what you were expecting?

## Fixing a Bug

1. You may have noticed the left motor is going backwards!  This is because the two motors are flipped 180 degrees, so forward will make one motor go forward, and reverse the other.
2. We can fix it!  All we need to do is make the value opposite on the left motor.
3. First, open `Drive_Tank.vi` again and go to the block diagram.
4. Right click on the left motor's orange wire and select "Insert">"Numeric Palette">"Negate"
![Tank Negate]({{ baseImagePath }}/Tank_Fix_0.png)
5. This will insert a new negate block, which multiplies the input by -1, in line with the wire.
![Tank Final]({{ baseImagePath }}/Tank_Fix_1.png)
6. Save again
7. Try running again from `ArgoBot_Main.vi`

Congratulations!  You have a driving robot!  Try driving it a little to see what you do or don't like.  You'll want to improve on the design in future exercises.

## Another Fix Using ArgoBot v2

If you are using and ArgoBot v2, there's a better way of fixing a motor that turns the wrong direction!
Every motor has an "Invert" property that is designed to allow a programmer to make the "forward" direction of a motor reverse of the default forward direction.

Before you try this new method, remove the fix from before then do the following:

1. Open `Begin.vi` from the project explorer
2. Switch to the block diagram
3. Change the `Left Motor 1 Inv` input constant to true by clicking on the green F block
![V2 Tank Fix]({{ baseImagePath }}/Tank_Fix_v2.png)
4. Save and try running your code

Keep in mind that future exercises will use the v1 fix instead of the v2 fix, but competition robot code will set motor direction in `Begin.vi`.

Next you'll be trying a new drive type: arcade drive.

| ------------------- |:-------------:| --------------:|
| [<-Previous][PREV]  | [Index][HOME] | [Next->][NEXT] |
