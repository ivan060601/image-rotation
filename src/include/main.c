#include <stdbool.h>
#include <stdio.h>

#include "bmp.h"
#include "util.h"
#include "errors.h"


void usage() {
    fprintf(stderr, "Usage: ./print_header BMP_FILE_NAME\n"); 
}

int main( int argc, char** argv ) {
    if (argc != 2) usage();
    if (argc < 2) err(describe_ru[NOT_ENOUGHT_ARGS]);
    if (argc > 2) err(describe_ru[TOO_MANY_ARGS]);

    
    struct bmp_header h = { 0 };
    if (read_header_from_file( argv[1], &h )) {
        bmp_header_print( &h, stdout );
    }
    else {
        err( "Failed to open BMP file or reading header.\n" );
    }

    return 0;
}
