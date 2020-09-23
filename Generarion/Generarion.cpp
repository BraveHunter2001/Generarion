#include <iostream>
#include <set>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

const short SHIFT = 192;
const short LENOFLETTERS = 32;
const int ONE = 1;

using namespace std;

#pragma region set

bool isInSet(unsigned char item, unsigned char* set) {
    for (size_t i = 0; set[i]; ++i) {
        if (set[i] == item) {
            return true;
        }
    }

    return false;
}

void DeleteItem(int index, unsigned char* set) {
    for (size_t i = index; set[i]; ++i) {
        set[i] = set[i + 1];
    }
}

void AddItem(unsigned char item, unsigned char* set) {
    size_t i;
    for (i = 0; set[i]; ++i);
    set[i] = item;
    set[i + 1] = 0;
}

void UnionSets(unsigned char* source, unsigned char* destination) {
    for (size_t i = 0; source[i]; ++i) {
        if (!isInSet(source[i], destination)) {
            AddItem(source[i], destination);
        }
    }
}

void ExclusionSets(unsigned char* source, unsigned char* destination) {
    for (size_t i = 0; destination[i]; ++i) {
        if (isInSet(destination[i], source)) {
            DeleteItem(i, destination);
        }
    }
}

void PrintSet(unsigned char* set) {
    for (size_t i = 0; set[i]; ++i) {
        cout << set[i];
    }
}

#pragma endregion all what neded for set

#pragma region list

struct ST {
    unsigned char letter;
    ST* next;
    ST(unsigned char l, ST* n) : letter(l), next(n) {}
    ~ST() { delete next; }
};

ST* ToList(unsigned char* set) {
    ST* x = nullptr;
    for (size_t i = 0; set[i]; ++i) {
        x = new ST(set[i], x);
    }
    return x;
}

bool isInSet(unsigned char item, ST* set) {
    ST* x = set;
    while (x) {
        if (x->letter == item) {
            return true;
        }
        x = x->next;
    }

    return false;
}

ST* DeleteItem(unsigned char item, ST* set) {
    ST* x = set;
    if (x->letter == item) {
        set = x->next;
        x->next = nullptr;
        delete x;
    }
    else {
        ST* tmp = x;
        x = x->next;
        while (x) {
            if (x->letter == item) {
                tmp->next = x->next;
                x->next = nullptr;
                delete x;
                x = nullptr;
            }
            else {
                x = x->next;
                tmp = tmp->next;
            }
        }
    }
    return set;
}

ST* AddItem(unsigned char item, ST* set) {
    set = new ST(item, set);
    return set;
}

ST* UnionSets(ST* source, ST* destination) {
    ST* s = source, * d = destination;
    while (s) {
        if (!isInSet(s->letter, d)) {
            d = AddItem(s->letter, d);
        }
        s = s->next;
    }
    return d;
}

ST* ExclusionSets(ST* source, ST* destination) {
    ST* s = source, * d = destination;
    while (s) {
        if (isInSet(s->letter, d)) {
            d = DeleteItem(s->letter, d);
        }
        s = s->next;
    }
    return d;
}

void PrintSet(ST* set) {
    while (set) {
        cout << set->letter;
        set = set->next;
    }
}

#pragma endregion all what needed for list

#pragma region bool

void ToBool(unsigned char* set, bool* universum) {
    for (size_t i = 0; set[i]; ++i) {
        universum[set[i] - SHIFT] = true;
    }
}

void UnionSets(bool* source, bool* destination) {
    for (size_t i = 0; i < LENOFLETTERS; ++i) {
        if (source[i] != destination[i]) {
            destination[i] = true;
        }
    }
}

void ExclusionSets(bool* source, bool* destination) {
    for (size_t i = 0; i < LENOFLETTERS; ++i) {
        if (source[i] == destination[i]) {
            destination[i] = false;
        }
    }
}

void PrintSet(bool* set) {
    for (size_t i = 0; i < LENOFLETTERS; ++i) {
        if (set[i]) {
            cout << (unsigned char)(i + SHIFT);
        }
    }
}

#pragma endregion all what neded for bool

#pragma region word

int ToMachineWord(unsigned char* set) {
    int mword = 0;
    for (size_t i = 0; set[i]; ++i) {
        mword = mword | ONE << (int)(set[i] - SHIFT);
    }
    return mword;
}

bool isInSet(int index, int mword) {
    return mword & ONE << index;
}

int DeleteItem(int index, int mword) {
    mword = mword & ~(ONE << index);
    return mword;
}

int AddItem(int index, int mword) {
    mword = mword | ONE << index;
    return mword;
}

void UnionSets(int source, int& destination) {
    for (size_t i = 0; i < LENOFLETTERS; ++i) {
        if (isInSet(i, source)) {
            destination = AddItem(i, destination);
        }
    }
}

void ExclusionSets(int source, int& destination) {
    for (size_t i = 0; i < LENOFLETTERS; ++i) {
        if (isInSet(i, source)) {
            destination = DeleteItem(i, destination);
        }
    }
}

void PrintSet(int mword) {
    int one = 1;
    for (size_t i = 0; i < LENOFLETTERS; ++i) {
        if (mword & one << i) {
            cout << (unsigned char)(i + SHIFT);
        }
    }
}

#pragma endregion all what neded for word

#pragma region Random generators
/*
* Первая версия генератора для машинного слова. 
Если делать десять генераций и задавать длину 5 символов, 
то на одной из итераций будет слово содержащее меньше 5 символов.
Так и не понял в чем причина.
Решил сделать в тупую(представлено ниже): генерирую тупо символ и добавляю его к массиву символов.
*/
//int Generator(int len)
//{
//    int mword = 0;
//    const int firs_value = 'А';
//    const int last_value = 'Я';
//
//    for (size_t i = 0; i < len; ++i) {
//        mword = mword | ONE << (int)((firs_value + rand() % (last_value - firs_value + 1)) - SHIFT);
//    }
//    return mword;
//}

/// <summary>
/// Генератор массива случайных чисел.
/// </summary>
/// <param name="len">Количество букв</param>
/// <param name="arr">Массив символов</param>
void Generator(int len, unsigned char* arr)
{
    const int firs_value = 'А';
    const int last_value = 'Я';
    unsigned char randChar;
    for (size_t i = 0; i < len; i++)
    {
        randChar = firs_value + rand() % (last_value - firs_value + 1);
        AddItem(randChar, arr);
    }
   
}
/// <summary>
/// Сбрасывает массив: ставит везде ноль.
/// </summary>
/// <param name="arr">Массив символов</param>
void Discharge(unsigned char* arr)
{
    for (size_t i = 0; arr[i]; i++)
    {
        arr[i] = 0;
    }
}

#pragma endregion Genarators for tests

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned char choose;

    unsigned char A[LENOFLETTERS + 1] = { '\0' };
    unsigned char B[LENOFLETTERS + 1] = { '\0' };
    unsigned char C[LENOFLETTERS + 1] = { '\0' };
    unsigned char D[LENOFLETTERS + 1] = { '\0' };
    unsigned char E[LENOFLETTERS + 1] = { '\0' };

    ST* A_List = nullptr;
    ST* B_List = nullptr;
    ST* C_List = nullptr;
    ST* D_List = nullptr;
    ST* E_List = nullptr;

    bool A_Bool[LENOFLETTERS] = { false };
    bool B_Bool[LENOFLETTERS] = { false };
    bool C_Bool[LENOFLETTERS] = { false };
    bool D_Bool[LENOFLETTERS] = { false };
    bool E_Bool[LENOFLETTERS] = { false };

    int A_Mword = 0;
    int B_Mword = 0;
    int C_Mword = 0;
    int D_Mword = 0;
    int E_Mword = 0;

#pragma region Время длителности
    clock_t t;
    int countIteartion = 10000;

    t = clock();
    for (int i = 0; i < countIteartion; i++)
    {
        Generator(15, A);
        Generator(15, B);
        Generator(15, C);
        Generator(15, D);

        UnionSets(A, E);
        ExclusionSets(B, E);
        ExclusionSets(C, E);
        ExclusionSets(D, E);

        Discharge(A);
        Discharge(B);
        Discharge(C);
        Discharge(D);
        Discharge(E);
    }
    t = clock() - t;
    cout <<"Array: "<< (float)t / CLK_TCK / countIteartion << endl;

   

    t = clock();
    for (size_t i = 0; i < countIteartion; i++)
    {
        Generator(15, A);
        Generator(15, B);
        Generator(15, C);
        Generator(15, D);

        A_List = ToList(A);
        B_List = ToList(B);
        C_List = ToList(C);
        D_List = ToList(D);

        E_List = UnionSets(A_List, E_List);

        E_List = ExclusionSets(B_List, E_List);
        E_List = ExclusionSets(C_List, E_List);
        E_List = ExclusionSets(D_List, E_List);

        Discharge(A);
        Discharge(B);
        Discharge(C);
        Discharge(D);
        Discharge(E);
    }
    t = clock() - t;
    
    cout << "List: " << (float)t / CLK_TCK/countIteartion << endl;


    t = clock();
    for (size_t i = 0; i < countIteartion; i++)
    {
        Generator(15, A);
        Generator(15, B);
        Generator(15, C);
        Generator(15, D);

        ToBool(A, A_Bool);
        ToBool(B, B_Bool);
        ToBool(C, C_Bool);
        ToBool(D, D_Bool);

        UnionSets(A_Bool, E_Bool);

        ExclusionSets(B_Bool, E_Bool);
        ExclusionSets(C_Bool, E_Bool);
        ExclusionSets(D_Bool, E_Bool);

        Discharge(A);
        Discharge(B);
        Discharge(C);
        Discharge(D);
        Discharge(E);
    }
    
    t = clock() - t;
    cout << "Boolean array: " << (float)t / CLK_TCK/countIteartion << endl;

    t = clock();
    for (size_t i = 0; i < countIteartion; i++)
    {
        Generator(15, A);
        Generator(15, B);
        Generator(15, C);
        Generator(15, D);

        A_Mword = ToMachineWord(A);
        B_Mword = ToMachineWord(B);
        C_Mword = ToMachineWord(C);
        D_Mword = ToMachineWord(D);

        UnionSets(A_Mword, E_Mword);

        ExclusionSets(B_Mword, E_Mword);
        ExclusionSets(C_Mword, E_Mword);
        ExclusionSets(D_Mword, E_Mword);


        Discharge(A);
        Discharge(B);
        Discharge(C);
        Discharge(D);
        Discharge(E);
    }
    
    t = clock() - t;
    
    cout << "Machine word: " << (float)t / CLK_TCK/countIteartion << endl;


#pragma endregion

    return 0;
}
