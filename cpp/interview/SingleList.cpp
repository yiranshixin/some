struct Node
{
       int data;
       Node *next;
};
typedef struct Node Node_t;
Node_t* ReverseList(Node_t* head)
{
       if (NULL == head || NULL == head->next)
       {
              return head;
       }
       Node_t* pre = NULL;
       Node_t* cur = head;
       Node_t* nxt = head->next;
       while(NULL != nxt)
       {
              cur->next = pre;
              pre = cur;
              cur = nxt;
              nxt = nxt->next;
       }
       cur->next = pre;
       return cur;
}

Node * ReverseList(Node *head)
{
       if (head == NULL || head->next == NULL)
              return head;
       Node *pre = head;
       Node *cur = pre->next;
       Node *nxt = cur->next;
       pre->next = NULL;
       while (nxt != NULL)
       {
              cur->next = pre;
              pre = cur;
              cur = nxt;
              nxt = nxt->next;
       }
       cur->next = pre;
       head = cur;
       return head;
}

Node_t* findK(Node_t* head, int k)
{
       Node_t* pre = NULL;
       Node_t* cur = head;
       while (k-- > 0 && NULL != cur)
       {
              cur = cur->next;
       }
       
       if (k > 0) return pre;
       pre = head;
       while (NULL != cur)
       {
              cur = cur->next;
              pre = pre->next;
       }
       return pre;
}

bool checkCircle(Node_t* head)
{
       if (NULL == head || NULL == head->next)
       {
              return false;
       }
       Node_t* slow = head;
       Node_t* fast = head->next;
       while (NULL != slow && NULL != fast->next)
       {
              if (slow == fast->next) return true;
              slow = slow->next;
              fast = fast->next->next;
       }
       return false;
}

Node_t* megerList(Node_t* head1, Node_t* head2)
{
       if (NULL == head1)
       {
              return head2;
       }
       
       if (NULL == head2)
       {
              return head1;
       }
       Node_t *it1 = head1, *it2 = head2, *head = NULL;
       if (it1->data <= it2->data)
       {
              head = it1;
              it1 = it1->next;
       }
       else
       {
              head = it2;
              it2 = it2->next;
       }
       Node_t* cur = head;
       while (NULL != it1 && NULL != it2)
       {
              if (it1 <= it2)
              {
                     cur->next = it1;
                     it1 = it1->next;
              }
              else
              {
                     cur->next = it2;
                     it2 = it2->next;
              }
              cur = cur->next;
       }
       
       if (NULL == it1)
       {
              cur->next = it2;
       }
       if (NULL == it2)
       {
              cur->next = it1;
       }
       return head;
}


Node_t* megerListRecursive(Node_t* head1, Node_t* head2)
{
       if (NULL == head1) return head2;
       if (NULL == head2) return head1;
       Node_t* head = NULL;
       Node_t* cur = NULL;
       if (head1->data <= head2->data)
       {
              head = head1;
              cur = megerListRecursive (head1->next, head2);
       }
       else
       {
              head = head2;
              cur = megerListRecursive (head1, head2->next);
       }
       head->next = cur;
       return head;
}
