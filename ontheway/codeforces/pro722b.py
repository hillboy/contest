n = int(raw_input().strip())
p = map(int, raw_input().strip().split())

ok = True

syllable = set(['a', 'e', 'i', 'o', 'u' , 'y'])

for i in range(0,n):
    now = raw_input().strip()
    num = 0
    for a in now:
        if a in syllable:
            num+=1
#    print num, p[i]
    if num != p[i]:
        ok=False
if ok:
    print 'YES'
else:
    print 'NO'
