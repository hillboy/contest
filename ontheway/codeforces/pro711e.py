n, m = map(int, raw_input().strip().split())

DIV = 1000003

rev2 = 500002

def mypow(a, n) :
  ans = 1
  now = a
  while(n > 0) :
    if n % 2 == 1:
      ans *= now
      ans %= DIV
    now *= now
    now %= DIV
    n /= 2
  return ans

def main()  :
  if n < 70 and pow(2, n) < m:
    print 1, 1
    return


  # a!
  def count2(a):
    ans = 0
    while a > 0 :
        a /= 2
        ans += a
    return ans

  A = 1

  temp = count2(m-1) + n

  if m < DIV:
    p = [0]*DIV
    i = 1
    j = 1
    while p[i] == 0:
      p[i] = j
      j += 1
      i = i * 2 % DIV

    cir = j - p[i]
    k = n % cir
    start = 0
    for i in range(0, DIV):
      if p[i] == k + 1:
        start = i

    for i in range(0, m):
      A = A * start % DIV
      start -= 1
      if start < 0:
        start += DIV

    A = A * mypow(rev2, temp) % DIV
  else:
    A = 0

  B = mypow(2, n*m - temp)
  A = B - A
  if A < 0 :
    A += DIV
  print A, B

main()
