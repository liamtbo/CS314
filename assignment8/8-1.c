#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 2

// 16B direct-mapped cache with 2B blocks (i.e. 8 cache sets)

struct Set {
    unsigned char data[BLOCK_SIZE];
    unsigned int tag; // Assume tag is at most 32 bits
    unsigned char valid; // valid bit (0 or 1)
};

struct Cache {
    struct Set *sets;
    int numSets;
};

unsigned int getOffset(unsigned int address) {
    return address & 0x1; // 2-byte blocks, so 1 offset bit
}

unsigned int getSet(unsigned int address) {
    return (address >> 1) & 0x7; // 2-byte blocks; 8 sets so 3 set bits
}

unsigned int getTag(unsigned int address) {
    return address >> 4; // total of 4 bits for offset and set
}

struct Cache* mallocCache(int numSets) {
    // TODO - malloc a pointer to a struct Cache, malloc a pointer to an array
    // of struct Set instances (array length is numSets).  Also initialize
    // valid to 0 for each struct Set.  Return the struct Cache pointer.
    // allocate mem. for cache
    struct Cache *cache = (struct Cache*)malloc(sizeof(struct Cache));
    // allocaate mem for # of sets
    struct Set *arr_set = (struct Set*)malloc(sizeof(struct Set) * numSets);
    // loop over each set in the cache and initliaze v to 0
    for (int i = 0; i < numSets; i++) {
        // var to hold address of current set
        struct Set *curr_set = &arr_set[i];
        // set current set valid to 0
        curr_set->valid = 0;
    }
    // set cache numsets to numsets
    cache->numSets = numSets;
    // set cache sets to array of allocated sets
    cache->sets = arr_set;
    return cache;
}

void freeCache(struct Cache *cache) {
    free(cache->sets);
    free(cache);
}

void printSet(struct Set *set, int setIndex) {
    printf("set: %x - tag: %x - valid: %u - data:", setIndex, set->tag, set->valid);
    unsigned char *data = set->data;
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        printf(" %.2x", data[i]); // prints
    }
    printf("\n");
}

void printCache(struct Cache *cache) {
    // TODO - print all valid sets in the cache.
    // loop over every set in the cache
    for (int i = 0; i < cache->numSets; i++) {
        // take set i out of cache
        struct Set *curr_set = &(cache->sets[i]);
        // check if valid is 0 or 1
        if (curr_set->valid == 1) {
            // print the set
            printSet(curr_set, i);
        }
    }
}

void readValue(struct Cache *cache, unsigned int address) {
    // TODO - check the cache for a cached byte at the specified address.
    // If found, indicate a hit and print the byte.  If not found, indicate
    // a miss due to either an invalid line (cold miss) or a tag mismatch
    // (conflict miss).
    unsigned int o = getOffset(address); // returns bit 1
    unsigned int s = getSet(address); // returns bits 2 - 4
    unsigned int t = getTag(address); // returns bits 5 - 8

    printf("looking for set: %d - tag: %d\n", s, t);

    struct Set *set = &cache->sets[s]; // grab set s from address
    if (set->valid == 0 || set->tag != t) { // check if valid 0 or diff tag
        printf("no valid line found - miss!\n");
        return;
    }
    printf("found set: ");
    // print set
    printSet(set, s);
    // print targeted data
    printf("hit: %x\n", set->data[o]);
}

void writeValue(struct Cache *cache, unsigned int address, unsigned char *newData) {
    unsigned int s = getSet(address); // 8 byte address, returns bits 2 - 4
    unsigned int t = getTag(address); // returns bits 5 - 8

    // Need to evict the set's current block if the set has a block (set->valid)
    // and the set's block does not have the same tag as the new block (set->tag != t).
    // grabs set at addresses set index
    struct Set *set = &cache->sets[s]; 
    // checks if valid = 1 and if the tags are the same
    if (set->valid && (set->tag != t)) {
        // if v = 0 or tags not the same
        // grab the data from the set that needs to be evicted (reduntant)
        unsigned char *data = set->data;
        printf("evicting line - ");
        printSet(set, s); // prints the evicted set
    }
    // grab the data from mthe set that needs to be evicted
    unsigned char *data = set->data;
    // loop over block, replacing the evicted data with the new data
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        // printf("hex: %x\n", newData[i]);
        data[i] = newData[i]; // update
    }

    set->tag = t; // update cache block tag
    set->valid = 1; // there's something in there

    printf("wrote set: ");
    // print out set
    printSet(set, s);
}

unsigned int readUnsignedIntFromHex() {
    char buffer[10];
    char *p = NULL;
    unsigned int n;
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        n = strtoul(buffer, &p, 16);
        if (buffer != p) {
            break;
        }
        printf("Invalid input - try again: ");
    }
    return n;
}

int main() {  
    struct Cache *cache = mallocCache(8);

    char buffer[10];
    char c;
    do {
        printf("Enter 'r' for read, 'w' for write, 'p' to print, 'q' to quit: ");
        fgets(buffer, sizeof(buffer), stdin);

        c = buffer[0];
        if (c == 'r') {                     
             printf("Enter 32-bit unsigned hex address: ");
             unsigned int a = readUnsignedIntFromHex();
             readValue(cache, a);
        } else if (c == 'w') {
            printf("Enter 32-bit unsigned hex address: ");
            unsigned int a = readUnsignedIntFromHex();
            printf("Enter 32-bit unsigned hex value: ");
            unsigned int v = readUnsignedIntFromHex();
            // converts int to char so you can access bytes one at a time
            // v is now stored in mem in little endian (0xaabb -> 0xbb | oxaa)
            unsigned char *data = (unsigned char *)&v;
            writeValue(cache, a, data);
        } else if (c == 'p') {
            printCache(cache);
        }
    } while (c != 'q');

    freeCache(cache);
}