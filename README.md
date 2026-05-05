*This project has been created as part of the 42 curriculum by <manmarqu>.*

## Description

**Philosophers** is a 42 school project that simulates the classic [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem), formulated by Edsger Dijkstra in 1965.

N philosophers sit at a round table with N forks between them. Each philosopher alternates between eating (requiring both adjacent forks), sleeping, and thinking. The simulation ends when a philosopher dies of starvation or — optionally — when all philosophers have eaten a minimum number of times.

The goal is to implement a concurrent solution using **POSIX threads** and **mutexes** with no data races, no deadlocks, and accurate death detection.

## Instructions

### Compilation

```bash
make        # builds philo
make clean  # removes object files
make fclean # removes object files and binary
make re     # full rebuild
```

### Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

All time values are in milliseconds.

### Examples

```bash
./philo 5 800 200 200        # 5 philosophers, nobody should die
./philo 5 800 200 200 7      # stops after each philosopher eats 7 times
./philo 1 800 200 200        # 1 philosopher always dies (only one fork)
./philo 4 410 200 200        # tight timing, nobody should die
```

### Output format

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

## Technical decisions

- **Deadlock prevention**: odd-numbered philosophers take left fork first, even-numbered take right fork first. This breaks the symmetry that causes deadlock.
- **Death detection**: a dedicated monitor thread checks every 0.5ms whether any philosopher has exceeded `time_to_die` without eating.
- **Atomic death print**: `simulation_over` is set and the death message is printed under the same `print_mutex` lock, guaranteeing no messages appear after `died`.
- **Smart sleep**: instead of a single long `usleep`, we loop with 100-500µs intervals checking `simulation_over` for fast reaction to deaths.

## Resources

- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming - Lawrence Livermore](https://hpc-tutorials.llnl.gov/posix/)
- [pthread_mutex_lock man page](https://linux.die.net/man/3/pthread_mutex_lock)
- [gettimeofday man page](https://linux.die.net/man/2/gettimeofday)
- [Philosophers Visualizer](https://nafuka11.github.io/philosophers-visualizer/)
- [CodeVault - Threads playlist (YouTube)](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
