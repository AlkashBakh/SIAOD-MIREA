//
//  main.cpp
//  Жадина и грубая сила
//
//  Created by Хто Я on 22.12.2022.
//

#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Drug
{
    int price;
    string name;
};

int rawPower(int val2, int kolvoDrugs, vector <Drug> drug)
{
    string checkList;
    string nameOfVitamin;
    string vitamins;
    string symbol;
    string name;
    bool flag1;
    int min;
    
    cout << " Введите список нужных витаминов в строку, без пробелов (Сила): " << endl << "  > ";
    cin >> checkList;
    cout << endl << " Список покупок:";
    
    for (int i = 0; i < checkList.size(); i++)
    {
        vector <Drug> :: iterator it = drug.begin();
        nameOfVitamin = checkList[i];
        min = 10000;
        
        while (it != drug.end())
        {
            vitamins = (*it).name;
            flag1 = false;
            
            for (int j = 0; j < vitamins.size() && flag1 == false; j++)
            {
                symbol = vitamins[j];
                if (nameOfVitamin == symbol)
                    flag1 = true;
            }
            
            if (flag1 == true && (*it).price < min)
            {
                min = (*it).price;
                name = (*it).name;
            }
            else
                ++it;
        }
        
        cout << endl << "  > Лекарство " << name[0];
        val2 += min;
    }
    
    return val2;
}

int greedyAlgorithm(int val1, map <int, string> items)
{
    string checkList;
    string nameOfVitamin;
    string vitamins;
    string symbol;
    string name;
    bool flag1;
    bool flag2;
    
    cout << endl << " Введите список нужных витаминов в строку, без пробелов (Жадина): " << endl << "  > ";
    cin >> checkList;
    cout << endl << " Список покупок:";
    
    for (int i = 0; i < checkList.size(); i++)
    {
        map <int, string> :: iterator it = items.begin();
        nameOfVitamin = checkList[i];
        flag2 = false;
        
        while (it != items.end() && flag2 == false)
        {
            vitamins = it -> second;
            flag1 = false;
            
            for (int j = 0; j < vitamins.size() && flag1 == false; j++)
            {
                symbol = vitamins[j];
                if (nameOfVitamin == symbol)
                    flag1 = true;
            }
            
            if (flag1 == true)
            {
                val1 += it -> first;
                name = it -> second;
                items.erase(it++);
                flag2 = true;
            }
            else
                ++it;
        }
        
        cout << endl << "  > Лекарство " << name[0];
    }
    
    return val1;
}

int main()
{
    map <int, string> items;
    string nameOfDrug;
    string id;
    int priceOfDrug;
    int kolvoDrugs;
    int val1 = 0;
    int val2 = 0;

    cout << endl << " Введите общее количество лекарств в списке: " << endl << "  > ";
    cin >> kolvoDrugs;
    
    vector <Drug> drug(kolvoDrugs);

    cout << endl << " ВНИМАНИЕ! Введите названия витаминов и стоимость каждого лекарства" << endl << endl;
    for (int i = 0; i < kolvoDrugs; i++)
    {
        cout << " Лекарство " << i << ": " << endl << "  > ";
        cin >> nameOfDrug;
        id = to_string(i);
        nameOfDrug = id + nameOfDrug;
        drug[i].name = nameOfDrug;
        cout << "  > ";
        cin >> priceOfDrug;
        drug[i].price = priceOfDrug;
        items.insert(make_pair (priceOfDrug, nameOfDrug));
        cout << endl;
    }
    cout << "-------------------------------------------------------------------------" << endl << endl;
    
    val2 = rawPower(val2, kolvoDrugs, drug);
    cout << endl << endl << " Минимальная сумарная стоимость всех покупок (Сила): " << val2 << endl;
    cout << endl << "-------------------------------------------------------------------------" << endl;
    
    val1 = greedyAlgorithm(val1, items);
    cout << endl << endl << " Минимальная сумарная стоимость всех покупок (Жадина): " << val1 << endl << endl;
    
    return 0;
}

/*
A 6
ABD 12
D 4
FB 20
BA 1
*/
