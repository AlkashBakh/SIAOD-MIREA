//
//  main.cpp
//  Работа с файлами
//
//  Created by Хто Я on 22.12.2022.
//

#include "file.h"

int main()
{
    int menu;
    while (1)
    {
        cout << "--ВЫБЕРИТЕ ДЕЙСТВИЕ--" << endl;
        cout << "1. Cоздание текстового файла кодировки ASCII" << endl;
        cout << "2. Вывод содержимого текстового файла" << endl;
        cout << "3. Добавление новой строки в конец файла" << endl;
        cout << "4. Прочитать значение числа, указав его порядковый номер в файле, и вернуть его значение" << endl;
        cout << "5. Определить количество чисел в файле" << endl;
        cout << "6. Вариант 14" << endl;
        cout << "7. Выход" << endl;
        cin >> menu;
        cout << endl;
        
        if (menu == 1)
        {
            cout << "--ВВОД ДАННЫХ--" << endl << "Введите имя файла с форматом .txt: ";
            string NameFile;
            cin >> NameFile;
            cout << "Введите кол-во строк: ";
            int num;
            cin >> num;
            cout << endl << "Добавьте строку";
            cout << endl << "ПРЕДУПРЕЖДЕНИЕ! В конце каждой строки пишите <<.>>" << endl;
            inputFile(NameFile, num);
            cout << endl << "--ИТОГ--" << endl << "Файл создан" << endl << endl;
        }
        else if (menu == 2)
        {
            cout << "--ВВОД ДАННЫХ--" << endl << "Введите имя файла с форматом .txt: ";
            string NameFile;
            cin >> NameFile;
            if (!checkFile(NameFile))
                cout << "ВНИМАНИЕ! Такого файла нет";
            else
                outputFile(NameFile);
        }
        else if (menu == 3)
        {
            cout << "--ВВОД ДАННЫХ--" << endl << "Введите имя файла с форматом .txt: ";
            string NameFile;
            cin >> NameFile;
            if (!checkFile(NameFile))
                cout << "ВНИМАНИЕ! Такого файла нет";
            else
            {
                cout << endl << "Добавьте строку";
                cout << endl << "ПРЕДУПРЕЖДЕНИЕ! В конце каждой строки пишите <<.>>" << endl;
                inTheEnd(NameFile);
                cout << endl << "--ГОТОВО--" << endl << endl;
            }
        }
        else if (menu == 4)
        {
            cout << "--ВВОД ДАННЫХ--" << endl << "Введите имя файла с форматом .txt: ";
            string NameFile;
            cin >> NameFile;
            if (!checkFile(NameFile))
                cout << "ВНИМАНИЕ! Такого файла нет";
            else
            {
                cout << "Введите позицию числа: ";
                int num;
                cin >> num;
                if (!getPosition(NameFile, num))
                    cout << "ВНИМАНИЕ! Не существует такого числа на данной позиции в заданном файле" << endl << endl;
                else
                    cout << endl << "--ИТОГ--" << endl
                    << "На выбранной позиции стоит число: " << getPosition(NameFile, num) << endl << endl;
            }
        }
        else if (menu == 5)
        {
            cout << "--ВВОД ДАННЫХ--" << endl << "Введите имя файла с форматом .txt: ";
            string NameFile;
            cin >> NameFile;
            if (!checkFile(NameFile))
                cout << "ВНИМАНИЕ! Такого файла нет";
            else
                cout << endl << "--ИТОГ--" << endl << "Количество чисел равно: " << counter(NameFile) << endl << endl;
        }
        else if (menu == 6)
        {
            string NameFile, NewNameFile;
            cout << "--ВВОД ДАННЫХ--" << endl << "Введите имя исходного файла с форматом .txt: ";
            cin >> NameFile;
            cout << "Введите имя нового файла с форматом .txt: ";
            cin >> NewNameFile;
            copyFile(NameFile, NewNameFile);
            cout << endl << "--ГОТОВО--" << endl << endl;
        }
        else if (menu == 7)
            return 0;
        else
            cout << "ВНИМАНИЕ! Такого действия нет" << endl;
    }
    return 0;
}

/*
 12 34 76.
 43 2 99.
*/
