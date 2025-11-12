#include <stdio.h>

int main() {
    FILE *fp = fopen("file.txt", "w");
    fprintf(fp, "Embedded Systems\n");
    fclose(fp);
    return 0;
}
