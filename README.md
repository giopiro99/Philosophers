# 🍝 Philosophers - I Eat, Therefore I Sleep

**Philosophers** is a project from the **42 School** curriculum designed to teach the fundamentals of **concurrency**, **threading**, and **process synchronization**.

The goal is to solve the classic "Dining Philosophers" problem, creating a simulation where philosophers alternate between eating, sleeping, and thinking, all while managing shared resources (forks) without succumbing to deadlocks or starvation.

## 🧠 The Problem

Several philosophers are sitting at a round table doing one of three things: eating, sleeping, or thinking.
* To eat, they need **two forks**.
* There is exactly one fork between each pair of philosophers.
* Ideally, no philosopher should starve.
* Philosophers don't speak with each other.
* Philosophers don't know when another philosopher is about to die.

The challenge is to design an algorithm that keeps the philosophers alive as long as possible (or infinitely) using specific synchronization primitives.

---

## 🏗️ Architecture & Implementation

The project is divided into two parts, each using different system primitives to handle concurrency.

### 🧵 Mandatory: Threads & Mutexes
* **Program:** `philo`
* **Entity:** Each philosopher is a **Thread**.
* **Resources:** Forks are **Mutexes**.
* **Shared Memory:** Since threads share the same address space, synchronization is handled via mutex locks (`pthread_mutex_lock`).
* **Deadlock Prevention:** To avoid deadlocks (where everyone holds one fork and waits for the other), I implemented an **Odd/Even fork assignment strategy**:
    * Even-numbered philosophers pick up the right fork first.
    * Odd-numbered philosophers pick up the left fork first.
    * This breaks the circular dependency chain.

### 🚥 Bonus: Processes & Semaphores
* **Program:** `philo_bonus`
* **Entity:** Each philosopher is a **Process** (`fork()`).
* **Resources:** Forks are represented by a **Semaphore** (`sem_t`).
* **Isolated Memory:** Processes do not share memory. Synchronization implies using named semaphores (`/forks`, `/write`, etc.) located in the system's semaphore table.
* **Logic:** All forks are in the middle of the table (a semaphore with value = `number_of_philosophers`). Philosophers `wait` to take a fork and `post` to return it.

---

## 🛠️ Tech Stack

* **Language:** C
* **Threads:** `pthread` library (`pthread_create`, `pthread_join`, `pthread_mutex_*`)
* **Processes:** `fork`, `kill`, `waitpid`
* **Synchronization:** `semaphore.h` (`sem_open`, `sem_wait`, `sem_post`)
* **Time:** `gettimeofday` for millisecond-precision timing.

---

## 🚀 Installation & Usage

### Compilation
Use the provided `Makefile` to compile the project.

```bash
# Compile the mandatory part (Threads)
make
# Compile the bonus part (Processes)
make bonus
```
``` text
Execution
Run the simulation by passing the required arguments:
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
Example:
Bash
./philo 5 800 200 200
5 Philosophers
Die if they don't eat for 800ms
Take 200ms to eat
Take 200ms to sleep
number_of_philosophers	count	The number of philosophers and also the number of forks.
time_to_die	ms	If a philosopher doesn't start eating time_to_die ms after the beginning of their last meal, they die.
time_to_eat	ms	The time it takes for a philosopher to eat. During this time, they hold two forks.
time_to_sleep	ms	The time a philosopher will spend sleeping.
number_of_times_...	count	(Optional) If all philosophers have eaten at least this many times, the simulation stops. If not specified, the simulation stops only when a philosopher dies.
```

```text
Structure:
.
├── Makefile                # Compilation rules
├── philo/                  # Mandatory Part (Threads)
│   ├── philo.c             # Main entry point
│   ├── init_data.c         # Initialization of structs and mutexes
│   ├── dinner.c            # Main simulation loop (Eat/Sleep/Think)
│   ├── monitor.c           # Thread checking for death/fullness
│   ├── syncro.c            # Time and synchronization utilities
│   ├── safe_read.c         # Thread-safe getters/setters
│   └── utils.c             # Logging and helpers
└── philo_bonus/            # Bonus Part (Processes)
    ├── philo_bonus.c       # Main entry point
    ├── dinner_bonus.c      # Routine for child processes
    ├── monitoring_bonus.c  # Death check inside processes
    └── init_data_bonus.c   # Initialization of semaphores
```

***🧠 What I Learned***

Race Conditions: How simultaneous access to data can corrupt memory and how to prevent it.

Mutex vs Semaphores: The difference between binary locks (ownership) and counting signals (availability).

Context Switching: The overhead differences between switching threads vs processes.

Starvation: Designing logic to ensure fair resource distribution.
