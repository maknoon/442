import sys
import hashlib

'''
TO RUN SCRIPT
(1) Ensure that 56047129.program2.exe is in the same directory
(2) $ python patch4c.py
'''

# Use SHA-1 library function to hash new password
def newPw():
    password = raw_input("\nEnter a password: ")
    h = hashlib.sha1(password)
    patch(h.hexdigest())


# Patch the password by
# (1) seeking to the address of the old SHA-1 hash
# (2) rewriting old hash with hex of the new hash
def patch( newhash ):
    
    hexhash = newhash.decode("hex")
    startaddr = 0x0001E011 # found via IDA <3

    with file('56047129.program2.exe', 'r+b') as fh:
        print "patching {0} into {1}".format(newhash, hex(startaddr))
        fh.seek(startaddr)
        fh.write(hexhash)
    fh.close()
            
    sys.exit("\nSuccessfully patched 56047129.program2. Goodbye!")


if __name__ == '__main__':
    try:
        newPw()
    except KeyboardInterrupt:
        sys.exit("\nProgram not patched. Goodbye!")
        