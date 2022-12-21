//
//  BinFile.h
//  5_Сбалансированное бинарное дерево
//
//  Created by Хто Я on 22.10.2022.
//

#ifndef BinFile_h
#define BinFile_h

#include <iostream>
#include <fstream>

using namespace std;

struct City
{
    int code;
    char name[500];
    char country[500];
};

int lineCounter(ifstream& file)
{
    string numStr = "";
    int counter = 1;
    while (!file.eof())
    {
        while (getline(file, numStr))
            counter++;
    }
    return counter;
}

void txtToBin(ifstream& TxtFile, ofstream& BinFile)
{
    City city;
    
    while (1)
    {
        TxtFile >> city.code;
        if (!TxtFile.eof())
        {
            TxtFile >> city.name >> city.country;
            BinFile.write((char*)&city, sizeof(City));
        }
        else
            break;
    }
}

void printBinary(ifstream& BinFile)
{
    City city;
    
    while (1)
    {
        BinFile.read((char*)&city, sizeof(city));
        if (!BinFile.eof())
            cout << city.code << " " << city.name << " " << city.country << endl;
        else
            break;
    }
}

City getStr(string NameFile, int position)
{
    City city;
    ifstream BinFile(NameFile, ios::binary | ios::in);
    
    if (position == -1)
        BinFile.seekg(-1*(int)sizeof(city), ios::end);
    else
        BinFile.seekg((position) * sizeof(city));
    
    BinFile.read((char*)&city, sizeof(City));
    BinFile.close();
    
    return city;
}

City lineSearch(string NameFile, string find)
{
    City city;
    string cityName;
    ifstream InFile(NameFile, ios::in);
    InFile.read((char*)&city, sizeof(City));
    
    while (!InFile.eof())
    {
        cityName = "";
        for (int i = 0; i < find.length(); i++)
            cityName += city.name[i];
        
        if (cityName == find)
        {
            InFile.close();
            return city;
        }
        
        InFile.read((char*)&city, sizeof(City));
    }
    
    InFile.close();
    city.code = -1;
    return city;
}

#endif /* BinFile_h */
