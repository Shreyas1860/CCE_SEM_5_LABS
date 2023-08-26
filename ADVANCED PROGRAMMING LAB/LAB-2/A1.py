# Create a dictionary to store cached results
fib_cache = {}

def fibonacci(n):
    # Check if the result is already in the cache
    if n in fib_cache:
        return fib_cache[n]

    # Base cases
    if n == 0:
        return 0
    elif n == 1:
        return 1

    # Calculate the Fibonacci number recursively
    result = fibonacci(n - 1) + fibonacci(n - 2)

    # Cache the result
    fib_cache[n] = result
    return result

# Calculate and print the Fibonacci numbers
for i in range(10):
    fib_value = fibonacci(i)
    print(f"Fibonacci({i}) = {fib_value}")
