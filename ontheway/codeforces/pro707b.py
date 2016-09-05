def get_input():
  return map(int, raw_input().strip().split())

n, m, k = get_input()
edges = []

for i in range(0, m):
  edges.append(get_input())

ans = -1

if k:
  bk = get_input()

  bakery = [False] * (n + 1)

  for i in bk:
    bakery[i] = True



  for a, b, c in edges:
    if bakery[a] and not bakery[b]:
      if c < ans or ans < 0:
        ans = c
    if bakery[b] and not bakery[a]:
      if c < ans or ans < 0:
        ans = c

print ans
