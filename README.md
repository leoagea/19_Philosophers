# Philosophers

This repository contains my implementation of the **Philosophers** project from [42](https://www.42.fr/).  
The project highlights and analyzes the well-known synchronization challenge called the “Dining Philosophers Problem,” originally proposed by Edsger Dijkstra.

![Grade](docs/Grade.png)

Link to the subject: [Click Here](docs/en.subject.pdf)
## Table of Contents

1. [About the Project](#about-the-project)  
2. [Project Structure](#project-structure)  
3. [Rules and Constraints](#rules-and-constraints)  
4. [Compilation](#compilation)  
5. [Usage](#usage)  

---

## About the Project

**Philosophers** presents a scenario in which several philosophers sit around a table, each with a fork (or chopstick) on their left and right sides. To eat, a philosopher must acquire both adjacent forks. The challenge lies in managing concurrency and synchronization to avoid undesirable situations:

- **Deadlock**: Every philosopher picks up one fork and waits indefinitely for the other.  
- **Starvation**: A philosopher is never able to eat because resources (forks) are always held by others.

This project requires using threads (or processes, depending on your version of the assignment) and synchronization mechanisms such as **mutexes** or **semaphores** to control access to forks and to ensure the simulation runs correctly.

### Learning Objectives

- Create, manage, and terminate threads (or processes).  
- Understand synchronization issues in concurrent programming.  
- Correctly handle mutexes, semaphores, or other locking primitives.  
- Write robust code that avoids deadlocks, race conditions, etc.

## Mandatory vs. Bonus

### Mandatory (Threads + Mutexes)
- **Implementation**: Each philosopher is represented by a thread. You must use **mutexes** (or equivalent locks) to protect shared resources—specifically the forks—ensuring no two philosophers hold the same fork simultaneously.
- **Execution Flow**: You create one thread per philosopher. Each thread loops through the “eat, sleep, think” cycle. A shared data structure (protected by mutexes) keeps track of fork usage and times (for dying, sleeping, etc.).
- **Death Detection**: If a philosopher doesn’t eat within `time_to_die` milliseconds, the simulation ends immediately. This check can be done either by a monitoring thread or each philosopher thread checking itself.

### Bonus (Processes + Semaphores)
- **Process Model**: Instead of threads, each philosopher is represented by a **separate process**. You must use **semaphores** to control access to shared resources like forks and to coordinate actions between processes.
  - **Example**: A semaphore for the forks (initialized to the number of forks), plus optional semaphores for logging or to protect read/write of shared variables.
- **Fork and Exec**: Typically, you `fork()` one child per philosopher. Each child process then follows the philosopher routine independently, using semaphores to ensure synchronization.
- **Death Detection**:  
  - One common approach is to have a separate “monitor” process or to use signals and shared memory.  
  - Alternatively, each philosopher process can track its own eating time and notify a controller process (via semaphores or pipes) if it dies.
- **Behavioral Differences**: Semaphores can simplify or complicate certain aspects (like counting how many philosophers can pick up forks simultaneously). They also require careful handling of process termination and cleanup to avoid orphaned semaphores.

This breakdown ensures you highlight the distinct concurrency mechanisms for each version:
- **Mandatory**: Threads + mutexes.  
- **Bonus**: Processes + semaphores.  

---

## Project Structure

Two directories, one is philo, the other is philo_bonus that contains both:


- **inc/**: Contains header files, function prototypes, and shared data structures.  
- **src/**: Source files for initialization, simulation, monitoring, and other logic.  
- **Makefile**: Defines targets like `all`, `clean`, `fclean`, and `re`.

---

## Rules and Constraints

Typical rules (may vary based on your specific instructions):

1. **Number of Philosophers**: An integer `N` representing how many philosophers sit around the table.  
2. **Time to Eat**: How long a philosopher spends eating (usually in milliseconds).  
3. **Time to Sleep**: How long a philosopher sleeps after eating.  
4. **Time to Die**: The maximum time a philosopher can go without eating before dying.  
5. **Number of Meals** (optional): Each philosopher must eat a certain number of times before the simulation stops.

The program often receives these arguments, for example:

./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]


- The simulation ends if a philosopher dies (fails to eat in time) or if all philosophers have eaten the required number of meals (if provided).

---

## Compilation

1. Git clone the project and go in directory:

```bash
git clone https://github.com/leoagea/19_Philosophers.git Philo
cd Philo
```

2. Compile the project, run:

```bash
make
```

---

## Usage

Run something like this:

```bash
./philo 5 800 200 200
```
When:

- 5  philosophers
- 800 ms before a philospher dies
- 200 ms time to eat
- 200 ms time to sleep

Another exemple with a required number of meals:

```bash
./philo 5 800 200 200 7
```

Ends the simulation when each philosopher has eaten at least 7 times (or if any philosopher dies first).


## Cross-Platform Note

To maintain compatibility between macOS and Linux, certain format specifiers or types may differ slightly. In particular, when printing timestamps or time-related values, you might need to use different format specifiers depending on the operating system. 

The **u_int_64_t** are handle differently on macOS and linux. On linux its an **unsigned long** and on macOS its an unsigned long long.

For instance, in one of the log-printing functions, we added the following condition:

```bash
#ifdef __APPLE__
	printf("[%llu] [%d] " RED "%s" RESET "\n", time, philo->id, str);
#elif __linux__
	printf("[%lu] [%d] " RED "%s" RESET "\n", time, philo->id, str);
#endif
```


This ensures that %llu is used under macOS and %lu under Linux for proper handling of the time variable. Always verify which types and format specifiers your system expects. For other OS-specific differences, using #ifdef __APPLE__ or #ifdef __linux__ blocks helps keep the code portable.