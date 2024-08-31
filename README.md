# Briscola Card Game

**Description**  
This project is a terminal-based copy of the traditional italian card game "briscola". This game allows you to play against a CPU.

## Rules

The rules of the game are as follows:

- Each player is given 3 cards.
- The last card of the deck is shown. Its suit will be the "briscola", the dominant suit which beats all others.
- The game proceeds with players taking turns to play a card.
- The player who plays the higher value card of the same suit or a briscola wins the round and takes both cards.

## How to Play

1. **Starting the Game:**
   - The game will randomly choose whether the player or the CPU goes first.

2. **Drawing Cards:**
   - At the beginning of each turn, both the player and the CPU will draw cards from the deck until each has 3 cards.

3. **Player's Turn:**
   - The player is prompted to choose a card from their hand by entering a number corresponding to the card they want to play.

4. **CPU's Turn:**
   - The CPU will play a card based on simple strategies:
     - If the CPU goes first, it will play the lowest value non-briscola card if available. If not, it will play the lowest value briscola card.
     - If the CPU goes second, it will choose a card based on the player's card. It aims to win the round using briscola cards or the highest card of the same suit if possible.

5. **Winning the Round:**
   - The player or CPU with the higher value card of the dominant suit or the briscola wins the round.
   - Points are accumulated based on the value of the cards won.

6. **Game End:**
   - The game continues until all cards are played.
   - The player with the most points at the end of the game is declared the winner.

## Installation

**Prerequisites**
- C++ compiler (e.g., g++, clang)

**Steps**

```bash
# Clone the repository
git clone https://github.com/FlavioMili/Briscola.git

# Navigate to the project directory
cd Briscola

# Compile the game
g++ -std=c++17 -o briscola briscola.cpp 

# Run the game
./briscola


