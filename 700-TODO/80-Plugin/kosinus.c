#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char **argv)
{
    void *handle = dlopen("/lib/libm.so.6", RTLD_LAZY);
    double (*cosine) (double) = dlsym(handle, "cos");
    printf("%f\n", (*cosine) (2.0));
    dlclose(handle);

    return EXIT_SUCCESS;
}
