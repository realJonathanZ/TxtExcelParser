// We assume the detection of the first data section in the input file is:
// to find a line of "UID: 001\n"

#include "parserToStruct.h" // This header contains dataStruct.h

DS* parseInputFile(const char* filename) {
    printf("the DS instance shall be returned\n");
    return NULL;

}

int main() {
    DS* data = parseInputFile("gym_20250629_180150.txt");
    
    return 0;
}
