a = raw_input().strip()
b = int(raw_input().strip())
if len(a) < b:
    print 'impossible'
else:
    c = len(set(a))
    print b - c if c < b else 0
