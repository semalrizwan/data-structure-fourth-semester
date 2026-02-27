#pragma once
#include"book.h"
#include"newspaper.h"
#include<iostream>
using namespace std;

const int n = 100;

class sorting
{
private:
    book books[n];
    newspaper newspapers[n];
    int bookcount;
    int newspapercount;

public:

    void addbook(book b)
    {
        books[bookcount++] = b;
    }

    void addnewspaper(newspaper news)
    {
        newspapers[newspapercount++] = news;
    }

    // Selection Sort 
    void sortbooks()
    {
        for (int i = 0; i < bookcount - 1; i++)
        {
            int minIndex = i;

            for (int j = i + 1; j < bookcount; j++)
            {
                if (books[j].getpage() < books[minIndex].getpage())
                    minIndex = j;
            }

            if (minIndex != i)
                swap(books[i], books[minIndex]);
        }
    }

    // Selection Sort 
    void sortnewspaper()
    {
        for (int i = 0; i < newspapercount - 1; i++)
        {
            int minIndex = i;

            for (int j = i + 1; j < newspapercount; j++)
            {
                if (newspapers[j].getedition() < newspapers[minIndex].getedition())
                    minIndex = j;
            }

            if (minIndex != i)
                swap(newspapers[i], newspapers[minIndex]);
        }
    }

    // linear search newspaper
    book* searchbook(string title)
    {
        for (int i = 0; i < bookcount; i++)
        {
            if (books[i].gettitle() == title)
                return &books[i];
        }
        return nullptr;
    }

    //linear search for newspaper
    newspaper* searchnewspaper(string title)
    {
        for (int i = 0; i < newspapercount; i++)
        {
            if (newspapers[i].gettitle() == title)
                return &newspapers[i];
        }
        return nullptr;
    }
    void displayCollection()
    {
        cout << "\nBOOKS\n";
        for (int i = 0; i < bookcount; i++)
            books[i].display();

        cout << "\nNEWSPAPER\n";
        for (int i = 0; i < newspapercount; i++)
            newspapers[i].display();
    }
};