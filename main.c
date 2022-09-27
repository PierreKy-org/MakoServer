#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc != 3 || argv[1] == NULL ||argv[2] == NULL){
        printf("Usage: ./main <source> <destination> \n");
        return 1;
    }
    //read the input file from the user
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    //check if the file is empty
    if (input == NULL)
    {
        printf("Error: File is empty or does not exist\n");
        return 1;
    }
    
    int c;
    while ((c = fgetc(input)) != EOF)
    {
        fputc(c,output);
    }
    fclose(output);
    fclose(input);
    printf("File copied successfully\n");
    return 0;
   
}


