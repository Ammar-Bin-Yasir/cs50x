// Modifies the volume of an audio file
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t byte;
typedef int16_t byte2;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // Array to store the header form input file
    byte header[HEADER_SIZE];
    // Read the header form input file
    fread(header, sizeof(header), 1, input);

    // Write the header data form the array to output file
    fwrite(header, sizeof(header), 1, output);

    // TODO: Read samples from input file and write updated data to output file
    // Array to store the samples from input file
    byte2 buffer;

    while (fread(&buffer, sizeof(byte2), 1, input))
    {

        // Update volume of sample
        buffer *= factor;
        // Write the updated sample to the output file
        fwrite(&buffer, sizeof(byte2), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
