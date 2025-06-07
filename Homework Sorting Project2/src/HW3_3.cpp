#include <iostream>
#include <cmath> // 用來取 log10
using namespace std;

int main() {
    // 輸入參數：磁碟存取時間
    double ts = 0.08;      // seek time (秒)
    double tl = 0.02;      // latency time (秒)
    double tt = 0.001;     // 傳輸時間 (秒 / 筆)
    int n = 200000;        // 總資料筆數
    double io_per_layer = ts + tl + n * tt; // 單層輸入時間

    // 我們要計算不同 k 對應的輸入總時間
    int k_values[] = { 2, 4, 10, 20, 50, 100 };
    cout << "k\tlog10(k)\tt_input(k) (秒)" << endl;
    for (int k : k_values) {
        double logk = log10(k);
        double t_input = (2.0 / logk) * io_per_layer; // log_k(100) = 2 / log10(k)
        cout << k << "\t" << logk << "\t\t" << t_input << "s" << endl;
    }

    return 0;
}
