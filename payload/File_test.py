import time
testfile = open("file_test.txt", "w")

# Get start time
t0 = time.time()
testfile.write("Start: {}".format(time.asctime(time.gmtime(t0))))
