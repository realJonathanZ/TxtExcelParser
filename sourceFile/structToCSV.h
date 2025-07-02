#ifndef STRUCTTOCSV_H
#define STRUCTTOCSV_H

#include "dataStruct.h"

/*Is a key string already existing in an keys array?
 * @param keys: array of strings to check element uniqueness
 * @param arrayLength: number of strings in the array 'keys'
 * @param key: the key to be checked whether it appears somewhere in the array
 * @return 1 if the key exists, 0 otherwise
 */
int isObtained(char** keys, int arrayLength, const char* key);

/* collect all unique keys from all data sections
 * @param head: pointer to the head of the linked list of data sections
 * @param found_uniqkeys_quantity: pointer to an integer that will hold the number of unique keys found even in main() scope
 * @return uniqKeys: an array containing all unique keys found in the data sections
 */
char** getAllUniqKeys(DS* head, int* found_uniqkeys_quantity);



#endif // STRUCTTOCSV_H