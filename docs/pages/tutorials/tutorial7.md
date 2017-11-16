---
title: "Tutorial 7: Debounce"
permalink: /tutorials/7/index.html
---
[PREV]: {{site.baseurl}}/tutorials/6/index.html
[HOME]: {{site.baseurl}}/index.html
[NEXT]: {{site.baseurl}}/tutorials/8/index.html

{% capture baseImagePath %}{{ site.baseurl }}/assets/images/tutorials/7{% endcapture %}

# Tutorial 7: Debounce

Up until this point, all our controls have been time-independent.
A joystick input will generate the same output no matter what has happened in the past.

Sometimes, we need to use time and history to determine control behavior.
One of the simplest forms of this is digital debounce

* TOC
{:toc}

## What is "debounce"

Digital inputs have two values: 0 or 1 (sometimes referred to as "Low" and "High").
In an ideal world, an input would always neatly fit into one of these categories, but that's not always the case.

Consider the following:
![Debounce]({{ baseImagePath }}/debounce_0.png)

We expect an input (say, a button) to go cleanly from 0 to 1 when we press it.
Instead, the value may fluctuate between 0 and 1 for some period before staying at 1.
If we want to perform an event when the button is first pressed, this "bounce" would cause our event to happen more often than we want it to.

The solution to this is to add "debounce" logic to eliminate the digital "bounce".

## Control Design

To remove the bounce, we want to only change the value of a digital value if it maintains the new value for a number of consecutive cycles.
This will involve some new blocks to compare old and new values

## Implement the Design

1. Start by making a new VI named `Debounce.vi` with one boolean input, one integer input, and one boolean output
2. Because the default numeric control is floating point value (can contain decimal numbers) and we want an integer value, we'll need to change the representation of the new control.  Do this by right clicking on the control an selecting "Representation">"Unsigned Long"
  - Any of the "I" values in the representation menu are signed integers, any of the "U" values are unsigned integers (positive values only), the top row has floating point values, and the bottom row has complex numbers
  - The "32" or other numbers on the icons indicate the number of bits that represent the number inside the computer.  Larger numbers indicate the control can handle larger values.  U32 or I32 is big enough for most applications since it can hold values up to 4 billion or 2 billion, respectively
![Debounce]({{ baseImagePath }}/debounce_1.png)
3. At this point, you should have a front panel like the following:
![Debounce]({{ baseImagePath }}/debounce_2.png)
4. Switch to the block diagram
5. The new block we're going to use is the "Feedback Node".  The feedback node "remembers" the previous value put into it and returns that value on the next execution
  - When wiring the feedback node, the current value goes into the back of the arrow, and the previous value comes out the arrow head side
![Debounce]({{ baseImagePath }}/debounce_3.png)
6. Now, we want to implement the following pseudocode

```
variables: Samples, SampleCount, In, PrevOut, Out

if firstRun:
    PrevOut = In
    SampleCount = 0

if In != PrevOut:
    SampleCount = SampleCount + 1
else:
    SampleCount = 0 // Zero consecutive new value samples

if SampleCount > Samples:
    Out = In
    SampleCount = 0 // Reset sample count on output change

PrevOut = Out

Loop
```

{:start="7"}
7. If you have an idea how to do this, go ahead and try it now before viewing the solution.
8. I'm serious, it may seem complicated, but you've done all the building blocks in previous exercises
9. Need some hints?
  - The `if firstRun` block is known as 'initialization' and is necessary to set the values of the feedback nodes at the beginning.  The input at the bottom of the feedback node is for initialization
  - The `SampleCount` and `PrevOut` variables in the pseudocode correspond to two feedback nodes in the solution
  - The `if` statements can be represented by select blocks in your LabVIEW code
  - There's a block called 'Increment' in the numeric palette that you can use for the `SampleCount = SampleCount + 1` statement
10. OK.  Now that you've come up with a solution on your own, see how it compares to this solution:
![Debounce]({{ baseImagePath }}/debounce_4.png)
11. Save your VI

Great!  Now that you're getting more comfortable in LabVIEW, you should be able to translate concepts into code more easily.
Don't worry if you had to look at the solution, but if you try it on your own first the solution may help you learn more.
Now let's use your new code

## Integrate Your Code

1. Open `Drive_Button.vi` and go to the block diagram
2. Add your debounce block to one of the button inputs
3. Add a control for the 'Sample' input
4. Insert `Drive_Button.vi` into `ArgoBot_Main.vi`
5. Run your code
6. Try driving with the sample count set low (e.g. 0-5)
7. Try driving with a high sample count (e.g. >20)
8. Try tapping the button you added debounce to and see how it responds with different sample counts

What did you notice when using the debounced output?
Was there a noticeable difference between low and high sample counts?

Congratulations!  You've completed your first control component with history!
Next, we'll be implementing another component with history, speed ramping!

| ------------------- |:-------------:| --------------:|
| [<-Previous][PREV]  | [Index][HOME] | [Next->][NEXT] |
