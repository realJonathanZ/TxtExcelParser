#ifndef CSVTOXLSX_H
#define CSVTOXLSX_H

/*
* Convert a CSV file to Excel (.xlsx) format
* using the libxlsxwriter library.
* tested with input file "./csvMiddleOutput/example.csv"
*/
void csvToExcel(const char* csvFile, const char* excelFile);

#endif // CSVTOXLSX_H