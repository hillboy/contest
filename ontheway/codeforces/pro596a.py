n = int(raw_input().strip())
p = []
q = []
for i in range(0, n):
  a,b=map(int, raw_input().strip().split())
  if a not in p:
    p.append(a)
  if b not in q:
    q.append(b)

if len(p) == 2 and len(q) == 2:
  p.sort()
  q.sort()
  print (p[1] - p[0]) * (q[1] - q[0])
else:
  print -1
