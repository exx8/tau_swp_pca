import subprocess
import time
import sys

tester = './tester'
cov = './cov'
eigen = './eigen'

subprocess.call(['make', 'cov'])
subprocess.call(['make', 'eigen'])
subprocess.call([tester, 'm_input.arr', sys.argv[1], sys.argv[2]])
subprocess.call([cov, 'm_input.arr', 'm_output.arr'])
subprocess.call([eigen, 'm_output.arr', 'm_vector.arr'])
subprocess.call([tester, 'm_input.arr', 'm_output.arr', 'm_vector.arr'])
