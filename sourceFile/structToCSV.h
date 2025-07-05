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

/* Helper function: adds a comma to the current string
 * @param lineStr: pointer to the string to append comma to
 */
void addComma(char* lineStr);

/* Helper function: adds a newline to the current string
 * @param lineStr: pointer to the string to append newline to
 */
void addNewline(char* lineStr);

/* Generate CSV file from DataSections
 * @param head: pointer to the head of the linked list of data sections
 * @param csvFilename: output CSV filename
 */
void generateCSV(DS* head, const char* csvFilename);

/*Suppose the string array is dynam-allocated, so are all strings in it..
* this func will free them.
* @param: uniqKeys - the array of unique keys
* @param: found_uniqkeys_quantity - the number of unique keys in the array
* @return: void
*/ 
void freeUniqKeys(char** uniqKeys, int found_uniqkeys_quantity);

int hasDogeWrapper(const char* str);

char* removeDogeWrapper(const char* str);

#endif // STRUCTTOCSV_H