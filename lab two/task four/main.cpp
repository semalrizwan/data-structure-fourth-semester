#include<iostream>
#include<fstream>
#include<string>
#include"MyStack.h"     
using namespace std;
const int MAX_WORDS = 100;
class WordStack
{
protected:
    int currentIndex;
    string* values;
    int maxCapacity;

public:
    WordStack(int _maxCapacity = 0)
    {
        currentIndex = -1;
        maxCapacity = _maxCapacity;
        values = new string[maxCapacity];
    }

    WordStack(const WordStack& W)
    {
        currentIndex = W.currentIndex;
        maxCapacity = W.maxCapacity;
        values = new string[maxCapacity];

        for (int i = 0; i <= currentIndex; i++)
            values[i] = W.values[i];
    }

    virtual void push(string v) = 0;
    virtual bool pop(string& value) = 0;

    bool isEmpty()
    {
        return currentIndex < 0;
    }

    bool isFull()
    {
        return currentIndex == maxCapacity - 1;
    }

    int size()
    {
        return currentIndex + 1;
    }
};

class MyWordStack : public WordStack
{
public:
    MyWordStack(int _maxCapacity = 0) : WordStack(_maxCapacity) {}
    MyWordStack(const MyWordStack& ms) : WordStack(ms) {}

    void push(string v)
    {
        if (!isFull())
            values[++currentIndex] = v;
        else
            cout << "Word Stack is full\n";
    }

    bool pop(string& v)
    {
        if (!isEmpty())
        {
            v = values[currentIndex];
            currentIndex--;
            return true;
        }
        return false;
    }
};

// helper function to display word stack without losing data
void displayWords(MyWordStack& S, ostream& out)
{
    MyWordStack temp(S.size());
    string x;

    while (S.pop(x))
        temp.push(x);

    while (temp.pop(x))
    {
        out << x << " ";
        S.push(x);
    }

    out << endl;
}

// reads words from para.txt into stack
// maximum 100 words--
void readWords(MyWordStack& S)
{
    ifstream fin("para.txt");
    string word;
    int count = 0;

    if (!fin)
    {
        cout << "File para.txt not found" << endl;
        return;
    }

    while (fin >> word && count < MAX_WORDS)
    {
        S.push(word);
        count++;
    }

    fin.close();
}

// copy the words stored in stack in reverse order
// into another stack and display reverse copy
void reverseCopy(MyWordStack& original, MyWordStack& reverseStack)
{
    MyWordStack temp(original.size());
    string word;

    // pop from original gives reverse order
    while (original.pop(word))
    {
        reverseStack.push(word);
        temp.push(word);
    }

    // restore original stack
    while (temp.pop(word))
        original.push(word);
}

// checks whether a word already exists in a stack
// stack is restored after checking
bool existsInWordStack(MyWordStack& S, string target)
{
    MyWordStack temp(S.size());
    string word;
    bool found = false;

    while (S.pop(word))
    {
        if (word == target)
            found = true;

        temp.push(word);
    }

    while (temp.pop(word))
        S.push(word);

    return found;
}

// remove duplicates from reverse copy and display
// only first occurrence of each word is kept
void removeDuplicates(MyWordStack& reverseStack, MyWordStack& uniqueStack)
{
    MyWordStack temp(reverseStack.size());
    string word;

    // reverse into temp so words are processed in display order
    while (reverseStack.pop(word))
        temp.push(word);

    while (temp.pop(word))
    {
        if (!existsInWordStack(uniqueStack, word))
            uniqueStack.push(word);

        // restore reverse stack also
        reverseStack.push(word);
    }
}

// counts frequency of one word in the reverse stack
// stack is restored after counting
int countOneWordFrequency(MyWordStack& reverseStack, string target)
{
    MyWordStack temp(reverseStack.size());
    string word;
    int count = 0;

    while (reverseStack.pop(word))
    {
        if (word == target)
            count++;

        temp.push(word);
    }

    while (temp.pop(word))
        reverseStack.push(word);

    return count;
}

// count frequency of each unique word
// store frequencies in int stack
void countFrequency(MyWordStack& uniqueStack, MyWordStack& reverseStack, MyStack& freqStack)
{
    MyWordStack temp(uniqueStack.size());
    string word;
    int freq;

    // reverse unique stack into temp for proper order
    while (uniqueStack.pop(word))
        temp.push(word);

    while (temp.pop(word))
    {
        freq = countOneWordFrequency(reverseStack, word);
        freqStack.push(freq);

        // restore unique stack
        uniqueStack.push(word);
    }
}

// display each word once with its frequency
// both stacks are restored after display
void displayWordFrequency(MyWordStack& uniqueStack, MyStack& freqStack)
{
    MyWordStack tempWords(uniqueStack.size());
    MyStack tempFreq(freqStack.size());

    string word;
    int freq;

    while (uniqueStack.pop(word))
        tempWords.push(word);

    while (freqStack.pop(freq))
        tempFreq.push(freq);

    while (tempWords.pop(word) && tempFreq.pop(freq))
    {
        cout << word << " -> " << freq << endl;

        uniqueStack.push(word);
        freqStack.push(freq);
    }
}

int main()
{
    MyWordStack words(MAX_WORDS);
    MyWordStack reverseWords(MAX_WORDS);
    MyWordStack uniqueWords(MAX_WORDS);
    MyStack frequencies(MAX_WORDS);   // existing int stack used for counts

    // read words from para.txt
    readWords(words);

    cout << "Original Words:" << endl;
    displayWords(words, cout);
    cout << endl;

    reverseCopy(words, reverseWords);
    cout << "Reverse Copy:" << endl;
    displayWords(reverseWords, cout);
    cout << endl;

    removeDuplicates(reverseWords, uniqueWords);
    cout << "After Removing Duplicates:" << endl;
    displayWords(uniqueWords, cout);
    cout << endl;

    countFrequency(uniqueWords, reverseWords, frequencies);
    cout << "Word Frequencies:" << endl;
    displayWordFrequency(uniqueWords, frequencies);

    return 0;
}