#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef uint8_t u8;
typedef uint64_t u64;

u64 getFileSize(FILE* file) 
{
    fseek(file, 0, SEEK_END); // offset 0 ; whence SEEK_END -> points eof
    u64 const size = ftell(file);
    fseek(file, 0, SEEK_SET); // return pointer to beginning 

    return size;
}

int main(int argc, char **argv) 
{
    assert(argc == 4); 
    char* const filename = argv[1];
    int const NB_RAND_ACC = atoi(argv[2]);
    int const RAND_SEED = atoi(argv[3]);

    srand(RAND_SEED);

    FILE* const f = fopen(filename, "rb"); assert(f != NULL);
    u64 size = getFileSize(f);

    u64 acc = 0;
    clock_t const start = clock();
    for(size_t i=0; i<NB_RAND_ACC; i++) 
    {
        u64 pos = rand() % size;

        int const ir = fseek(f, pos, SEEK_SET);
        assert(ir == 0);
        u8 val;
        size_t const n = fread(&val, 1, 1, f);
        assert(n == 1);
        acc += val;
    }
    clock_t const duration = clock() - start;

    printf("%.3f %llu \n", (double)duration / CLOCKS_PER_SEC, acc);
    fclose(f);
}