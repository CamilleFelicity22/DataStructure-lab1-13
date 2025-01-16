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
    void PrintAll();                 // 打印函数
    int Length() const { return last + 1; }    // 长度
    int IsEmpty() { return last == -1; }
    int IsFull() { return last == maxSize - 1; }
    Type Get(int i);

    int Find(Type x) const;
    int Insert(Type x, int i);
    int Remove(int i);
    int RemoveBetween(Type x, Type y);

private:
    Type *list;         // 顺序表
    int maxSize;        // 顺序表最大长度
    int last;           // 顺序表长度
};

// 构造函数，初始化顺序表
template <class Type>
SeqList<Type>::SeqList(int size)
{
    if (size > 0)
    {
        maxSize = size;
        last = -1;     //初始化为空表
        list = new Type[maxSize];    //分配存储空间
        if (list == NULL)
        {
            cerr << " Memory Allocation Error " << endl;
            return;
        }
    }
}


//获取指定元素的位置
template <class Type>
Type SeqList<Type>::Get(int i)
{
    if (i < 0 || i > last)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return list[i];
}


//打印所有元素
template <class Type>
void SeqList<Type>::PrintAll()
{
    if(IsEmpty())          //判断顺序表是否为空
    {
        cout << "Empty" << endl;
        return;
    }
    for (int i = 0; i < last; i++)
        cout << list[i] << ' ';
    cout << list[last] << endl;
}

//查找某个元素并返回其位置
template <class Type>
int SeqList<Type>::Find(Type x) const
{
    for (int i = 0; i <= last; i++)
        if (list[i] == x)
            return i;
    return -1;
}


//在指定位置插入
template <class Type>
int SeqList<Type>::Insert(Type x, int i)
{
    if(IsFull()) //判断是否表已满
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
}

//删除某个元素
template <class Type>
int SeqList<Type>::Remove(int i)
{
    int flag = Find(i);  //查找元素
    if(flag == -1)     
    {
        cout << "Position "<< i << " EMPTY" << endl;
        return -1;
    }
    //删除元素，依次向前移动
    if(i < 0 || i > last) return -1;
    for(int j = i; j < last; j++){
        list[j] = list[j + 1];
    }
    last--;      //顺序表长度-1
    return 1;

}


//删除某个范围内的元素
template <class Type>
int SeqList<Type>::RemoveBetween(Type x, Type y)
{
    int count = 0;   // 记录删除的个数
    for(int i = 0; i <= last;i++)
    {
        if(list[i] >= x && list[i] <= y)  // 判断是否在指定范围内
        {
            Remove(i);  //删除当前元素，自动前移
            i--;
            count++;
        }
    }
    PrintAll();
    return count;
}

int main()
{
    SeqList<int> a(5);     //创建长度为5的顺序表
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

    //输入删除区间
    int x, y;
    cin >> x;
    cin >> y;
    int k = a.RemoveBetween(x, y);   //删除区间内的元素
    // a.PrintAll();    //打印顺序表
    cout << k << endl;     //打印删除的个数
    return 0;
}



/* 时间复杂度：
插入操作：O(n)
删除操作：O(n)
查找操作：O(n)
区间删除：O(n^2)
打印所有元素：O(n)
总：O(n^2)
*/
// 空间复杂度：O(1)