// compile with g++ avx_test1.cpp -O2 -mavx2
#include<stdio.h>
#include<vector>
#include <immintrin.h>
#include <smmintrin.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<string>
#include<iostream>
using namespace std;
#define maxn 64000000
#define same_ptr 60000000

char A[maxn+1] __attribute__((aligned(64)));
char B[maxn+1] __attribute__((aligned(64)));

void prepare() {
  for(int i = 0; i < same_ptr; i++) {
    A[i] = B[i] = 'a' + rand() % 26;
  }
  for(int i = same_ptr; i < maxn; i++) {
    A[i] = 'a' + rand() % 26;
    B[i] = 'a' + rand() % 26;
  }
}

void test1() {
  int i;
  for(i=0;i<maxn;i++) {
    if(A[i]!=B[i])
      break;
  }
  printf("%d\n", i);
}

template<class T> inline void Log(const T * data, size_t size, const std::string & name)
{
    std::cout << name << " = { ";
    for (int i = 0; i < size; i++)
    {
        std::cout << int(data[i]) << " ";
    }
    std::cout << "} " << std::endl;
}

inline void LogU8(const __m128i & value, const std::string & name)
{
    uint8_t buffer[16];
    _mm_storeu_si128((__m128i*)buffer, value);
    Log(buffer, 16, name);
}

void test3() {
  int i;
  __m128i zero = _mm_setzero_si128();
  for(i=0;i<maxn;i+=16) {
    __m128i a = _mm_loadu_si128((__m128i const*) &A[i]);
    __m128i b = _mm_loadu_si128((__m128i const*) &B[i]);

    __m128i ans = _mm_xor_si128(a, b);
    if(_mm_movemask_epi8(_mm_cmpeq_epi32(ans,zero)) != 0xFFFF)
    {
      break;
    }
  }
  printf("%d\n", i);
}

void test4() {
  int i;
  __m256i zero = _mm256_setzero_si256();
  for(i=0;i<maxn;i+=16) {
    __m256i a = _mm256_loadu_si256((__m256i const*) &A[i]);
    __m256i b = _mm256_loadu_si256((__m256i const*) &B[i]);

    __m256i ans = _mm256_xor_si256(a, b);
    if(_mm256_testz_si256(ans, zero))
    {
      break;
    }
  }
  printf("%d\n", i);
}

void test2() {
  int l=0, r = maxn-1, mid;
  while(l<=r) {
    mid=(l+r)/2;
    int ans = strncmp(A,B,mid);
    if(ans==0) {
      l=mid+1;
    } else {
      r=mid-1;
    }

  }
  printf("%d\n", r);
}


int main() {
  prepare();
  auto last = clock();
  test1();
  auto now = clock();
  printf("%lf.\n", (float)(now-last)/CLOCKS_PER_SEC);
  last = clock();
  test2();
  now = clock();
  printf("%lf.\n", (float)(now-last)/CLOCKS_PER_SEC);

  last = clock();
  test3();
  now = clock();
  printf("%lf.\n", (float)(now-last)/CLOCKS_PER_SEC);

  last = clock();
  test4();
  now = clock();
  printf("%lf.\n", (float)(now-last)/CLOCKS_PER_SEC);
  return 0;
}
