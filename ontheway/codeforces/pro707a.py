n, m = map(int, raw_input().strip().split())

a = set()

for i in range(0, n):
  a |= set(raw_input().strip().split())

if set(['C', 'M', 'Y']) & a :
  print '#Color'
else:
  print '#Black&White'
