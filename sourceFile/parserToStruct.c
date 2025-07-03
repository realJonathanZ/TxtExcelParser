// We assume the detection of the first data section in the input file is:
// to find a line of "UID: 001\n"

#include "parserToStruct.h" // This header contains dataStruct.h

DS* parseInputFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }

    DS* head = NULL;
    DS* currentSection = NULL;
    char line[500];
    int foundFirstUID = 0; // initially false, indicating the fact whether the first UID line is found

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // replace newline with null terminator

        // if not found, compare current line, otherwise just pass it.
        if (!foundFirstUID) {
            if (strncmp(line, "UID: 001", 8) == 0) { // if the first 8 chars match the line without newline..
                foundFirstUID = 1; // set to true, indicating the first UID line is found
                currentSection = createDataSection();
                addKeyValueLast(currentSection, "UID", "001"); // add the UID key-value pair
            }
            continue; // jump back to the beginning of the next loop iteration
        }

        // at this point we must have found the first UID line,and
        // the first uid is already added as key-value pair inside the currentSection
        
        //if this current line is empty..
        if (strlen(line) == 0) {
            if (currentSection != NULL) { // and if we actually got things in current ds instance
                addDataSectionLast(&head, currentSection); // add the ds instance at the end of the chain
                currentSection = NULL; // reset to null for next iteration
            }
            continue; // have just added the current section to the last of ds chain, so continue to the next iteration.
        }

        // if we are here, it means we have a non-empty line, and we are inside a data section
        // check if line contains UID 
        if (strncmp(line, "UID:", 4) == 0) {
            // if have a previous section which is not none,
            // since now it is new section, add it to the ds chain.
            if (currentSection != NULL) {
                addDataSectionLast(&head, currentSection);
                // there is a reason why the same section won't be added twice.
            }

            // create new ds section
            currentSection = createDataSection();
            
            // parse this UID line
            char* colon = strchr(line, ':'); // colon points to the ':'
            if (colon != NULL) {
                char* value = colon + 2; // the space after the colon, the first digit after the space
                addKeyValueLast(currentSection, "UID", value);
            }
            continue;  // jump to next iteration on next line
        }

        // parse key-value pair
        // for now, the current line should be in format:
        // <key>: <value>
        // notice there is space after the colon
        char* colon = strchr(line, ':'); // var colon pointing to ':'
        if (colon != NULL && currentSection != NULL) {
            *colon = '\0';  // the terminate of the key
            char* key = line;
            char* value = colon + 2;  // skip colon and one space
            addKeyValueLast(currentSection, key, value);
        } else {
        // error
        if (colon == NULL) {
            printf("Error: no colon found: \n Line:'%s'\n(parserToStruct.c)", line);
        } else if (currentSection == NULL) {
            printf("Error: no current section to add data to. \n Line:'%s'\n(parserToStruct.c)", line);
        }
    
        continue; // continue on next loop iteration
        }

    } // this is the closing brace of the while loop


    // for the last section, although all pairs are added to (var) currentSection, 
    // it is isolated from head(ds)
    if (currentSection != NULL) {
        addDataSectionLast(&head, currentSection); // add the last data section of the file
    }

    return head;
} // this is the closing brace of the parseInputFile function

// int main() {
//     DS* data = parseInputFile("./input/gym_20250629_180150.txt");
//     if (data == NULL) {
//         printf("Failed to parse input file\n");
//         return 1;
//     }
    
//     printf("Successfully parsed input file!\n");
//     printDataSections(data);
//     freeDataSections(data);
//     return 0;


// }
