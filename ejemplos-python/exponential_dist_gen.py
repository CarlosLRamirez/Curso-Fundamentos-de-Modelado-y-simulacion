import numpy as np
import matplotlib.pyplot as plt

# Step 1: Generate random numbers using LCG
def lcg(m, a, c, X0, n):
    """
    Linear Congruential Generator (LCG) for generating random numbers.
    
    :param m: The modulus
    :param a: The multiplier
    :param c: The increment
    :param X0: The initial seed
    :param n: The number of random numbers to generate
    :return: A list of generated random numbers
    """
    random_numbers = []
    X = X0
    for _ in range(n):
        X = (a * X + c) % m
        random_numbers.append(X / m)  # Normalize
    return random_numbers

# Step 2: Generate exponential distribution using the inverse transform method
def exponential_distribution(lambd, uniform_random_numbers):
    """
    Generate an exponential distribution using the inverse transform method.
    
    :param lambd: The rate parameter (lambda)
    :param uniform_random_numbers: A list of uniform random numbers [0,1)
    :return: A list of numbers following an exponential distribution
    """
    return [-np.log(1 - u) / lambd for u in uniform_random_numbers]

# Custom parameters for LCG
m = 2**32
a = 1664525
c = 1013904223
X0 = 123456789  # Initial seed
n = 100000  # Number of random numbers to generate

# Generate random numbers using LCG
lcg_random_numbers = lcg(m, a, c, X0, n)

# Lambda for exponential distribution
lambd = 1.5  # Custom lambda

# Generate exponential distribution
exponential_numbers = exponential_distribution(lambd, lcg_random_numbers)

# Step 3: Plotting
plt.figure(figsize=(14, 6))

# Plot LCG Random Numbers
plt.subplot(1, 2, 1)
plt.hist(lcg_random_numbers, bins=20, color='skyblue', edgecolor='black')
plt.title('Histogram of LCG Random Numbers')

# Plot Exponential Distribution
plt.subplot(1, 2, 2)
plt.hist(exponential_numbers, bins=20, color='salmon', edgecolor='black')
plt.title('Histogram of Exponential Distribution')

plt.tight_layout()
plt.show()
