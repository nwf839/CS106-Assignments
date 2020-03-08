/**
 * File: boggle.cpp
 * ----------------
 * Implements the game of Boggle.
 */
 
#include <cctype>
#include <iostream>
#include <algorithm>

#include "simpio.h"
#include "gwindow.h"
#include "gboggle.h"
#include "random.h"
#include "grid.h"
#include "vector.h"
#include "set.h"
#include "lexicon.h"

const int kBoggleWindowWidth = 650;
const int kBoggleWindowHeight = 350;

const std::string kStandardCubes[16] = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const std::string kBigBoggleCubes[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function Prototypes */
static void welcome();
static void giveInstructions();
static void shuffleBoard(Grid<char>& board, Vector<std::string>& cubes);
static bool chainExists(Grid<char>& board, const std::string& word, int row, int col);
static bool wordExists(Grid<char>& board, const std::string& word, Set<std::string>& words);

int main() 
{
   Vector<std::string> cubes;
   Grid<char> board;
   GWindow gw(kBoggleWindowWidth, kBoggleWindowHeight);
   initGBoggle(gw);
   welcome();
   if (getYesOrNo("Do you need instructions?")) 
   {
      giveInstructions();
   }
   if (getYesOrNo("Would you like to use the large board?"))
   {
       for (size_t i = 0; i < 25; i++)
       {
           cubes += kBigBoggleCubes[i];
       }
       board.resize(5, 5);
   }
   else
   {
       for (size_t i = 0; i < 16; i++)
       {
           cubes += kStandardCubes[i];
       }
       board.resize(4, 4);
   }
   shuffleBoard(board, cubes);
   std::string response;
   Set<std::string> words;
   Lexicon english("EnglishWords.dat");
   while (true)
   {
       response == getLine("Enter a word (Return to exit): ");
       if (response == "") break;
       if (!english.contains(response) || response.length() < 4)
       {
           std::cout << "Invalid word" << std::endl;
       }
       else if (wordExists(board, response, words))
       {
           std::cout << "Word found" << std::endl;
       }
       else
       {
           std::cout << "Word not found" << std::endl;
       }
   }
   return 0;
}


static void welcome() {
    std::cout << "Welcome!  You're about to play an intense game ";
    std::cout << "of mind-numbing Boggle.  The good news is that ";
    std::cout << "you might improve your vocabulary a bit.  The ";
    std::cout << "bad news is that you're probably going to lose ";
    std::cout << "miserably to this little dictionary-toting hunk ";
    std::cout << "of silicon.  If only YOU had a gig of RAM..." << std::endl << std::endl;
}

static void giveInstructions() {
    std::cout << std::endl;
    std::cout << "The boggle board is a grid onto which I ";
    std::cout << "I will randomly distribute cubes. These ";
    std::cout << "6-sided cubes have letters rather than ";
    std::cout << "numbers on the faces, creating a grid of ";
    std::cout << "letters on which you try to form words. ";
    std::cout << "You go first, entering all the words you can ";
    std::cout << "find that are formed by tracing adjoining ";
    std::cout << "letters. Two letters adjoin if they are next ";
    std::cout << "to each other horizontally, vertically, or ";
    std::cout << "diagonally. A letter can only be used once ";
    std::cout << "in each word. Words must be at least four ";
    std::cout << "letters long and can be counted only once. ";
    std::cout << "You score points based on word length: a ";
    std::cout << "4-letter word is worth 1 point, 5-letters ";
    std::cout << "earn 2 points, and so on. After your puny ";
    std::cout << "brain is exhausted, I, the supercomputer, ";
    std::cout << "will find all the remaining words and double ";
    std::cout << "or triple your paltry score." << std::endl << std::endl;
    std::cout << "Hit return when you're ready...";
    getLine();
}

static void shuffleBoard(Grid<char>& board, Vector<std::string>& cubes)
{
    for (int i = 0; i < cubes.size(); i++)
    {
        int r = randomInteger(i, cubes.size() - 1);
        swap(cubes[i], cubes[r]);
    }

    drawBoard(board.numRows(), board.numCols());
    int index = 0;
    for (int row = 0; row < board.numRows(); row++) {
        for (int col = 0; col < board.numRows(); col++) {
            board[row][col] = cubes[index][randomInteger(0, 5)];
            labelCube(row, col, board[row][col]);
            index++;
        }
    }
}


static bool chainExists(Grid<char>& board, const std::string& word, int row, int col)
{
    if (word == "") return true;
    if (word[0] != board[row][col]) return false;

    for (int drow = -1; drow <= 1; drow++) {
        for (int dcol = -1; dcol <= 1; drow++) {
            if (board.inBounds(row + drow, col+dcol))
            {
                if (chainExists(board, word.substr(1), row + drow, col + dcol))
                {
                    return true;
                }
            }
        }
    }
    return false;
}
    

static bool wordExists(Grid<char>& board, const std::string& word, Set<std::string>& words)
{   
    if (words.contains(word)) return false;

    for (int row = 0; row < board.numRows(); row++) {
        for (int col = 0; col < board.numCols(); col++) {
            if (board[row][col] == word[0])
            {
                if (chainExists(board, word.substr(1), row, col))
                {
                    recordWordForPlayer(word, HUMAN);
                    words.add(word);
                    return true;
                }
            }
        }
    }
    return false;
}
