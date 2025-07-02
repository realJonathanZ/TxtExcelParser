/*
will try to implement the logic in this file:
input will be any (expected) un-NULL DS instance(defined inside dataStruct.h)
output will be a CSV file with the data from the DS instance.
output csv file will have format similar to example.csv
*/ 

#include "structToCSV.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int isObtained(char** keys, int arrayLength, const char* key) {
    for (int i = 0; i < arrayLength; i++) {
        if (strcmp(keys[i], key) == 0) {
            return 1; // True, key exists
        }
    }
    return 0; // False, cannot find any existence
}


char** getAllUniqKeys(DS* head, int* found_uniqkeys_quantity) {

    char** uniqKeys = malloc(50 * sizeof(char*)); // at last fill it with all unique keys and return
    *found_uniqkeys_quantity = 0; // Initialize the count of unique keys

    DS* currentSection = head; // copy the pointer pointing to first data section

    // traverse
    while (currentSection != NULL) {
        KV* currentKV = currentSection->fields; // pointing to current key-value pair

        while (currentKV != NULL) {
            // if key does not exist in the array [uniqKeys], add it, otherwise skip
            if (!isObtained(uniqKeys, *found_uniqkeys_quantity, currentKV->key)) {
                uniqKeys[*found_uniqkeys_quantity] = malloc(strlen(currentKV->key) + 1);  // allocate memory for the new key at specific index
                strcpy(uniqKeys[*found_uniqkeys_quantity], currentKV->key); 
                (*found_uniqkeys_quantity)++; // increment
            }
            currentKV = currentKV->next; // move to next key-value pair
        }
        currentSection = currentSection->next; // move to next data section
    }
    
    return uniqKeys; // meanwhile, the actual value of (*found_uniqkeys_quantity) is preserved in main() scope
}
