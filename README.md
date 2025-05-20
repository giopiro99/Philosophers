# Philosophers
Simulation of the Dining Philosophers problem using threads (mandatory) and processes with semaphores (bonus). Demonstrates concurrency, synchronization, and deadlock avoidance in C.
-------------------------------------------------------------------
Philosophers is a concurrency project that simulates the classic Dining Philosophers problem. It manages philosophers who alternate between thinking, eating, and sleeping while avoiding deadlocks and starvation.

## Features

- Implementation using threads and mutexes (mandatory part)
- Bonus: implementation using processes and semaphores for inter-process synchronization
- Correct handling of synchronization, timing, and resource sharing
- Prevention of deadlocks and race conditions
- Clean termination and resource management

---

This project deepens understanding of concurrency, synchronization primitives, and process/thread management in C.

too compile
  `bash`
    `make` or `make bonus`


./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]



./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

