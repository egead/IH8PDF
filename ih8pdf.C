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
        char *input_directory=argv[i];
        char *input_file;
        if (strchr(input_directory, '/')==NULL){ // on the current directory
            input_file = input_directory;
        }
        else{
            input_file=strrchr(input_directory, '/')+1; // add 1 to skip the '/'
        }
        char out_file[FILE_BUFFER_SIZE];
	

        snprintf(out_file,FILE_BUFFER_SIZE,"compressed_%s",input_file);

        //Build Ghostscript command
        char cmd[CMD_BUFFER_SIZE];
        snprintf(cmd, CMD_BUFFER_SIZE,
                 "gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=%s "
                 "-dNOPAUSE -dQUIET -dBATCH -sOutputFile=%s %s",
                 pdf_setting, out_file, input_directory);
        printf("Running command: %s\n",cmd);
        int ret=system(cmd);
        if (ret != 0){
            fprintf(stderr, "Error compressing the file: %s\n",input_directory);
        }
    }
    return EXIT_SUCCESS;
}
