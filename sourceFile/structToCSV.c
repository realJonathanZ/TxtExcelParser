/*
will try to implement the logic in this file:
input will be any (expected) un-NULL DS instance(defined inside dataStruct.h)
output will be a CSV file with the data from the DS instance.
output csv file will have format similar to example.csv

I must find a way to gather all unique keys, they will
soon become the header of the CSV file, and eventually become the first row
in the style sheet.

To do so, will need functionality to check if key is unique.

If want to generate csv from datasection, will need:
get all unique keys to be filled in first row, then,
for the remaining rows, will iterate all kv pairs in every ds for values,
therefore still need getValue() which shall stay in dataStruct.h
*/ 


/*Is a key string already existing in an array?
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


