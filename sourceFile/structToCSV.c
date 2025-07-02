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



/*Is a key string already existing in an keys array?
* @param keys: array of strings to check element uniqueness
* @param arrayLength: number of strings in the array 'keys'
* @param key: the key to be checked whether it appears somewhere in the array
* @return 1 if the key exists, 0 otherwise
*/
int isObtained(char** keys, int arrayLength, const char* key) {
    for (int i = 0; i < arrayLength; i++) {
        if (strcmp(keys[i], key) == 0) {
            return 1; // True, key exists
        }
    }
    return 0; // False, cannot find any existence
}

/* collect all unique keys from all data sections
* @param head: pointer to the head of the linked list of data sections
* @param keys: pointer to an array of strings to store unique keys
* @return uniqueKeys: an array conatining all unique keys found in the data sections
*/
char** getAllUniqKeys(DS* head, int* found_uniqkeys_quantity) {
    // will use nested loop: for each section, need traverse all kv pairs
    // and whether to put key inside is determined by uniqueness (the function above)
    
}
