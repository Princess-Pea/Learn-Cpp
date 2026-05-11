#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

using namespace std;

// let's realize a simple game where players use Dice to compete with each other, the one with the highest score wins

// the first class to create is the Dice class

class Dice
{

private:
    // what do we need to store in the Dice class?

public:
    // we need a function to roll the dice (generate a random number between 1 and 6)
    int roll()
    {
        return rand() % 6 + 1;
    }
};

// the second class to create is the Player class
class Player
{
private:
    string name;
    int score;

public:
    // constructor with default parameter
    Player(string n = "") : name(n), score(0) {}

    // we need a function to enable the player to roll the dice and update their score
    void play(Dice &dice)
    {
        int rollResult = dice.roll();
        score += rollResult;
        cout << name << " rolled a " << rollResult << " and now has a score of " << score << endl;
    }

    // we also need some getter functions to access the player's name and score
    string getName() const
    {
        return name;
    }

    int getScore() const
    {
        return score;
    }
};

// the third class to create is the Game class, which will manage the players and the dice, process the game and determine the winner
class Game
{
private:
    Dice dice;
    Player player1, player2;

public:
    // so what do we need to initialize a game? For the basic version, we just need two players and a dice.
    // constructor with default parameter
    Game(string name1, string name2) : player1(name1), player2(name2) {}
    void determineWinner()
    {
        if (player1.getScore() > player2.getScore())
        {
            cout << player1.getName() << " wins with a score of " << player1.getScore() << "!" << endl;
        }
        else if (player2.getScore() > player1.getScore())
        {
            cout << player2.getName() << " wins with a score of " << player2.getScore() << "!" << endl;
        }
        else
        {
            cout << "It's a tie! Both players have a score of " << player1.getScore() << "!" << endl;
        }
    }
    void start()
    {
        cout << "Game started between " << player1.getName() << " and " << player2.getName() << "!" << endl;
        for (int i = 0; i < 5; ++i) // let's play 5 rounds
        {
            player1.play(dice);
            player2.play(dice);
        }
        determineWinner();
    }
};

int main()
{
    srand(static_cast<unsigned int>(time(0))); // seed the random number generator
    Game game("Alice", "Bob");
    game.start();
    return 0;
}