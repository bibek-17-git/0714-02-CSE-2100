/*
 * backup_utility.c
 * A simple backup utility that demonstrates file copying.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void backup_file(const char *source, const char *destination) {
    FILE *srcFile, *destFile;
    char buffer[1024];
    size_t bytesRead;

    srcFile = fopen(source, "rb");
    if (srcFile == NULL) {
        perror("Failed to open source file");
        exit(EXIT_FAILURE);
    }

    destFile = fopen(destination, "wb");
    if (destFile == NULL) {
        perror("Failed to open destination file");
        fclose(srcFile);
        exit(EXIT_FAILURE);
    }

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), srcFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    fclose(srcFile);
    fclose(destFile);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    backup_file(argv[1], argv[2]);
    printf("Backup successful from %s to %s\n", argv[1], argv[2]);
    return EXIT_SUCCESS;
}