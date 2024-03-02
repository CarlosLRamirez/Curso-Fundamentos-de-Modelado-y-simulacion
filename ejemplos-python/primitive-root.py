def is_primitive_root(a, m):
    seen = set()
    for k in range(1, m):
        seen.add(pow(a, k, m))
    return len(seen) == m - 1

m = 997
for a in range(2, m):
    if is_primitive_root(a, m):
        print(f"A good value for a is: {a}")
        break
