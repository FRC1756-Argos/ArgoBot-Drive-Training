---
title: "Tutorial 6: Lookup Table Mapping"
permalink: /tutorials/6/index.html
---
[PREV]: {{site.baseurl}}/tutorials/5/index.html
[HOME]: {{site.baseurl}}/index.html
[NEXT]: {{site.baseurl}}/tutorials/7/index.html

{% capture baseImagePath %}{{ site.baseurl }}/assets/images/tutorials/6{% endcapture %}

# Tutorial 6: Lookup Table Mapping

Now that we have the basics of a drivetrain that only drives when we want it to, let's try making the robot easier to control!
One way of doing this is by creating a lookup table map to translate an input value to a desired output value.

* TOC
{:toc}

## What is a "Lookup Table Map"?

You may have noticed that even though we move the joysticks in a full range of 0-1 when moving forward, only part of this range is useful.
For example, when the joystick goes from 20% to 30% you will experience a significant change in speed and you may want high control in this range for precise movement.
However, when the joystick goes from 90%-100% you will experience very little change in speed and you probably just want to go fast.

The problem here is that our current controls don't allow for fine controls and quick ramp up to top speed simultaneously.
This is where we apply a lookup table map.  A lookup table map takes our linear input range and maps (or translates) it to a custom output model.
Think of "mapping" as a sort of mathematical function that generates an output for a given input.

If this is not yet clear, that's perfectly fine.
In the next few sections, we'll try applying the lookup table map concept.

## A Simple Approach: Exponential Mapping

Remember that our goal is creating a map that generates slowly increasing outputs at small input values and quickly increasing outputs at large input values.
Some mathematical functions naturally exhibit this behavior.  For example, consider the function `f(x) = x^2` as plotted below.
![y=x^2]({{ baseImagePath }}/LUT_x2_0.png)
You can see that the slope increases as the value of x increases, which fits our needs.  Let's try using this with our existing arcade drive.

1. Open `Drive_Arcade.vi` from the earlier exercise and go to the block diagram
2. If you've already made a deadband VI, first add that to each Joystick input
  - Even though the exponential function we'll be adding will reduce motion at small joystick values, it still won't eliminate motion at small input values
![y=x^2]({{ baseImagePath }}/LUT_x2_1.png)
3. Now, find the "Power of X" block in the function palette under "Mathematics">"Elementary & Special Functions">"Exponential Functions">"Power of X" and insert one for each joystick input.
![y=x^2]({{ baseImagePath }}/LUT_x2_2.png)
4. Right click on the "y" input and select "Create">"Control" so we have an input we can change while the program is running.
![y=x^2]({{ baseImagePath }}/LUT_x2_3.png)
5. Connect the control to both y inputs.  The control will also appear on the front panel
![y=x^2]({{ baseImagePath }}/LUT_x2_4.png)
6. Switch to the block diagram
7. As written, this exponent would use a power of 0 at startup, which would cause the motors to run at 100%.  We need to set a new default value of 1 so we get our linear mapping at startup.
8. Type '1' into the new control you made
9. Right click on the control and choose "Data Operations">"Make Current Value Default"
![y=x^2]({{ baseImagePath }}/LUT_x2_5.png)
10. Save your VI

## Try Exponential Mapping

1. Insert your modified `Drive_Arcade.vi` VI into `ArgoBot_Main.vi` like before
2. Run the code
3. The robot should drive like the original arcade drive
4. Now, open `Drive_Arcade.vi` while the code is running and change the exponent control to '2'
5. Try driving now.

D'oh! It turns out x^2 is an even function, so the sign of the input is not propagated properly to the output

## Exponential Drive Sign Fix

1. Stop your running code if it's still running
2. Open `Drive_Arcade.vi` and go to the block diagram
3. To get the original sign of the inputs, insert a sign block from the numeric palette for each input
![y=x^2]({{ baseImagePath }}/LUT_x2_6.png)
4. For each output we want to ensure it has the same sign as the input
  - The idea behind this is `final_output = sign(input) * absolute_value(exponential_output)`
5. Insert multiply and absolute value blocks from the numeric palette to implement this strategy
![y=x^2]({{ baseImagePath }}/LUT_x2_7.png)
6. Now try driving the robot with this corrected exponential drive
7. What do you notice as you increase the exponent?

## Lookup Table Maps' Advantage

You may be thinking "if exponential drive is so great, why do we need the complexity of lookup table maps?"
You have a good point, sometimes exponential drive is good enough just like sometimes linear drive with a deadband is good enough.
However, there are times when we want to fine-tune the drive train to help the driver maneuver around the field.
Lookup table maps give us full control of how the inputs affect the outputs.

## Lookup Table Design

We'll do this by making a "look up table", which is a set of reference input-output correspondences.
For example, if we have the following table:

| Input | Output |
| ----- | ------ |
| 0     | 0      |
| 0.1   | 0      |
| 0.11  | 0.2    |
| 0.7   | 0.4    |
| 1     | 1      |

Now, if we have a joystick input of 0.1, there will be no output \(just like our deadband VI\).
If we have a joystick value of 0.11, the input jumps to 0.2, which may correspond to the minimum motor power to move the robot.
What if the input doesn't match any of the input values?
In this case, we'll use a concept called 'linear interpolation'.

Imagine the inputs as x values and outputs as y values on a plot.
![Linear Interpolation]({{ baseImagePath }}/LUT_lut_0.png)

If an input `x` is not at the endpoints, we will find a y value that falls on the line drawn between the known points.

This may sound complicated, but implementing this in LabVIEW is easy!
If you're interested in more information on how this works, you should read about it on [Wikipedia](https://en.wikipedia.org/wiki/Linear_interpolation).

## Lookup Table Map Implementation

1. First, create a new VI like we did in [the Deadband tutorial]({{site.baseurl}}/tutorials/5/index.html#making-a-new-vi)
  - Call this VI `LookupTableMap.vi`
  - You can create an icon if you like
  - Choose an I/O pattern with at least three inputs and at least one output
2. Go to the block diagram
3. From the array palette, add a "Threshold 1D Array" block
  - An array is an ordered list of elements that are accessed using an 'index'
  - The index is like the address of an element so you can tell where an element is located within the array
  - The "Threshold 1D Array" block finds where in a sorted array a new element would fit
  - If the element is already in the array, the block returns the index of the duplicate
  - If the element is not in the array, the block uses linear interpolation to find a "fractional index" showing how close it is to existing elements
![Threshold 1D Array]({{ baseImagePath }}/LUT_lut_1.png)
4. Now add an "Interpolate 1D Array" block from the array palette
  - This block takes the fractional index generated by the threshold block and uses linear interpolation to generate an output
![Interpolate 1D Array]({{ baseImagePath }}/LUT_lut_2.png)
5. Wire the two blocks together so the output of the threshold block feeds the fractional index of the interpolate block
6. Add controls for the remaining three inputs
  - We will not use the "start index" input to the threshold block, so leave it unwired
7. In the same way, add an indicator for the output of the interpolate block
![LUT Wiring]({{ baseImagePath }}/LUT_lut_3.png)
8. On the front panel, wire the controls and indicators to inputs and outputs respectively
![LUT Front Panel]({{ baseImagePath }}/LUT_lut_4.png)
9. Save your VI

That's all there is to it!  Now, we're ready to use the lookup table map VI in our drive code

## Lookup Table Map Integration

1. Open `Drive_Arcade.vi`
  - You may want to make a new copy and name it something new like `Drive_Arcade_LUT.vi` so you still have the old arcade drive to use
2. Add your new `LookupTableMap.vi` to each joystick VI like we did with the deadband VI
  - The joystick value should come in the 'X' input and come out the 'Y' output
![Integration Block Diagram]({{ baseImagePath }}/LUT_lut_5.png)
3. Create controls for both X and Y Arrays of the LUT VIs
  - Make sure you give them good names so you know what's what on the front panel
![Integration Block Diagram]({{ baseImagePath }}/LUT_lut_6.png)
4. On the front panel, organize the controls so everything is easy to access
5. Expand each array control so at least 9 values are visible
  - Do this by dragging the resize dot down to show more elements
![Integration Front Panel]({{ baseImagePath }}/LUT_lut_7.png)
6. It would be nice to visualize these maps, so let's add some graphs!
  - Graphs on robot control VIs won't be visible during competition, but they allow us to visualize control elements during development and testing
7. On the front panel, insert two "XY Plot"s
![Integration Front Panel]({{ baseImagePath }}/LUT_lut_8.png)
8. Arrange and name the plots for clarity
9. Set the X and Y ranges of the plots to [-1, 1] by clicking on the axis labels and typing in new values
10. Right click on each plot axis and uncheck the "AutoScale" option so the plots always show the full range of values
![Integration Front Panel]({{ baseImagePath }}/LUT_lut_9.png)
11. On the block diagram, add a "bundle" block from the "Cluster, Class, & Variant" palette
  - This will combine the X and Y arrays to create a plot
![Integration Block Diagram]({{ baseImagePath }}/LUT_lut_10.png)
12. Connect the X and Y arrays to the bundle block then to the plot indicator for both plots
![Integration Block Diagram Final]({{ baseImagePath }}/LUT_lut_11.png)
13. On the front panel again, let's put in some values.
  - Start with the values shown below
  - Remember to cover the entire range of inputs [-1, 1]
  - When you're complete, make sure you set the values as default so you don't lose them after closing the VI
  - Don't worry that your graphs don't show anything yet, they'll show up after you run the VI
![Integration Front Panel Final]({{ baseImagePath }}/LUT_lut_12.png)
14. Save your VI

## Try It Out

1. Add your new LUT arcade drive to `ArgoBot_Main.vi`
2. Run the code
3. While the code is running, open your LUT arcade drive
4. Try driving around
5. Try modifying the LUT values and see how driving changes

What changes make the robot easier to drive?
Can you think of any situations where using LUT gives the driver an advantage over simple deadbands or exponential drive?

Now we've got some more advanced methods to translate human input to robot drive.
You may have noticed all the controls we've made so far work independent of time.
For example, when I input some joystick value, it will always output the same value regardless of what has happened in the past.
This is important, but what if we have our controls make decisions based on history (or predictions of the future)?

Next up, using history to improve digital controls!

| ------------------- |:-------------:| --------------:|
| [<-Previous][PREV]  | [Index][HOME] | [Next->][NEXT] |
