import random
s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" * 1000
s += "Bulbasaur" * 1000
print ''.join(random.sample(s,len(s)));
