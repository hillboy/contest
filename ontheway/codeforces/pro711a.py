n = int(raw_input())
a = []
ok = False
for i in range(0, n):
  a.append(raw_input().strip())
  if 'OO' in a[-1]:
    ok = True
if not ok:
  print 'NO'
else:
  print 'YES'
  for i in a:
    if ok and 'OO' in i:
      i = i.replace('OO', '++', 1)
      ok = False
    print i
