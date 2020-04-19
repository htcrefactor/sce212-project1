#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/******************************************************
 * Structure Declaration
 *******************************************************/

struct Inst {
    char *name;
    char *op;
    char type;
    char *funct;
};

struct Data {
    int value;
    struct Data *next;
};

struct Text {
    int idx;
    char *d;
    char *s;
    char *t;
    unsigned int address;
    struct Text *next;
};

struct Sym {
    char *name;
    int size;
    unsigned int address;
    struct Data *first;
    struct Sym *next;
    struct Data *last;
};


/******************************************************
 * Global Variable Declaration
 *******************************************************/

struct Inst inst[20] = {
    {"addiu",   "001001", 'I', ""},
    {"addu",    "000000", 'R', "100001"},
    {"and",     "000000", 'R', "100100"},
    {"andi",    "001100", 'I', ""},
    {"beq",     "000100", 'I', ""},
    {"bne",     "000101", 'I', ""},
    {"j",       "000010", 'J', ""},
    {"jal",     "000011", 'J', ""},
    {"jr",      "000000", 'R', "001000"},
    {"lui",     "001111", 'I', ""},
    {"lw",      "100011", 'I', ""},
    {"nor",     "000000", 'R', "100111"},
    {"or",      "000000", 'R', "100101"},
    {"ori",     "001101", 'I', ""},
    {"sltiu",   "001011", 'I', ""},
    {"sltu",    "000000", 'R', "101011"},
    {"sll",     "000000", 'S', "000000"},
    {"srl",     "000000", 'S', "000010"},
    {"sw",      "101011", 'I', ""},
    {"subu",    "000000", 'R', "100011"}
};
struct Sym *Symbols;
struct Text *Texts;
int datasize, textsize;


/******************************************************
 * Function Declaration
 *******************************************************/

/* You may need the following functions */
char* change_file_ext(char *str);
char* num_to_bits(unsigned int num, int len);

/* You may fill the following functions */
void read_asm();
void subst_asm_to_num();
void print_bits();


/******************************************************
 * Function: main
 *
 * Parameters:
 *  int
 *      argc: the number of argument
 *  char*
 *      argv[]: array of a sting argument
 *
 * Return:
 *  return success exit value
 *
 * Info:
 *  The typical main function in C language.
 *  It reads system arguments from terminal (or commands)
 *  and parse an assembly file(*.s).
 *  Then, it converts a certain instruction into
 *  object code which is basically binary code.
 *
 *******************************************************/
int main(int argc, char* argv[]) {

    FILE *input, *output;
    char *filename;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <*.s>\n", argv[0]);
        fprintf(stderr, "Example: %s sample_input/example?.s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // reading the input file
    input = freopen(argv[1], "r", stdin);
    if (input == NULL) {
        perror("ERROR");
        exit(EXIT_FAILURE);
    }

    // creating the output file (*.o)
    filename = strdup(argv[1]); // strdup() is not a standard C library but fairy used a lot.
    if(change_file_ext(filename) == NULL) {
        fprintf(stderr, "'%s' file is not an assembly file.\n", filename);
        exit(EXIT_FAILURE);
    }

    output = freopen(filename, "w", stdout);
    if (output == NULL) {
        perror("ERROR");
        exit(EXIT_FAILURE);
    }

    Symbols = (struct Sym *)malloc(sizeof(struct Sym));
    Texts = (struct Text *)malloc(sizeof(struct Text));

    /******************************************************
     *  Let's complete the below functions!
     *
     *  read_asm(): Read the assmebly code.
     *  subst_asm_to_num(): Convert the assembly code to num.
     *  print_bits(): Print the results of assemble.
     *
     *******************************************************/
    read_asm();
    subst_asm_to_num();
    print_bits();

    // freeing the memory
    free(filename);
    free(Symbols);
    free(Texts);

    fclose(input);
    fclose(output);
    exit(EXIT_SUCCESS);
}

/******************************************************
 * Function: change_file_ext
 *
 * Parameters:
 *  char
 *      *str: a raw filename (without path)
 *
 * Return:
 *  return NULL if a file is not an assembly file.
 *  return empty string
 *
 * Info:
 *  This function reads filename and converts it into
 *  object extention name, *.o
 *
 *******************************************************/
char* change_file_ext(char *str) {
    char *dot = strrchr(str, '.');

    if (!dot || dot == str || (strcmp(dot, ".s") != 0))
        return NULL;

    str[strlen(str) - 1] = 'o';
    return "";
}

/******************************************************
 * Function: num_to_bits
 *
 * Parameters:
 *  unsigned int
 *      num: a decimal number to be converted to binary bits
 *  int
 *      len: a length of bits
 *
 * Return:
 *  return string of binary bits
 *
 * Info:
 *  This function reads an integer number and converts it into
 *  binary bits represented by string.
 *
 *******************************************************/
char* num_to_bits(unsigned int num, int len) {
    char* bits = (char *) malloc(len+1);
    int idx = len-1, i;

    while (num > 0 && idx >= 0) {
        if (num % 2 == 1) {
            bits[idx--] = '1';
        } else { 
            bits[idx--] = '0';
        }
        num /= 2;
    }

    for (i = idx; i >= 0; i--){ 
        bits[i] = '0';
    }

    return bits;
}


/******************************************************
 * Function: read_asm
 *
 * Info:
 *  This function reads assembly code and saves the
 *  information into struct Sym, Data, Text, respectively.
 *
 *******************************************************/
void read_asm() {
    int tmp, i;
    unsigned int address;
    char temp[0x1000] = {0};
    struct Sym *temp_sym = NULL;
    struct Data *temp_data = NULL;
    struct Text *temp_text = NULL;

    //Read .data region
    address = 0x10000000;
    for (i = 0; scanf("%s", temp) == 1;) {
       if (strcmp(temp, ".text") == 0) {
           /* blank */

       } else if(temp[strlen(temp)-1] == ':') {
           /* blank */

       } else if(strcmp(temp, ".word") == 0) {
           /* blank */

       }
    }

    datasize = address - 0x10000000;

    //Read .text region
    address = 0x400000;
    for (i = 0; scanf("%s", temp) == 1;) {
       if (temp[strlen(temp)-1] == ':') {
           /* blank */

       } else {
           /* blank */

       }
    }

    textsize = address - 0x400000;
}


/******************************************************
 * Function: subst_asm_to_num
 *
 * Info:
 *  This function converts assembly code to numbers.
 *
 *******************************************************/
void subst_asm_to_num() {
    struct Text *text;

    for (text = Texts->next; text != NULL; text = text->next) {
        /* blank */

    }
}


/******************************************************
 * Function: print_bits
 *
 * Info:
 *  This function prints binary bit string converted by
 *  assembler. It will make binary object file of assembly code.
 *
 *******************************************************/
void print_bits() {
    struct Text* text;
    struct Sym* sym;
    struct Data* data;
    
    // print the header
    printf("%s", num_to_bits(textsize, 32));
    printf("%s", num_to_bits(datasize, 32));

    // print the body
    for (text = Texts->next ; text != NULL ; text = text->next) {
        printf("%s", inst[text->idx].op);

        if (inst[text->idx].type == 'R') {
            /* blank */

        } else if(inst[text->idx].type == 'I') {
            /* blank */

        } else if(inst[text->idx].type == 'S') {
            /* blank */

        } else {
            /* blank */

        }
    }

    for (sym = Symbols->next; sym != NULL; sym = sym->next) {
        /* blank */

    }
    printf("\n"); // To exclude "No newline at end of file"
}
