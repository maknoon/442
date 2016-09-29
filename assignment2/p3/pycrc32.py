import random
import time
from PyCRC.CRC32 import CRC32


'''
module for problem #3
uses PyCRC and random string generator
(16bit hexadecimal)

before running this script, install PyCRC 
$ pip install PyCRC 
'''

if __name__ == '__main__':

	start_time = time.time()
	crc_dict = {}
	crc_hit = {}
	hit_found = False

	while(1):

		# randomly generate a string and find the crc32
		crc = ''.join(random.choice('0123456789abcdef') for i in range(16))
		crc_val = CRC32().calculate(crc)
		print "crc32 of {0} is {1}".format(crc, crc_val)

		# check if this crc exists in the table
		# check if this crc_val exists in the table
		if crc not in crc_dict.keys() and crc_val in crc_dict.values():

			hit_found = True
			# record the matching crcs in a separate dict
			for key in crc_dict:
				if crc_dict[key] == crc_val:
					crc_hit[key] = crc

		else:
			crc_dict[crc] = crc_val

		if hit_found:
			print "hit found!"
			print("--- took %s seconds ---" % (time.time() - start_time))
			break

	for key in crc_hit:
		print "found a hit for {0}, {1}".format(key, crc_hit[key])

