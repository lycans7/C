http://samanbarghi.com/blog/2014/09/05/how-to-wrap-a-system-call-libc-function-in-linux/


Using LD_PRELOAD
LD_PRELOAD allows a shared library to be loaded before any other libraries.
So all I need to do is to write a shared library that overrides write and puts functions.
If we wrap these functions, we need a way to call the real functions to perform the system call.
dlsym just do that for us [man 3 dlsym]: > The function dlsym() takes a “handle” of a dynamic library
returned by dlopen() and the null-terminated symbol name, returning the address where that symbol is
loaded into memory. If the symbol is not found, in the specified library or any of the libraries that
were automatically loaded by dlopen() when that library was loaded, dlsym() returns NULL…

So inside the wrapper function we can use dlsym to get the address of the related symbol in memory
and call the glibc function. Another approach can be calling the syscall directly, both approaches
will work. Here is the code:

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

/* Function pointers to hold the value of the glibc functions */
static ssize_t (*real_write)(int fd, const void *buf, size_t count) = NULL;
static int (*real_puts)(const char* str) = NULL;

/* wrapping write function call */
ssize_t write(int fd, const void *buf, size_t count) {

	/* printing out the number of characters */
	printf("write:chars#:%lu\n", count);
	/* reslove the real write function from glibc
	 * and pass the arguments.
	 */
	real_write = dlsym(RTLD_NEXT, "write");
	real_write(fd, buf, count);

}

int puts(const char* str) {

	/* printing out the number of characters */
	printf("puts:chars#:%lu\n", strlen(str));
	/* resolve the real puts function from glibc
	 * and pass the arguments.
	 */
	real_puts = dlsym(RTLD_NEXT, "puts");
	real_puts(str);
}
We first declare pointers to hold the value of the glibc functions, we will use these later
to get the pointer from dlsym. Then we simply implement the glibc functions that we want to wrap,
add our code and finally call the real function to perform the intended task.

Compiling the shared library
We compile the shared library as follows:

gcc -fPIC -shared -o bin/libpreload.so src/wrap-preload.c -ldl
We need to make sure we are generating a position-independent code(PIC) by passing
-fPIC that is shared -shared. We also need to link our library with Dynamically Loaded (DL)
libraries -ldl, since we are using dlsym in our code.

To run our test code and wrap glibc functions, we simply set LD_PRELOAD enviornment variable to the
generated shared object file:

$ LD_PRELOAD=/home/saman/Programming/wrap-syscall/bin/libpreload.so ./bin/test

write:chars
#:15
Hello, Kernel!
puts:chars
#:13
Hello, World!

LD_PRELOAD loads the libpreload.so library before the execution of our code, and thus calling write
and puts will call our wrapper functions inside the library.

Using ld --wrap=symbol
Another way of wrapping functions is by using linker at the link time. GNU linker provides an option to
		wrap a function for a symbol [man 1 ld]:

Use a wrapper function for symbol. Any undefined reference to symbol will be resolved to “wrap_symbol”.
Any undefined reference to “real_symbol” will be resolved to symbol.

This can be used to provide a wrapper for a system function. The wrapper function should be
called “wrap_symbol”. If it wishes to call the system function, it should call “real_symbol”.

Here is a trivial example:

void *
__wrap_malloc (size_t c)
{
	printf ("malloc called with %zu\n", c);
	return __real_malloc (c);
}

If you link other code with this file using –wrap malloc, then all calls to “malloc” will call the function
“wrap_malloc” instead. The call to “real_malloc” in “__wrap_malloc” will call the real “malloc” function.

You may wish to provide a “real_malloc” function as well, so that links without the –wrap option will succeed.
If you do this, you should not put the definition of “real_malloc” in the
same file as “__wrap_malloc”; if you do, the assembler may resolve the call before the linker has
a chance to wrap it to “malloc”.

Based on the description, we need to implement two function __real_symbol and __wrap_symbol
(in our case __real_write and __wrap_write), and link the application with our code. Here is the code:

#include <stdio.h>
#include <string.h>

/* create pointers for real glibc functions */
ssize_t __real_write(int fd, const void *buf, size_t count);
int __real_puts(const char* str);

/* wrapping write function */

ssize_t __wrap_write(int fd, const void *buf, size_t count) {
	/* printing out the number of characters */
	printf("write:chars#:%lu\n", count);

	/* call the real glibc function and return the result */
	ssize_t result = __real_write(fd, buf, count);
	return result;
}

/* wrapping puts function */
int __wrap_puts(const char* str) {
	/* printing out the number of characters */
	printf("puts:chars#:%lu\n", strlen(str));

	/* call the real glibc function and return the result */
	int result = __real_puts(str);
	return result;
}

The code is very straight forward, but now lets try to compile the code and link it with our test application.

gcc -c src/wrap-link.c -o bin/wrap-link.o
gcc -c src/test.c -o bin/test-link.o
gcc -Wl,-wrap,write -Wl,-wrap=write -Wl,-wrap=puts bin/test-link.o bin/wrap-link.o -o bin/test-link-bin
I used gcc to pass the option to the linker with -Wl, which is equal to calling ld with --wrap option.
Now if I run the code I get:

$ ./bin/test-link-bin
write:chars
#:15
Hello, Kernel!
puts:chars
#:13
Hello, World!
Conclusion
In order to wrap system calls in Linux, one have to wrap related glibc function calls.
You have to be careful about the type of system calls you are tryting to override, since various
functions might call different functions from glibc, e.g. printf calls puts from glibc which calls
write at the end.

There are two ways to do this: 1-Using LD_PRELOAD environment variable, 2-using ld --wrap.
I personally prefer the first approach since if the number of wrapper functions increases
I do not have to specify them one by one, as in the second case.

You can find the source code and the related Makefile in the following github
repository: https: //github.com/samanbarghi/wrap-syscall.
