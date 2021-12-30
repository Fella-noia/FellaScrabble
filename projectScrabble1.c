#include<stdio.h>
 #include<string.h>
 #include<stdbool.h>
 #include<time.h>
 #include<stdlib.h>
 #include<windows.h>
 #include<mmsystem.h>

 typedef struct{
 	char nama[100];
 	int score;
 	int pass;
 	int acakHuruf;
 	char blokHuruf[7];
 	bool win;
 } pemain;
 
 typedef struct{
 	char huruf;
 	int poin;
 	int jumlah;	  	
 } huruf;
 
 typedef struct{
 	huruf;
 	int bonus;
 } papan;
 
 void mainMenu();
 void playTheGame();
 void persiapanPemain(int *level, int *lawan);
 void persiapanPapan();
 void giliranBermain(int level, int lawan);
 void blokPemain(int giliran);
 void tampilPapan();
 void tambahPosisi(int *row, char *col);
 bool cekPosisi(int row, char col);
 char tambahArah();
 bool cekArah(char arah);
 void tambahHuruf(char *kata[7]);
 bool finish(int giliran);
 int pilihLawan();
 void menambahNama(int lawan);
 int pilihLevel();
 
 
 // variabel global
 pemain Pemain[2];
 huruf infoHuruf[27]={{'A',1,9},{'B',3,2},{'C',3,2},
 					  {'D',2,4},{'E',1,12},{'F',4,2},
					  {'G',2,3},{'H',4,2},{'I',1,9},
					  {'J',8,1},{'K',5,1},{'L',1,4},
					  {'M',3,2},{'N',1,6},{'O',1,8},
					  {'P',3,2},{'Q',10,1},{'R',1,6},
					  {'S',1,4},{'T',1,6},{'U',1,4},
					  {'V',4,2},{'W',4,2},{'X',8,1},
					  {'Y',4,2},{'Z',10,1},{' ',0,2}};
 papan infoPapan[15][15];
 
 int main(){
 	int n;
 	menu :
 	system("cls");
 	mainMenu(); 	
 	scanf("%d", &n);
 	switch(n){
 		case 1 : playTheGame(); break;
 		case 2 : printf("pilih lawan\n"); break;
 		case 3 : printf("high score\n"); break;
 		case 4 : printf("exit\n"); break;
 		default:
        	printf("WRONG INPUT NUMBER.\n");
	        goto menu; 
 	}

// 	printf("%s\n", Nama1.nama);
// 	printf("%s\n", Nama2.nama);
 	return 0;
 }
 
 void mainMenu(){
 	printf("1. Play the Game\n");
 	printf("2. How to Play\n");
 	printf("3. High Score\n");
 	printf("4. Exit\n");
 	printf("Select number : ");
 }
 
 void playTheGame(){
 	int lawan, level;
 	persiapanPemain(&level,&lawan);
 	persiapanPapan();
 	giliranBermain(level,lawan);
 }
 
 void persiapanPemain(int *level, int *lawan){
 	*lawan=pilihLawan();
 	menambahNama(*lawan);
 	*level=pilihLevel();
 }
 
 int pilihLawan(){
 	int lawan;
 	printf("Select your oponent type (1 : Computer / 2 : People) : ");
 	scanf("%d", &lawan);
 	
 	return lawan;
 }
 
 void menambahNama(int lawan){
 	int i;
 	char temp[100];
	printf("lawan : %d\n", lawan);
	if (lawan==1){
 		printf("Input name for player : ");	
		scanf("%s", &temp);
		strcpy(Pemain[0].nama, temp);
	}
 	else if (lawan==2){
		printf("Input name for player 1: ");	
		scanf("%s", &temp);
		strcpy(Pemain[0].nama, temp); 
		printf("Input name for player 2: ");	
		scanf("%s", &temp);
		strcpy(Pemain[1].nama, temp); 
 	}
 }

 int pilihLevel(){
 	int level;
 	printf("Select level (1 : Easy / 2 : Medium / 3 : Hard) : ");
 	scanf("%d", &level);
 	
 	return level;
 }
 
 void giliranBermain(int level, int lawan){
// 	papan();
	int giliran=-1, i, j;
	int row;
	char col, arah, kata[7];
	system("cls");
	
	do {
		giliran = (giliran + 1) % 2 ;
		tampilPapan();
//		timer(level); 
		printf("\n\nlevel : %d", level); 	
		printf("\nname : %s", Pemain[giliran].nama);
		printf("\nscore : %s", Pemain[giliran].score);
		printf("\nremaining block : 84");
		printf("\n=======================\n");
		blokPemain(giliran); // 
		tambahPosisi(&row,&col);
		arah = tambahArah();
		printf("posisi %c", arah);
		tambahHuruf(&kata[7]);
//		printf("%c", tambahArah());
//		cekKata(); //  
		scanf("%d", &i);
		system("cls");	
//		menambahPosisi();
	} while(finish(giliran)==false);
 }
 
 void persiapanPapan(){
 	int i, j;
 	for (i = 0; i<15;i++){
	 	for (j = 0; j<15; j++){
	 		infoPapan[i][j].huruf='_';
		}
	}
 }
 
 void tampilPapan(){
 	int i, j;
 	printf("  ");
 	for (i = 0; i<15;i++){
 		printf("   %c",i+0x41);
 	}
 	for (i = 0; i<15;i++){
	 	printf("\n%d ",i+1);
	 	if (i>=0 && i<=8){
	 		printf(" ");
		}
		printf ("|");
	 	for (j = 0; j<15; j++){
	 		printf(" %c |", infoPapan[i][j].huruf);
		}
		printf(" %d ",i+1);
	}
	printf("\n  ");
	for (i = 0; i<15;i++){
 		printf("   %c",i+0x41);
 	}
// 	scanf("%d", j);
 }
 
 void blokPemain(int giliran){
 	int i, j, idx=0, jml, total;
	char temp, ran;	
 	char kantongHuruf[100];
 	srand((unsigned) time(NULL));
 	
 	for (i=0;i<27;i++){
 		jml=infoHuruf[i].jumlah;
 		if (jml!=0){
 			for (j=0;j<jml;j++){
 				temp = infoHuruf[i].huruf;
 				kantongHuruf[idx] = temp;
 				idx++;
 			}
		}	
	}

	total = idx;
	
    /* now shuffle */
    for (i=0;i<total;i++) {
        int p1 = rand() % total;
        int p2 = rand() % total;
        int temp = kantongHuruf[p1];
        kantongHuruf[p1] = kantongHuruf[p2];
        kantongHuruf[p2] = temp;
    }
 	
    for (i=0; i<7; i++) { //print random matrix
        ran = 'A' + rand() % 26;
        printf("|");
        printf(" %c |", kantongHuruf[i]);
        temp = kantongHuruf[i]; // A
    	Pemain[giliran].blokHuruf[i]=temp;
    	for (j=0; j<27; j++){
    		if(infoHuruf[j].huruf==temp){
    			infoHuruf[j].jumlah--;	
			}
		}
	}
 }
 
 void tambahPosisi(int *row, char *col){
 	int rowT;
 	char colT;
 	
 	add:
	printf("\nInsert Row & Column (ex : 8H) : "); 
	scanf("%d%c", &rowT, &colT);
	getchar();
	
	if(cekPosisi(rowT, colT)==false){
		printf("Wrong input!\n");
		goto add;
	} else {
		*row=rowT;
		*col=colT;
	}
 }

 bool cekPosisi(int row, char col){
 	bool cek=false;
 	
 	if(row>=1 && row<=15){
 		if (col>=65 && col<=79 || col>=97 && col<=111){
	 		cek = true;
	 	}
	 }
	 return cek;
 }
 
 char tambahArah(){
 	char arah;
 	
 	add :
 	printf("Insert direction (H / V) : ");
 	scanf("%c", &arah);
 	fflush(stdin);
 	
 	if (cekArah(arah)==true){
 		return arah;
 	}
 	else {
 		printf("wrong input!\n");
 		goto add;
	}
 }
 
 bool cekArah(char arah){
 	if (arah=='H' || arah=='V' || arah=='h' || arah=='v'){
 		return true;
	}
	else {
		return false;
	}
 }
 
 void tambahHuruf(char *kata[7]){
// 	char kataT;
	printf("Input letter : ");
	scanf("%s", *kata);
	
 }
// int periksa (char posisi[2]){
// 	
// 	pass();
// 	acakHuruf();
// }
 
 bool finish(int giliran){
 	int hasil;
// 	if (Pemain[giliran].blokHuruf==0 || Pemain[giliran].pass==2){
 	if (Pemain[giliran].pass==2){
	 	Pemain[giliran].win=true;
 		hasil=true;
	} else {
		hasil=false;
	}
 	
 	return hasil;
 }

