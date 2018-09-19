---
title: "Tutorial 4: Cheezy Drive"
permalink: /tutorials/4/index.html
---
[PREV]: {{site.baseurl}}/tutorials/3/index.html
[HOME]: {{site.baseurl}}/index.html
[NEXT]: {{site.baseurl}}/tutorials/5/index.html

{% capture baseImagePath %}{{ site.baseurl }}/assets/images/tutorials/4{% endcapture %}

# Tutorial 4: Cheezy Drive

Seems like you've mastered driving with joysticks.  What about all those buttons on the controller?
Now, we'll try a different approach to driving: button drive.
This exercise will skip over some of the more detailed steps covered in the tank drive and arcade drive tutorials, so you may want to refer to those tutorials if you get stuck.

* TOC
{:toc}

## What is "Cheezy Drive"?

![Cheezy Control Scheme]({{ baseImagePath }}/Cheezy_Control.png)

Cheezy drive is an adaptation of drive code developed by [FRC team 254 The Cheesy Poofs](https://www.team254.com/).
It is based off the simple arcade drive code we wrote earlier, but with some notable improvements.

In arcade drive, you may have noticed that the radius of your turning is different when you drive fast vs driving slow.
This limitation means that when driving full speed, you cannot perform tight turns.

Cheezy drive uses some more advanced control logic to enable constant-radius turning.
This means that if you keep the right joystick stationary, the robot's turning radius should be constant regardless of the robot speed.

As you'll see, this has several advantages and disadvantages, but it's still fairly simple to implement.

## Open and Unbundle Joysticks

Just like before, we'll start by opening the drive VI and unbundling the joystick values we want.
1. Open `Drive_Cheezy.vi` from the project explorer
2. Go to the block diagram
3. Using the tool palette, insert an "Unbundle By Name" block
4. Connect the unbundle block to the `Joystick_In` control
5. Expand the unbundle to 3 cells
6. Select `Joystick.RB`, `Joystick.Y_Axis_Left`, and `Joystick.X_Axis_Right`

When you are complete, your unbundle should be identical to arcade drive except with an additional boolean (green) output.

## Control Design

To make a working Cheezy drive, we need to implement the following \([as described on Chief Delphi](https://www.chiefdelphi.com/forums/showpost.php?p=1181728&postcount=2)\):

```
skim( v ):
  // gain determines how much to skim off the top
  if (v > 1.0):
    return -((v - 1.0) * gain)
  else if (v < -1.0):
    return -((v + 1.0) * gain)
  return 0;

t_left = throttle + turn
t_right = throttle - turn

left = t_left + skim(t_right)
right = t_right + skim(t_left)
```

That might seem pretty complicated, but we can simplify this if we think about what we want to do.

Here's a simpler design which accomplishes the same thing:

```
turnPower = turn * |throttle|
left = throttle + turnPower
right = throttle - turnPower
```

Don't worry if you're unsure how this works.  For now, we will implement the design to evaluate it's advantages and disadvantages.
How it works may become easier to understand as we go along.

If you have any ideas on how to do this, try it on your own before following the step-by-step instructions.

## Implement the Design

1. You may notice that `left` and `right` both require `turnPower`, so let's calculate that first.
![Cheezy Turn Power]({{ baseImagePath }}/Cheezy_TurnPower.png)
2. Next, let's make the left and right drive outputs.  This is nearly identical to arcade drive.
![Cheezy Drive Output]({{ baseImagePath }}/Cheezy_DriveOut.png)
3. Technically, we're done now, but let's use the right bumper to switch back and forth between arcade drive and Cheezy drive.  This will make it more clear how the two are different.  Add in a selector, like in button drive, to switch between arcade and Cheezy drive.  See if you can do this without looking at the final product. 
4. Once you're done, your VI should look like the VI below.
![Cheezy Drive Output]({{ baseImagePath }}/Cheezy_Final.png)
5. Save your VI

## Try It Out

Now that we've got a new drive control VI, let's try driving with it.

1. Open `ArgoBot_Main.vi`
2. Go to the block diagram
3. Right click on the `Drive_Button` block and select "Replace">"All Palettes">"Select A VI..."
4. Select `Drive_Cheezy.vi`
5. Save and run the VI

Try driving it a little to see what you do or don't like.  You'll want to improve on the design in future exercises.

What did you like more or less about this drive style?
Is there anything that makes it hard to drive?
How does changing the gain change how it drives?

Try switching between Arcade and Cheezy drive by holding the right bumper on the controller.  Which do you like better?  Can you think of the advantages/disadvantages of the different approaches?

Congratulations!  Now you have four different drive styles under your belt!  But are any of them ready for competition?
These are the building blocks of more advanced controls, and we'll explore some refinements and advanced features next.
Next up: drive code refinements

| ------------------- |:-------------:| --------------:|
| [<-Previous][PREV]  | [Index][HOME] | [Next->][NEXT] |
