def get_input():
  return map(int, raw_input().strip().split())

n, m, q = get_input()

inverted = [False] * (n + 1)

nxt = [ [] for i in range(q + 1)]

pre = [-1] * (q + 1)

ops = []

p = [set() for i in range(n+1)]

ans = [0] * (q+1)
now_num = 0


for i in range(0, q):
  ops.append(get_input())

for i, now in enumerate(ops):
  if now[0] == 4:
    if now[1] > 0 and pre[now[1]-1] >= 0:
      pre[i] = pre[now[1] - 1]
    else:
      pre[i] = now[1]
    nxt[pre[i]].append(i)


stack = []

def mydfs():
  stack.append([0, 0])
  global now_num
  while stack:
    i = stack[-1][0]
    j = stack[-1][1]
    if nxt[i] and j < len(nxt[i]):
      stack[-1][1] += 1
      stack.append([nxt[i][j] + 1, 0])
      continue

    if len(stack[-1]) == 2:
      ans[i] = now_num
      if i >= q or ops[i][0] == 4:
        stack.pop()
        continue

      if ops[i][0] == 3:
        if inverted[ops[i][1]]:
          now_num -= m - 2 * len(p[ops[i][1]])
        else:
          now_num += m - 2 * len(p[ops[i][1]])

        inverted[ops[i][1]] = not inverted[ops[i][1]]

        stack[-1].append(0)

        stack.append([i + 1, 0])

        continue

      if ops[i][0] == 1:
        done = 0
        if inverted[ops[i][1]]:
          if ops[i][2] in p[ops[i][1]]:
            p[ops[i][1]].remove(ops[i][2])
            now_num += 1
            done = 1
        else:
          if ops[i][2] not in p[ops[i][1]]:
            p[ops[i][1]].add(ops[i][2])
            now_num += 1
            done = 1
        stack[-1].append(done)
        stack.append([i + 1, 0])
        continue

      if ops[i][0] == 2:
        done = 0
        if not inverted[ops[i][1]]:
          if ops[i][2] in p[ops[i][1]]:
            p[ops[i][1]].remove(ops[i][2])
            now_num -= 1
            done = 1
        else:
          if ops[i][2] not in p[ops[i][1]]:
            p[ops[i][1]].add(ops[i][2])
            now_num -= 1
            done = 1
        stack[-1].append(done)
        stack.append([i + 1, 0])
        continue

    if len(stack[-1]) == 3:
      if ops[i][0] == 3:
        inverted[ops[i][1]] = not inverted[ops[i][1]]
        if inverted[ops[i][1]]:
          now_num += m - 2 * len(p[ops[i][1]])
        else:
          now_num -= m - 2 * len(p[ops[i][1]])
        stack.pop()
        continue

      if ops[i][0] == 1:
        done = stack[-1][2]
        if done:
          now_num -= 1
          if inverted[ops[i][1]]:
            p[ops[i][1]].add(ops[i][2])
          else:
            p[ops[i][1]].remove(ops[i][2])
        stack.pop()
        continue

      if ops[i][0] == 2:
        done = stack[-1][2]
        if done:
          now_num += 1
          if not inverted[ops[i][1]]:
            p[ops[i][1]].add(ops[i][2])
          else:
            p[ops[i][1]].remove(ops[i][2])
        stack.pop()
        continue
    assert(False)

def dfs(i):
  global now_num
  ans[i] = now_num
  if i >= q:
    return
  for j in nxt[i]:
    dfs(j+1)
  if ops[i][0] == 4:
    return

  if ops[i][0] == 3:
    if inverted[ops[i][1]]:
      now_num -= m - 2 * len(p[ops[i][1]])
    else:
      now_num += m - 2 * len(p[ops[i][1]])

    inverted[ops[i][1]] = not inverted[ops[i][1]]

    dfs(i+1)

    inverted[ops[i][1]] = not inverted[ops[i][1]]
    if inverted[ops[i][1]]:
      now_num += m - 2 * len(p[ops[i][1]])
    else:
      now_num -= m - 2 * len(p[ops[i][1]])

  if ops[i][0] == 1:
    done = False
    if inverted[ops[i][1]]:
      if ops[i][2] in p[ops[i][1]]:
        p[ops[i][1]].remove(ops[i][2])
        now_num += 1
        done = True
    else:
      if ops[i][2] not in p[ops[i][1]]:
        p[ops[i][1]].add(ops[i][2])
        now_num += 1
        done = True
    dfs(i+1)
    if done:
      now_num -= 1
      if inverted[ops[i][1]]:
        p[ops[i][1]].add(ops[i][2])
      else:
        p[ops[i][1]].remove(ops[i][2])

  if ops[i][0] == 2:
    done = False
    if not inverted[ops[i][1]]:
      if ops[i][2] in p[ops[i][1]]:
        p[ops[i][1]].remove(ops[i][2])
        now_num -= 1
        done = True
    else:
      if ops[i][2] not in p[ops[i][1]]:
        p[ops[i][1]].add(ops[i][2])
        now_num -= 1
        done = True
    dfs(i+1)
    if done:
      now_num += 1
      if not inverted[ops[i][1]]:
        p[ops[i][1]].add(ops[i][2])
      else:
        p[ops[i][1]].remove(ops[i][2])


# dfs(0)

mydfs()

for i in ans[1:]:
  print i

