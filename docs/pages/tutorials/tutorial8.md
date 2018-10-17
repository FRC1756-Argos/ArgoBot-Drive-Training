---
title: "Tutorial 8: Speed Ramping"
permalink: /tutorials/8/index.html
---
[PREV]: {{site.baseurl}}/tutorials/7/index.html
[HOME]: {{site.baseurl}}/index.html
[NEXT]: {{site.baseurl}}/tutorials/9/index.html

{% capture baseImagePath %}{{ site.baseurl }}/assets/images/tutorials/8{% endcapture %}

# Tutorial 8: Speed Ramping

Debounce is a great way to prevent unwanted input change in digital inputs, but what about joysticks and other analog inputs?  If we want to control how quickly an analog input can change values, we can use an approach called speed ramping.

* TOC
{:toc}

## What is "speed ramping"

Analog inputs, unlike digital inputs, can have a range of values.  Sometimes analog inputs change rapidly, but these rapidly changing values aren't as useful as more steady values.  For example, if you go from full forward to full reverse on the robot very quickly, the quick change in direction can stretch chain and put additional wear on drivetrain components.

Consider the following:
![SpeedRamp]({{ baseImagePath }}/speedRamp_0.png)

Notice how the raw input has a fast change from positive to negative, but the output smoothly transitions.  This linear ramping is a simple way to prevent "jerkiness" on the output.

## Control Design

To perform this ramping, we will utilize similar concepts to debounce where the program will compare the desired output to the previous output and ensure the difference between the previous output and the new output is below some threshold value.  This is effectively finding the slope the line in the diagram above and enforcing a maximum slope.

## Implement the Design

1. Start by making a new VI named `SpeedRamp.vi` with two numeric inputs and one numeric output
2. At this point your front panel should look like the following:
![SpeedRamp]({{ baseImagePath }}/speedRamp_1.png)
3. Switch to the block diagram
4. In addition to the feedback node we used to make debounce, we're going to use the `In Range and Coerce` VI.  This VI both detects if an input is between two values and generates an output value that is guaranteed to be between two values.  For example, if we provide an expected range of 0 to 1 with an input of 1.2, the `In Range and Coerce` VI would output `false` because 1.2 is greater than 1 and the coerced output would be `1`.  You can find the `In Range and Coerce` VI here:
![SpeedRamp]({{ baseImagePath }}/speedRamp_2.png)
5. Now, we want to implement the following pseudocode

```
variables: MaxRampRate, CommandedChange, In, PrevOut, Out

if firstRun:
    PrevOut = In
    SampleCount = 0

CommandedChange = In - PrevOut

if CommandedChange > MaxRampRate:
    CommandedChange = MaxRampRate
else if CommandedChange < -MaxRampRate:
    CommandedChange = -MaxRampRate

Out = PrevOut + CommandedChange

PrevOut = Out

Loop
```

{:start="6"}
6. If you have an idea how to do this, go ahead and try it now before viewing the solution.
7. I'm serious, it may seem complicated, but you've done all the building blocks in previous exercises
8. Need some hints?
  - The `if firstRun` block is known as 'initialization' and is necessary to set the values of the feedback nodes at the beginning.  The input at the bottom of the feedback node is for initialization
  - The `PrevOut` variable in the pseudocode corresponds to a feedback node in the solution
  - The `if ... else if` block in the middle can be represented by a `In Range and Coerce` VI
10. OK.  Now that you've come up with a solution on your own, see how it compares to this solution:
![SpeedRamp]({{ baseImagePath }}/speedRamp_3.png)
11. Save your VI

Great!  Now that you're getting more comfortable in LabVIEW, you should be able to translate concepts into code more easily.
Don't worry if you had to look at the solution, but if you try it on your own first the solution may help you learn more.
Now let's use your new code

## Integrate Your Code

1. Open `Drive_Arcade.vi` and go to the block diagram
2. Add your speed ramp block to both of the joystick inputs like this:
![SpeedRamp]({{ baseImagePath }}/speedRamp_4.png)
3. Add a control for the 'MaxRampRate' input
4. Insert `Drive_Arcade.vi` into `ArgoBot_Main.vi`
5. Run your code
6. Try driving with the sample count set low (e.g. 0.01)
7. Try driving with a high sample count (e.g. >0.1)
8. Try rapidly moving the joysticks back and forth and see what happens

## Another Bug 

:bug::honeybee::ant::beetle::bug::honeybee::ant::beetle:

You just uncovered one of the tricky parts of making VIs in LabVIEW.  It turns out that feedback nodes from different copies of the same VI can share values and interfere with each other.  We didn't see this when we made debounce because we only had one debounce block in our program.

Thankfully, this is easy to fix.  We'll have to change the properties of `SpeedRamp.vi`.

1. Open `SpeedRamp.vi` again
2. From the File menu, select VI Properties
3. In the VI Properties window, choose "Execution" from the Category selector
4. Change Reentrancy to "Preallocated clone reentrant execution".
  - We generally use "Non-reentrant execution" for VIs that do not have state (state is kept with blocks like the feedback node)
  - "Preallocated clone reentrant execution" is useful for VIs that keep state
  - We typically do not use "Shared clone reentrant execution"
  - The remaining settings on the Execution page should only be changed in special circumstances as they can impact code performance
5. When you're done, the Execution settings should look like this:
![SpeedRamp]({{ baseImagePath }}/speedRamp_5.png)
6. Try driving again with various ramp rates

What did you notice when using the speed ramped output?
Was there a noticeable difference between low and high max ramp rates?

Congratulations!  You're getting the hang of using history to enhance drive code!
Next, we'll be using what we've learned so far to make a turbo button!

| ------------------- |:-------------:| --------------:|
| [<-Previous][PREV]  | [Index][HOME] | [Next->][NEXT] |
