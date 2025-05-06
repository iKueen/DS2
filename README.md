# 41048110梁詠琳 41143201吳佩儒

作業一(Homework Sorting Project)

## 1. 解題說明

### 題目描述
本作業需完成 5 種排序法的實作，包括：
- Insertion Sort
- Quick Sort (using median-of-three method to choose pivot)
- Merge Sort (using iterative method)
- Heap Sort
- Composite Sort

帶入資料量：500，1000，2000，3000，4000，5000

### 解題策略
- Insertion Sort：第一種簡單排序，適合小量資料。
- Quick Sort：使用 median-of-three 選取 pivot，並以 iterative 方式實作避免追加軟體繁複性。
- Merge Sort：採用底向 bottom-up iterative 合併。
- Heap Sort：使用簡單的 heapify 程式，完成實作。
- Composite Sort：根據資料量，小量用 Insertion，大量用 Heap 加速。

## 2. 程式實作

使用 C++，分為 Header.h 和 sorting.cpp：
- Header.h：定義了出所有函式。
- sorting.cpp：實作所有排序法，資料生成，測量時間，即時顯示。
  
  =========================================================
- Insertion Sort
  ```
  void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}


  =========================================================
  
- Quick Sort (using median-of-three method to choose pivot)
```
int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = (low + high) / 2;
    if (arr[mid] < arr[low]) swap(arr[mid], arr[low]);
    if (arr[high] < arr[low]) swap(arr[high], arr[low]);
    if (arr[high] < arr[mid]) swap(arr[high], arr[mid]);
    return arr[mid];
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = medianOfThree(arr, low, high);
    int left = low, right = high;
    while (true) {
        while (arr[left] < pivot) left++;
        while (arr[right] > pivot) right--;
        if (left >= right) return right;
        swap(arr[left++], arr[right--]);
    }
}
void quickSort(vector<int>& arr) {
    int n = arr.size();
    stack<pair<int, int>> s;
    s.push({ 0, n - 1 });
    while (!s.empty()) {
        int low = s.top().first;
        int high = s.top().second;
        s.pop();
        if (low < high) {
            int p = partition(arr, low, high);
            s.push({ low, p });
            s.push({ p + 1, high });
        }
    }
}
```
  
=========================================================
  
- Merge Sort (using iterative method)
```
void mergePass(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i < mid) temp[k++] = arr[i++];
    while (j < right) temp[k++] = arr[j++];
}

void mergeSort(vector<int>& arr) {
    int n = arr.size();
    vector<int> temp(n);
    for (int width = 1; width < n; width *= 2) {
        for (int i = 0; i < n; i += 2 * width) {
            int left = i;
            int mid = min(i + width, n);
            int right = min(i + 2 * width, n);
            mergePass(arr, temp, left, mid, right);
        }
        arr = temp;
    }
}
```
  
=========================================================
  
- Heap Sort
```
void heapify(vector<int>& arr, int n, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```
  
  ================================================================
  
- Composite Sort
```
  void compositeSort(vector<int>& arr) {
    if (arr.size() <= 1000) insertionSort(arr);
    else heapSort(arr);
}
```
  
  ================================================================
  

通過 chrono::high_resolution_clock 計算排序時間，確保高精度。

每種排序則獨立使用一份 copy 的原始資料，確保比較公平。

## 3. 效能分析

對程式效能進行 Big-O 分析：

### 時間複雜度
- Insertion Sort：O(n^2)
- Quick Sort：O(n log n)
- Merge Sort：O(n log n)
- Heap Sort：O(n log n)
- Composite Sort：O(n) 或 O(n log n) (根據資料量分分別)

### 空間複雜度
- Insertion Sort：O(1)
- Quick Sort：O(log n) 至 O(n)
- Merge Sort：O(n)
- Heap Sort：O(1)
- Composite Sort：根據選擇，O(1)~O(n)

## 4. 測試與驗證

### 編譯指令：
```shell
$ g++ sorting.cpp -o sorting.exe
$ ./sorting.exe
```

顯示：
- 各種資料量 (500, 1000, 2000, 3000, 4000, 5000) 的原始資料
- 排序後每種排序法的執行時間
- 排序原始資料都是隨機生成，固定存記，確保各排序公平比較

## 5. 由來與開發報告

### 有用到的計算法
- Insertion 排序：第一種執行說明步驟，第一種數据搭配最等等調整
- Quick Sort：補教 median-of-three，避免最壞情況，並使用堆積代替遞對
- Merge Sort：底向 iterative 合併，避免繁複 recursive overhead
- Heap Sort：帶入 heapify，同時定義最大 heap 的觀念

### 開發考量
- 根據資料量，有效分配 Insertion Sort 與 Heap Sort，優化排序效能
- 每種排序都有自己獨立設計與定義

---
