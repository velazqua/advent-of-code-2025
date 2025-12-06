def isInvalid(num):
    for l in range(1, len(num)//2 + 1):
        if len(num) % l != 0:
            continue
        num_test = num[0:l]
        all_equal = True
        #print("Num test: " + num_test)
        for i in range(0, len(num) - l + 1, l):
            substring = num[i:i+l]
            #print("Substring: " + substring)
            if substring != num_test:
                all_equal = False
                break
        if all_equal:
            return True
    return False

line = input()
ranges = line.split(",")
invalid_ids = 0
for r in ranges:
    bounds = r.split("-")
    start = int(bounds[0])
    end = int(bounds[1])
    for num in range(start, end + 1):
        #print(num)
        if isInvalid(str(num)):
            print(str(num) + " is invalid")
            invalid_ids += num

print("Answer is " + str(invalid_ids))