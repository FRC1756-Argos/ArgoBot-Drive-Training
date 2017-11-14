---
title: "Tutorial 5: Deadbands"
permalink: /tutorials/5/index.html
---
[PREV]: {{site.baseurl}}/tutorials/4/index.html
[HOME]: {{site.baseurl}}/index.html
[NEXT]: {{site.baseurl}}/tutorials/6/index.html

{% capture baseImagePath %}{{ site.baseurl }}/assets/images/tutorials/5{% endcapture %}

# Tutorial 5: Deadbands

Now that we've got some base drive code, let's explore some refinements that will make it even better!
First up, we'll fix a common problem with joystick inputs.

If you don't remember how to do any of the steps, you can go back to the previous tutorials for more explanation.

* TOC
{:toc}

## What is a "Deadband"?

You may have noticed when driving the robot, that the motors move slightly even when you don't touch the joysticks.
If you didn't notice this, try this to see the issue:

1. Run your robot code as normal from `ArgoBot_Main.vi`
2. Pick up the robot and hold it near your ear so you can hear the sound of the motors and motor controller
  - Make sure you keep the robot wheels away from any hair, jewelry, or loose clothing.  These could get tangled up in the wheels.
3. Drive the robot slowly forward so the wheels just barely move
4. You should hear a high-pitched sound even before the motors begin to move
  - This is the sound of the motor controllers and it indicates an output, but that input is not high enough to move the robot
5. Let go of the joystick, and you may still hear the sound
6. Even if you don't hear the sound, we can use the "probe" feature in LabVIEW to see the output of our drive code.
7. While the code is running, open up the block diagram of `ArgoBot_Main.vi`
8. Click on the wire going to the left motor output.  This will create a probe, which is a live view of what the code is doing
![Deadband Single Probe]({{ baseImagePath }}/Deadband_Probe_0.png)
9. Try moving the joystick back and forth to see the value change.  Does it always go back to 0 when you let go of the joystick?
10. You can monitor multiple probes at the same time!  Try probing the other motor output.
![Deadband Double Probe]({{ baseImagePath }}/Deadband_Probe_1.png)
11. Now that we see the symptom, let's find the cause.  Open up the drive VI you're using and probe the Joystick values
![Deadband Joystick Probe]({{ baseImagePath }}/Deadband_Probe_2.png)

Looks like those joysticks don't always stay at 0.
This isn't really noticeable on the ArgoBot since it needs quite a bit of output before the motors move, but on an FRC robot, 10% can be significant.

To fix this, we need a "Deadband" to designate a range of small input values that should produce no output.

## Control Design

Consider the following plot:

![Deadband Plot]({{ baseImagePath }}/Deadband_Plot_0.png)

*Plot by Krishnavedala (Own work) [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0), via Wikimedia Commons*

For our deadband implementation, we also want to force the joystick output to 0 for small joystick input values.
However, if we used the value 0.5 as shown, only half of the speed range would be available.
Instead, we'll use a threshold of 0.1 or 10%.

If you have any ideas on how to do this, try it on your own before following the step-by-step instructions.

## Making a New VI

Sometimes, we have some code that we want to re-use in several places.
In these situations we could copy and paste that code for each instance, but then making changes becomes difficult.

Instead, we're going to make a new VI that implements our deadband.

1. In the project explorer, click "File">"New VI".  This will bring up a new front panel and block diagram.
2. Save the new VI as `Deadband.vi`
3. Right click on the I/O pattern in the top right corner of the front panel window and select a pattern with at least one box on the left and at least one box on the right.
  - Inputs and outputs may go on either side of the pattern, but keeping inputs on the left and outputs on the right makes cleaner VI wiring.
![Deadband IO Pattern]({{ baseImagePath }}/Deadband_VI_0.png)
4. Next, we'll make an icon for the VI.  This determines how the VI will look inside other VIs.  Right click on the current icon and select "Edit Icon..."
![Deadband IO Pattern]({{ baseImagePath }}/Deadband_VI_1.png)
5. Use the "Filled Rectangle" tool and drag a rectangle around the window to clear the icon
![Deadband Icon]({{ baseImagePath }}/Deadband_VI_2.png)
6. You can change colors, add shapes, and write text to make an icon you like.  Use the preview to determine if your icon is recognizable in small format.
  - When writing text, use capital letters for best visibility.  To move text, use the arrow keys immediately after typing.
![Deadband Icon]({{ baseImagePath }}/Deadband_VI_3.png)
7. Click "OK" when you are happy with your new icon
8. Next, add a numeric control and numeric indicator to the block diagram using the controls palette on the front panel.  This is accessible by right clicking in the empty space just like the tools palette in the block diagram.
  - The control will be our input, and the indicator will be our output
  - Name the control "In" and the indicator "Out"
![Front panel]({{ baseImagePath }}/Deadband_VI_4.png)
9. Currently, our VI has no inputs and outputs, but we can wire our control and indicator so they become accessible outside our VI.
10. Do this by first left clicking one of the left rectangles in the IO Pattern you chose.  It will turn black as shown and you will get a wire cursor.
![Front panel]({{ baseImagePath }}/Deadband_VI_5.png)
11. Then click the control.  The block you wired will turn orange indicating a floating point control was connected.
![Front panel]({{ baseImagePath }}/Deadband_VI_6.png)
12. Do the same with the output indicator.
![Front panel]({{ baseImagePath }}/Deadband_VI_7.png)

Now we have a starting point for our VI with the necessary input and output.

## Add Deadband Logic

1. Go to the block diagram of your new deadband VI
2. Use the absolute value block from the numeric palette and the greater than and selector blocks from the comparison palette to implement the following:
```
if |Input| > 0.1:
    Output = Input
else:
    Output = 0
```
3. You should end up with something that looks like this:
![Deadband Final]({{ baseImagePath }}/Deadband_Final.png)
4. Save your VI

## Try It Out

Now, let's add the deadband VI to our tank drive VI to see it in action.

1. Open `Drive_Tank.vi` and go to the block diagram
2. Add in two instances of your deadband VI using "Select a VI..." in the tools palette
3. Insert the deadbands in the joystick inputs as shown here:
![Deadband Integration]({{ baseImagePath }}/Deadband_Integration_0.png)
4. Add `Drive_Tank.vi` as the drive block in `ArgoBot_Main.vi`
5. Run `ArgoBot_Main.vi`
6. Probe before and after the deadband blocks
![Deadband Test]({{ baseImagePath }}/Deadband_Integration_1.png)

How does this work compared to the non-deadbanded tank drive?

Congratulations!  You just made your first VI from scratch!  Creating new VIs is an easy way to reuse and organize code.

You can add this deadband to any drive VI, but we're going to try another approach for our next exercise.

| ------------------- |:-------------:| --------------:|
| [<-Previous][PREV]  | [Index][HOME] | [Next->][NEXT] |
