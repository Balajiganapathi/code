#include <bits/stdc++.h>

using namespace std;

const int md = 1000000007;

inline void add(int &a, int b) {
  a += b;
  if (a >= md) {
    a -= md;
  }
}

inline void sub(int &a, int b) {
  a -= b;
  if (a < 0) {
    a += md;
  }
}

inline int mul(int a, int b) {
  return (long long) a * b % md;
}

inline int power(int a, int b) {
  int res = 1;
  while (b > 0) {
    if (b & 1) {
      res = mul(res, a);
    }
    b >>= 1;
    a = mul(a, a);
  }
  return res;
}

inline int inv(int x) {
  return power(x, md - 2);
}

const int N = 4345678;

int fact[N], invfact[N];

inline int C(int n, int k) {
  if (k < 0 || k > n) {
    return 0;
  }
  return mul(fact[n], mul(invfact[k], invfact[n - k]));
}

int a[N], b[N];
int foo[N];

void get(int n, int *a) {
  int ka;
  scanf("%d %d", a, &ka);
  int pos = 1;
  while (ka--) {
    int rep, len;
    scanf("%d %d", &rep, &len);
    for (int j = 0; j < len; j++) {
      scanf("%d", foo + j);
    }
    for (int i = 0; i < rep; i++) {
      for (int j = 0; j < len; j++) {
        a[pos] = a[pos - 1] + foo[j];
        pos++;
      }
    }
  }
  assert(pos == n);
}

void advance(int n, int &i, int *a, int &ka) {
  while (i < n) {
    if (i + 1 < n && a[i] == a[i + 1]) {
      ka++;
      i += 2;
      continue;
    }
    if (i + 3 < n && a[i] == a[i + 2] && a[i + 1] == a[i + 3]) {
      ka++;
      i += 4;
      continue;
    }
    break;
  }
}

int cc[N];

int main() {
  fact[0] = 1;
  for (int i = 1; i < N; i++) {
    fact[i] = mul(fact[i - 1], i);
  }
  for (int i = 0; i < N; i++) {
    invfact[i] = inv(fact[i]);
  }
  int tt;
  scanf("%d", &tt);
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    int n;
    scanf("%d", &n);
    get(n, a);
    get(n, b);
    for (int i = 1; i <= n; i++) {
      cc[i] = 0;
    }
    for (int i = 0; i < n; i++) {
      assert(1 <= a[i] && a[i] <= n);
      assert(1 <= b[i] && b[i] <= n);
      cc[a[i]]++;
      cc[b[i]]++;
    }
    for (int i = 1; i <= n; i++) {
      assert(cc[i] == 2);
    }
    int ans = 1;
    int i = 0, j = 0;
    while (i < n || j < n) {
      int ka = 0, kb = 0;
      advance(n, i, a, ka);
      advance(n, j, b, kb);
      if (ka > 0 || kb > 0) {
        ans = mul(ans, C(ka + kb, ka));
        continue;
      }
      if (i < n && j < n && a[i] == b[j]) {
        i++;
        j++;
        continue;
      }
      if (i + 1 < n && j + 1 < n && a[i] == b[j + 1] && a[i + 1] == b[j]) {
        add(ans, ans);
        i += 2;
        j += 2;
        continue;
      }
      if (i < n && j + 2 < n && a[i] == b[j + 1] && b[j] == b[j + 2]) {
        add(ans, ans);
        i += 1;
        j += 3;
        continue;
      }
      if (i + 2 < n && j < n && a[i + 1] == b[j] && a[i] == a[i + 2]) {
        add(ans, ans);
        i += 3;
        j += 1;
        continue;
      }
      ans = 0;
      break;
    }
    printf("%d\n", ans);
    fflush(stdout);
  }
  return 0;
}
