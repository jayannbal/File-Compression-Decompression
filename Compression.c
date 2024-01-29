
#include <stdio.h>
#include <string.h>
#include <time.h>

// NAMES:                    SECTION: BSIS-2AB
/* BALATERO, JAY-ANN ANGELA
   RECAÑA, ANGEL CYRHEN */


typedef struct comp_node {
	struct comp_node *left, *right;
	int frq; char chr;
} *node;

void delay(unsigned int mseconds)

{
    clock_t goal = mseconds + clock();
    while(goal > clock());
}


int nodesNum = 0;
int e_que = 1;
struct comp_node grp[256] = {{0}};
node pq[255], *q = pq-1;
char *code[128] = {0};
char str[1024];
int data_i=0,data_o=0;


int main(int argument, char* vector[]){

int arr;
	system("cls");
    system("COLOR F1");
    printf("\n\n\n\n\t\t\t\t\t   ********** PROJECT#2 **********");
    printf("\n\n\t\t\t\t\t          BALATERO | RECANA");
    printf("\n\t\t\t\t\t             BSIS - 2AB");
    printf("\n\n\n\n\n\n\t\t\t\t\t           PLEASE WAIT");

    for(arr=1; arr<=3; arr++)
        {
            printf(" .");
            delay(800);
        }

	system("cls");
	printf("\n\n\n");
	printf("\n\t\t\t\t\t  ================================");
    printf("\n\t\t\t\t\t         HUFFMAN COMPRESSION           ");
    printf("\n\t\t\t\t\t  ================================");
    printf("\n\n\n");


FILE *fpGet, *fpDisp;
char fname[50]={0};
unsigned int frq[128] = {0},i;


if( argument == 2 ) {
    strcpy(fname,vector[1]);}
else if( argument > 2 ) {
    printf(" [INVALID: There are too many arguments given]\n");}
else {
    printf("\t\t\t Enter a text file you want to compress:  ");
    scanf("%s",fname);}
if(strlen(fname)>=50){
    printf(" [INVALID: The MAX character for file name is 50]");
    return 0;}

	system("cls");
	printf("\n\n\n");
	printf("\n\t\t\t\t\t  ================================");
    printf("\n\t\t\t\t\t         HUFFMAN COMPRESSION           ");
    printf("\n\t\t\t\t\t  ================================");
    printf("\n\n\n");
    printf("\n\t\t\t\t\t  Entered file: %s", fname);


	if((fpGet = fopen(fname,"r"))==NULL){
		printf("\n ERROR: No file exist\n");
		return 0;
	}

import_file(fpGet,frq);
print_code(frq);
strcat(fname,".txt");
fpDisp = fopen(fname,"w");
compress(fpGet,fpDisp,frq);
fclose(fpGet);
fclose(fpDisp);

strcat(fname,".table");
fpDisp = fopen(fname,"w");
    for(i=0; i<128; i++){
        fprintf(fpDisp,"%c",(char)frq[i]);}
	for(i=0; i<128; i++)	data_i += frq[i];
	fclose(fpDisp);
	printf("\n\n\t\t\t\t\t  Original bytes:\t%d\n",data_i);
	data_o= (data_o%8)? (data_o/8)+1 : (data_o/8);
	printf("\t\t\t\t\t  Compressed bytes:\t%d\n",data_o);
	printf("\t\t\t\t\t  Compression ratio:\t%.2f%%\n\n\n\n\n\n\n",((double)(data_i-data_o)/data_i)*100);
	return 0;
}


node makeNode(int frq, char chr, node x, node y)
{
node z = grp + nodesNum++;
if (frq != 0){
    z->chr = chr;
    z->frq = frq;}
	else {
		z->left = x, z->right = y;
		z->frq = x->frq + y->frq;}
	return z;}

//to insert the que to priority node
void ins_que(node z){
    int a, b = e_que++;
	while ((a= b / 2)) {
        if (q[a]->frq <= z->frq) break;
            q[b] = q[a], b = a;
        } q[b] = z;
}

node rmv_que(){
int i;
int r;
node z = q[i = 1];
if (e_que < 2) return 0;
    e_que--;
while ((r = i * 2) < e_que) {
    if (r + 1 < e_que && q[r + 1]->frq < q[r]->frq) r++;
        q[i] = q[r], i = r; }
	q[i] = q[e_que];
	return z;
}

// the huffman tree was builded and code for each character is being assigned
void makeCode(node z, char *c, int length){
    static char *otp = str;
	if (z->chr) {
		c[length] = 0;
		strcpy(otp, c);
		code[(int)z->chr] = otp;
		otp += length + 1;
		return;}
	c[length] = '0'; makeCode(z->left,  c, length + 1);
	c[length] = '1'; makeCode(z->right, c, length + 1);
}

void import_file(FILE *fpGet, unsigned int *frq){
int i = 0;
char t;
char v[16]={0};
while((t=fgetc(fpGet))!=EOF){
        frq[(int)t]++;}
	for (i = 0; i < 128; i++)
		if (frq[i]) ins_que(makeNode(frq[i], i, 0, 0));
	while (e_que > 2)
		ins_que(makeNode(0, 0, rmv_que(), rmv_que()));
        makeCode(q[1], v, 0);
}

void compress(FILE* fpGet, FILE* fpDisp, unsigned int *frq ){

char get;
char c,temp[20] = {0};
int i,j=0,k=0,max=0;
rewind(fpGet);
for(i=0; i<128; i++){
if(frq[i])	max += (frq[i]*strlen(code[i]));}
	data_o = max;
	fprintf(fpDisp,"%04d\n",max);
}

void print_code(unsigned int *frq){
int i;
printf("\n\n\n\n\t\t\t\t       *************  TABLE *************\n\t\t\t\t\t ------------------------------------\n\t\t\t\t\t CHARACTER     FREQUENCY       CODE\n\t\t\t\t\t  -------------------------------------\n");
for(i=0; i<128; i++){
    if(isprint((char)i)&&code[i]!=NULL&&i!=' ')
    printf("\t\t\t\t\t    %-4c    %-4d    %16s\n",i,frq[i],code[i]);
    else if(code[i]!=NULL){
        switch(i){
            case '\n':
                printf("\t\t\t\t\t    \\n  ");
                break;
            case ' ':
                printf("\t\t\t\t\t    \' \' ");
                break;
            case '\t':
                printf("\t\t\t\t\t     \\t  ");
                break;
            default:
                printf("\t\t\t\t\t     %0X  ",(char)i);
                break;}
			printf("    %-4d  %16s\n",frq[i],code[i]);
		}
	}
	printf("\n\t\t\t\t\t   ----------------------------------\n");
}

