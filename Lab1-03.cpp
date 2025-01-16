#include <cstdio>
#include <iostream>
using namespace std;

#define ERROR -1
#define defaultSize 10010

template <class Type>
class SeqList
{
public:
    SeqList(int size = defaultSize); // 构造函数
    ~SeqList() { delete[] list; }    // 析构函数
    void PrintAll();
    int Length() const { return last + 1; }
    int IsEmpty() { return last == -1; }
    int IsFull() { return last == maxSize - 1; }
    Type Get(int i);

    int Find(Type x) const;
    int Insert(Type x, int i);
    int Remove(int i);
    int RemoveBetween(Type x, Type y);

private:
    Type *list;
    int maxSize;
    int last;
};

template <class Type>
SeqList<Type>::SeqList(int size)
{
    if (size > 0)
    {
        maxSize = size;
        last = -1;
        list = new Type[maxSize];
        if (list == NULL)
        {
            cerr << " Memory Allocation Error " << endl;
            return;
        }
    }
}

template <class Type>
Type SeqList<Type>::Get(int i)
{
    if (i < 0 || i > last)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return list[i];
}

template <class Type>
void SeqList<Type>::PrintAll()
{
    if(IsEmpty())
    {
        cout << "Empty" << endl;
        return;
    }
    for (int i = 0; i < last; i++)
        cout << list[i] << ' ';
    cout << list[last] << endl;
}

template <class Type>
int SeqList<Type>::Find(Type x) const
{
    for (int i = 0; i <= last; i++)
        if (list[i] == x)
            return i;
    return -1;
}

template <class Type>
int SeqList<Type>::Insert(Type x, int i)
{
    if(IsFull()) 
    {
        cout << "Full" << endl;
        return -1;
    }
    if(i < 0 || i > last + 1) return -1;
    if(last == maxSize - 1) return 0;
    last++;   //顺序表长度+1
    for(int j = last; j > i; j--){
        // 依次向后移动
        list[j] = list[j - 1];   
    }
    list[i] = x; // 在此插入
    return 1;
    // here is your code
}

template <class Type>
int SeqList<Type>::Remove(int i)
{
    int flag = Find(i);
    if(flag == -1)
    {
        cout << "Position "<< i << " EMPTY" << endl;
        return -1;
    }
    if(i < 0 || i > last) return -1;
    for(int j = i; j < last; j++){
        list[j] = list[j + 1];
    }
    last--;
    return 1;
    // here is your code
}

template <class Type>
int SeqList<Type>::RemoveBetween(Type x, Type y)
{
    int count = 0;   // 记录删除的个数
    for(int i = 0; i <= last; i++)
    {
        if(list[i] >= x && list[i] <= y)
        {
            Remove(list[i]);
            i--;
            count++;
        }
    }
    return count;
    // here is your code
}

int main()
{
    SeqList<int> a(5);
    int n;
    cin >> n; // 输入插入长度
    for (int i = 0; i < n; i++)
    { // 逐个输入顺序表中的值
        int temp;
        cin >> temp;
        if (a.Insert(temp, i) == -1)
            cout << "Insertion Error: " << temp << " is not in." << endl;
    }

    cin >> n; // 输入查找长度
    for (int i = 0; i < n; i++)
    {
        int temp, p;
        cin >> temp;
        p = a.Find(temp);
        if (p == -1)
            cout << "Finding Error: " << temp << " is not in." << endl;
        else
            cout << temp << " is at position " << p << "." << endl;
    }

    cin >> n; // 输入删除长度
    for (int i = 0; i < n; i++)
    {
        int temp, p;
        cin >> temp;
        if (a.Remove(temp) == -1)
            printf("Deletion Error.\n");
    }

    int x, y;
    cin >> x;
    cin >> y;
    int k = a.RemoveBetween(x, y);
    a.PrintAll();
    cout << k << endl;
    return 0;
}