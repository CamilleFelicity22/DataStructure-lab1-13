#include <cstdio>
#include <iostream>

class PolyLinkedList;

class TermNode
{
    friend class PolyLinkedList;
    friend TermNode *PolyAdd(TermNode *ah, TermNode *bh);
    friend TermNode *InsertTerm(TermNode *pc,int c,int e);
    // friend TermNode *PolyMul(TermNode *ah, TermNode *bh);

public:
    TermNode() : coef(0), exp(0), link(nullptr) {}
    TermNode(float c, int e) : coef(c), exp(e), link(nullptr) {}

private:
    float coef; // 系数
    int exp;    // 指数
    TermNode *link;  //后继指针
};

class PolyLinkedList
{
public:
    PolyLinkedList() : head(nullptr) {}
    PolyLinkedList(TermNode *head) : head(head) {}

    ~PolyLinkedList()
    {
    }

    // 返回链表头指针
    TermNode *getHead() const
    {
        return head;
    }

    void InitFrom2DArray(float terms[][2], int size)
    {
        head = nullptr;
        TermNode *tail = nullptr;

        // 依次遍历给定的terms数组
        for (int i = 0; i < size; ++i)
        {
            float coef = terms[i][0];
            int exp = terms[i][1];

            TermNode *newTerm = new TermNode(coef, exp);
            if (head == nullptr)
            {
                // 如果链表为空，则新节点为头结点
                head = newTerm;
                tail = newTerm;
            }
            else
            {
                // 否则将新节点连接到链表的末尾
                tail->link = newTerm;
                tail = newTerm;
            }
        }
    }

    // 打印多项式
    void PrintPoly() const
    {
        TermNode *current = head;
        if (current == nullptr)
        {
            std::cout << "0" << std::endl; // 如果链表为空，输出0
            return;
        }

        bool firstTerm = true;
        while (current != nullptr)
        {
            float coef = current->coef;
            int exp = current->exp;
            if (!firstTerm && current->coef > 0)
                std::cout << " + "; // 为正数的项前加上"+"符号
            else if (current->coef < 0)
            {
                std::cout << " - "; // 为负数的项前加上"-"符号
                coef = -coef;       // 系数取绝对值
            }

            if (coef != 1 || exp == 0)
            {
                std::cout << coef;
            }

            // 输出变量部分
            if (exp != 0)
            {
                std::cout << "x";
                if (exp != 1)
                {
                    std::cout << "^" << exp; // 只在指数不为 1 时显示幂次
                }
            }

            current = current->link;
            firstTerm = false;
        }
        std::cout << std::endl;
    }

private:
    TermNode *head;
};




TermNode *PolyAdd(TermNode *ah, TermNode *bh)
{
    // here is your code
    if (!ah) return bh;
    if (!bh) return ah;

    TermNode *result = nullptr;  // 结果链表头
    TermNode *tail = nullptr;    // 结果链表的尾部

    // 遍历两个链表，合并同类项
    while (ah != nullptr && bh != nullptr)
    {
        // 新的项节点，用于存储合并后的项
        TermNode *term = nullptr;

        if (ah->exp == bh->exp) // 指数相同，合并系数
        {
            float newCoef = ah->coef + bh->coef;

            if (newCoef != 0) // 系数不为零时保留节点
            {
                ah->coef = newCoef;
                term = ah;
            }
            ah = ah->link; // 移动到下一项
            bh = bh->link;
        }
        else if (ah->exp < bh->exp) // ah的指数较小，保留ah
        {
            term = ah;
            ah = ah->link;
        }
        else // bh的指数较小，保留bh
        {
            term = bh;
            bh = bh->link;
        }

        if (term != nullptr) //如果有新的项要加入结果
        {
            if (result == nullptr)
            {
                result = term; //初始化结果链表头
            }
            else
            {
                tail->link = term;   //从后链接
            }
            tail = term; // 更新尾部节点
        }
    }

    // 将剩余的节点链接到最后
    if (ah != nullptr)
    {
        if (result == nullptr)
            result = ah;
        else
            tail->link = ah;
    }
    else if (bh != nullptr)
    {
        if (result == nullptr)
            result = bh;
        else
            tail->link = bh;
    }

    // 将结果链表的尾节点链接置空
    if (tail != nullptr)
        tail->link = nullptr;

    return result;
}



int main()
{
    // 创建两个多项式链表
    PolyLinkedList poly1, poly2;

    // 初始化第一个多项式 (1.8 + 2.0x^1000)
    float terms1[][2] = {{1.8, 0}, {2, 1000}};
    int size1 = sizeof(terms1) / sizeof(terms1[0]);
    poly1.InitFrom2DArray(terms1, size1);

    // 初始化第二个多项式 (1.2 + 51.3x^50 + 3.7x^101)
    float terms2[][2] = {{1.2, 0}, {51.3, 50}, {3.7, 101}};
    int size2 = sizeof(terms2) / sizeof(terms2[0]);
    poly2.InitFrom2DArray(terms2, size2);

    // 打印初始多项式
    std::cout << "Polynomial 1: ";
    poly1.PrintPoly();

    std::cout << "Polynomial 2: ";
    poly2.PrintPoly();

    // 相加两个多项式
    TermNode *result = PolyAdd(poly1.getHead(), poly2.getHead());

    std::cout << "Sum of Polynomials: ";
    PolyLinkedList resultPoly(result);
    resultPoly.PrintPoly();

    return 0;
}



/*时间复杂度：
时间复杂度为 O(m + n)，m和n是两个多项式的项数。

空间复杂度：
空间复杂度为 O(1)，因为没有创建新的节点，而是重用了原链表的节点。
*/