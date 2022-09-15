#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
int main(int argc, char *argv[])
{
    typedef uint8_t BYTE ;
    BYTE buffer[512];


    int jpeg_count = 0;
    if(argc != 2)
    {
        printf("usage ./recover name of the raw file to recover\n");
        return 1;
    }

    // open card.raw and read from it
    FILE *input = fopen(argv[1], "r");
    FILE *img = NULL;
    if(input == NULL)
    {
        printf("The file could not be opened.\n");
        return 2;
    }
    
        char *filname = malloc(200);
        while(fread(buffer, sizeof(char), 512, input))
        {
            if((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
            {
                sprintf(filname, "%03i.jpg", jpeg_count);
                img = fopen(filname, "w");
                jpeg_count++;
            }
            if( img != NULL)
            {
                fwrite(buffer, sizeof(char) ,512 , img);
            }
        }
    fclose(input);
    fclose(img);
    free(filname);
    return 0;

}
