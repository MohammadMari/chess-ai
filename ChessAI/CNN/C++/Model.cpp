#include <stdio.h>
#include "./tensorflow/c/c_api.h"

int main()
{
   printf("Hello from tensorflow C Library version %s\n", TF_Version());
   return 0;
}