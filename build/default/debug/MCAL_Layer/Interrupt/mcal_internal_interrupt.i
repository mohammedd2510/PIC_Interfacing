# 1 "MCAL_Layer/Interrupt/mcal_internal_interrupt.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC18Fxxxx_DFP/1.4.151/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "MCAL_Layer/Interrupt/mcal_internal_interrupt.c" 2
# 1 "MCAL_Layer/Interrupt/mcal_internal_interrupt.h" 1
# 13 "MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
# 1 "MCAL_Layer/Interrupt/mcal_interrupt_config.h" 1
# 12 "MCAL_Layer/Interrupt/mcal_interrupt_config.h"
# 1 "MCAL_Layer/Interrupt/../my_pic18f4620.h" 1
# 10 "MCAL_Layer/Interrupt/../my_pic18f4620.h"
# 1 "MCAL_Layer/Interrupt/../mcal_std_types.h" 1
# 12 "MCAL_Layer/Interrupt/../mcal_std_types.h"
# 1 "MCAL_Layer/Interrupt/../std_libraries.h" 1
# 11 "MCAL_Layer/Interrupt/../std_libraries.h"
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdio.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\musl_xc8.h" 1 3
# 5 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdio.h" 2 3





# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\features.h" 1 3
# 11 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdio.h" 2 3
# 24 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdio.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 1 3





typedef void * va_list[1];




typedef void * __isoc_va_list[1];
# 122 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned size_t;
# 137 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long ssize_t;
# 168 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __int24 int24_t;
# 204 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 246 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long off_t;
# 399 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef struct _IO_FILE FILE;
# 25 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdio.h" 2 3
# 52 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdio.h" 3
typedef union _G_fpos64_t {
 char __opaque[16];
 double __align;
} fpos_t;

extern FILE *const stdin;
extern FILE *const stdout;
extern FILE *const stderr;





FILE *fopen(const char *restrict, const char *restrict);
FILE *freopen(const char *restrict, const char *restrict, FILE *restrict);
int fclose(FILE *);

int remove(const char *);
int rename(const char *, const char *);

int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
void clearerr(FILE *);

int fseek(FILE *, long, int);
long ftell(FILE *);
void rewind(FILE *);

int fgetpos(FILE *restrict, fpos_t *restrict);
int fsetpos(FILE *, const fpos_t *);

size_t fread(void *restrict, size_t, size_t, FILE *restrict);
size_t fwrite(const void *restrict, size_t, size_t, FILE *restrict);

int fgetc(FILE *);
int getc(FILE *);
int getchar(void);
int ungetc(int, FILE *);
int getch(void);

int fputc(int, FILE *);
int putc(int, FILE *);
int putchar(int);
void putch(char);

char *fgets(char *restrict, int, FILE *restrict);

char *gets(char *);


int fputs(const char *restrict, FILE *restrict);
int puts(const char *);

__attribute__((__format__(__printf__, 1, 2)))
int printf(const char *restrict, ...);
__attribute__((__format__(__printf__, 2, 3)))
int fprintf(FILE *restrict, const char *restrict, ...);
__attribute__((__format__(__printf__, 2, 3)))
int sprintf(char *restrict, const char *restrict, ...);
__attribute__((__format__(__printf__, 3, 4)))
int snprintf(char *restrict, size_t, const char *restrict, ...);

__attribute__((__format__(__printf__, 1, 0)))
int vprintf(const char *restrict, __isoc_va_list);
int vfprintf(FILE *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__printf__, 2, 0)))
int vsprintf(char *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__printf__, 3, 0)))
int vsnprintf(char *restrict, size_t, const char *restrict, __isoc_va_list);

__attribute__((__format__(__scanf__, 1, 2)))
int scanf(const char *restrict, ...);
__attribute__((__format__(__scanf__, 2, 3)))
int fscanf(FILE *restrict, const char *restrict, ...);
__attribute__((__format__(__scanf__, 2, 3)))
int sscanf(const char *restrict, const char *restrict, ...);

__attribute__((__format__(__scanf__, 1, 0)))
int vscanf(const char *restrict, __isoc_va_list);
int vfscanf(FILE *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__scanf__, 2, 0)))
int vsscanf(const char *restrict, const char *restrict, __isoc_va_list);

void perror(const char *);

int setvbuf(FILE *restrict, char *restrict, int, size_t);
void setbuf(FILE *restrict, char *restrict);

char *tmpnam(char *);
FILE *tmpfile(void);




FILE *fmemopen(void *restrict, size_t, const char *restrict);
FILE *open_memstream(char **, size_t *);
FILE *fdopen(int, const char *);
FILE *popen(const char *, const char *);
int pclose(FILE *);
int fileno(FILE *);
int fseeko(FILE *, off_t, int);
off_t ftello(FILE *);
int dprintf(int, const char *restrict, ...);
int vdprintf(int, const char *restrict, __isoc_va_list);
void flockfile(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);
ssize_t getdelim(char **restrict, size_t *restrict, int, FILE *restrict);
ssize_t getline(char **restrict, size_t *restrict, FILE *restrict);
int renameat(int, const char *, int, const char *);
char *ctermid(char *);







char *tempnam(const char *, const char *);
# 11 "MCAL_Layer/Interrupt/../std_libraries.h" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdlib.h" 1 3
# 21 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdlib.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 18 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long int wchar_t;
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdlib.h" 2 3

int atoi (const char *);
long atol (const char *);
long long atoll (const char *);
double atof (const char *);

float strtof (const char *restrict, char **restrict);
double strtod (const char *restrict, char **restrict);
long double strtold (const char *restrict, char **restrict);



long strtol (const char *restrict, char **restrict, int);
unsigned long strtoul (const char *restrict, char **restrict, int);
long long strtoll (const char *restrict, char **restrict, int);
unsigned long long strtoull (const char *restrict, char **restrict, int);

int rand (void);
void srand (unsigned);

void *malloc (size_t);
void *calloc (size_t, size_t);
void *realloc (void *, size_t);
void free (void *);

          void abort (void);
int atexit (void (*) (void));
          void exit (int);
          void _Exit (int);

void *bsearch (const void *, const void *, size_t, size_t, int (*)(const void *, const void *));







__attribute__((nonreentrant)) void qsort (void *, size_t, size_t, int (*)(const void *, const void *));

int abs (int);
long labs (long);
long long llabs (long long);

typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;
typedef struct { long long quot, rem; } lldiv_t;

div_t div (int, int);
ldiv_t ldiv (long, long);
lldiv_t lldiv (long long, long long);

typedef struct { unsigned int quot, rem; } udiv_t;
typedef struct { unsigned long quot, rem; } uldiv_t;
udiv_t udiv (unsigned int, unsigned int);
uldiv_t uldiv (unsigned long, unsigned long);
# 12 "MCAL_Layer/Interrupt/../std_libraries.h" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\string.h" 1 3
# 25 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\string.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 411 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef struct __locale_struct * locale_t;
# 26 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\string.h" 2 3

void *memcpy (void *restrict, const void *restrict, size_t);
void *memmove (void *, const void *, size_t);
void *memset (void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void *memchr (const void *, int, size_t);

char *strcpy (char *restrict, const char *restrict);
char *strncpy (char *restrict, const char *restrict, size_t);

char *strcat (char *restrict, const char *restrict);
char *strncat (char *restrict, const char *restrict, size_t);

int strcmp (const char *, const char *);
int strncmp (const char *, const char *, size_t);

int strcoll (const char *, const char *);
size_t strxfrm (char *restrict, const char *restrict, size_t);

char *strchr (const char *, int);
char *strrchr (const char *, int);

size_t strcspn (const char *, const char *);
size_t strspn (const char *, const char *);
char *strpbrk (const char *, const char *);
char *strstr (const char *, const char *);
char *strtok (char *restrict, const char *restrict);

size_t strlen (const char *);

char *strerror (int);




char *strtok_r (char *restrict, const char *restrict, char **restrict);
int strerror_r (int, char *, size_t);
char *stpcpy(char *restrict, const char *restrict);
char *stpncpy(char *restrict, const char *restrict, size_t);
size_t strnlen (const char *, size_t);
char *strdup (const char *);
char *strndup (const char *, size_t);
char *strsignal(int);
char *strerror_l (int, locale_t);
int strcoll_l (const char *, const char *, locale_t);
size_t strxfrm_l (char *restrict, const char *restrict, size_t, locale_t);




void *memccpy (void *restrict, const void *restrict, int, size_t);
# 13 "MCAL_Layer/Interrupt/../std_libraries.h" 2
# 12 "MCAL_Layer/Interrupt/../mcal_std_types.h" 2


typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;
typedef signed char sint8;
typedef signed int sint16;
typedef signed long sint32;

typedef uint8 Std_ReturnType;
# 10 "MCAL_Layer/Interrupt/../my_pic18f4620.h" 2
# 62 "MCAL_Layer/Interrupt/../my_pic18f4620.h"
typedef union {
  struct {
   uint8 RBIF :1;
   uint8 INT0IF :1;
   uint8 TMR0IF :1;
   uint8 RBIE :1;
   uint8 INT0IE :1;
   uint8 TMR0IE :1;
   uint8 PEIE :1;
   uint8 GIE :1;
};
  struct {
   uint8 :6;
   uint8 GIEL :1;
   uint8 GIEH :1;
};
}INTCON_t;




typedef struct {
   uint8 RBIP :1;
   uint8 :1;
   uint8 TMR0IP:1;
   uint8 :1;
   uint8 INTEDG2 :1;
   uint8 INTEDG1:1;
   uint8 INTEDG0 :1;
   uint8 RBPU :1;
}INTCON2_t;




typedef struct {
   uint8 INT1IF :1;
   uint8 INT2IF :1;
   uint8 :1;
   uint8 INT1IE :1;
   uint8 INT2IE :1;
   uint8 :1;
   uint8 INT1IP :1;
   uint8 INT2IP :1;
}INTCON3_t;




typedef struct {
  uint8 TMR1IF :1;
  uint8 TMR2IF :1;
  uint8 CCP1IF :1;
  uint8 SSPIF :1;
  uint8 TXIF :1;
  uint8 RCIF :1;
  uint8 ADIF :1;
  uint8 PSPIF :1;
}PIR1_t;




typedef struct {
  uint8 CCP2IF :1;
  uint8 TMR3IF :1;
  uint8 HLVDIF :1;
  uint8 BCLIF :1;
  uint8 EEIF :1;
  uint8 :1;
  uint8 CMIF :1;
  uint8 OSCFIF :1;
}PIR2_t;





typedef struct {
  uint8 TMR1IE :1;
  uint8 TMR2IE :1;
  uint8 CCP1IE :1;
  uint8 SSPIE :1;
  uint8 TXIE :1;
  uint8 RCIE :1;
  uint8 ADIE :1;
  uint8 PSPIE :1;
}PIE1_t;




typedef struct {
  uint8 CCP2IE :1;
  uint8 TMR3IE :1;
  uint8 HLVDIE :1;
  uint8 BCLIE :1;
  uint8 EEIE :1;
  uint8 :1;
  uint8 CMIE :1;
  uint8 OSCFIE :1;
}PIE2_t;




typedef struct {
  uint8 TMR1IP :1;
  uint8 TMR2IP :1;
  uint8 CCP1IP :1;
  uint8 SSPIP :1;
  uint8 TXIP :1;
  uint8 RCIP :1;
  uint8 ADIP :1;
  uint8 PSPIP :1;
}IPR1_t;




typedef struct {
  uint8 CCP2IP :1;
  uint8 TMR3IP :1;
  uint8 HLVDIP :1;
  uint8 BCLIP :1;
  uint8 EEIP :1;
  uint8 :1;
  uint8 CMIP :1;
  uint8 OSCFIP :1;
}IPR2_t;




typedef struct {
  uint8 BOR :1;
  uint8 POR :1;
  uint8 PD :1;
  uint8 TO :1;
  uint8 RI :1;
  uint8 :1;
  uint8 SBOREN :1;
  uint8 IPEN :1;
}RCON_t;
# 12 "MCAL_Layer/Interrupt/mcal_interrupt_config.h" 2
# 13 "MCAL_Layer/Interrupt/mcal_internal_interrupt.h" 2
# 1 "MCAL_Layer/Interrupt/mcal_internal_interrupt.c" 2

