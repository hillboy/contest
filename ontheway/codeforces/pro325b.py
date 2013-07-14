n=int(raw_input())
n*=2

def cal(a,x):
  ans=x/2*(x/2-1)
  while a > 0 :
    ans+=a*x
    a/=2
  return ans

def solve(a):
  l=1
  r=n
  while l<=r :
    mid=(l+r)/2
    if cal(a,mid) <=n :
      l=mid+1
    else:
      r=mid-1
  if cal(a,r) == n and (r/2)%2==1:
    return r
  if cal(a,l) == n and (l/2)%2==1:
    return l
  return 0


ans=[]

a=0
while a <= n:
  now = solve(a)
  if now > 0 :
    if a > 0:
      ans.append(now*a)
    else:
      ans.append(now/2)
  if a==0:
    a+=1
  else:
    a*=2

last =0

if len(ans) ==0 :
  print -1
else:
  ans.sort()
  for i in ans:
    if i != last:
      print i
    last=i
