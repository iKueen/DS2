# 資料結構作業:MinHeap最小堆積實作
>
Write a C++ abstract class similar to ADT 5.2 for the ADT MinPQ, which defines a min priority queue.
Now write a C++ class MinHeap that derives from this abstract class and implements all the virtual functions of MinPQ.
The complexity of each function should be the same as that for the corresponding function of MaxHeap.

## 程式碼

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;             // 檢查是否為空
    virtual const T& Top() const = 0;             // 取得最小值
    virtual void Push(const T& item) = 0;         // 插入
    virtual void Pop() = 0;                       //彈出
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    vector<T> heap; 
    void HeapUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] >= heap[parent]) break;
            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void HeapDown(int index) {
        int size = heap.size();
        while (2 * index + 1 < size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = left;

            if (right < size && heap[right] < heap[left])
                smallest = right;

            if (heap[index] <= heap[smallest]) break;
            swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

public:
    bool IsEmpty() const override {  //（override）覆寫父類別的虛擬函式
        return heap.empty();
    }

    // 取得最小值
    const T& Top() const override {
        if (IsEmpty()) throw runtime_error("Heap 是空的");
        return heap[0];
    }

    void Push(const T& item) override {
        heap.push_back(item);
        HeapUp(heap.size() - 1);
    }

    void Pop() override {
        if (IsEmpty()) throw runtime_error("Heap 是空的");
        heap[0] = heap.back();
        heap.pop_back();
        if (!IsEmpty())
            HeapDown(0);
    }


    void Print() const {
        cout << "陣列內容為: ";
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};
int main() {
    MinHeap<int> h;

    h.Push(5);  //插入一個數字五 (目前為Heap唯一資料所以在最上面)
    h.Push(3); //插入一個數字三 (原:[5,3]->][3,5])
    h.Push(8);  //插入一個數字八 (8>5>3 不交換)
    h.Push(1);  //插入一個數字一 (1<3<5<8 -> [1,3,5,8])

    cout << "Heap content: ";
    h.Print();  // 應該是 1 在最前面

    cout << "Top: " << h.Top() << endl;  //  1
    h.Pop();
    cout<<"------------"<<endl;
    cout << "Top: " << h.Top() << endl;  //  3

    return 0;
}

```
>範例測資
5-3-8-1

## 步驟1:插入5(首個元素)
![alt text](image-1.png)

## 步驟2:插入3(3<5 SWAP)
![alt text](image-2.png)

## 步驟3:插入8(3<5<8 不需SWAP)
![alt text](image-3.png)

## 步驟3:插入1(1<3<5<8 1  1和5先交換)
![alt text](image-5.png)
## 1再和3交換
![alt text](image-6.png)
## 樹

![alt text](image-7.png)

## 範例2
  ```  h.Push(10);
    h.Push(9);
    h.Push(8);
    h.Push(7);
    h.Push(6);
    h.Push(5);
    h.Push(4);
    h.Push(3);
    h.Push(2);
    h.Push(1);
```
![alt text](image-4.png)