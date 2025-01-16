#include <iostream>
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;

class NestedInteger
{
public:
    NestedInteger() : is_integer(false) {}
    NestedInteger(int value) : is_integer(true), integer_value(value) {}

    bool isInteger() const
    {
        return is_integer;
    }

    int getInteger() const
    {
        return integer_value;
    }

    const std::vector<NestedInteger> &getList() const
    {
        return list_value;
    }

    void add(const NestedInteger &ni)
    {
        list_value.push_back(ni);
    }

private:
    bool is_integer;
    int integer_value;
    std::vector<NestedInteger> list_value;
};

NestedInteger parseNestedInteger(const std::string &s, int &index)
{
    NestedInteger result;
    if (s[index] == '[')
    {
        ++index; // skip the '['
        while (s[index] != ']')
        {
            result.add(parseNestedInteger(s, index));
            if (s[index] == ',')
                ++index; // skip the ','
        }
        ++index; // skip the ']'
    }
    else
    {
        int start = index;
        while (index < s.size() && (isdigit(s[index]) || s[index] == '-'))
        {
            ++index;
        }
        int number = std::stoi(s.substr(start, index - start));
        result = NestedInteger(number);
    }
    return result;
}

std::vector<NestedInteger> buildNestedList(const std::string &input)
{
    std::vector<NestedInteger> nestedList;
    int index = 0;
    nestedList.push_back(parseNestedInteger(input, index));
    return nestedList;
}

int depthSumInverse(vector<NestedInteger> &nestedList)
{
    if(nestedList.empty()) return 0;
    queue<pair< NestedInteger, int > >  q;  //队列q存储NestedInteger和深度

    //全存入q里，初始深度为1
    for(const NestedInteger& ni : nestedList){
         q.push(make_pair(ni,1));
    }   
    int maxDepth = 1;  //最大深度，先初始化为1，后面再更新
    vector<int> levelSum;  //levelSum向量，用于记录每一层的整数和。
    while(!q.empty())
    {
        pair<NestedInteger,int> current_depth = q.front();    //q.front()获取队列中的第一个元素current_depth
        q.pop();
        NestedInteger current = current_depth.first;
        int depth = current_depth.second;
        if(current.isInteger()){
            if(levelSum.size() < depth){
                levelSum.resize(depth);
            }
            levelSum[depth-1]+=current.getInteger();
            maxDepth = max(maxDepth,depth);
        }
        else{   //当前NestedInteger是一个列表，遍历这个列表中的每个元素，并将其加入队列 q，
            for(const NestedInteger&ni : current.getList()){
                q.push(make_pair(ni,depth+1));    //深度depth增加1，进入了更深的一层。
            }
        }
    }
    int weightedsum = 0;
    for(int i = 0;i< levelSum.size();++i){
        weightedsum += levelSum[i] * (maxDepth-i);  //按深度加权计算和
    }
    return weightedsum;
}

int main()
{
    std::string input = "[1,[4,[6]]]";
    std::vector<NestedInteger> nestedList = buildNestedList(input);

    int result = depthSumInverse(nestedList);
    std::cout << "Depth Sum Inverse: " << result << std::endl;

    std::string input2 = "[[1,1],2,[1,1]]";
    std::vector<NestedInteger> nestedList2 = buildNestedList(input2);

    int result2 = depthSumInverse(nestedList2);
    std::cout << "Depth Sum Inverse: " << result2 << std::endl;

    return 0;
}

/*
时间复杂度O(n)
空间复杂度O(n)
*/