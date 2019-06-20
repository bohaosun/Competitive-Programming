l = int(input())
s = input()

vec = []
for i in range(1, l):
    if s[i] == '0':
        continue
    vec.append(i)

vec = sorted(vec, key=lambda x: abs(x - l / 2))

ans = 10 ** 100000

cnt = 0
for i in vec:
    cnt += 1
    if cnt > 4:
        break
    ans = min(ans, int(s[:i]) + int(s[i:]))

print(ans)
