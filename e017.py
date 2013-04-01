words = ["",
  "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
  "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen",
  "twenty", None, None, None, None, None, None, None, None, None,
  "thirty", None, None, None, None, None, None, None, None, None,
  "forty", None, None, None, None, None, None, None, None, None,
  "fifty", None, None, None, None, None, None, None, None, None,
  "sixty", None, None, None, None, None, None, None, None, None,
  "seventy", None, None, None, None, None, None, None, None, None,
  "eighty", None, None, None, None, None, None, None, None, None,
  "ninety", None, None, None, None, None, None, None, None, None
]

for n in xrange(1,1000):
  if len(words) <= n or words[n] == None:
    w = words[n/10*10] + words[n%10] if n < 100 else words[n/100]+"hundred"+("and"+words[n%100] if n%100 else "")
    if len(words) <= n: words.append(w)
    else: words[n] = w
words.append("onethousand")
print sum(map(lambda x: len(x), words))
