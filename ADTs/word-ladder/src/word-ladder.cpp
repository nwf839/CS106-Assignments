/**
 * File: word-ladder.cpp
 * ---------------------
 * Implements a program to find word ladders connecting pairs of words.
 */

#include <iostream>

#include "console.h"
#include "lexicon.h"
#include "strlib.h"
#include "simpio.h"
#include "queue.h"
#include "vector.h"
#include "set.h"

static std::string getWord(Lexicon& english, std::string prompt) {
    while (true) {
        string response = trim(toLowerCase(getLine(prompt)));
        if (response.empty() || english.contains(response)) return response;
        cout << "Your response needs to be an English word, so please try again." << endl;
    }
}

static void generateLadder(Lexicon& english, std::string start, std::string end) {
    cout << "Here's where you'll search for a word ladder connecting \"" << start << "\" to \"" << end << "." << endl;
    Queue<Vector <std::string> > ladders;
    Vector<std::string> ladder;
    Set<std::string> repeatWords;
    ladder += start;
    ladders.enqueue(ladder);
    while (ladders.size() != 0)
    {
        ladder = ladders.dequeue();
        if (ladder[ladder.size() - 1] == end)
        {
            for (int i = 0; i < ladder.size() - 1; i++)
            {
                std::cout << ladder[i] << " -> ";
            }
            std::cout << ladder[ladder.size() - 1] << std::endl;
        }
        else
        {
            for (int i = 0; i < start.length(); i++)
            {
                for (char letter = 'a'; letter <= 'z'; letter++)
                {
                    std::string nextWord = ladder[ladder.size() - 1];
                    nextWord[i] = letter;
                    if (english.contains(nextWord) && !repeatWords.contains(nextWord))
                    {
                        repeatWords += nextWord;
                        Vector<std::string> nextLadder = ladder;
                        nextLadder += nextWord;
                        ladders.enqueue(nextLadder);
                    }
                }
            }
        }
    }

   }


static const std::string kEnglishLanguageDatafile = "EnglishWords.dat";
static void playWordLadder() {
    Lexicon english(kEnglishLanguageDatafile);
    while (true) {
        std::string start = getWord(english, "Please enter the source word [return to quit]: ");
        if (start.empty()) break;
        std::string end = getWord(english, "Please enter the destination word [return to quit]: ");
        if (end.empty()) break;
        generateLadder(english, start, end);
    }
}

int main() {
    std::cout << "Welcome to the CS106 word ladder application!" << std::endl << std::endl;
    playWordLadder();
    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}
