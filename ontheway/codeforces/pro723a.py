p = map(int, raw_input().strip().split())
p.sort()
print p[-1]-p[0]
