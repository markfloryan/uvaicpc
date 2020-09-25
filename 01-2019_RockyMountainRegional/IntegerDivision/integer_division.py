# Get the input
n, d = map(int, input().split())

nums = [x for x in map(int, input().split())]

# Compute the division and store the count for each result
results = {}

for num in nums:
	result = num // d

	if result not in results:
		results[result] = 0

	results[result] += 1

# Compute the number of unqiue pairs for each result, add them up
pairs = 0 
for key, result in results.items():
	if result > 1:
		pairs += (result * (result-1) / 2)

print(int(pairs))
