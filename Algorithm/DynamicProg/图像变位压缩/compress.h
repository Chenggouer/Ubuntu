#ifndef COMPRESS_H_
#define COMPRESS_H_

void compress(int* p, int n, int* s, int* l, int* b);
int length(int a);
int Traceback(int n, int* l, int* c);
void output(int* c, int len_c, int* p);

#endif
