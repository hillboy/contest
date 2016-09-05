n = int(raw_input().strip())

if n <= 2 :
  print -1
else:
  x = 0
  y = 0
  if n % 2 == 0:
    x = 2
    y = n * n / 2
  else:
    x = 1
    y = n * n
  print (x + y) / 2, (y - x) / 2

