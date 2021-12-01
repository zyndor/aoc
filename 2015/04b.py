#!/bin/python

import hashlib;

def main():
	n = 346386
	md5 = ""
	while not md5.startswith("000000"):
		n += 1
		if md5.startswith("00"):
			print("{}: {}".format(n, md5))

		md5 = hashlib.md5("iwrupvqb" + str(n)).hexdigest()

	print("{}: {}".format(n, md5))

main()

