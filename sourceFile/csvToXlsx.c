#include <xlsxwriter.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structToCSV.h"

/* input a (var:char*) line, returning an array (var:char**) dogeArray 
* consists of different (var:char*) doges
* how many doges on a line to process(grab down to array)? -> (int) maxDogeQuantity
*/
int parseCSVLineToDogeArray(char* line, char** dogeArray, int maxDogeQuantity) {

    int dogeArrayMovingIndex = 0;
    int i = 0;
    int start = 0; // the starting of doge wrapper or doge content
    int lineLength = strlen(line);
    int bool_is_inDogeWrapper = 0; // flag indicating in dogewrapper or not

    // when i can be = to lineLength, it's after (origin-lineStr)-newline
    while (i <= lineLength && dogeArrayMovingIndex < maxDogeQuantity) {
        char c = line[i]; //position cursor

        // determine flag bool_is_inDogeWrapper
        // if position cursor at the start of a doge wrapper. (#)
        if (i <= lineLength - 7 && strncmp(&line[i], "#DOGES@", 7) == 0) {
            bool_is_inDogeWrapper = 1; // set flag to true
            start = i + 7; // move start to the end of doge wrapper head
            i += 7; // skip the doge wrapper head
        } else if (bool_is_inDogeWrapper && i <= lineLength - 7 && strncmp(&line[i], "@DOGEE#", 7) == 0) {
            // if position cursor at the end of a doge wrapper. (@)
            bool_is_inDogeWrapper = 0; // set flag to false
            int end = i; // find the end of doge wrapper
            int length = end - start; // calculate length of the doge
            // #DOGES@content@DOGEE#
            // (var) start locates to c ; (var) end locates to @
            // the length calculated is 7 = length("content")

            char* doge = malloc(length + 1);
            strncpy(doge, &line[start], length); // copy the doge content(within calculated length)
            doge[length] = '\0'; // null-terminate the string
            dogeArray[dogeArrayMovingIndex] = doge; // add to array
            dogeArrayMovingIndex++; // for the next doge.. in the next iteration
            i += 8; // skip the doge wrapper tail
            // if +7, will be positioned at the comma.. Thus plus 8
            start = i; // move start to index of first char of next doge
        } else if (c == ',' && !bool_is_inDogeWrapper) {
            // if position cursor at a comma and not in a doge wrapper.
            line[i] = '\0'; // replace comma with null terminator
            char* doge = malloc(strlen(&line[start]) + 1);
            strcpy(doge, &line[start]); // copy the doge content
            dogeArray[dogeArrayMovingIndex] = doge; // add to array
            dogeArrayMovingIndex++; // for the next doge.. in the next iteration
            start = i + 1; // move start to index of first char of next doge
        }

        // if position cursor at a '\0'
        if (c == '\0') {
            // Process remaining content as the last field
            if (start < i && !bool_is_inDogeWrapper) {
            char* doge = malloc(strlen(&line[start]) + 1);
            strcpy(doge, &line[start]); // Copies "nice"
            dogeArray[dogeArrayMovingIndex] = doge;
            dogeArrayMovingIndex++;
            }
            break; // Normal termination
        }

        i++; // position cursor moves to the next char on this line

    } // (end) of (while)
    return dogeArrayMovingIndex; // moving index eventually = element counts in DogeArray
}


void csvToExcel(const char* csvFile, const char* excelFile) {
    lxw_workbook* workbook = workbook_new(excelFile);
    lxw_worksheet* worksheet = workbook_add_worksheet(workbook, NULL);
    
    FILE* file = fopen(csvFile, "r");
    if (!file) {
        printf("Error opening CSV file: %s\n", csvFile);
        workbook_close(workbook);
        return;
    }
    printf("execution happening in csvToExcel function body before trying to write to sheet\n");

    char line[1500]; // each line's butter storing up to 1500 chars
    int row = 0;     // starts with row 0 (which is row 1st in the sheet)

    // starting to: process the csv file line by line
    while (fgets(line, sizeof(line), file)) {
        // remove the '\n'
        line[strcspn(line, "\n")] = '\0'; // the index is set to newline char and then get replaced with null terminator

        printf("currently processing line(%d): %s\n", row, line);

        char* dogeArray[30]; // consists unwrapped (var:char*) doges.
        int dogeCount = parseCSVLineToDogeArray(line, dogeArray, 30); // parse the line to get doges
        // doges are stored in dogeArray

        // write doges to the sheet
        for (int col = 0; col < dogeCount; col++) {
            worksheet_write_string(worksheet, row, col, dogeArray[col], NULL);

            printf("have written this doge ('%s') to cell located at (%d, %d)\n", dogeArray[col], row, col);
            free(dogeArray[col]); // pre-allocated in parseCSVLineToDogeArray()
        }


        row = row + 1; // increment for the next loop iteration, on the NEXT ROW (inner loop examines all COLS in the next ROW)
    }

    printf("execution done: writing to sheet\n");

    fclose(file);
    workbook_close(workbook);
}

// int main() {
//     csvToExcel("./csvMiddleOutput/example.csv", "./output/example.xlsx");
//     return 0;
// }