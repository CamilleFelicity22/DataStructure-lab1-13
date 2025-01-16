#include <cstdio>
#include <ctime>
#include <iostream>
#define random(a, b) (rand() % (b - a) + a)

template <class Type>
class List;

template <class Type>
class LinkNode
{
    friend class List<Type>;

public:
    LinkNode() { link = nullptr; }
    LinkNode(const Type &value)
    {
        data = value;
        link = nullptr;
    }

private:
    Type data;
    LinkNode<Type> *link;
};

template <class Type>
class List
{
public:
    List() { first = nullptr; }
    List(const Type &value)
    {
        first = new LinkNode<Type>(value);
        first->link = first;
    }
    ~List();
    LinkNode<Type> *Print();

    void Initialize(const Type arr[], int size);
    void Insert(const Type &value);

private:
    LinkNode<Type> *first;
};

template <class Type>
List<Type>::~List()
{
    if (first == nullptr)
        return;

    LinkNode<Type> *current = first;
    LinkNode<Type> *next;

    do
    {
        next = current->link;
        delete current;
        current = next;
    } while (current != first);
}

template <class Type>
LinkNode<Type> *List<Type>::Print()
{
    if (first == nullptr)
    {
        std::cout << "The list is empty." << std::endl;
        return nullptr;
    }

    LinkNode<Type> *current = first;

    do
    {
        std::cout << current->data << " ";
        current = current->link;
    } while (current != first);

    std::cout << std::endl;

    return first;
}

// 初始化循环单调非递减链表
template <class Type>
void List<Type>::Initialize(const Type arr[], int size)
{
    if (size <= 0)
        return;

    first = new LinkNode<Type>(arr[0]);
    LinkNode<Type> *current = first;

    for (int i = 1; i < size; ++i)
    {
        LinkNode<Type> *newNode = new LinkNode<Type>(arr[i]);
        current->link = newNode;
        current = newNode;
    }

    current->link = first;
}


// 插入节点到循环单调非递减链表中
template <class Type>
void List<Type>::Insert(const Type &value)
{
    // here is your code
    //如果链表空，需要创建一个新节点
    if(first == nullptr){
        first = new LinkNode<Type>(value);
        first->link = first;
        return;
    }

    //链表不为空，设置两个指针，pr和current，pr在前，current在后，利用它们来确定插入位置
    LinkNode<Type> *current = first;
    LinkNode<Type> *pr = nullptr;
    do{
        pr = current;
        current = current->link;
        if(pr->data <= value && current->data >= value){
            break; 
        }
        if(pr->data > current ->data)
        {
            if(value >= pr->data || value <= current->data){
                break;
        }
        }
    }while(true);

    LinkNode<Type> *newNode = new LinkNode<Type>(value);
    pr ->link = newNode;
    newNode->link = current;
    
    }




int main()
{

    List<int> myList;
    int size;
    std::cout<<"请输入链表大小:";
    std::cin >> size;
    int *arr = new int[size];
    std::cout<<"请输入链表元素:";
    for(int i = 0;i < size; i++){
        std::cin>>arr[i];
    }
    myList.Initialize(arr, size);
    myList.Print();

    int value;
    std::cout << "请输入要插入的值: ";
    std::cin >> value;
    myList.Insert(value);
    myList.Print();

    return 0;
}


/*时间复杂度：
Initialize 函数：O(size)
Insert 函数：O(n)
总时间复杂度：O(size + n)

空间复杂度：
Initialize 函数：O(size)
Insert 函数：O(1)
总空间复杂度：O(size)
*/