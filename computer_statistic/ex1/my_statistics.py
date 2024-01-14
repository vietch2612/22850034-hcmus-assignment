def mean(samples):
    # total samples / number of samples
    return sum(samples) / len(samples)

def median(samples):
    # sort samples first, ascending order
    samples = sorted(samples)
    # if number of samples is even, median is the mean of the two middle values
    if len(samples) % 2 == 0:
        return mean([samples[len(samples) // 2 - 1], samples[len(samples) // 2]])
    # if number of samples is odd, median is the middle value
    else:
        return samples[len(samples) // 2]

def mode(samples):
    # return the most frequent value in samples
    # max() returns the maximum value in a list
    # key=samples.count is a function that returns the number of times a value appears in samples
    return max(set(samples), key=samples.count)

def range(samples):
    # return the difference between the maximum and minimum values in samples
    return max(samples) - min(samples)

def variance(samples):
    # sum of the squared differences between each value and the mean, divided by the number of samples
    return sum([(x - mean(samples)) ** 2 for x in samples]) / len(samples)

def standard_deviation(samples):
    # square root of the variance
    return variance(samples) ** 0.5