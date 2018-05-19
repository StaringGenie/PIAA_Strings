#include <stdio.h>
#include <stdlib.h>

int main(){
    system("sudo chmod +x ../src/clean.sh");
    system("../src/clean.sh");
    return 0;
}