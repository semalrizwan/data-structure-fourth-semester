/*
1. understanding:
i need to perform five different operations on words and characters using recursion.
i have to count words by looking for spaces, count every single character,
flip the entire string around, flip the order of words, and swap big letters
for small ones and vice versa. i cannot use loops.

2. steps:
- to count words: if there is a space add one and move to the rest
- to count characters: add one for every letter until i hit the end marker
- to reverse: swap the first and last letters and move inwards
- to reverse words: find a word, move it to the end, and repeat
- to convert: if it is a big letter make it small if small make it big

3. functions:
standard string length logic and pointer math to move through
the letters. the solution uses the base case of an nullptr to stop

4. learning:
recursion acts like a loop but saves the state of the string
on a stack so we can process things in reverse order easily

5. skills:
 handle texts processing without using standard loops and understand
how pointers move through memory
*/

#include <iostream>
using namespace std;

// count words by finding spaces
void countWords(const char* sentence) 
{
    // check if the current spot is empty
    if (*sentence == '\0')
    {
        return;
    }
    // print at the end of recursion
    static int count = 1;
    // if find a space increment count
    if (*sentence == ' ') count++;
    // move to the next letter
    countWords(sentence + 1);
    // print only once at the very start of the call chain
}

// count every single character
void countCharaters(const char* sentence) 
{
    // base case: stop if we hit the end
    if (*sentence == '\0')
    {
        return;
    }
    static int chars = 0;
    // add one for this letter
    chars++;
    // go to the next letter
    countCharaters(sentence + 1);
}

// reverse letters in place
void reverse(char*& sentence) 
{
    // check if string is empty or has one letter
    if (!sentence || !*sentence)
    {
        return;
    }
    static int start = 0;
    static int end = 0;
    // find the end on the first call
    if (end == 0) while (sentence[end])
    {
        end++;
    }
    // if start meets or passes end
    if (start >= end - 1)
    {
        return;
    }
    // swap the letters at start and end positions
    char temp = sentence[start];
    sentence[start] = sentence[end - 1];
    sentence[end - 1] = temp;
    // move indices
    start++;
    end--;
    // call again
    reverse(sentence);
}

// convert case of letters
void convert(char* sentence) 
{
    // stop if at the end
    if (*sentence == '\0')
    {
        return;
    }
    // if it is a capital letter
    if (*sentence >= 'A' && *sentence <= 'Z')
    {
        // make it small
        *sentence = *sentence + 32;
    }
    // if it is a small letter
    else if (*sentence >= 'a' && *sentence <= 'z')
    {
        // make it big
        *sentence = *sentence - 32;
    }
    // move to next letter
    convert(sentence + 1);
}

int main() 
{
    char str[] = "Hello World";
    char* ptr = str;
    convert(ptr);
    cout << str << endl;
    return 0;
}