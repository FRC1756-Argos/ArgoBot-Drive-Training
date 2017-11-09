---
title: "Tutorial 3: Button Drive"
permalink: /tutorials/3/index.html
---
[PREV]: {{site.baseurl}}/tutorials/2/index.html
[HOME]: {{site.baseurl}}/index.html
[NEXT]: {{site.baseurl}}/tutorials/4/index.html

{% capture baseImagePath %}{{ site.baseurl }}/assets/images/tutorials/3{% endcapture %}

# Tutorial 3: Button Drive

Seems like you've mastered driving with joysticks.  What about all those buttons on the controller?
Now, we'll try a different approach to driving: button drive.
This exercise will skip over some of the more detailed steps covered in the tank drive and arcade drive tutorials, so you may want to refer to those tutorials if you get stuck.

* TOC
{:toc}

## What is "Button Drive"?

![Button Control Scheme]({{ baseImagePath }}/Button_Control.png)

Button drive may be the strangest drive control covered in this training because it uses pure digital controls.
Typically we use analog controls like joysticks because they allow both slow and fast driving, but with digital controls like buttons we get "stop" and "go" with no speed control.
We will use the four right hand buttons to go forward, backward, turn left, and turn right as shown in the diagram.
To do this, we will use the tank and arcade drive concepts and add in digital controls.

If you have already used LabVIEW, try implementing this drive control now.  Otherwise, read on for step-by-step instructions.

## Open and Unbundle Joysticks

Just like before, we'll start by opening the drive VI and unbundling the joystick values we want.
1. Open `Drive_Button.vi` from the project explorer
2. Go to the block diagram
3. Using the tool palette, insert an "Unbundle By Name" block
4. Connect the unbundle block to the `Joystick_In` control
5. Expand the unbundle to 4 cells
6. Select `Joystick.A`, `Joystick.B`, `Joystick.X`, and `Joystick.Y`,

When you are complete, you should end up with the following:

![Arcade Unbundle]({{ baseImagePath }}/Button_Unbundle_0.png)

## Control Design

To make a working button drive, we need to implement the following:

```
if A is pressed:
  Reverse
else if B is pressed:
  Right
else if X is pressed:
  Left
else if Y is pressed:
  Forward
else:
  Stop
```

And the motor outputs for each state should be as follows:

| Mode    | Left Output | Right Output |
| ------- | ----------- | ------------ |
| Forward | -1          | 1            |
| Reverse | 1           | -1           |
| Left    | -1          | -1           |
| Right   | 1           | 1            |
| Stop    | 0           | 0            |

Notice that the left motor is inverted as in the previous drives because forward is inverted on the left motor.
The order of the button checks is not important, but what is important is that we can only ever drive one way at a time in button drive.
There will be no forward and turn a little this time :)

If you have any ideas on how to do this, try it on your own before following the step-by-step instructions.

## Implement the Design

1. First, we'll create an 'enum' constant for the drive mode.  An enum is a data type that lets us name a set of states \(e.g. 'Forward', 'Reverse', etc.\) so we can pass the state information around.  Probably best to see it in action!
![Arcade Enum Constant]({{ baseImagePath }}/Button_Enum_0.png)
2. Now we need to add some states to the enum.  Right click on it and select 'Edit Items...'
3. Insert all the drive states.  Your order may be different than mine, that is OK!  Just make sure there are only states numbered 0-4.
![Arcade Enum Items]({{ baseImagePath }}/Button_Enum_1.png)
4. Now when you left click on the enum constant, you can see the states you created
![Arcade Enum Select]({{ baseImagePath }}/Button_Enum_2.png)
5. To use these states, we need some selectors!  Selectors take a boolean selection input and choose between two inputs to wire to the output.
   Essentially, if we wire a button to the selector, when the button is pressed, the 'T' input comes out, and when the button is released the 'F' input comes out.
   Place a selector from the comparisons palette
![Arcade Selector]({{ baseImagePath }}/Button_Select_0.png)
6. Now, let's make a cascading bridge of selectors.  This implements the if, else if logic described before.
   The input at the top of the bridge has top priority, so in the figure below, when `Joystick.A` is pressed it doesn't matter what other buttons are pressed.  A's output will always be asserted.
   Inputs above other inputs will have priority over those below.  The bottommost value is called 'default' because it is only output if no button is pressed.
![Arcade Select Cascade]({{ baseImagePath }}/Button_Select_1.png)
7. Notice, the wires are all orange, but the enum is blue.  This is because none of the wires are connected yet.
   Make some copies of your enum constant and wire one to all the `True` inputs and one to the default input.
8. Change the constant values to match the logic described in our control design above.
![Arcade Select Final]({{ baseImagePath }}/Button_Select_2.png)
9. Now we're going to use our first structure: the case structure.  Structures are boxes that perform special operations on the blocks inside.
   The case structure takes a condition input \(in our case the drive mode\) and swaps out the contents based on mode.
   First, select "Case Structure" from the "Structures" palette and draw a box between the selector cascade and the outputs.
![Arcade Case Structure]({{ baseImagePath }}/Button_Case_0.png)
10. Wire the output of the selector cascade to the case structure's question mark input \(the green box\) and wire the two motor outputs to the right wall of the case structure.
    Notice that the outputs have broken wires because no inputs are connected yet.  We'll fix that soon
![Arcade Case Wire]({{ baseImagePath }}/Button_Case_1.png)
11. Right click on the drop down menu of the case structure and click "Add Case For Every Value".  This will make one case for every enum value we made earlier.
![Arcade Case Populate]({{ baseImagePath }}/Button_Case_2.png)
12. Finally, add some "DBL Numeric Constant" values from the numeric palette to connect inside each case.  Use the table above to choose the right values.
![Arcade Final]({{ baseImagePath }}/Button_Final.png)
13. Save your VI

## Try It Out

Now that we've got a new drive control VI, let's try driving with it.

1. Open `ArgoBot_Main.vi`
2. Go to the block diagram
3. Right click on the `Drive_Arcade` block and select "Replace">"All Palettes">"Select A VI..."
4. Select `Drive_Button.vi`
5. Save and run the VI

Try driving it a little to see what you do or don't like.  You'll want to improve on the design in future exercises.

What did you like more or less about this drive style?
Is there anything that makes it hard to drive?

Congratulations!  Now you have three different drive styles under your belt!
Next up: Cheezy drive!

| ------------------- |:-------------:| --------------:|
| [<-Previous][PREV]  | [Index][HOME] | [Next->][NEXT] |
