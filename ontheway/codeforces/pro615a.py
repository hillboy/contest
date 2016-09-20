n, m = map(int, raw_input().strip().split())
ha = [False] * (m + 1)
num = 0
for i in range(0, n):
    now = map(int, raw_input().strip().split())
    for j in now[1:]:
        if not ha[j]:
            ha[j] = True
            num += 1

if num == m:
    print 'YES'
else:
    print 'NO'
