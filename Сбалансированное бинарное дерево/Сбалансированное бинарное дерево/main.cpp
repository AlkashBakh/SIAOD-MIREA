//
//  main.cpp
//  Сбалансированное бинарное дерево
//
//  Created by Хто Я on 22.10.2022.
//

#include "BinFile.h"
#include "BinaryTree.h"
#include "BalanceBinaryTree.h"
#include <chrono>

using namespace std::chrono;

auto start_t = steady_clock::now();
auto end_t = steady_clock::now();

BST t1;
BSTRand t2;

void menuBinFile()
{
    int num;
    char end = ' ';
    ifstream InFile;
    ofstream OutFile;
    string input, output;
    
    while(end != 'y')
    {
        cout << "--ВЫБЕРИТЕ ДЕЙСТВИЕ ДЛЯ РАБОТЫ С БИНАРНЫМ ФАЙЛОМ--" << endl;
        cout << "1. Преобразование данных из текстового файла в двоичный" << endl;
        cout << "2. Добавить запись в бинарный файл" << endl;
        cout << "3. Поиск и вывод записи в файле с помощью линейного поиска" << endl;
        cout << "4. Найти запись с нужным ключом" << endl;
        cout << "5. Вывести бинарный файл" << endl;
        cout << "6. Тест поиска" << endl;
        cout << "0. Выход" << endl;
        cin >> num;
        
        switch (num)
        {
            case 1:
            {
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите имя файла с форматом .txt: ";
                cin >> input;
                InFile.open(input, ios::in);
                if (InFile.good())
                {
                    OutFile.open("1.bin", ios::binary);
                    
                    if (OutFile.good())
                    {
                        txtToBin(InFile, OutFile);
                        cout << "--ГОТОВО--" << endl << endl;
                    }
                    else
                        cout << "ВНИМАНИЕ! Такого файла нет" << endl << endl;

                    OutFile.close();
                    InFile.close();
                }
                else
                    cout << "ВНИМАНИЕ! Такого файла нет" << endl << endl;
                
                break;
            }
                    
            case 2:
            {
                City temp;
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите имя файла с форматом .bin: ";
                cin >> output;
                OutFile.open(output, ios::out | ios::app);
                if (OutFile.good())
                {
                    cout << "Введите код города: ";
                    cin >> temp.code;
                    cout << "Введите название города: ";
                    cin >> temp.name;
                    cout << "Введите страну: ";
                    cin >> temp.country;

                    OutFile.write((char*)&temp, sizeof temp);
                    cout << "--ГОТОВО--" << endl << endl;
                    
                    OutFile.close();
                }
                else
                    cout << "ВНИМАНИЕ! Такого файла нет" << endl << endl;
                
                break;
            }
            
            case 3:
            {
                char symbol;
                string line, find;
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите имя файла с форматом .bin: ";
                cin >> input;
                InFile.open(input, ios::in);
                
                if (InFile.good())
                {
                    while (!InFile.eof())
                    {
                        InFile.get(symbol);
                        line.push_back(symbol);
                    }
                    InFile.close();
                    
                    cout << "Введите значение для поиска: ";
                    cin >> find;
                    unsigned long pos = line.find(find);
                    
                    if (pos == -1)
                        cout << "ОШИБКА! Значение не найдено" << endl << endl;
                    else
                        cout << endl << "--ВЫВОД--" << endl << "Значение найдено на позиции " << pos << endl << endl;
                }
                else
                    cout << "ВНИМАНИЕ! Такого файла нет" << endl << endl;
                
                break;
            }
            
            case 4:
            {
                int positionNum;
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите имя бинарного файла с форматом .bin: ";
                cin >> input;
                ifstream check(input);
                if (check.is_open())
                {
                    cout << "Введите номер нужной строки: ";
                    cin >> positionNum;
                    positionNum--;
                    ifstream tmp(input, ios::binary | ios::in);
                    int c = lineCounter(tmp) + 1;
                    if (positionNum < c)
                    {
                        cout << endl << "--ВЫВОД--" << endl;
                        City city = getStr(input, positionNum);
                        cout << city.code << " " << city.name << " " << city.country << endl << endl;
                    }
                    else
                        cout << "ВНИМАНИЕ! Такого файла нет" << endl << endl;
                }
                else
                    cout << "ВНИМАНИЕ! Такого файла нет" << endl << endl;
                
                break;
            }
                
            case 5:
            {
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите имя бинарного файла с форматом .bin: ";
                cin >> input;
                InFile.open(input, ios::in | ios::binary);
                if (InFile.good())
                {
                    cout << endl << "--ВЫВОД--" << endl;
                    printBinary(InFile);
                    cout << endl;
                    InFile.close();
                }
                else
                    cout << "ВНИМАНИЕ! Такого файла нет" << endl << endl;

                break;
            }
                
            case 6:
            {
                string name;
                string input;
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите название файла .bin: ";
                cin >> input;
                cout << "Введите ключ искомого элемента: ";
                cin >> name;
                
                start_t = steady_clock::now();
                City city = lineSearch(input, name);
                end_t = steady_clock::now();
                auto ms = duration_cast<nanoseconds>(end_t - start_t);
                
                cout << endl << "--ВЫВОД--" << endl << "Номер: " << city.code << "\nГород: " << city.name << "\nСтрана: " << city.country << endl;
                cout << "Время выполнения: " << (double)ms.count() / 1000000 << " ms" << endl << endl;
                
                break;
            }
                
            default:
            {
                cout << endl << "Хочешь выйти (y/n)?: ";
                cin >> end;
                cout << endl;
                break;
            }
        }
    }
}

void menuBinaryTree()
{
    BST t1;
    int num;
    char end = ' ';
    string input;
    ifstream InFile;
    
    while(end != 'y')
    {
        cout << "--ВЫБЕРИТЕ ДЕЙСТВИЕ ДЛЯ РАБОТЫ С БИНАРНЫМ ДЕРЕВОМ ПОИСКА--" << endl;
        cout << "1. Создать дерево" << endl;
        cout << "2. Добавить элемент в дерево" << endl;
        cout << "3. Поиск по ключу в дереве" << endl;
        cout << "4. Удаление элемента из дерева" << endl;
        cout << "5. Вывести бинарное дерево" << endl;
        cout << "6. Тест поиска" << endl;
        cout << "0. Выход" << endl;
        cin >> num;
        
        switch (num)
        {
            case 1:
            {
                BST::BSTNode element;
                int cityCode;
                int fileNumber = 0;
                string cityName, counrtyName;
                
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите имя файла с форматом .txt: ";
                cin >> input;
                InFile.open(input, ios::in);
                
                if (InFile.good())
                {
                    while (!InFile.eof())
                    {
                        InFile >> cityCode >> cityName >> counrtyName;
                        t1.insert(cityName, fileNumber);
                        fileNumber++;
                    }
                    
                    InFile.close();
                    cout << "--ГОТОВО--" << endl << endl;
                    t1.printBinaryTree();
                    cout << endl;
                }
                else
                    cout << "ВНИМАНИЕ! Такого файла нет" << endl << endl;
                
                break;
            }
                    
            case 2:
            {
                string element;
                int fileNumber;
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите элемент, который хотите добавить: ";
                cin >> element;
                cout << "Введите номер элемента в файле: ";
                cin >> fileNumber;
                t1.insert(element, fileNumber);
                cout << "--ГОТОВО--" << endl << endl;
                t1.printBinaryTree();
                cout << endl;
                
                break;
            }
            
            case 3:
            {
                string element;
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите элемент, который хотите найти: ";
                cin >> element;
                cout << "Позиция элемента: " << t1.search(element) << endl << endl;
                
                break;
            }
            
            case 4:
            {
                string element;
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите элемент, который хотите удалить: ";
                cin >> element;
                t1.remove(element);
                cout << "--ГОТОВО--" << endl << endl;
                t1.printBinaryTree();
                cout << endl;
                
                break;
            }
                
            case 5:
            {
                cout << endl << "--ВЫВОД ДАННЫХ--" << endl << endl;
                t1.printBinaryTree();
                cout << endl;
                
                break;
            }
                
            case 6:
            {
                string name;
                string input;
                
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите название файла .bin: ";
                cin >> input;
                cout << "Введите ключ искомого элемента: ";
                cin >> name;
                
                start_t = steady_clock::now();
                int number = t1.search(name) - 1;
                
                if (number == -1)
                {
                    end_t = steady_clock::now();
                    cout << "ВНИМАНИЕ! Элемент не найден" << endl << endl;
                }
                else
                {
                    City city = getStr(input, number);
                    end_t = steady_clock::now();
                    auto ms = duration_cast<nanoseconds>(end_t - start_t);
                    cout << endl << "--ВЫВОД--" << endl << "Номер: " << city.code << "\nГород: " << city.name << "\nСтрана: " << city.country << endl;
                    cout << "Время выполнения: " << (double)ms.count() / 1000000 << " ms" << endl << endl;
                }
                
                break;
            }
                
            default:
            {
                cout << endl << "Хочешь выйти (y/n)?: ";
                cin >> end;
                cout << endl;
                
                break;
            }
        }
    }
}

void menuBalanceBinaryTree()
{
    BSTRand t2;
    int num;
    char end = ' ';
    int counter = 0;
    string input;
    ifstream InFile;
    
    while(end != 'y')
    {
        cout << "--ВЫБЕРИТЕ ДЕЙСТВИЕ ДЛЯ РАБОТЫ СО СБАЛАНСИРОВАННЫМ БИНАРНЫМ ДЕРЕВОМ ПОИСКА--" << endl;
        cout << "1. Создать дерево" << endl;
        cout << "2. Добавить элемент в дерево" << endl;
        cout << "3. Поиск по ключу в дереве" << endl;
        cout << "4. Удаление элемента из дерева" << endl;
        cout << "5. Вывести бинарное дерево" << endl;
        cout << "6. Тест поиска" << endl;
        cout << "0. Выход" << endl;
        cin >> num;
        
        switch (num)
        {
            case 1:
            {
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите имя файла с форматом .txt: ";
                cin >> input;
                InFile.open(input, ios::in);
                if (InFile.good())
                {
                    int fileNumber = 0, cityCode;
                    string cityName, counrtyName;
                    while (!InFile.eof())
                    {
                        InFile >> cityCode >> cityName >> counrtyName;
                        t2.insert(cityName, fileNumber, counter);
                        fileNumber++;
                    }
                                
                    InFile.close();
                    cout << "--ГОТОВО--" << endl;
                    cout << "Кол-во поворотов: " << counter << endl << endl;
                    t2.printBinaryTree();
                    cout << endl;
                }
                else
                    cout << "ВНИМАНИЕ! Такого файла нет" << endl << endl;
                                
                break;
            }
                    
            case 2:
            {
                string element;
                int fileNumber;
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите элемент, который хотите добавить: ";
                cin >> element;
                cout << "Введите номер элемента в файле: ";
                cin >> fileNumber;
                t2.insert(element, fileNumber, counter);
                cout << "--ГОТОВО--" << endl << endl;
                cout << "Кол-во поворотов: " << counter << endl << endl;
                t2.printBinaryTree();
                cout << endl;
                
                break;
            }
            
            case 3:
            {
                string element;
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите элемент, который хотите найти: ";
                cin >> element;
                cout << "Позиция элемента: " << t2.search(element) << endl << endl;
                
                break;
            }
            
            case 4:
            {
                string element;
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите элемент, который хотите удалить: ";
                cin >> element;
                t2.remove(element);
                cout << "--ГОТОВО--" << endl << endl;
                t2.printBinaryTree();
                cout << endl;
                
                break;
            }
                
            case 5:
            {
                cout << endl << "--ВЫВОД ДАННЫХ--" << endl << endl;
                t2.printBinaryTree();
                cout << endl;
                
                break;
            }
                
            case 6:
            {
                string input;
                string name;
                
                cout << endl << "--ВВОД ДАННЫХ--" << endl << "Введите название файла .bin: ";
                cin >> input;
                cout << "Введите ключ искомого элемента: ";
                cin >> name;
                
                start_t = steady_clock::now();
                int number = t2.search(name);
                
                if (number == -1)
                {
                    cout << "ВНИМАНИЕ! Элемент не найден" << endl << endl;
                    end_t = steady_clock::now();
                }
                else
                {
                    City city = getStr(input, number--);
                    end_t = steady_clock::now();
                    auto ms = duration_cast<nanoseconds>(end_t - start_t);
                    cout << endl << "--ВЫВОД--" << endl << "Номер: " << city.code << "\nГород: " << city.name << "\nСтрана: " << city.country << endl;
                    cout << "Время выполнения: " << (double)ms.count() / 1000000 << " ms" << endl << endl;
                }
                
                break;
            }
                
            default:
            {
                cout << endl << "Хочешь выйти (y/n)?: ";
                cin >> end;
                cout << endl;
                break;
            }
        }
    }
}

int main()
{
    int num;
    while (1)
    {
        cout << "--ВЫБЕРИТЕ СПОСОБ РАБОТЫ--" << endl;
        cout << "\t1. Работа с бинарным файлом" << endl;
        cout << "\t2. Работа с БДП" << endl;
        cout << "\t3. Работа с рандомизированным деревом" << endl;
        cout << "\t0. Выход" << endl;
        cin >> num;
        cout << endl;
        
        switch(num)
        {
            case 1:
            {
                menuBinFile();
                break;
            }
                
            case 2:
            {
                menuBinaryTree();
                break;
            }
                
            case 3:
            {
                menuBalanceBinaryTree();
                break;
            }
                
            default:
            {
                cout << endl << "Хочешь выйти (y/n)?: ";
                char end;
                cin >> end;
                if (end == 'y')
                    return 0;
            }
        }
    }
}

