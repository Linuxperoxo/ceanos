#pragma once

#define MAX_FILES 100
#define MAX_FILE_SIZE 1024
#define MAX_FILE_NAME 32

#include <stdint.h>
#include <util.h>

typedef struct {
        char name[MAX_FILE_NAME];
        char data[MAX_FILE_SIZE];
        unsigned int size;
} File;

typedef struct {
        File files[MAX_FILES];
        int file_count;
} VFS;


void init_vfs(VFS *vfs);
uint32_t create_file(VFS *vfs, const char *filename, const char *data);
const char* read_file(VFS* vfs, const char *filename);
void delete_file(VFS *vfs, const char *filename);
