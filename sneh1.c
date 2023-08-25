//anything
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;

    struct ListNode* result;

    if (l1->val < l2->val) {
        result = l1;
        result->next = mergeTwoLists(l1->next, l2);
    } else {
        result = l2;
        result->next = mergeTwoLists(l1, l2->next);
    }

    return result;
}

struct ListNode* mergeKLists(struct ListNode** lists, int k) {
    if (k == 0)
        return NULL;

    struct ListNode* heap[k + 1];
    int heapSize = 0;

    for (int i = 0; i < k; i++) {
        if (lists[i] != NULL) {
            heapSize++;
            heap[heapSize] = lists[i];
        }
    }

    for (int i = heapSize / 2; i >= 1; i--) {
        for (int j = i; j <= heapSize / 2; j++) {
            int smallest = j;
            int leftChild = 2 * j;
            int rightChild = 2 * j + 1;

            if (leftChild <= heapSize && heap[leftChild]->val < heap[smallest]->val)
                smallest = leftChild;

            if (rightChild <= heapSize && heap[rightChild]->val < heap[smallest]->val)
                smallest = rightChild;

            if (smallest != j) {
                struct ListNode* temp = heap[j];
                heap[j] = heap[smallest];
                heap[smallest] = temp;
            }
        }
    }

    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = NULL;
    struct ListNode* tail = dummy;

    while (heapSize > 0) {
        struct ListNode* smallestNode = heap[1];
        tail->next = smallestNode;
        tail = tail->next;

        if (smallestNode->next != NULL) {
            heap[1] = smallestNode->next;
        } else {
            heap[1] = heap[heapSize];
            heapSize--;
        }

        int current = 1;
        while (current <= heapSize / 2) {
            int smallest = current;
            int leftChild = 2 * current;
            int rightChild = 2 * current + 1;

            if (leftChild <= heapSize && heap[leftChild]->val < heap[smallest]->val)
                smallest = leftChild;

            if (rightChild <= heapSize && heap[rightChild]->val < heap[smallest]->val)
                smallest = rightChild;

            if (smallest != current) {
                struct ListNode* temp = heap[current];
                heap[current] = heap[smallest];
                heap[smallest] = temp;
                current = smallest;
            } else {
                break;
            }
        }
    }

    tail->next = NULL;
    struct ListNode* mergedList = dummy->next;
    free(dummy);

    return mergedList;
}

struct ListNode* createNode(int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

void printList(struct ListNode* head) {
    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}
