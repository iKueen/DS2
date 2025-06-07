# 資料結構課程報告整合  
41048110 梁詠琳  
41143201 吳佩儒  

---

## 作業一：Sorting Project

### 解題說明

本作業需完成 5 種排序法的實作：
- Insertion Sort
- Quick Sort（使用 median-of-three pivot）
- Merge Sort（iterative）
- Heap Sort
- Composite Sort（小量資料用 Insertion，大量用 Heap）

資料量依序為：500、1000、2000、3000、4000、5000。

### 程式碼架構

分為 `Header.h` 與 `sorting.cpp`，程式內有 `chrono` 計算排序時間，每種排序會使用相同的原始資料副本，確保公平性。

### 各排序函式關鍵程式碼（節錄）

```cpp
void insertionSort(vector<int>& arr) { ... }
void quickSort(vector<int>& arr) { ... }
void mergeSort(vector<int>& arr) { ... }
void heapSort(vector<int>& arr) { ... }
void compositeSort(vector<int>& arr) {
    if (arr.size() <= 1000) insertionSort(arr);
    else heapSort(arr);
}
```

### 效能分析

| 演算法       | 時間複雜度 | 空間複雜度 |
|--------------|------------|------------|
| Insertion    | O(n²)      | O(1)       |
| Quick Sort   | O(n log n) | O(log n)   |
| Merge Sort   | O(n log n) | O(n)       |
| Heap Sort    | O(n log n) | O(1)       |
| Composite    | 視條件而定 | O(1)~O(n)  |

### 測試與驗證

```bash
$ g++ sorting.cpp -o sorting.exe
$ ./sorting.exe
```

---

## 作業二：ADT、BST 與 External Sorting

### 題目一：MinHeap 實作

實作 MinPQ 抽象類別，並由 MinHeap 派生實作 `Push`, `Pop`, `Top` 等操作，配合 `HeapUp`, `HeapDown`。

```cpp
template <class T>
class MinHeap : public MinPQ<T> {
    ...
    void Push(const T& item) override { ... }
    void Pop() override { ... }
    const T& Top() const override { ... }
};
```

---

### 題目二：BST 高度分析與刪除節點

1. 隨機插入 n 筆資料
2. 計算 BST 高度 / log₂n 的比值
3. 以 Python 繪製可視化圖表

```cpp
Node* insert(Node* root, int x) { ... }
int getHeight(Node* root) { ... }
```

Python 繪圖：
```python
plt.plot(data["n"], data["ratio"], marker='o')
```

(b) 實作 BST 刪除節點的三種情況，並分析其時間複雜度為 O(h)。

---

### 題目三：外部排序輸入時間分析（p.457 Exercise 1）

#### 問題描述：
外部排序合併階段中，使用 k-way merge 時，總輸入時間為：
```
t_input(k) = log_k(m) × (ts + tl + n × tt)
```

#### 數值代入：
n = 200000, S = 2000 → m = 100  
ts = 0.08, tl = 0.02, tt = 0.001  
⇒ t_input(k) = (2 / log₁₀(k)) × 200.1

#### 結果表格：

| k   | t_input(k) |
|-----|------------|
| 2   | 1328.3     |
| 10  | 400.2      |
| 100 | 200.1      |

#### 小結：
當 k 趨近 100 時，t_input 約等於 CPU 合併時間，達到平衡。

---

## 編譯與測試說明

```bash
$ g++ main.cpp -std=c++17 -o program
$ ./program
```

每題程式碼皆可獨立執行，程式碼與報告統一整合，符合作業格式與章節規範。
