#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using namespace std;

const array<int, 9> init = {1,2,3,4,5,6,7,8,0};

struct Node
{
    array<int, 9> board;
    int space;
    int father;
    int depth;
    int distance;
    Node(array<int, 9> arr, int spc, int dep, int fat)
    {
        board = arr;
        space = spc;
        depth = dep;
        father = fat;
    }
    int getDis(void)
    {
        int sum = 0;
        for (int i=0; i<9; ++i)
        {
            for (int j=0; j<9; ++j)
            {
                if (init[i] == board[j]) 
                {
                    sum += abs((i/3)-(j/3)) + abs((i%3)-(j%3));
                    break;
                }
            }
        }
        return sum;
    }
    bool operator==(Node n)
    {
        return board == n.board;
    }
};

struct SearchTree
{
    int ansInd;
    vector<Node> nodes;
    vector<int> leaves;
    SearchTree(array<int, 9> arr, int space)
    {
        Node node = Node(arr, space, 0, -1);
        node.distance = node.getDis();
        nodes.push_back(node);
        leaves.push_back(0);

    }
    int minDisNode(void)
    {
        int minInd = leaves[0];
        int minDis = nodes[leaves[0]].distance+nodes[leaves[0]].depth;
        for( auto x : leaves)
        {
            int dis = nodes[x].distance+nodes[x].depth;
            if (dis < minDis)
            {
                minDis = dis;
                minInd = x;
            }
        }
        return minInd;
    }
    void newNode(int ind)
    {
        int spc = nodes[ind].space;
        array<int, 9> bd = nodes[ind].board;
        int dep = nodes[ind].depth;
        if (spc%3 != 0)
        {
            Node node = Node(bd, spc, dep+1, ind);
            node.board[spc] = bd[spc-1];
            node.board[spc-1] = 0;
            node.space -= 1;
            node.distance = node.getDis();
            if (find(nodes.begin(), nodes.end(), node) == nodes.end())
            {
                nodes.push_back(node);
                leaves.push_back(nodes.size()-1);
            }
        }
        if (spc%3 != 2)
        {
            Node node = Node(bd, spc, dep+1, ind);
            node.board[spc] = bd[spc+1];
            node.board[spc+1] = 0;
            node.space += 1;
            node.distance = node.getDis();
            if (find(nodes.begin(), nodes.end(), node) == nodes.end())
            {
                nodes.push_back(node);
                leaves.push_back(nodes.size()-1);
            }

        }
        if (spc >= 3)
        {
            Node node = Node(bd, spc, dep+1, ind);
            node.board[spc] = bd[spc-3];
            node.board[spc-3] = 0;
            node.space -= 3;
            node.distance = node.getDis();
            if (find(nodes.begin(), nodes.end(), node) == nodes.end())
            {
                nodes.push_back(node);
                leaves.push_back(nodes.size()-1);
            }

        }
        if (spc <= 5)
        {
            Node node = Node(bd, spc, dep+1, ind);
            node.board[spc] = bd[spc+3];
            node.board[spc+3] = 0;
            node.space += 3;
            node.distance = node.getDis();
            if (find(nodes.begin(), nodes.end(), node) == nodes.end())
            {
                nodes.push_back(node);
                leaves.push_back(nodes.size()-1);
            }
        }
        leaves.erase(find(leaves.begin(), leaves.end(), ind));
    }
    bool extend(void)
    {
        int id = minDisNode();
        if (nodes[id].distance == 0)
        {
            ansInd = id;
            return true;
        }
        newNode(id);
        return false;
    }
};

int main()
{
    vector<int> answer;
    array<int, 9> begArr = {1,0,2,4,5,3,7,8,6};
    SearchTree st = SearchTree(begArr, 1);
    while(!st.extend());
    for(int i=st.ansInd; i!=-1; i=st.nodes[i].father)
    {
        answer.push_back(i);
    }
    for (int i=answer.size()-1; i>=0; --i)
    {
        int newLine = 0;
        for (auto x:st.nodes[answer[i]].board)
        {
            cout << x << " " ;
            ++newLine;            
            if (newLine == 3)
            {
                cout << '\n';
                newLine = 0;
            }
        }
        cout << "distance:" << st.nodes[answer[i]].distance << endl;
    }
    return 0;
}