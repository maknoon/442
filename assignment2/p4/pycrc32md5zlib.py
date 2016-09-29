import sys
#import random
import time
import zlib


'''
module for problem #4
uses zlib's crc32 and incrementing through 32bit hex string
tried to do it first like module in p3 (i.e. using random & PyCRC)
...but it took forever..

usage:
[int] = which point in the string incrementation you want to start at 
> python pycrc32md5zlib.py [int]

 ensure to:
 1) run at least two processes to cover both evens and odds
 2) run multiples of two processes starting in 3 billion intervals
 to cover more ground
'''


# helper to change an integer value to 32bit hexadecimal string
def hex_parse(inc):
	return '{:032x}'.format(inc)

# helper to use zlib tools for crc calculation
def zlib_crc(z_string):
	return format(zlib.crc32(z_string, 0) & 0xFFFFFFFF, '08x')


if __name__ == '__main__':

	start_time = time.time()
	inc_string = int(sys.argv[1])
	hit_found = False
	found_id = ''

	# these are the hard values to check against
	# found using pycrc
	student_id = 'fe1b02ce427cf3079febf3f3deb56ed0'
	student_id_crc = '906073bc'

	while(1):

		# randomly generate a string and find the crc32
		#crc = ''.join(random.choice('0123456789abcdef') for i in range(32))

		# evaluate CRC of hex string that was returned by hex_parse
		crc = hex_parse(inc_string)
		crc_val = zlib_crc(crc)

		# let's not waste resources; print a result every 800000th try
		if (inc_string % 800000 == 0) or ((inc_string - 1) % 800000 == 0):
			print "{0}, {1}".format(crc, crc_val)

		# check if we have a match :)
		if crc != student_id and crc_val == student_id_crc:
			hit_found = True
			found_id = crc
		# otherwise we keep going :(
		else:
			count += 2

		# results
		if hit_found:
			print "hit found!"
			print("--- took %s seconds ---" % (time.time() - start_time))
			break

	print "found a CRC hit between {0}, {1}".format(student_id, found_id)

