#include <cstdio>
#include <iostream>
#include <assert.h>

using namespace std;

#define MAXN 100 // 多项式最大项数

class Term
{
    friend class Polynomial;

private:
    float coef; // 系数
    int exp;    // 指数
};

class Polynomial
{
public:
    Polynomial();                          // 无形参构造函数，返回多项式A(x)=0
    ~Polynomial();                         // 析构函数
    int Poly_Append(float c, int e);       // 插入系数为c、指数为e的项至指针free所指示位置
    Polynomial *Poly_Mul(Polynomial poly); // 返回多项式*this与多项式poly的乘
    void Print() const;                    // 打印多项式

private:
    static Term *Poly_Array; // 存放多项式的数组
    static int free;         // 多项式有效项数的下一位置
    int start, finish;
};

// 在类外初始化 Term, 所有 Ploy_Array 共享同一块内存
Term *Polynomial::Poly_Array = new Term[MAXN + 1];
int Polynomial::free = 0; // 初始化 free 为 0

Polynomial::Polynomial()
{
    start = free;      // 初始化 start 为当前的 free 位置
    finish = free - 1; // 表示没有项，finish 初始化为 free 之前的位置
}

Polynomial::~Polynomial()
{
}

int Polynomial::Poly_Append(float c, int e)
{
    if (free >= MAXN)
    {
        return -1; // 超过多项式最大项数
    }
    Poly_Array[free].coef = c; // 插入系数
    Poly_Array[free].exp = e;  // 插入指数
    free++;                    // 更新 free 指向下一个空闲位置
    finish = free - 1;         // 更新 finish 指向最后一个有效项
    return 0;                  // 成功插入
}

void Polynomial::Print() const
{
    bool isZero = true; // 标志是否是零多项式

    for (int i = start; i <= finish; i++)
    {
        float coef = Poly_Array[i].coef;
        int exp = Poly_Array[i].exp;

        // 忽略系数为 0 的项
        if (coef == 0)
        {
            continue;
        }

        isZero = false; // 存在非零项

        // 输出符号
        if (i > start && coef > 0)
        {
            std::cout << " + ";
        }
        else if (coef < 0)
        {
            std::cout << " - ";
            coef = -coef; // 如果系数为负数，符号已处理，接下来输出绝对值
        }

        // 输出系数（只在系数不是 1 或 -1 时显示）
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
    }

    // 如果所有项的系数都为 0，则输出 "0"
    if (isZero)
    {
        std::cout << "0";
    }

    std::cout << std::endl; // 换行
}

Polynomial *Polynomial::Poly_Mul(Polynomial poly)
{
    Polynomial *result = new Polynomial();   // 用于存放乘积结果的多项式
    // 遍历 *this 多项式的每一项
    for (int i = start; i <= finish; i++)
    {
        // 遍历另一个多项式的每一项
        for (int j = poly.start; j <= poly.finish; j++)
        {
            float new_coef = Poly_Array[i].coef * poly.Poly_Array[j].coef; // 系数相乘
            int new_exp = Poly_Array[i].exp + poly.Poly_Array[j].exp;      // 指数相加

            // 查找是否已经存在相同指数的项，如果存在则合并系数
            bool merged = false;
            for (int k = result->start; k <= result->finish; k++)
            {
                if (result->Poly_Array[k].exp == new_exp)
                {
                    result->Poly_Array[k].coef += new_coef;
                    merged = true;
                    break;
                }
            }

            // 如果不存在相同指数的项，则插入新的项
            if (!merged)
            {
                result->Poly_Append(new_coef, new_exp);
            }
        }
    }
    return result;
}

int main()
{
    // 创建多项式 A = 1.8 + 2.0x^1000
    Polynomial A;
    A.Poly_Append(1.8, 0);    // 1.8
    A.Poly_Append(2.0, 1000); // 2.0x^1000

    // 创建多项式 B = 1.2 + 51.3x^50 + 3.7x^1000
    Polynomial B;
    B.Poly_Append(1.2, 0);    // 1.2
    B.Poly_Append(51.3, 50);  // 51.3x^50
    B.Poly_Append(3.7, 1000); // 3.7x^1000

    // 进行乘法运算
    Polynomial *result = A.Poly_Mul(B);

    // 输出结果，期望结果为 2.16 + 92.34x^50 + 9.06x^1000 + 102.6x^1050 + 7.4x^2000
    std::cout << "Test Case: (1.8 + 2.0x^1000) * (1.2 + 51.3x^50 + 3.7x^1000)" << std::endl;
    result->Print(); // 应输出：2.16 + 92.34x^50 + 9.06x^1000 + 102.6x^1050 + 7.4x^2000

    return 0;
}


/*
1.时间复杂度：
对于多项式 A 和 B，假设 A 和 B 分别包含 m 项和 n 项。
    乘法运算:
    每一项的系数与指数组合都需要与另一多项式的每一项相乘。因此，乘法运算需要进行m×n次操作，遍历 A 的每一项并与 B 的每一项相乘。
    时间复杂度：O(m*n)。
    合并相同指数项:
    当插入新项时，需要检查 result 中是否已经存在相同指数的项。这一步最多需要遍历 result 中的每一项。假设 result 最多有m+n 项，合并的时间复杂度为 O(m + n)。
总时间复杂度：O(m*m*n*n)

2.空间复杂度分析。
乘积结果的空间开销:
结果多项式最多可能有 m*n 项，因此 result 所需的空间为 O(m * n)。
总空间复杂度：O(m*n)







*/