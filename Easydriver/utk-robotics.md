The EasyStepper libraries have been slightly modified on the live robot.

I am not sure if this is the true EasyStepper library as released by the original author or not. Hopefully it still works for you.
```
28c28
<    EasyStepper(int number_of_steps, int dir_pin, int step_pin, long initial_speed);
---
>    Stepper(int number_of_steps, int dir_pin, int step_pin, long initial_speed);


27c27
< EasyStepper::EasyStepper(int number_of_steps, int dir_pin, int step_pin, long initial_speed)
---
> EasyStepper::EasyStepper(int number_of_steps, int dir_pin, int step_pin, long inital_speed)
33c33
<  this->speed = initial_speed;
---
>  this->initial_speed = initial_speed;
```
