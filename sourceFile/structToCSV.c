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


/* to append a comma char at the end of the para string*/
void addComma(char* lineStr) {
    strcat(lineStr, ",");
}

/* to append a newline char at the end of the para string*/
void addNewline(char* lineStr) {
    strcat(lineStr, "\n");
}

void generateCSV(DS* head, const char* csvFilename) {
    if (head == NULL) {
        printf("Error: the head data section is NULL.\n");
        printf("Error place in generateCSV()\n");
        return;
    }

    printf("******************Generation started***************\n");

    // Get all keys
    int found_uniqkeys_quantity = 0;
    char** uniqKeys = getAllUniqKeys(head, &found_uniqkeys_quantity);

    // unique keys are found, below is for console output to show every key
    // btw test about helpwe funcs
    char consoleStr[1000] = ""; // buffer to store all key, initialed to empty str
    strcat(consoleStr, "Found unique keys: ");
    for (int i = 0; i < found_uniqkeys_quantity; i++) {
        strcat(consoleStr, uniqKeys[i]);
        if (i < found_uniqkeys_quantity - 1) {
            addComma(consoleStr); // add comma
            strcat(consoleStr, " "); // for dispaly purpose
        }
    }
    printf("%s\n", consoleStr); // display to console

    // Create CSV file, name obtained from the parameter
    FILE* csvFile = fopen(csvFilename, "w");
    if (csvFile == NULL) {
        printf("Error: Could not open csv file %s for writing.\n", csvFilename);
        printf("Error happened in generateCSV()\n");
        return;
    }

    printf("CSV file created, opened and waiting to write: %s\n", csvFilename);

    // process and write head row into file
    char hline[3000] = ""; // buffer for the header line
    for (int i = 0; i < found_uniqkeys_quantity; i++) {
        strcat(hline, uniqKeys[i]); // append key to the header line
        if (i < found_uniqkeys_quantity - 1) {
            addComma(hline); // add comma if not the last key
        }
    }
    addNewline(hline); 
    fprintf(csvFile, "%s", hline); // write header line to the CSV file
    printf("writtened header line for csv: %s\n", hline);

    // process and write remaining lines into file
    DS* cs = head; // (var:DS*) cs pointing to first data section (abbreviation for current section)
    int rowIndex = 0; 

    printf("writing data rows: %d\n", rowIndex);
    while (cs != NULL) {
        char strOnBuild[2000] = ""; // str builder for THIS line for THIS DS

        for (int i = 0; i < found_uniqkeys_quantity; i++) {
            // get the value
            // expected return value: string, empty string or NULL if not found
            char* value = getValue(cs, uniqKeys[i]);

            // if can find key-value pair, optained value in THIS section
            if (value != NULL) {
                // value might contain comma
                // sttempt approach: warp around with double quotes
                if (strchr(value, ',') != NULL) {
                    char wrappedValue[500]; // str buffer for quoted value
                    sprintf(wrappedValue, "\"%s\"", value); // wrap with double quotes
                    strcat(strOnBuild, wrappedValue); // append last to the data line
                } else {
                    strcat(strOnBuild, value);
                }
            }
            // if cannot find a value with given key in THIS section..
            // DO NOTHING, empty string is appended before next comma or newline

            // Add comma.. but not add at last before '\n'
            if (i < found_uniqkeys_quantity -1) {
                addComma(strOnBuild);
            }
        } // (end) of (for loop) the string is almost built, but..

        // newline shall be added
        addNewline(strOnBuild);

        // insert the built string as line
        fprintf(csvFile, "%s", strOnBuild);
        
        // debug output
        char debugLine[2000] = "";
        sprintf(debugLine, "[DEBUGGING[generateCSV()]] output row %d: %s", rowIndex, strOnBuild);
        printf("%s\n", debugLine);

        cs = cs->next; //(var:DS*) cs pointing to next data section
        rowIndex++; // increment row index

    } // (end) of (while loop) expecting all builted strings for every data section/line is injected to csv

    fclose(csvFile);
    printf("CSV file created and closed: %s\n", csvFilename);

    // completed, tell to console
    char congratulationMessage[200] = "";
    sprintf(congratulationMessage, "Total rows written: %d (including header)", rowIndex + 1);
    printf("%s\n", congratulationMessage);

    // free them all (the dynam allocated for every string)
    for (int i = 0; i < found_uniqkeys_quantity; i++) {
        free(uniqKeys[i]);
    }
    // free itself (the dynam allocated memory for the array)
    free(uniqKeys);
    printf("free() -ed all dynam memory but might be missing some -------\n");
    printf("***** Generation Done For csv File [%s] *****\n", csvFilename);
}

/*Suppose the string array is dynam-allocated, so are all strings in it..
* this func will free them.
* @param: uniqKeys - the array of unique keys
* @param: found_uniqkeys_quantity - the number of unique keys in the array
* @return: void
*/ 
void freeUniqKeys(char** uniqKeys, int found_uniqkeys_quantity) {
    for (int i = 0; i < found_uniqkeys_quantity; i++) {
        free(uniqKeys[i]);
    }
    free(uniqKeys);
}