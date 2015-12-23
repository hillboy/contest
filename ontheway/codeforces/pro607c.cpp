#include<stdio.h>
#define maxn 1000100

char s1[maxn],s2[maxn];

char s[maxn*2];

int i,j,n,m;

inline char rev(char& a) {
  if(a=='N')
    return 'S';
  if(a=='W')
    return 'E';
  if(a=='S')
    return 'N';
  if(a=='E')
    return 'W';
  return 0;
}

int z[maxn*2];

inline void Z() {
  int L = 0, R = 0;
  for (int i = 1; i < n; i++) {
    if (i > R) {
      L = R = i;
      while (R < n && s[R-L] == s[R]) R++;
      z[i] = R-L; R--;
    } else {
      int k = i-L;
      if (z[k] < R-i+1) z[i] = z[k];
      else {
        L = i;
        while (R < n && s[R-L] == s[R]) R++;
        z[i] = R-L; R--;
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  n--;
  scanf(" %s %s", s1, s2);
  for(i=0;i<n;i++) {
    s2[i]=rev(s2[i]);
    s[n-i-1]=s2[i];
    s[i+n]=s1[i];
    
  }
//  printf("%s\n", s);
  n*=2;
  Z();
  n/=2;
//  for(i=0;i<n+n;i++) {
//    printf("%d\n", z[i]);
//  }
  for(i=0;i<n;i++) {
    if(z[i+n] >= n-i) {
      printf("NO\n");
      return 0;
    }
  }
  printf("YES\n");
  return 0;
}
