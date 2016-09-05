n = int(raw_input().strip())
a = [map(int, raw_input().strip().split()) for i in range(0, n)]
b = sum(map(lambda x: x[0] > x[1], a))
c = sum(map(lambda x: x[0] < x[1], a))
if b == c:
    print 'Friendship is magic!^^'
if b > c:
    print 'Mishka'
if b < c:
    print 'Chris'
