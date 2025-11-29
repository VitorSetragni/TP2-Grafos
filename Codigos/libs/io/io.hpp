#ifndef IO_HPP
#define IO_HPP

/**
   IO - Console input/output library.
   @author  PUC-Minas - ICEI
   @version 0.1 - 2023-1
*/

// ---------------------- lista de dependencias

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stddef.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

// ---------------------- redefinicoes para apontamentos

#define nullptr   NULL
#define null      NULL
#define addr(p)  (&(p))
#define deref(p) (*(p))
#define val(p)   (*(p))
#define ref *
#define var &

// ---------------------- redefinicoes uteis

#define IO_printf        printf
#define IO_scanf         scanf
#define IO_fprintf       fprintf
#define IO_fscanf        fscanf

#define AND &&
#define OR  ||
#define NOT !
#define XOR ^

// ---------------------- definicoes de constantes

const bool FALSE = false;
const bool TRUE  = true;

const char EOS          = '\0';
const char EOL          = '\n';
const char ENDL[]       = "\n";
const char STR_EMPTY[]  = "";
const int  STR_SIZE     = 80;

// ---------------------- definicoes de tipos

typedef char*   chars;
typedef int*    ints;
typedef double* doubles;
typedef bool*   bools;

// ---------------------- variáveis globais

extern int  IO_error;
extern bool IO_trace;

// ---------------------- PROTÓTIPOS de funções (para o io.cpp)

void   IO_debugOFF();
void   IO_debugON();
void   IO_debug(bool condition, const char *text);

void   IO_clrscr();
void   IO_flush();

std::string IO_version();
void   IO_id(std::string text);

bool   IO_readbool(std::string text);
char   IO_readchar(std::string text);
double IO_readdouble(std::string text);
float  IO_readfloat(std::string text);
int    IO_readint(std::string text);

void   IO_pause();
void   IO_pause(std::string text);

chars    IO_new_chars(int size);
ints     IO_new_ints(int size);
doubles  IO_new_doubles(int size);
bools    IO_new_bools(int size);

std::string IO_concat(std::string, std::string);
std::string IO_toString(bool);
std::string IO_toString(char);
std::string IO_toString(int);
std::string IO_toString(double);
std::string IO_toString(std::string);

void IO_print(std::string);
void IO_println(std::string);
void IO_fprint(FILE*, std::string);
void IO_fprintln(FILE*, std::string);

chars       IO_fread(FILE*);
std::string IO_freadln(std::ifstream&);

char*        IO_readstring(std::string);
char*        IO_readln(std::string);

chars IO_boolalpha(bool value);
bool  IO_check(void *p1, void *p2, int size);

std::string IO_next(std::string);
std::string IO_nextLine(std::string);

int   IO_length(char* text);
char  IO_charAt(char* text, unsigned int index);
char* IO_substring(char *text, int start, int size);

#endif // IO_HPP
