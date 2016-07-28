from subprocess import Popen, PIPE
cmd = 'echo Hello world'
p = Popen(cmd, shell=True, stdout=PIPE, stderr=PIPE)
stdout_data, stderr_data = p.communicate()
print stdout_data