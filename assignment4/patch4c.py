import sys

#with file('task4_wc/56047129.program2a', 'rb') as fh:
#    patch1 = fh.read()

with file('task4_wc/56047129.program2', 'r+b') as fh:
    #fh.write(patch1)
    fh.seek(0x00004859)
    fh.write(90)
    fh.seek(0x0000485A)
    fh.write(90)
