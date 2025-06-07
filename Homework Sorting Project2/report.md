# 41048110 梁詠琳 41143201 吳佩儒

資料結構作業整合報告

---

## 作業二
# 題目一:MinHeap最小堆積實作
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

---

## 題目二：BST 高度與刪除
# 資料結構第二題Binary Search Tree

> (a.)Write a program to start with an initially empty binary search tree and make n random insertions. Use a uniform random number generator to obtain the values to be inserted. Measure the height of the resulting binary search tree and divide this height by log₂n. Do this for n = 100, 500, 1000, 2000, 3000, ..., 10,000. Plot the ratio height / log₂n as a function of n. The ratio should be approximately constant (around 2). Verify that this is so.
---

``` cpp
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
    int val;  // node 值 
    Node* left;   //左子樹
    Node* right;  //右子樹
};

Node* insert(Node* root, int x) {
    if (root == nullptr) {
        root = new Node;
        root->val = x;
        root->left = nullptr;
        root->right = nullptr;
        return root;
    }
    if (x < root->val)
        root->left = insert(root->left, x);
    else
        root->right = insert(root->right, x);
    return root;
}

int getHeight(Node* root) {
    if (root == nullptr) return 0;
    int l = getHeight(root->left);
    int r = getHeight(root->right);
    return max(l, r) + 1;
}

int getRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main() {
    srand(time(0));

    for (int n = 100; n <= 10000; n += 500) {
        Node* root = nullptr;
        for (int i = 0; i < n; i++) {
            int x = getRandom(1, n * 10);
            root = insert(root, x);
        }
        int h = getHeight(root);
        double logn = log2(n);
        double ratio = h / logn;
        cout << "n = " << n << ", height = " << h << ", log2(n) = " << logn << ", ratio = " << ratio << endl;
    }

    return 0;
}

```
## 輸出結果
![alt text](image-1.png)

## 驗結果圖表
> 利用pytho 將資料可視化
``` python
import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("bst_ratio.csv")

plt.figure(figsize=(10, 6))
plt.plot(data["n"], data["ratio"], marker='o')
plt.xticks(data["n"], rotation=45)
plt.xlabel("n")
plt.ylabel("height / log2(n)")
plt.title("BST Height vs log2(n) Ratio")
plt.grid(True)

for i in range(len(data)):
    plt.text(data["n"][i], data["ratio"][i], f'{data["ratio"][i]:.2f}', fontsize=8, ha='right')

plt.tight_layout()
plt.show()
```
![alt text](img.png)

>(b.刪除結點)

1. **沒有子節點 → 直接刪除**

2. **有一個子節點 → 用子節點取代**

3. **有兩個子節點 → 找右子樹最小值（或左子最大值）取代，然後遞迴刪除**

``` cpp 
#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* findMin(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, int k) {
    if (root == nullptr) return nullptr;

    if (k < root->key) {
        root->left = deleteNode(root->left, k);
    } else if (k > root->key) {
        root->right = deleteNode(root->right, k);
    } else {
        // 找到節點
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        } else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    return root;
}

```

>在這個刪除節點的函式中，主要的時間花費是在從樹的上方一路搜尋到目標節點，然後根據節點的情況做對應的刪除處理。這樣的操作最主要的時間取決於樹的高度（h）。
如果這棵二元搜尋樹是平均分布的，那麼高度大約是 log₂(n)，此時刪除的時間是 O(log n)，執行效率很好。但如果這棵樹退化成一條線（像是一直插入遞增或遞減的數字），那就可能要一路找到底，變成 O(n)，效率就會比較差。

因此，這個函式的時間複雜度是 O(h)，其中 h 是樹的高度，最好的情況是 O(log n)，最壞的情況是 O(n)。

---

## 題目三：外部排序輸入時間分析
# 資料結構第二題：Textbook p.457 Exercise 1

## 1. 解題說明

### 問題描述：
這題是關於external sorting的第二階段，也就是合併sorted runs的時候，我們要去分析讀取資料時所花費的總輸入時間(input time)，並觀察這個時間與k-way merge中參數k的關係，找出是否存在一個k值可以讓CPU合併時間與資料輸入時間差不多。

### 解題策略：
-資料量總共有n筆，而記憶體一次只能處理S筆資料，這表示我們會先切 m=n/S個sorted run。
-合併這些run的方式是用k-way merge，意思是每一層可以同時處理k個run，這樣總共就會需要logₖ(m)層。
-每一層都需要把所有資料從硬碟中讀一次進來，因此每一層的輸入時間包含三部分：seek time(磁頭移動)、latency(等待旋轉到位)、加上n筆資料的傳輸時間。
-所以每層輸入時間是：`ts+tl+n×tt`，總輸入時間就是這個數值乘上層數`logₖ(m)`。

---

## 2. 程式實作與數學推導

### 輸入時間公式推導：
```math
t_input(k)=log_k(m)×(ts+tl+n×tt)
```
代入換底公式：
```math
t_input(k)=(log₁₀(m)/log₁₀(k))×(ts+tl+n×tt)
```
代入給定值：
```math
n=200000,S=2000=>m=100
ts=0.08,tl=0.02,tt=0.001
```
最終公式：
```math
t_input(k)=(2/log₁₀(k))×200.1
```

---

## 3. 效能分析

### 時間複雜度：
輸入時間的主成分是磁碟I/O，每層花費O(n)，總共log_k(m)層：
```math
O(log_k(m)× n)≈O(nlogn)
```

### 空間複雜度：
資料在磁碟中處理，記憶體只需要 buffer，因此是：
```math
O(S)≈O(1)
```

---

## 4. 測試與驗證

### 編譯指令：
```shell
$ g++ input_time.cpp -o input_time.exe
$ ./input_time.exe
```

### 輸出範例（表格）：

| k | log₁₀(k)  | t_input(k) (秒) |
|---|----------|-----------------|
| 2 | 0.3010   | ≈ 1328.3        |
| 4 | 0.6020   | ≈ 664.2         |
|10 | 1.0000   | ≈ 400.2         |
|20 | 1.3010   | ≈ 307.5         |
|50 | 1.6990   | ≈ 235.5         |
|100| 2.0000   | ≈ 200.1         |

---

## 5. 申論與開發報告

### 選擇推導方式的原因：

感覺這一題重點其實不是寫程式，而是要描述實際外部排序情境的樣子。  
我們知道：資料太大放不進記憶體，只能切割成run來處理。然後思考在合併run的過程中，每層需要讀一次資料，加上seek和latency。這樣一層的I/O成本就算出來了。

選擇logₖ(m)是因為我們是用k-waymerge，也就是每層合併k個run。logₖ(m)則是合併所需的層數。  
最後我們帶入log公式與數值做出分析，進而可以找到最佳的k值，達到讓CPU時間和輸入時間接近的效果。

結論：真的有這樣的k存在（例如 k = 100）

---

---
