# 41048110

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
