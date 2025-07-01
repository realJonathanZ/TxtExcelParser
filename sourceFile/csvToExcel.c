#include <xlsxwriter.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

    char line[1000]; // each line's butter storing up to 1000 chars
    int row = 0;     // starts with row 0 (which is row 1st in the sheet)

    // starting to: process the csv file line by line
    while (fgets(line, sizeof(line), file)) {
        // remove the '\n'
        line[strcspn(line, "\n")] = '\0'; // the index is set to newline char and then get replaced with null terminator

        printf("currently processing line(%d): %s\n", row, line);

        char* doge;  // suppose in the csv file, between each comma, there is a string. var named 'doge', can be NULL
        doge = strtok(line, ","); // find the next doge (or what they called token anyway)
        int col = 0;    // starts with column 0 (which is column A in the sheet)

        while (doge != NULL) {
            // at location (row, col) in the sheet, write (var:string) doge in
            worksheet_write_string(worksheet, row, col, doge, NULL);

            printf("have written this doge ('%s') to cell located at (%d, %d)\n", doge, row, col);

            // change to the doge after the next comma
            doge = strtok(NULL, ",");
            col = col + 1; // increment for the next loop iteration, on the next COL but SAME ROW
        }

        row = row + 1; // increment for the next loop iteration, on the NEXT ROW (inner loop examines all COLS in the next ROW)
    }

    printf("execution done: writing to sheet\n");

    fclose(file);
    workbook_close(workbook);
}

int main() {
    csvToExcel("./csvMiddleOutput/example.csv", "./output/example.xlsx");
    return 0;
}