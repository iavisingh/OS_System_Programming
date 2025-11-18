Steps to perform and questions to ask yourself, analysis and self study !!!

1. Go through each .c file and check their systemcall by running their executable using strace ./<executable> for eg strace ./write  
2. Differentiate between user application, buffered glibc , glibc systemcall wrapper and actual system calls.
3. what are systemcalls?
4. Why glibc functions are buffered?
5. run system.c with strace ./system and check which system_calls are called inside it.
6. why do we use fopen instead of directly calling open?? If fopen calls open() under it then why we use fopen() fwrite() fread() instread of open() read() write()?
7. read "man strace" and try using strace with 
	strace -e trace=file ./program
	strace -e trace=memory ./program
	strace -e trace=process ./program
8. syscalls to read and analyse = open,read,write,mmap,brk,sbrk,execv,
9. Analyse which system calls are called in malloc.c through strace.
10. What is need for kernel and user space distinction??
11. Why do we need to have have kernel and have to go through it for any hardware, peripheral, memory, etc operations??
12. Why is there is need for buffered io??
13. What is the drawback of large amount of systemcalls if we dont have buffered io layer??
14. How a process differs from threads? Difference in their address space?? What is shared or not shared in threads?
15. Create a child process from parent. and create 2 threads from parent and child. use wait() and pthread_join() so parent() and thread creater waits for child and thread exit.
16. Create a parent and child process. Now use unnamed pipe to communicate 	from child to parent.
17. Create a parent and child process. now use named pipe to communicate from parent to child.
18. Create 2 threads and use unnamed pipe to communicate from thread1 to thread2. 
19. Use Shared memory, message queue and dont delete in end of program.
now check your create shared memory using "ipcs -m" if it exists there.
also check your message queue using "ipcs -q".
20. Create 2 threads and increment counter in one and decrement in another and use mutex and semaphore to signal and concurrency.
21. differnce between mutex and sempahore?? can mutex be locked by one and unlocked by another thread?? can seamphore be acquired by one and released by another thread??
22. Create 2 programs simple TCP/IP socket server and client chat programs. 
MAN PAGES==>>
	man 2 <function>  => systemcall apis for system programming. unistd.h layer, reaches to kernel space.
	man 3 <function> => Glibc apis/functions which can buffered over the actual systemcalls which then reaches kernel space.




