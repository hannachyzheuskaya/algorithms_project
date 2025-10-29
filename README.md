Final Project C(2022–2023)

## Description

This project was developed as the Final Exam Project for the course _Algoritmi e Principi dell'Informatica_ in the academic year 2022–2023.  
It received the maximum grade: **30/30 cum laude**.

## Implementation Details

The project is implemented in the C programming language.

Key technical constraints and choices:

- **Language standard:** C11
- **Libraries:** only the Standard C Library (`libc`) is used
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

### `aggiungi-stazione`

Adds a new service station to the highway.

The station is characterized by:

- its distance from the start of the highway
- a set of electric vehicles, each with a given range

### `demolisci-stazione`

Removes an existing service station, identified by its distance.

### `aggiungi-auto`

Adds an electric vehicle (with a specified autonomy / range) to an existing service station.

### `rottama-auto`

Removes (“scraps”) a specific electric vehicle from a given service station.

### `pianifica-percorso`

Computes and returns the route with the **minimum number of legs** between two given stations.

The output of this command represents the planned sequence of stations to visit in order to travel from the origin to the destination under the movement rules described above.

## Tie-breaking Rule for Ambiguous Paths

In some cases, multiple different routes may have the same minimum number of legs.

When two or more candidate routes have equal length, the implementation applies the following deterministic tie-break rule:

> Among the shortest routes, prefer the one that, in its final portion, visits stations that are **closer to the beginning of the highway** (i.e. stations with a lower distance value).

This ensures that results are consistent and reproducible even in the presence of multiple optimal solutions.
