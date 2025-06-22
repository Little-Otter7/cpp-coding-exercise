// solution.cpp
// g++ -std=c++17 -O2 -pipe solution.cpp -o solution

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdint>      
#include <cstdlib>      
using namespace std;

struct SymbolStat {
    long long  prev_ts   = -1;          // Timestamp
    long long  max_gap   = 0;           //Time gap
    long long  volume    = 0;           // Volume
    long long  px_qty    = 0;           // Σ(price * quantity)
    int        max_price = 0;          
};
static inline void parse_line(const string& line,
                              long long& ts,
                              string& sym,
                              int& qty,
                              int& price)
{
    size_t p1 = line.find(',');
    size_t p2 = line.find(',', p1 + 1);
    size_t p3 = line.find(',', p2 + 1);

    ts    = stoll(line.substr(0, p1));
    sym   = line.substr(p1 + 1, p2 - p1 - 1);
    qty   = stoi (line.substr(p2 + 1, p3 - p2 - 1));
    price = stoi (line.substr(p3 + 1));
}

int main(int argc, char* argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " input.csv output.csv\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Failed to open input file\n";
        return 1;
    }
    unordered_map<string, SymbolStat> m;
    string line;
    line.reserve(128);

    while (getline(fin, line)) {
        long long ts;  string sym;  int qty, price;
        parse_line(line, ts, sym, qty, price);

        auto& s = m[sym];                       // O(1) 摊销
        if (s.prev_ts != -1)
            s.max_gap = max(s.max_gap, ts - s.prev_ts);
        s.prev_ts  = ts;

        s.volume  += qty;
        s.px_qty  += 1LL * qty * price;
        s.max_price = max(s.max_price, price);
    }
    fin.close();


    vector<pair<string, SymbolStat>> v(m.begin(), m.end());
    sort(v.begin(), v.end(),
         [](auto& a, auto& b) { return a.first < b.first; });

    ofstream fout(argv[2]);
    if (!fout) {
        cerr << "Failed to open output file\n";
        return 1;
    }

    for (const auto& [sym, s] : v) {
        long long wavg = s.px_qty / s.volume;   
        fout << sym        << ','
             << s.max_gap  << ','
             << s.volume   << ','
             << wavg       << ','
             << s.max_price
             << '\n';
    }
    return 0;
}
// End of solution.cpp