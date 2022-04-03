#include "node.h"

/////////////////////////////////////////////////////////// member functions
Node::Node(int val)
{
    this->val = val;
    this->left = this->right = NULL;
}

Node* Node::insert(Node* root, int val)
{
    if(!root)
        return new Node(val);

    if(val > root->val)
        root->right = insert(root->right, val);

    else if(val <= root->val)
        root->left = insert(root->left, val);

    return root;
}



/////////////////////////////////////////////////////////// other functions
void optimal_bts
(
    std::vector<int> key,
    std::vector<int> freq,
    std::vector<std::vector<int>> &cost,
    std::vector<std::vector<int>> &root
)
{
    //initial cost

    int N = key.size();

    std::vector<int> init(key.size());
    for(int i = 0; i < N; i++)
    {
        cost.push_back(init);
        root.push_back(init);
    }

    for(int i = 0; i < N; i++)
    {
        cost[i][i] = freq[i];
        root[i][i] = i;
    }

    //choose chain length
    for(int l = 2; l <= N; l++)
        //start at i, end at j
        for(int i = 0; i < N-l+1; i++)
        {
            int j = i+l-1;
            cost[i][j] = INT32_MAX;

            //choose root
            for(int k = i; k <= j; k++)
            {
                int tmp = ((k > i)? cost[i][k-1]:0) +
                        ((k < j)? cost[k+1][j]:0) +
                        sum_freq(freq, i, j);

                if(tmp < cost[i][j])
                {
                    cost[i][j] = tmp;
                    root[i][j] = k;
                }
            }
        }
}


void Node::inorder(Node* root, std::vector<int> &preorderList, std::vector<int> &levelList, int level)
{
    if(!root)
        return;

    inorder(root->left, preorderList, levelList, level + 1);
    preorderList.push_back(root->val);
    levelList.push_back(level);
    inorder(root->right, preorderList, levelList, level + 1);
}

int sum_freq(std::vector<int> freq, int i, int j)
{
    int sum = 0;
    for(int s = i; s <= j; s++)
        sum += freq[s];
    return sum;
}

Node* buildTree_wrap(std::vector<int> key, std::vector<int> freq)
{
    if(key.empty())
        return new Node(0);

    std::vector<std::vector<int>> cost, best;

    //find optimal bts, store in cost and best
    optimal_bts(key, freq, cost, best);


    Node root, *tree = NULL;
    int k = best[0][best.size()-1];
    tree = root.insert(tree, key[k]);

    tree = buildTree(tree, key, best, 0, k-1);
    tree = buildTree(tree, key, best, k+1, best.size()-1);

    return tree;
}

Node* buildTree(Node* root, std::vector<int> key, std::vector<std::vector<int>> best, int start, int end)
{
    if(start > end)
        return root;

    int k = best[start][end];
    root->insert(root, key[k]);

    root = buildTree(root, key, best, start, k-1);
    root = buildTree(root, key, best, k+1, end);

    return root;
}


int treeHeight(Node* root)
{
    if(!root)
        return -1;

    return 1 + std::max(treeHeight(root->left), treeHeight(root->right));
}
