#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc != 3 || argv[1] == NULL ||argv[2] == NULL){
        printf("Usage: ./main <source> <destination> \n");
        return 1;
    }
    //read the input file from the user
    FILE *input = fopen(argv[1], "r");
    //check if the file is empty
    if (input == NULL)
    {
        printf("Error: File is empty or does not exist\n");
        return 1;
    }
    char c;
    FILE *output = fopen(argv[2], "w");
    while ((c = fgetc(input)) != EOF)
    {
        fprintf(output, "%c", c);
    }
    fclose(output);
    fclose(input);
    printf("File copied successfully\n");
    return 0;
   
}