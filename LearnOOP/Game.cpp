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

    void resetScore()
    {
        score = 0;
    }
};

// the third class to create is the Game class, which will manage the players and the dice, process the game and determine the winner
class Game0
{
private:
    Dice dice;
    Player player1, player2;

public:
    // so what do we need to initialize a game? For the basic version, we just need two players and a dice.
    // constructor with default parameter
    Game0(string name1, string name2) : player1(name1), player2(name2) {}
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
    friend void restart(); // declare the restart function as a friend of the Game class
};

// int main()
// {
//     srand(static_cast<unsigned int>(time(0))); // seed the random number generator
//     Game0 game("Alice", "Bob");
//     game.start();
//     return 0;
// }

// 进一步优化这个游戏，增加一些功能。
// 1.游戏结束后，询问玩家是否想要再玩一次，如果是，则重新开始游戏；如果不是，则退出程序。

void restart()
{
    char choice;
    cout << "Do you want to play again? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y')
    {
        Game0 game("Alice", "Bob");
        game.start();
    }
    else
    {
        cout << "Thanks for playing! Goodbye!" << endl;
        exit(0);
    }
}

// 2.玩家可以给角色命名，并且可以决定玩家数量。

// 3.玩家可以选择他们想要玩的轮数，而不是固定的5轮。

class Game
{
private:
    Dice dice;
    Player *players; // 使用数组来存储，这样就可以支持任意数量的玩家
    int numPlayers;
    int NumRounds;

public:
    Game(int N, int n) : NumRounds(N), numPlayers(n)
    {
        players = new Player[numPlayers];
        for (int i = 0; i < numPlayers; ++i)
        {
            string name;
            cout << "Enter name for player " << i + 1 << ": ";
            cin >> name;
            players[i] = Player(name);
        }
        do
        {
            for (int i = 0; i < numPlayers; ++i)
                players[i].resetScore();

            for (int i = 0; i < NumRounds; ++i)
                forward(players, numPlayers);

            determineWinner(players, numPlayers);

        } while (restart());
    }

    void determineWinner(Player *players, int numPlayers)
    {
        int maxScore = 0, winnerIndex = 0;
        for (int i = 0; i < numPlayers; ++i)
        {
            cout << players[i].getName() << " has a score of " << players[i].getScore() << endl;
            if (players[i].getScore() > maxScore)
            {
                maxScore = players[i].getScore();
                winnerIndex = i;
            }
        }
        cout << "The winner is " << players[winnerIndex].getName() << " with a score of " << maxScore << "!" << endl;
    }

    void forward(Player *players, int numPlayers)
    {
        for (int i = 0; i < numPlayers; ++i)
            players[i].play(dice);
    }

    bool restart()
    {
        char choice;
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
        return (choice == 'y' || choice == 'Y');
    }
};

int main()
{
    srand(static_cast<unsigned int>(time(0))); // seed the random number generator
    int numPlayers, numRounds;
    cout << "Enter the number of players: ";
    cin >> numPlayers;
    cout << "Enter the number of rounds: ";
    cin >> numRounds;
    Game game(numRounds, numPlayers);
    return 0;
}