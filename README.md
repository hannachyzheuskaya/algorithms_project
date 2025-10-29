# Highway Planner

Algorithms and Data Structures — Final Project (2022–2023)
Politecnico di Milano

## Description

This project was developed as the Final Exam Project for the course _Algoritmi e Principi dell'Informatica_ in the academic year 2022–2023.  
It received the maximum grade: **30/30 cum laude**.

## Implementation Details

The project is implemented in the C programming language.

Key technical constraints and choices:

- **Language standard:** C11
- **Libraries:** only the Standard C Library (`libc`) is used
- **Concurrency:** no multithreading is used
- **I/O model:**
  - Input is provided via `stdin`
  - Output is written to `stdout`

## Project Structure

The project models a **highway** as an ordered list of **service stations**.

- Each station is identified by its distance from the beginning of the highway.
- Each station maintains a set of **electric vehicles**, and every vehicle is characterized by its driving range (autonomy).

In other words, you can think of the highway as a sequence of checkpoints, and at each checkpoint there are zero or more available electric cars, each with a certain maximum distance it can cover.

## Goal of the System

The core goal is to compute a route between two given stations that uses the **minimum possible number of legs (stops)**.

Important constraints:

- Every leg of the journey is traveled using **one vehicle chosen from the origin station of that leg**.
- You are allowed to switch vehicles at every station you stop at.
- The algorithm is only responsible for **planning** this route.  
  No vehicle is physically moved or reassigned in the data model when a route is requested.

So the system answers the question:

> "Starting from station A and wanting to reach station B, what is the path with the fewest stops, assuming I can pick any car available at the current station to cover the next jump?"

## Supported Commands and Expected Behavior

The program supports a set of text commands to manage the highway and to plan routes.  
All commands are read from `stdin`, and each command produces a deterministic response on `stdout`.

- `aggiungi-stazione` : Adds a new service station to the highway with a specific distance and an initial set of electric vehicles, each with a defined range.
- `demolisci-stazione` : Removes an existing service station, identified by its distance.
- `aggiungi-auto` : Adds an electric vehicle (with a specified autonomy / range) to an existing service station.
- `rottama-auto` : Scraps (removes) a specific electric vehicle from a given service station.
- `pianifica-percorso` : Computes the route with the minimum number of legs between two given stations.

## Tie-breaking Rule for Ambiguous Paths

In some cases, multiple different routes may have the same minimum number of legs.

When two or more candidate routes have equal length, the implementation applies the following deterministic tie-break rule:

> Among the shortest routes, prefer the one that, in its final portion, visits stations that are **closer to the beginning of the highway** (i.e. stations with a lower distance value).

This ensures that results are consistent and reproducible even in the presence of multiple optimal solutions.

---

## Example Usage

Below is an example session showing input commands and the corresponding program output.

### Input

```text
aggiungi-stazione 20 3 5 10 15
aggiungi-stazione 4 3 1 2 3
aggiungi-stazione 30 0
demolisci-stazione 3
demolisci-stazione 4
aggiungi-auto 30 40
aggiungi-stazione 50 3 20 25 7
rottama-auto 20 8
rottama-auto 9999 5
rottama-auto 50 7
pianifica-percorso 20 30
pianifica-percorso 20 50
pianifica-percorso 50 30
pianifica-percorso 50 20
aggiungi-auto 50 30
pianifica-percorso 50 20
```

### Output

```text
aggiunta
aggiunta
aggiunta
non demolita
demolita
aggiunta
aggiunta
non rottamata
non rottamata
rottamata
20 30
20 30 50
50 30
50 30 20
aggiunta

```

## Reference Materials

- `main.c` : main program implementation.
- `project_specification.pdf` : detailed description of all functional requirements.
- `test.py` : Python script used to execute the provided tests.

## Tools used

- Valgrind;
- Callgrind;
- Massif-Visualizer;
- Address-Sanitizer;
- GDB;
- GCC.

## Software used

- Clion;
- Visual Studio Code.
