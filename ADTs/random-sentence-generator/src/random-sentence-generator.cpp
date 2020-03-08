/**
 * File: random-sentence-generator.cpp
 * -----------------------------------
 * Presents a short program capable of reading in
 * context-free grammar files and generating arbitrary
 * sentences from them.
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include "console.h"
#include "simpio.h"   // for getLine
#include "strlib.h"   // for toLowerCase, trim
#include "random.h"
#include "map.h"

void buildMap(Map<std::string,Vector<std::string> > & tagMap, std::ifstream & infile);
//std::string generateSentence(Map<std::string,Vector<std::string> > & tagMap);
std::string generateSentence(Map<std::string,Vector<std::string> > & tagMap);
std::string findTag(std::string & str);

static const std::string kGrammarsDirectory = "grammars/";
static const std::string kGrammarFileExtension = ".g";
static std::string getNormalizedFilename(std::string filename) {
    std::string normalizedFileName = kGrammarsDirectory + filename;
    if (!endsWith(normalizedFileName, kGrammarFileExtension))
        normalizedFileName += kGrammarFileExtension;
    return normalizedFileName;
}

static bool isValidGrammarFilename(std::string filename) {
    std::string normalizedFileName = getNormalizedFilename(filename);
    std::ifstream infile(normalizedFileName.c_str());
    return !infile.fail();
}

static std::string getFileName() {
    while (true) {
        std::string filename = trim(getLine("Name of grammar file? [<return> to quit]: "));
        if (filename.empty() || isValidGrammarFilename(filename)) return filename;
        std::cout << "Failed to open the grammar file named \"" << filename << "\". Please try again...." << std::endl;
    }
}

int main() {
    while (true) 
    {
        std::string filename = getFileName();
        if (filename.empty()) break;
        Map<std::string,Vector<std::string> > tagMap;
        std::ifstream infile;
        infile.open(getNormalizedFilename(filename.c_str()));
        buildMap(tagMap, infile);
        for (int i = 0; i < 3; i++)
        {
            std::cout << generateSentence(tagMap) << std::endl;
        }
        std::cout << "Thanks for playing!" << std::endl;
        infile.close();
    }
    return 0;
}

void buildMap(Map<std::string,Vector<std::string> > & tagMap, std::ifstream & infile)
{
    std::string line;
    int n;
    while (std::getline(infile, line))
    {
        std::string key = line;
        std::getline(infile, line);
        n = stringToInteger(line);
        Vector<std::string> values;
        for (int i = 0; i < n; i++)
        {
            std::getline(infile, line);
            values += line;
        }
        tagMap.put(key, values);
        std::getline(infile, line);
    }
}


std::string generateSentence(Map<std::string,Vector<std::string> > & tagMap)
{
    int tagStart;
    std::string sentence = "<start>";
    std::string tag = findTag(sentence);
    while (tag != "")
    {
        tagStart = sentence.find(tag);
        sentence.erase(tagStart, tag.length());
        sentence.insert(tagStart, tagMap[tag][randomInteger(0, tagMap[tag].size() - 1)]);
        tag = findTag(sentence);
    }

    return sentence;
}

// Returns first tag or empty string in its absence
std::string findTag(std::string & sentence)
{
    std::istringstream inStream(sentence);
    std::ostringstream tag;
    char ch;
    bool tagFound = false;

    while (inStream.get(ch))
    {
        if (ch == '<')
        {
            tagFound = true;
        }
        if (tagFound == true)
        {
            tag.put(ch);
        }
        if (ch == '>')
        {
            return tag.str();
        }
    }
    return tag.str();
}
