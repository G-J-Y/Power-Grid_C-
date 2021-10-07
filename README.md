# Comp345 Project tabletop game: Power Grid
A2
Part 1: Game start
Provide a group of C++ classes that implements a user interaction mechanism to start the POWER GRID game by allowing the player to:
1) Select a map (a map is separated into 6 areas, each with 7 cities) from a list of file(s) as stored in a directory.
2) Select the number of players in the game (2-6 players).
3) Each player choose which areas they will play in. It is recommended to have one area per player. Of course, the areas chosen must be adjacent. During the game, every playe can    play in all the chosen areas.

Part 2: Game play: main game loop Phase 1 and 2
Provide a group of C++ classes that implements the main game loop following the rules of the POWER GRID game. The main game loop has five phases and constitutes one game round. In each phase, all players take their actions in the order specified for the phase before the game continues with the next phase. In this part you are implementing phase 1 and 2:
  1. Determine Player Order
  2. Auction Power Plants.

Part 3: Game play: main game loop Phase 3 and 4
Provide a group of C++ classes that implements the main game loop following the rules of the POWER GRID game. During the main game loop that has five phases. In each phase, all players take their actions in the order specified for the phase before the game continues with the next phase. In this part you are implementing phase 3 and 4.
  3. Buying Resources, where the players can buy resources for their power plants from the resource market. This phase is played in reverse player order.
  4. Building, where the players start or add cities to their networks on the map.

Part 4: Game play: main game loop Phase 5
Provide a group of C++ classes that implements the main game loop following the rules of the POWER GRID game. During the main game loop that has five phases. In each phase, all players take their actions in the order specified for the phase before the game continues with the next phase. In this part you are implementing phase 5.
  5. Bureaucracy, where the players earn cash, re-supply the resource market, and remove a power plant from the power plant market, replacing it with a new one from the stack.
