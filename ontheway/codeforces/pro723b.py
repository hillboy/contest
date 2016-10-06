n = int(raw_input().strip())
s = raw_input().strip()
s = ')' + s + '('
n = 0
m = 0
for i in range(0, len(s)):
    if s[i] == '(' and i != len(s)-1:
        j = s.find(')', i+1)
        m += len(filter(lambda x: len(x), s[i+1:j].split('_')))
    if s[i] == ')':
        j = s.find('(', i+1)
        n = max(n, max([len(i) for i in s[i+1:j].split('_')]))
print n, m
