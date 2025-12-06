def isInvalid(num):
    if len(num) % 2:
        return False
    return num[:len(num)//2] == num[len(num)//2:]

line = input()
ranges = line.split(",")
invalid_ids = 0
for r in ranges:
    bounds = r.split("-")
    start = int(bounds[0])
    end = int(bounds[1])
    for num in range(start, end + 1):
        if isInvalid(str(num)):
            invalid_ids += num

print(invalid_ids)