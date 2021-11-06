# philosophers
philosophers

Overview
What you should understand to succeed this project:
• One or more philosophers are sitting at a round table either eating, either thinking, either sleeping. While they are eating, they do not think or sleep; while thinking they don’t eat or sleep; and, of course, while sleeping, they do not eat or think.
• The philosophers sit at a circular table with a large bowl of spaghetti in the center.
• There are some forks on the table. Serving and eating spaghetti with a single fork
is very inconvenient, so the philosophers will eat with two forks, one for each hand.
• Each time a philosopher finishes eating, they will drop their forks and start sleeping. Once they have finished sleeping, they will start thinking. The simulation stops when a philosopher dies.
• Every philosopher needs to eat and they should never starve.
• Philosophers don’t speak with each other.
• Philosophers don’t know when another philosopher is about to die.
• No need to say that philosophers should avoid dying!

General Instructions
You have to write a program for the mandatory part and another one for the bonus part but they will have the same basic rules:
• Global variables are forbidden!
• The program should take the following arguments: number_of_philosophers time_to_die
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
◦ number_of_philosophers: is the number of philosophers and also the number of forks.
◦ time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting their last meal or the beginning of the simulation,
it dies.
◦ time_to_eat: is in milliseconds and is the time it takes for a philosopher to eat. During that time they will need to keep the two forks.
◦ time_to_sleep: is in milliseconds and is the time the philosopher will spend sleeping.
◦ number_of_times_each_philosopher_must_eat: argument is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.
• Each philosopher should be given a number from 1 to ’number_of_philosophers’.
• Philosopher number 1 is next to philosopher number ’number_of_philosophers’. Any other philosopher with the number N is seated between philosopher N - 1 and philosopher N + 1.
About the logs of your program:
• Any change of status of a philosopher must be written as follows (with X replaced with the philosopher number and timestamp_in_ms the current timestamp in mil- liseconds):
◦ timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
• The status printed should not be scrambled or intertwined with another philoso-
pher’s status.
• You can’t have more than 10 ms between the death of a philosopher and when it will print its death.
• Again, philosophers should avoid dying!


