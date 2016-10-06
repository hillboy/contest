n, m = map(int, raw_input().strip().split())
a = map(int, raw_input().strip().split())

b = {}

mi = n/m

p = []

for i in range(1, m+1):
    b[i] = 0

for k,i in enumerate(a):
    if i >=1 and i <=m :
        b[i] = b[i]+1
        if b[i] >mi:
            p.append(k)
    else:
        p.append(k)

ans = 0
j = 0
for i in b:
    if b[i] < mi:
        ans += mi - b[i]
        while b[i] < mi:
            b[i] += 1
            a[p[j]] = i
            j += 1
print mi, ans
print ' '.join([str(i) for i in a])
