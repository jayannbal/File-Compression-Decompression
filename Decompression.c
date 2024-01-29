
#include <stdio.h>
#include <string.h>
#include <time.h>

/* NAMES:                     SECTION: BSIS-2AB
   BALATERO, JAY-ANN ANGELA
   RECAÑA, ANGEL CYRHEN */

void delay(unsigned int mseconds)

{
    clock_t goal = mseconds + clock();
    while(goal > clock());
}

typedef struct dcomp_node {
	struct dcomp_node *left, *right;
	int frq;
	char chr;
} *node;

int main(int argument, char* vector[]){
FILE *fpTbl,*fp_Hfn,*fp_disp;		//FIFO pointers
char file_name[50]={0},temp[50]={0};		//file name
unsigned int frq[128] = {0};			//frequency of the letters

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
    printf("\n\t\t\t\t\t       HUFFMAN DECOMPRESSION           ");
    printf("\n\t\t\t\t\t  ================================");
    printf("\n\n\n");

if( argument == 2 ) {
    strcpy(file_name,vector[1]);				//commandline argument directly allows to compress the file
if(strstr(file_name,"txt") == NULL){
    printf("\n\n\n\t\t\t\t\t[INVALID FILE FORMAT]\n");
    return 0;}}
else if( argument > 2 ) {
    printf("\t\t\t [ERROR: There are too many arguments given]\n");}
else {
    printf("\t\t\t Enter a text file you want to decompress:  "); 	//else a prompt comes to enter the file name
    scanf("%s",file_name);
        if(strstr(file_name,"txt") == NULL){
			printf("\n\n\n\t\t\t\t\t[INVALID FILE FORMAT]\n\n\n\n\n");
			return 0;}
   	}


	if((fp_Hfn = fopen(file_name,"r"))==NULL){
		printf("\n\n\n\t\t\t\t\t\t[FILE DOES NOT EXIST]\n\n\n\n\n");
		return 0;}
		strcat(file_name,".table");

	if((fpTbl = fopen(file_name,"r"))==NULL){
		printf("\n\n\n\t\t\t [ERROR: TABLE OF FREQUENCY IS NOT FOUND]\n\n\n\n\n");
		return 0;}
	printf("\n\n\n");
	tableGet(fpTbl,frq);

	*strstr(file_name,".txt") = '\0';
	strcpy(temp,"mkdir ");
	strcat(temp,file_name);
	system(strcat(temp,".decompressed"));
	strcpy(temp,"./");
	strcat(temp,file_name);
	strcat(temp,".decompressed/");

	if((fp_disp = fopen(strcat(temp,file_name),"w"))==NULL){
		printf("\t\t\t[ERROR CREATING A DECODED FILE]n\n\n\n\n");
		return 0;
	}
	decompress(fp_Hfn,fp_disp);
	fclose(fp_Hfn);
	fclose(fpTbl);
	fclose(fp_disp);
	return 0;
}


int n_nodes = 0;
int e_que = 1;
struct dcomp_node grp[256] = {{0}};
node pq[255], *q = pq-1;
char str[1024];

// to create a new node
node makeNode(int frq, char chr, node x, node y){
node z = grp + n_nodes++;
	if (frq != 0){
		z->chr = chr;
		z->frq = frq;}
	else {
		z->left = x, z->right = y;
		z->frq = x->frq + y->frq;}
	return z;
}
// the node will be insert to the priority que
void ins_que(node z){
int a, b = e_que++;
	while ((a = b / 2)) {
    if (q[a]->frq <= z->frq) break;
		q[b] = q[a], b = a;
	}
	q[b] = z;}

node rmv_que(){
int i;
int r;
node z = q[i = 1];
	if (e_que < 2) return 0;
	e_que--;
        while ((r = i * 2) < e_que) {
            if (r + 1 < e_que && q[r + 1]->frq < q[r]->frq) r++;
            q[i] = q[r], i = r;}
            q[i] = q[e_que];
	return z;
}

void tableGet(FILE *fpTbl, unsigned int *frq){
char tempr;
int i = 0;
	while((tempr=fgetc(fpTbl))!=EOF){
        frq[i++] = (unsigned char)tempr;
	}
	for (i = 0; i < 128; i++)
		if (frq[i]) ins_que(makeNode(frq[i], i, 0, 0));
            while (e_que > 2)
                ins_que(makeNode(0, 0, rmv_que(), rmv_que()));
}

void decompress(FILE *fp_Hfn,FILE *fp_disp){
int i=0;
int lmt=0;
int j=0;
char chr;
node z= q[1];
fscanf(fp_Hfn,"%d",&lmt);
fseek(fp_Hfn,1,SEEK_CUR);
	printf("Decoded : \n");
	for(i=0; i<lmt; i++){
		if(j==0)
			chr = fgetc(fp_Hfn);
		if(chr&128)	z = z->right;
		else 		z = z->left;
            if(z->chr){
                putchar(z->chr);
                fputc(z->chr,fp_disp);
                z = q[1];}
		chr = chr<<1;
		if(++j>7)
			j = 0;}
	putchar('\n');
        if (q[1] != z) printf("garbage input\n");
}

