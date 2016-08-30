n = int(raw_input())

grid = []

for i in range(0, n):
  grid.append(map(int, raw_input().strip().split()))

def update(a, b):
  if len(a) < 2:
    if not b in a:
      a.append(b)

def main():
  if n == 1:
    print '1'
    return

  value = []
  value2 = []
  for i in range(0, n):
    ans = 0
    ok = False
    for j in range(0, n):
      if grid[i][j] == 0:
        ok = True
      ans += grid[i][j]
    if ok:
      update(value2, ans)
    else:
      update(value, ans)

  for i in range(0, n):
    ans = 0
    ok = False
    for j in range(0, n):
      if grid[j][i] == 0:
        ok = True
      ans += grid[j][i]
    if ok:
      update(value2, ans)
    else:
      update(value, ans)

  ans = 0
  ok = False
  for i in range(0, n):
    if grid[i][i] == 0:
      ok = True
    ans += grid[i][i]
  if ok:
    update(value2, ans)
  else:
    update(value, ans)

  ans = 0
  ok = False
  for i in range(0, n):
    if grid[i][-i-1] == 0:
      ok = True
    ans += grid[i][-1-i]
  if ok:
    update(value2, ans)
  else:
    update(value, ans)



  if len(value) > 1 or len(value2) > 1:
    print -1
    return
  if value[0] <= value2[0]:
    print -1
  else:
    print value[0] - value2[0]

main()
