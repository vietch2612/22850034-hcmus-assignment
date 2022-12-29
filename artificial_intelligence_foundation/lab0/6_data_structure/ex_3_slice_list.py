# Exercise 3: Slice list into 3 equal chunks and reverse each chunk
# sample_list = [11, 45, 8, 23, 14, 12, 78, 45, 89]
# Chunk  1 [11, 45, 8]
# After reversing it  [8, 45, 11]
# Chunk  2 [23, 14, 12]
# After reversing it  [12, 14, 23]
# Chunk  3 [78, 45, 89]
# After reversing it  [89, 45, 78]

def slice_list(list):
    length = len(list)
    if length % 3 != 0:
        print('Please input the list with length is divisible by 3.')
        return
    size = len(list[0:int(length/3)])
    for i in range(0, 3):
        print(list[i*3:i*3 + size])


slice_list([11, 45, 8, 23, 14, 12, 78, 45, 89])
slice_list([11, 45, 8, 11, 33, 44, 23, 14, 12, 78, 45, 89])
slice_list([11, 45, 8, 11, 33, 44, 23, 14, 12, 78, 45, 89, 90])