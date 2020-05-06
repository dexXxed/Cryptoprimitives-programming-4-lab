#ifndef POLYNOMS_IO_PROCEDURES
#define POLYNOMS_IO_PROCEDURES
// Вывод полинома в текстовом виде
void print_pol(M_LONG f);

/* Вывод полинома в векторном виде
	(от старших степеней к младшим) */
void print_vect(M_LONG f);


// Вывод полинома в текстовом виде в текстовый файл 
// Файл f_out открыт заранее (в режиме записи)
void fprint_pol(FILE *f_out,M_LONG f);

#endif