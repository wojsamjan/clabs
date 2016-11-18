#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char **argv)
{
    void *handle;
    double (*cosine) (double);
    char *error;

    handle = dlopen("/lib/libm.so", RTLD_LAZY);
    if (!handle) {
	fputs(dlerror(), stderr);
	exit(1);
    }

    cosine = dlsym(handle, "cos");
    if ((error = dlerror()) != NULL) {
	fputs(error, stderr);
	fputs("\n", stderr);
	exit(1);
    }

    printf("%f\n", (*cosine) (2.0));
    dlclose(handle);

    return EXIT_SUCCESS;
}
