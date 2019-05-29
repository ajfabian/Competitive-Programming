a, b = map(float, input().strip().split())
if abs(b-a) > 1e-4:
  exit(0)
else:
  exit(1)
