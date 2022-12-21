//
//  main.cpp
//  Порязрядные операции
//
//  Created by Хто Я on 22.12.2022.
//

#include <iostream>
using namespace std;

void Binary (unsigned int x)
{
    unsigned int mask = 0x80000000;
    for (int i = 0; i < 32; i++)
    {
        cout << (1 && (mask & x));
        mask = mask >> 1;
    }
    cout << endl;
}

int Ex1 (unsigned int x, unsigned int mask)
{
    x = x | mask;
    return x;
}

int Ex2 (unsigned int x, unsigned int mask)
{
    x = x & mask;
    return x;
}

int Ex3 (unsigned int x)
{
    x = x << 9;
    return x;
}

int Ex4 (unsigned int x)
{
    x = x >> 9;
    return x;
}

int Ex5 (unsigned int mask, unsigned int x, short int n)
{
    mask = mask >> (31 - n);
    cout << "mask(2cc):  ";
    Binary(mask);
    x = x | mask;
    
    return x;
}

int main ()
{
    unsigned int mask;
    unsigned int x;
    short int n;
    short int var;
    cout << "--ВЫБЕРИТЕ УПРАЖНЕНИЕ--" << endl;
    cout << "1. Задать 12 14 и 3 биту значение 1" << endl;
    cout << "2. Обнулить нечетные биты" << endl;
    cout << "3. Сдвинуть влево на 9 битов" << endl;
    cout << "4. Сдвинуть вправо на 9 битов" << endl;
    cout << "5. Установить n-ый бит в 1, используя маску 2" << endl;
    cin >> var;
    cout << endl;
    
    switch (var)
    {
        case 1:
        {
            mask = 0x5008;
            x = 0xAF10F9;
            cout << "--ДАНО--" << endl;
            cout << "x(16cc): \t\t" << hex << x << endl << "mask(16cc): \t" << hex << mask << endl;
            cout << "x(2cc): \t\t";
            Binary(x);
            cout << "mask (2cc): \t";
            Binary(mask);
            
            x = Ex1(x, mask);
            cout << endl << "--РЕЗУЛЬТАТ--" << endl;
            cout << "x|mask(16cc): \t" << hex << x << endl;
            cout << "x|mas(2cc): \t";
            Binary(x);
            
            break;
        }
            
        case 2:
        {
            mask = 0x55555555;
            x = 0xAF10F9;
            cout << "--ДАНО--" << endl;
            cout << "x(16cc):  \t\t" << hex << x << endl << "m(16cc):  \t\t" << hex << mask << endl;
            cout << "x(2cc):    \t\t";
            Binary(x);
            cout << "mask(2cc):   \t";
            Binary(mask);
            
            x = Ex2(x, mask);
            cout << endl << "--РЕЗУЛЬТАТ--" << endl;
            cout << "x & mask(16cc): " << hex << x << endl;
            cout << "x & mask(2cc):  ";
            Binary(x);
            
            break;
        }
            
        case 3:
        {
            cout << "--ВВОД--" << endl;
            cout << "Введите число x: ";
            cin >> x;
            cout << endl << "--ДАНО--" << endl;
            cout << "x(2cc): \t\t";
            Binary(x);
            
            x = Ex3(x);
            cout << endl << "--РЕЗУЛЬТАТ--" << endl;
            cout << "x << 9(10cc): \t" << x << endl;
            cout << "x << 9(2cc): \t";
            Binary(x);
            
            break;
        }
            
        case 4:
        {
            cout << "--ВВОД--" << endl;
            cout << "Введите число x: ";
            cin >> x;
            cout << endl << "--ДАНО--" << endl;
            cout << "x(2cc): \t\t";
            Binary(x);
            
            x = Ex4(x);
            cout << endl << "--РЕЗУЛЬТАТ--" << endl;
            cout << "x >> 9(10cc): \t" << x << endl;
            cout << "x >> 9(2cc): \t";
            Binary(x);
            
            break;
        }
            
        case 5:
        {
            mask = 0x80000000;
            cout << "--ВВОД--" << endl;
            cout << "Введите число x: ";
            cin >> x;
            cout << "Введите номер позиции n: ";
            cin >> n;

            cout << endl << "--ДАНО--" << endl;
            cout << "x(2cc): \t";
            Binary(x);
            
            x = Ex5(mask, x ,n);
            cout << endl << "--РЕЗУЛЬТАТ--" << endl;
            cout << "x(10cc): \t" << x << endl;
            cout << "x(2cc): \t";
            Binary(x);
            
            break;
        }
            
        default:
            break;
    }
    return 0;
}
