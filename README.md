# Philosopher-42  
The goal of this project is extremely similar to the well-known dining philosophers problem, but with different restrictions. We take 4 to 5 arguments when we launch the program and run the simulation with those 5 parameters.  
```
First argument : number_of_philosophers
Second argument : time_to_die (in milliseconds)
Third argument : time_to_eat (in milliseconds)
Fourth argument : time_to_sleep (in milliseconds)
Fifth argument : nbr_times_to_eat (optional argument)  
```
If the fifth argument is 0 or none is given, we just run the simulation until a philosopher dies.

# Mandatory part  

The mandatory part forces you to only use mutexes and no semaphores. My solution was to make the odd-numbered philosophers eat first, then make the even-numbered philosophers eat after, while avoiding deadlock and race conditions. In order to implement a solution that was solid, I first started with this:
![This is an image](https://github.com/Producks/Philosopher-42/blob/main/doc/double%20arrow.PNG?raw=true)

When I give the forks away to the threads, I follow the fork priority image. Odd-numbered philosophers always grab the first fork to their left, and even-numbered philosophers always grab their right fork. This makes it so there is no way to deadlock. I also have a timer at the beginning of the simulation launch where even-numbered philosophers wait for time_to_eat / 2 before they start eating. This makes it synchronize better.
# Bonus Part
BONUS IS NOT CORRECT, IT"S MEANT TO BE USED WITH FORKS NOT PTHREAD. threads aren't process 
The bonus part cannot use mutexes, but we get access to semaphores! The forks are also all in the middle, represented by a semaphore. Since we can't do it like in the image, I created an extra semaphore called "availability" which contains the number of philosophers / 2. This avoids any potential deadlock.
