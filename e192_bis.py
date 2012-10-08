import decimal
import fractions
from math import *
decimal.getcontext().prec = 100
def get_approx(n, den_limit):
  sqrt_n = decimal.Decimal(n).sqrt()
  return fractions.Fraction.from_decimal(sqrt_n).limit_denominator(den_limit)

print(sum(get_approx(n, 10**12).denominator if n != floor(sqrt(n)) ** 2 else 0 for n in range(2, 100001)))
