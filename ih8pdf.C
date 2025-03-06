#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CMD_BUFFER_SIZE 512
#define FILE_BUFFER_SIZE 256

void print_instructions(const char *progname){
    printf("I H8 PDF \n");
    fprintf(stderr, "Usage: %s [-c compress_level] input_file1 [input_file2 ...]\n",progname);
    fprintf(stderr, " -c: Compression level. (0 = Less compression (/prepress), 1 = Moderate compression (/ebook), 2 = High compression (/screen) default is 1)\n");

}

int main(int argc, char *argv[]){

    int compress_level=1;
    int opt;

    while ((opt=getopt(argc,argv,"c:"))!=-1){
        switch(opt){

            case 'c':
                compress_level=atoi(optarg);
                break;
            default:
                print_instructions(argv[0]);
                return EXIT_FAILURE;
        }
    }
    if(optind >= argc){
    fprintf(stderr, "Error: Expected at least one input PDF file.\n");
    print_instructions(argv[0]);
    return EXIT_FAILURE;
    }

    const char *pdf_setting;

    switch (compress_level){
        case 0:
            pdf_setting="/prepress";
            break;
        case 1:
            pdf_setting="/ebook";
            break;
        case 2:
        default:
            pdf_setting="/screen";
            break;
    }

    for (int i=optind; i<argc;i++){
        char *input_directory=argv[i], input_directory_backup[FILE_BUFFER_SIZE / 2],
             *input_file, *output = input_directory, new_filename[FILE_BUFFER_SIZE], out_file[FILE_BUFFER_SIZE];

        // to be modularized
        if (strchr(input_directory, '/') == NULL) { // on the current directory
            input_file = input_directory;
            strcpy(input_directory_backup, input_directory);
            snprintf(out_file, FILE_BUFFER_SIZE, "compressed_%s", input_file);
        }
        else {
            strcpy(input_directory_backup, input_directory);
            input_file = strrchr(input_directory, '/') + 1; // add 1 to skip the '/'
            output[strrchr(input_directory, '/') - input_directory] = '\0'; // remove the old filename from the path
            strcpy(new_filename, "/compressed_");
            strcat(new_filename, input_file);
            strcat(output, new_filename); // add the new filename to the path
            snprintf(out_file, FILE_BUFFER_SIZE, "%s", output);
        }

        printf("Input file: %s\n",input_directory);

        //Build Ghostscript command
        char cmd[CMD_BUFFER_SIZE];
        snprintf(cmd, CMD_BUFFER_SIZE,
                 "gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=%s "
                 "-dNOPAUSE -dQUIET -dBATCH -sOutputFile=%s %s",
                 pdf_setting, out_file, input_directory_backup);
        printf("Running command: %s\n",cmd);
        int ret=system(cmd);
        if (ret != 0){
            fprintf(stderr, "Error compressing the file: %s\n",input_directory_backup);
        }
    }
    return EXIT_SUCCESS;
}
