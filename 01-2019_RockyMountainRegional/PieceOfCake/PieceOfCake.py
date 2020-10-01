n, h, v = (int(i) for i in input().split(" "))
print(max(n - h, h) * max(n - v, v) * 4)
