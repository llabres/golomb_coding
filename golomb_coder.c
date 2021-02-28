#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "encode.h"

char *hex2bin[] = {
    "0000", "0001", "0010", "0011",
    "0100", "0101", "0110", "0111",
    "1000", "1001", "1010", "1011",
    "1100", "1101", "1110", "1111"
};

int encode(char *, char *);
int decode(char *, char *);

int main (int argc, char **argv)
{
    char input_path[1064], output_path[1064], mode[2], c[]="c", d[]="d";	

    if (argc!=4 || sscanf(argv[1], "%s", input_path) !=1 || sscanf(argv[2], "%s", output_path) !=1 || sscanf(argv[3], "%s", mode) !=1) { printf("./%s input_path output_path mode\n", argv[0]); exit(1); }

    if (!strcmp(mode,c)) encode(input_path, output_path);
    else if (!strcmp(mode,d)) decode(input_path, output_path);
    else {fprintf(stderr, "Incorrect mode entered, please use c or d\n"); exit(1);}

    return 0;
}

int encode(char *input_path, char *output_path){
    /*Reading the input file*/
    FILE *fp;
    long lSize;
    unsigned char *input;

    fp = fopen ( input_path , "rb" );
    if( !fp ) perror(input_path),exit(1);

    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );

    /* allocate memory for entire content */
    input = calloc( 1, lSize+1 );
    if( !input ) fclose(fp),fputs("memory alloc fails\n",stderr),exit(1);

    /* copy the file into the buffer */
    if( 1!=fread( input , lSize, 1 , fp) )
    fclose(fp),free(input),fputs("entire read fails\n",stderr),exit(1);

    fclose(fp);

    int inputsz = lSize;	

    srand (time(NULL));

    /*Golomb Encoding*/
    unsigned char *ge;
    unsigned long ge_size;
    unsigned int golomb_param;

    if (golomb_encode (input, inputsz, (void*)&ge, &ge_size, &golomb_param) ) {
	fprintf(stderr, "Golomb Encoding Failed");
	exit(1);
    }
    free(input);

    printf("%u\n", golomb_param);
    /*Save encoding to file*/
    FILE *f = fopen(output_path, "wb");
    fwrite(&golomb_param, sizeof(unsigned int), 1, f);
    fwrite(ge, sizeof(char), ge_size, f);
    fclose(f);
    
    return 0;
}

int decode(char *input_path, char *output_path){
    /*Reading the input file*/
    FILE *fp;
    long lSize;
    unsigned char *input;
    unsigned int golomb_param;

    fp = fopen ( input_path , "rb" );
    if( !fp ) perror(input_path),exit(1);

    fread(&golomb_param, 4, 1, fp);
    fseek( fp , -4, SEEK_END);
    lSize = ftell( fp );
    rewind( fp );
    fseek(fp, 4, SEEK_SET);

    /* allocate memory for entire content */
    input = calloc( 1, lSize+1 );
    if( !input ) fclose(fp),fputs("memory alloc fails\n",stderr),exit(1);

    /* copy the file into the buffer */
    if( 1!=fread( input , lSize, 1 , fp) )
    fclose(fp),free(input),fputs("entire read fails\n",stderr),exit(1);

    fclose(fp);

    int inputsz = lSize;	

    srand (time(NULL));

    /*Glomb Decoding*/
    unsigned int  *gd;
    unsigned long gd_size;
    if (golomb_decode (input, inputsz, golomb_param, (void**)&gd, &gd_size)) {
        fprintf(stderr, "Golomb Decoding Failed");
	exit(1);
    }
    free(input);

    /*Save encoding to file*/
    FILE *f = fopen(output_path, "wb");
    fwrite(gd, sizeof(char), gd_size, f);
    fclose(f);

    return 0;
}
