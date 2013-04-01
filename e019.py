from datetime import * # Easy with this module
print len([1 for month in xrange(1, 13) for year in xrange(1901, 2001) if datetime(year, month, 1).weekday() == 6])
