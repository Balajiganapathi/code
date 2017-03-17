#!/usr/bin/python

n = 50
m = 50
array = [0] * (n * m)

for j in range(m):
    for i in range(n):
        array[j * n + i] = i;
    jj = (j + 1) % n
    if j > 0:
        array[j * n + j] = jj;


print ','.join([str(x) for x in array])
print len(array)
