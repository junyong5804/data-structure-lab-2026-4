// MinHeap.h: 최소 힙 클래스 (프로그램 10.7)
... // 코드 동일

// 삽입 함수
void insert(int key, int u, int v) {
    if (isFull()) return;
    int i = ++size;
    while (i != 1 && key < getParent(i).getKey()) {
        node[i] = getParent(i);
        i /= 2;
    }
    node[i].setKey(key, u, v);
}
... // 코드 동일
};

