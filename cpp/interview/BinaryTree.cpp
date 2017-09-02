struct BinaryTreeNode
{
       int m_data;
       BinaryTreeNode* m_pLeft;
       BinaryTreeNode* m_pRight;
};

unsigned int getNodeNum(BinaryTreeNode * pRoot)
{
       if (!pRoot) return 0;
       return getNodeNum(pRoot->m_pLeft) + getNodeNum(pRoot->m_pRight) + 1;
}

int getDepth(BinaryTreeNode * pRoot)
{
       if (!pRoot) return 0;
       return std::max(getDepth(pRoot->m_pLeft), getDepth(pRoot->m_pRight)) + 1;
}

void preOrderTraverse(BinaryTreeNode * pRoot)
{
       if (!pRoot) return;
       printf("%d\t", pRoot->_data);
       preOrderTraverse(pRoot->m_pLeft);
       preOrderTraverse(pRoot->m_pRight);
       return;
}

void inOrderTraverse(BinaryTreeNode * pRoot)
{
       if (!pRoot) return;
       inOrderTraverse(pRoot->m_pLeft);
       printf("%d\t", pRoot->_data);
       inOrderTraverse(pRoot->m_pRight);
       return;
}

void postOrderTraverse(BinaryTreeNode * pRoot)
{
       if (!pRoot) return;
       postOrderTraverse(pRoot->m_pLeft);
       postOrderTraverse(pRoot->m_pRight);
       printf("%d\t", pRoot->_data);
       return;
}

#include <queue>
void levelTraverse(BinaryTreeNode * pRoot)
{
       if (!pRoot) return;
       std::queue<BinaryTreeNode*> squeue;
       squeue.push(pRoot);
       
       BinaryTreeNode* pOutRoot = NULL;
       while(!squeue.empty())
       {
              if (pRoot->m_pLeft) squeue.push(pRoot->m_pLeft);
              if (pRoot->m_pRight) squeue.push(pRoot->m_pRight);
              pOutRoot = squeue.front();
              squeue.pop();
              printf("%d\t", pOutRoot->_data);
       }
       return;
}

int getNodeNumKthLevel(BinaryTreeNode * pRoot, int k)
{
       if (!pRoot || k < 1) return 0;
       if (k == 1) return 1;
       return getNodeNumKthLevel(pRoot->m_pLeft, k - 1) + getNodeNumKthLevel(pRoot->m_pRight, k - 1);
}

int getLeafNodeNum(BinaryTreeNode * pRoot)
{
       if (!pRoot) return 0;
       if (!pRoot->m_pLeft && !pRoot->m_pRight) return 1;
       return getLeafNodeNum(pRoot->m_pLeft) + getLeafNodeNum(pRoot->m_pRight);
}

bool structureCmp(BinaryTreeNode * pRoot1, BinaryTreeNode * pRoot2)
{
       if (!pRoot1 && !pRoot2) return true;
       if (!pRoot1 || !pRoot2) return false;
       return structureCmp(pRoot1->m_pLeft, pRoot2->m_pLeft) && structureCmp(pRoot1->m_pRight, pRoot2->m_pRight);
}

BinaryTreeNode * mirror(BinaryTreeNode * pRoot)
{
       if (!pRoot) return NULL;
       BinaryTreeNode* lSubRoot = mirror(pRoot->m_pLeft);
       BinaryTreeNode* rSubRoot = mirror(pRoot->m_pRight);
       pRoot->m_pLeft = rSubRoot;
       pRoot->m_pRight = lSubRoot;
       return pRoot;
}
