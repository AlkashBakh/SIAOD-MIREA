//
//  file.h
//  Работа с файлами
//
//  Created by Хто Я on 22.12.2022.
//

#ifndef file_h
#define file_h

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void inputFile(string NameFile, int num)
{
    ofstream OutFile;
    ifstream InFile;
    OutFile.open(NameFile, ofstream::app);
    char str[256];
    
    for (int i = 0; i < num; i++)
    {
        cin.getline(str, 256, '.');
        OutFile << str;
    }
    InFile.close();
}

void outputFile(string NameFile)
{
    ifstream InFile;
    InFile.open(NameFile);
    
    if (!InFile.is_open())
        cout << "ОШИБКА! Файл не открыт" << endl;
    else
    {
        string StrOut;
        while (!InFile.eof())
        {
            StrOut = "";
            getline(InFile, StrOut);
            cout << StrOut << endl;
        }
    }
    cout << endl;
    InFile.close();
}

bool checkFile(string NameFile)
{
    ifstream check(NameFile);
    return check.is_open();
}

void inTheEnd(string NameFile)
{
    ofstream OutFile;
    ifstream InFile;
    OutFile.open(NameFile, ofstream::app);
    char str[256];
    
    for (int i = 0; i < 1; i++)
    {
        cin.getline(str, 256, '.');
        OutFile << str;
    }
    InFile.close();
}

int getPosition(string NameFile, int position)
{
    ifstream InFile(NameFile);
    int temp;
    int TempPos = 0, res = 0;
    
    while (TempPos != position - 1)
    {
        InFile >> temp;
        if (InFile.eof())
            break;
        TempPos++;
    }
    if (TempPos == position - 1)
    {
        InFile >> res;
        return res;
    }
    else
        return 0;
}

int counter(string NameFile)
{
    ifstream InFile(NameFile);
    string tmp;
    int result = 0;
    
    while (InFile >> tmp)
        result++;
    
    InFile.close();
    return result;
}

int findMin(string NameFile)
{
    ifstream InFile(NameFile);
    int min = 1000;
    int temp = 0;
    int num;
    
    while (!InFile.eof())
    {
        InFile >> num;
        if (num < min)
        {
            temp = num;
            min = temp;
        }
    }
    return min;
}

int findMax(string NameFile)
{
    ifstream InFile(NameFile);
    int max = 0;
    int temp = 0;
    int num;
    
    while (!InFile.eof())
    {
        InFile >> num;
        if (num > max)
        {
            temp = num;
            max = temp;
        }
    }
    return max;
}

void copyFile(string NameFile, string NewNameFile)
{
    ifstream InFile(NameFile);
    ofstream OutFile(NewNameFile);
    int max = findMax(NameFile);
    int min = findMin(NameFile);
    int numOfLine;
    
    while (!InFile.eof())
    {
        InFile >> numOfLine;
        OutFile << numOfLine + (max + min) << " ";
    }
    
    InFile.close();
    OutFile.close();
}

#endif /* file_h */
