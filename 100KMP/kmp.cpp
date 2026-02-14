#include<bits/stdc++.h>
using namespace std;
// KMP算法
	int kmp(vector<char>& s1, vector<char>& s2) {
		// s1中当前比对的位置是x
		// s2中当前比对的位置是y
		int n = s1.size(), m = s2.size(), x = 0, y = 0;
		// O(m)
		vector<int> next = nextArray(s2, m);
		// O(n)
		while (x < n && y < m) {
			if (s1[x] == s2[y]) {
				x++;
				y++;
			} else if (y == 0) {
				x++;
			} else {
				y = next[y];
			}
		}
		return y == m ? x - y : -1;
	}

	// 得到next数组
	vector<int> nextArray(vector<char>& s, int m) {
		if (m == 1) {
			return { -1 };
		}
		vector<int> next;
        next.resize(m);
		next[0] = -1;
		next[1] = 0;
		// i表示当前要求next值的位置
		// cn表示当前要和前一个字符比对的下标
		int i = 2, cn = 0;
		while (i < m) {
			if (s[i - 1] == s[cn]) {
				next[i++] = ++cn;
			} else if (cn > 0) {
				cn = next[cn];
			} else {
				next[i++] = 0;
			}
		}
		return next;
	}

