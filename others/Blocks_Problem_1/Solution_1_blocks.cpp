/*
Author: Snickeen
Time: 202205231 

Problem Intro:
    维护区间加法，查询区间gcd
Solution: 
    分块解法

More: 
    没有提交过，只测试了一下样例并且通过了。

*/


#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

// [0, x), [x, 2x)...
struct Block {
    LL n; // there are [0, n] elements
    LL size; // size of each block
    LL number; // number of blocks
    std::vector<LL> t; 
    std::vector<LL> tag; // lazy mark
    std::vector<LL> g; // gcd of the sigle block
    
    Block(LL m = 0) {
        Reset(m);
    }
    void Reset(LL m = 0) {
        n = m + 1;
        size = sqrt(n + n + 1) + 1;
        number = (n + size - 1) / size;
        t.resize(size * number + 3);
        tag.resize(number + 3);
        g.resize(number + 3);
    }

    LL GetWhichBlock(LL m) {
        return m / size;
    }
    // get [l_i, r_i] when index m is in the i-th block
    LL GetLeftIndex(LL m) {
        return m / size * size;
    }
    LL GetRightIndex(LL m) {
        return GetLeftIndex(m) + size - 1;
    }

    LL OpWholeBlock(LL p) {
        LL l = p * size, r = l + size - 1;
        g[p] = 0;
        for (; l <= r; ++l) {
            t[l] += tag[p];
            g[p] = __gcd(g[p], t[l]);
        }
        tag[p] = 0;
        return g[p];
    } 
    LL OpSingleBlock(LL p, LL l, LL r, LL value) {
        for (LL i = l; i <= r; ++i) t[i] += value;
        OpWholeBlock(p);
        LL d = 0;
        for (LL i = l; i <= r; ++i) d = __gcd(d, t[i]);
        return d;
    }
    LL Op(LL l, LL r, LL value = 0) {
        LL lo = GetWhichBlock(l);
        LL hi = GetWhichBlock(r);
        if (lo == hi) {
            return OpSingleBlock(lo, l, r, value);
        }
        LL d = 0;
        d = __gcd(d, OpSingleBlock(lo, l, GetRightIndex(lo), value));
        d = __gcd(d, OpSingleBlock(hi, GetLeftIndex(hi), r, value));
        for (LL i = lo + 1; i < hi; ++i) tag[i] += value;
        if (value) {
            for (LL i = lo + 1; i < hi; ++i) {
                if (tag[i]) OpWholeBlock(i);
                d = __gcd(d, g[i]);
            }
        }
        return d;
    }
};



signed main() 
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    LL n, m;
    cin >> n >> m;
    Block ans(n);
    for (LL i = 1; i <= n; ++i) cin >> ans.t[i];
    for (LL f, l, r, x; m; --m) {
        cin >> f >> l >> r;
        if (1 == f) cout << ans.Op(l, r) << endl;
        else {
            cin >> x;
            ans.Op(l, r, x);
        }
    }
    return 0;
}

/*

# input sample 1

3 4 
2 3 4
1 1 3
2 2 2 1
1 1 3
1 2 3

# output sample 1

1 
2
4



# input sample 2

3 4 
2 4 6
1 1 3
2 2 2 1
1 1 3
1 1 2

# output sample 2

2
1
1


*/