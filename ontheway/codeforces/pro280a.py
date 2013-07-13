"""One-line documentation for pro280a module.

A detailed description of pro280a.
"""
import math
from decimal import *

getcontext().prec = 100

w,h,a=map(Decimal,(raw_input().split()))

if a>90 :
  a=Decimal(180)-a

pi=math.acos(Decimal(-1))

alpha=a/Decimal(180)*Decimal(pi)

k=1/math.sin(alpha)+1/math.tan(alpha)
k=Decimal(k)
y=(w-k*h)/(1-k*k)
x=h-y*k
tg=Decimal(math.tan(alpha))
print w*h-(x*x+y*y)/tg
