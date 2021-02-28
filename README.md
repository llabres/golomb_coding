# Golomb Coding
Golomb coding implemented in C

## Contents
Implementation of Golomb coding to encode and decode files using Golomb coding based on 'Compression and Coding Algorithms' by Alistair Moffat & Andrew Turping, Kluwer Academic Publishers, 2002.

The code can be found on the following files:
- `encode.h`
- `encode.c`
- `golomb_coder.c`

On `encode.h` and `encode.c` the Golomb encoder and decoder functions are defined and implemented, as well as a Run-Length encoding and decoding functions. This files have been slightly altered from the original ones created by Anirudh Ramachandran <anirudhvr@gmail.com> which can be found at https://github.com/anirudhvr/golomb-coding and are used here under the GPLv2 license.

The third file `golomb_coder.c` contains the main function which takes inputs from the user and reads the file to be encoded/decoded and feeds it to the functions on `encode.c` and then saves the output to a file.

A MakeFile is provided to compile the code.

## Usage
- Download/Clone this repository and run `make`.
- To encode run: `./golomb_coding input_path output_path c`
- To decode run: `./golomb_coding input_path output_path d`



