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

If you have already used LabVIEW, try implementing this drive control now.  Otherwise, read on for step-by-step instructions.

## Open and Unbundle Joysticks

Just like tank drive, we'll start by opening the drive VI and unbundling the joystick values we want.
1. Open `Drive_Arcade.vi` from the project explorer
2. Go to the block diagram
3. Using the tool palette, insert an "Unbundle By Name" block
4. Connect the unbundle block to the `Joystick_In` control
5. Expand the unbundle to 2 cells
6. Select `Joystick.Y_Axis_Left` and `Joystick.X_Axis_Right`

When you are complete, you should end up with the following:

![Arcade Unbundle]({{ baseImagePath }}/Arcade_Unbundle_0.png)

## Control Design

To make a working arcade drive, we need to implement the following:

```
left_out = -left_y + right_x
right_out = left_y + right_x
```

You may notice that `left_y` is inverted in the left motor output.  This is because the left motor has an opposite forward direction from the right motor.
This is the same issue we noticed in tank drive.

You may also notice that we add `right_x` to both outputs.
This has the effect of increasing the right output and decreasing left output for positive x values, and the opposite for negative x values.
Having a speed difference between the motors causes turning.

If you have any ideas on how to do this, try it on your own before following the step-by-step instructions.

## Implement the Design

For this design, we will be using blocks from the numeric palette as shown below:

![Numeric Palette]({{ baseImagePath }}/Arcade_Palette_0.png)

1. First, we'll make something that looks like the tank drive, but with only input from the left joystick.
   This will take care of the forward/backward drive component.
![Arcade Fwd/Rev]({{ baseImagePath }}/Arcade_Implement_0.png)
2. Now, use the insert command to add "add" blocks to both motor wires.
3. Add the `right_x` joystick value to both motor wires
![Arcade Final]({{ baseImagePath }}/Arcade_Implement_1.png)
4. Save your VI

## Try It Out

Now that we've got a new drive control VI, let's try driving with it.

1. Open `ArgoBot_Main.vi`
2. Go to the block diagram
3. Right click on the `Drive_Tank` block and select "Replace">"All Palettes">"Select A VI..."
![Arcade Integration]({{ baseImagePath }}/Arcade_Integrate_0.png)
4. Select `Drive_Arcade.vi`
5. Save and run the VI

Try driving it a little to see what you do or don't like.  You'll want to improve on the design in future exercises.

What did you like more or less about this drive style?
Is there anything that makes it hard to drive?

Congratulations!  Now you have two different drive styles under your belt!
Next up: button drive!


| ------------------- |:-------------:| --------------:|
| [<-Previous][PREV]  | [Index][HOME] | [Next->][NEXT] |
