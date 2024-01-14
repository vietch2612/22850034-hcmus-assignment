def mean(samples):
    return sum(samples) / len(samples)

def median(samples):
    samples = sorted(samples)
    if len(samples) % 2 == 0:
        return mean([samples[len(samples) // 2 - 1], samples[len(samples) // 2]])
    else:
        return samples[len(samples) // 2]

def mode(samples):
    return max(set(samples), key=samples.count)

def range(samples):
    return max(samples) - min(samples)

def variance(samples):
    return sum([(x - mean(samples)) ** 2 for x in samples]) / len(samples)

def standard_deviation(samples):
    return variance(samples) ** 0.5