#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string.h>
#include <locale>
#include <windows.h>
#include <algorithm>
#include <cmath>

using namespace std;

struct student
{
    string name;
    string surname;
    string patronymic;
    int day = 0;
    int month = 0;
    int year = 0;
    int course = 0;
    int group = 0;
    int* s_makes = 0;
    double sum()
    {
        double s = 0;
        for (int i = 0; i < 8; i++)
        {
            s += s_makes[i];
        }
        return s /= 8;
    }
    double average_mark = 0;
};
//поиск наименьшего 
double search_min(student stud[], int n, int course)
{
    double ans = 10; //число, заведомо большее любой средней оценки
    for (int i = 0; i < n; ++i)
    {
        if (stud[i].course == course)
        {
            ans = min(ans, stud[i].sum());
        }
    }
    return ans;
}
//поиск наибольшего
double search_max(student stud[], int n, int course)
{
    double maxx = 0; //число, заведомо меньшее любой средней оценки
    for (int i = 0; i < n; ++i)
    {
        if (stud[i].course == course)
        {
            maxx = max(maxx, stud[i].sum());
        }
    }
    return maxx;
}
//считывание из файла 
int load(student stud[], string file)
{
    ifstream fin;
    fin.open(file);
    int k = 0;

    while (!fin.eof())
    {
        fin >> stud[k].surname;
        fin >> stud[k].name;
        fin >> stud[k].patronymic;
        fin >> stud[k].day;
        fin >> stud[k].month;
        fin >> stud[k].year;
        stud[k].s_makes = new int[8];
        for (int i = 0; i < 8; i++)
        {
            fin >> stud[k].s_makes[i];
        }
        stud[k].average_mark = stud[k].sum();
        fin >> stud[k].course;
        fin >> stud[k].group;
        k++;
    }
    fin.close();
    return k;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    while (1)
    {

        int z = 0;
        cout << "Выберите действие: 1 - обработка данных, 0 - выход. \t";
        cin >> z;
        system("cls");

        if (z != 1)
        {
            break;
        }
        else
        {
            cout << "Наименьшие и наибольшие баллы на каждом курсе" << endl;
            double ans, maxx;
            student* stud = new student[500];
            int n = load(stud, "sp.txt");
            for (int i = 1; i <= 6; i++)
            {
                ans = search_min(stud, n, i);
                maxx = search_max(stud, n, i);

                cout << i << " course, " << "Minimum : \n";
                for (int i = 0; i < n; ++i)
                {
                    if (abs(stud[i].average_mark - ans) < 0.001)
                    {
                        cout << stud[i].surname << " " << stud[i].average_mark << endl;
                    }
                }
                cout << "Maximum : \n";
                for (int i = 0; i < n; ++i) 
                {
                    if (abs(stud[i].average_mark - maxx) < 0.001)
                    {
                        cout << stud[i].surname << " " << stud[i].average_mark << endl;
                    }
                }
            }
            delete[] stud;
        }
    }
    system("pause");
    return 0;
}