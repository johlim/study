from multiprocessing import Process, Lock


import os

def f(lock, x):
	lock.acquire()
	print("{0} - iD {1} p ID {2}".format(x, os.getpid(), os.getppid()))
	lock.release()

def main():
	lock = Lock()
	for i in range(3):
		p = Process(target=f, args=(lock,i))
		p.start()
	p.join()

if __name__ == "__main__":
	main()