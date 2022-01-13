 #include<stdio.h>
 #include<string.h>
 #include<stdbool.h>
 #include<time.h>
 #include<stdlib.h>
 #include<windows.h>
 #include<mmsystem.h>
 #include <conio.h>
 
 #define putchar(c) putc(c, stdout)

 typedef struct{
 	char nama[100];
 	int score;
 	int pass;
 	int waktuTerlewat;
 	bool menyerah;
 	char blokHuruf[7];
 	bool win;
 	bool awalMain;
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
 
 typedef struct{
	char nama[100];
	int score;
 } highscore;
 
 // untuk koordinat tampil di layar
 void gotoxy(int x, int y);

 // menu utama program
 void mainMenu();
 void playTheGame();
 void howToPlay();
 
 // modul untuk menyetting permainan
 int pilihLawan();
 void menambahNama();
 int pilihLevel();
 void persiapanPemain(int *level);
 void persiapanPapan();
 void persiapanHuruf();
 
 // modul saat permainan berlangsung
 void giliranBermain(int level);
 int sisaBlokHuruf();
 void blokPemain(int giliran);
 void tampilBlokPemain(int giliran);
 void tampilKeterangan();
 void tampilPapan();
 void tambahPosisi(int *row, char *col);
 bool cekPosisi(int row, char col);
 bool cekPosisiPapan(int akhir);
 bool cekAwalMain(char *kata, int row, char col, char arah);
 bool cekAdaHuruf(char *kata, int row, char col, char arah);
 char tambahArah();
 bool cekArah(char arah);
 void tambahHuruf(char *kata, int giliran, int row, char col, char arah);
 bool cekHuruf(char *kata, int giliran);
 void kataTerbentuk(char *kata, int row, char col, char arah, char *kataBaru, int *mulaiKata);
 bool cekKamus(char *kata);
 void tambahKePapan(char *kata, int row, char col, char arah);
 void hapusBlokPemain(char *kata);
 int kolomKeAngka(char col);
 
 // modul untuk menghitung poin
 int akumulasiPoin(char *kata, int giliran, int mulaiKata, int row, int kolom, char arah);
 int poinHuruf(char huruf);
 
 // cek kamus
 bool cekKamus(char *kata);
 
 // fitur dalam game
 void pass(int giliran);
 void menyerah(int giliran);
 void blokKosong(char *kata);
 
 // akhir permainan
 bool finish(int giliran);
 void akhirPermainan(int level);
 void poinAkhir(int level);
 void poinMenyerah();
 void pemenang();
 void tampilPemenang();
 void tampilExit();
 
 // high score
 void tampilHighScore();
 void inputHighScore();
 
 // waktu
 int StartTime();
 int EndTime();
 int batasWaktuInput(int level);
 
 // variabel global
 pemain Pemain[2];
 huruf infoHuruf[27];
 papan infoPapan[15][15];
 int posisiX, posisiY;
 
 // struct gotoxy
 COORD coord = {0,0};
 
 int main(){
 	char n;
 	bool exit=false;
 	menu :
	system("cls");
	mainMenu(); 	
 	scanf("%s", &n);
 	system("cls");
 	if (n=='1'){
 		playTheGame(); // inputan satu akan masuk ke modul playTheGame() untuk memulai game
	} else if (n=='2') {
		howToPlay(); // inputan dua akan masuk ke modul howToPlay() untuk melihat cara bermain game
	} else if (n=='3') {
		tampilHighScore(); // inputan tiga akan masuk ke modul tampilHighScore() untuk melihat daftar highscore
	} else if (n=='4'){
		tampilExit(); // inputan empat akan menampilkan tampilan akhir dan keluar dari program
		exit=true;
	} else {	
		getch();                                                                                           
	    goto menu;
	}   	 
 	
 	if (exit==false){
 		goto menu;
 	}

 	return 0;
 }
 
 
 // modul gotoxy()
 // untuk menentukan koordinat tampil di layar
 // referensi dari youtube, link: 
 void gotoxy(int x, int y){
 	coord.X = x;
 	coord.Y = y;
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
 }
 
 // modul mainMenu()
 // untuk menampilkan menu utama
 void mainMenu(){
 	printf("\n\n");
	gotoxy(25, 4);printf("                 +----  +----  +      +      +----+             \n");
	gotoxy(25, 5);printf("                 |      |      |      |      |    |             \n");
	gotoxy(25, 6);printf("                 +----  +----  |      |      +----+             \n");
	gotoxy(25, 7);printf("                 |      |      |      |      |    |             \n");
	gotoxy(25, 8);printf("                 |      +----  +----  +----  |    |           \n\n");

	gotoxy(25, 10);printf("     +----  +----  +----+  +----+  +----+  +----+  +      +---- \n");
	gotoxy(25, 11);printf("     |      |      |    |  |    |  |    /  |    /  |      |     \n");
	gotoxy(25, 12);printf("     +---+  |      | ---+  +----+  +---+   +---+   |      +---- \n");
	gotoxy(25, 13);printf("         |  |      |  |    |    |  |    |  |    |  |      |     \n");
	gotoxy(25, 14);printf("     +---+  +----  |   |   |    |  +----+  +----+  +----  +---- \n\n\n");
	
	gotoxy(30, 16);printf("========================================================== \n");
	gotoxy(30, 17);printf("                        MAIN MENU                          \n");
	gotoxy(30, 18);printf("========================================================== \n");
	
 	gotoxy(50, 20);printf("1. Play the Game\n");
 	gotoxy(50, 21);printf("2. How to Play\n");
 	gotoxy(50, 22);printf("3. High Score\n");
 	gotoxy(50, 23);printf("4. Exit\n");
 	gotoxy(50, 24);printf("Select number : ");
 }
 
 // modul playTheGame()
 // untuk menyetting permainan
 void playTheGame(){
 	int level;
 	persiapanPemain(&level);
 	persiapanHuruf();
 	persiapanPapan();
 	giliranBermain(level);
 }
 
 // modul howToPlay()
 // untuk menampilkan cara bermain game
 // referensi : modul file teks (dari Ibu Ani)
 void howToPlay(){	
	FILE *FF; 
	char CC, x[1]; //var penunjuk karakter yang dibaca
	
	if((FF=fopen("howtoplay.txt","r"))== NULL) //Buka file mode baca
	{
	 	printf("Pembukaan File Gagal !");
	}
	
	system("cls");
	while((CC=getc(FF))!=EOF) //CC akan berisi karakter yg dibaca
	{ //akhir teks dengan EOF
	 	putch(CC); //baca dan tampilkan ke layar
	}
	
	fclose(FF);
	
	printf("Back to menu (Y : Yes) ? ");
	scanf("%s", &x);
	if(x == "Y" || x == "y"){
		system("cls");
		mainMenu();
	}
 }
 
 // modul persiapanPemain()
 // untuk menampilkan cara bermain game
 void persiapanPemain(int *level){
 	menambahNama();
 	*level=pilihLevel();
 	Pemain[0].score=0;
 	Pemain[0].pass=0;
 	Pemain[0].waktuTerlewat=0;
 	Pemain[0].menyerah=false;
 	Pemain[0].win=false;
	Pemain[1].score=0;
 	Pemain[1].pass=0;
 	Pemain[1].waktuTerlewat=0;
 	Pemain[1].menyerah=false;
 	Pemain[1].win=false;
	Pemain[0].awalMain=true;
 }
 
 
 // modul menambahNama()
 // untuk menambah nama pemain
 void menambahNama(){
 	int i;
 	char temp[100];
	gotoxy(30, 4);printf("========================================================== \n");
	gotoxy(30, 5);printf("                     NAME OF PLAYER                        \n");
	gotoxy(30, 6);printf("========================================================== \n");
	getchar();
	gotoxy(45, 9);printf("Input name for player 1: ");	
	gets(Pemain[0].nama);
	gotoxy(45, 10);printf("Input name for player 2: ");	
	gets(Pemain[1].nama);
 	system("cls");
 }

 // modul pilihLevel()
 // untuk menentukan level permainan
 int pilihLevel(){
 	int level;
 	gotoxy(30, 4);printf("========================================================== \n");
	gotoxy(30, 5);printf("                      CHOOSE LEVEL                         \n");
	gotoxy(30, 6);printf("========================================================== \n");
	gotoxy(50, 9);printf("1. Easy\n");
	gotoxy(50, 10);printf("2. Medium\n");
	gotoxy(50, 11);printf("3. Hard\n");
 	gotoxy(50, 12);printf("Select level : ");
 	scanf("%d", &level);
 	
 	return level;
 }
 
 // modul giliranBermain()
 // untuk memulai permainan secara bergantian
 void giliranBermain(int level){
	int giliran=-1, i, j, t, batasWaktu;
	double waktuInput;
	int row;
	char col, arah, kata[7], enter;
	bool errorPilih=false;
	system("cls");
	
	batasWaktu=batasWaktuInput(level);
	
	do {
		pass :	
		giliran = (giliran + 1) % 2 ;
		
		// memanggil modul bagikan blok pemain
		blokPemain(giliran);
		
		restart :
		// memanggil modul tampil papan
		tampilPapan();
		
		// // memanggil modul untuk memulai waktu
		if (batasWaktu!=0){
			t = StartTime(); 
		}
		
		if (level==1){
			gotoxy(80,3);printf("Level : Easy"); 	
			gotoxy(80,4);printf("Time  : -");
		} else if (level==2){
			gotoxy(80,3);printf("Level : Medium");
			gotoxy(80,4);printf("Time  : 2 minutes");
		} else {
			gotoxy(80,3);printf("Level : Hard");
			gotoxy(80,4);printf("Time  : 1 minutes");
		}	
		gotoxy(80,5);printf("Remaining block : %d", sisaBlokHuruf());
		gotoxy(80,6);printf("=============================");
		gotoxy(80,8);printf("Score");
		gotoxy(80,9);printf("%s : %d", Pemain[0].nama, Pemain[0].score);
		gotoxy(80,10);printf("%s : %d", Pemain[1].nama, Pemain[1].score);
		
		// memanggil modul tampil keterangan
		tampilKeterangan();
		
		gotoxy(80,25);printf("%s's turn!", Pemain[giliran].nama);
		
		// memanggil modul tampil blok pemain
		tampilBlokPemain(giliran);
		
		// memanggil modul tambah posisi
		tambahPosisi(&row,&col);
		
		// memanggil modul tambah arah
		arah = tambahArah();
		
		if(arah=='P' || arah=='p'){
			pass(giliran);
			goto pass;
		} else if (arah=='G' || arah=='g'){
			menyerah(giliran);
			goto akhir;
		}
		
		tambahHuruf(kata,giliran,row,col,arah);
		if (*kata=='*'){
			system("cls");
			goto restart;
		}
		
		// waktu
		akhir :
		if (batasWaktu!=0){
			t = EndTime() - t; //waktu akhir
			waktuInput = ((double) t)/CLOCKS_PER_SEC; //hitung waktu menjadi detik
			if(waktuInput>batasWaktu){
				gotoxy(posisiX,posisiY);printf("You exceed the time limit for %ds",batasWaktu);
				posisiY++;
				gotoxy(posisiX,posisiY);printf("Your time is %2.fs", waktuInput);
				posisiY++;			
				Pemain[giliran].waktuTerlewat++;
			}
		}
		posisiY++;
		gotoxy(posisiX,posisiY);printf("Press any key to continue!",batasWaktu);
		getch();
		posisiY++;
		system("cls");
	} while(finish(giliran)==false);
	
	if (finish(giliran)==true){
		akhirPermainan(level);
	}
 }
 
 // modul persiapanHuruf()
 // untuk menginisialisasi nilai dari struct huruf
 void persiapanHuruf(){
	infoHuruf[0].huruf='A';
 	infoHuruf[0].poin=1;
 	infoHuruf[0].jumlah=9;
 	infoHuruf[1].huruf='B';
 	infoHuruf[1].poin=3;
 	infoHuruf[1].jumlah=2;
 	infoHuruf[2].huruf='C';
 	infoHuruf[2].poin=3;
 	infoHuruf[2].jumlah=2;
 	infoHuruf[3].huruf='D';
 	infoHuruf[3].poin=2;
 	infoHuruf[3].jumlah=4;
 	infoHuruf[4].huruf='E';
 	infoHuruf[4].poin=1;
 	infoHuruf[4].jumlah=12;
 	infoHuruf[5].huruf='F';
 	infoHuruf[5].poin=4;
 	infoHuruf[5].jumlah=2;
 	infoHuruf[6].huruf='G';
 	infoHuruf[6].poin=2;
 	infoHuruf[6].jumlah=3;
 	infoHuruf[7].huruf='H';
 	infoHuruf[7].poin=4;
 	infoHuruf[7].jumlah=2;
 	infoHuruf[8].huruf='I';
 	infoHuruf[8].poin=1;
 	infoHuruf[8].jumlah=9;
 	infoHuruf[9].huruf='J';
 	infoHuruf[9].poin=8;
 	infoHuruf[9].jumlah=1;
 	infoHuruf[10].huruf='K';
 	infoHuruf[10].poin=5;
 	infoHuruf[10].jumlah=1;
 	infoHuruf[11].huruf='L';
 	infoHuruf[11].poin=1;
 	infoHuruf[11].jumlah=4;
 	infoHuruf[12].huruf='M';
 	infoHuruf[12].poin=3;
 	infoHuruf[12].jumlah=2;
 	infoHuruf[13].huruf='N';
 	infoHuruf[13].poin=1;
 	infoHuruf[13].jumlah=6;
 	infoHuruf[14].huruf='O';
 	infoHuruf[14].poin=1;
 	infoHuruf[14].jumlah=8;
 	infoHuruf[15].huruf='P';
 	infoHuruf[15].poin=3;
 	infoHuruf[15].jumlah=2;
 	infoHuruf[16].huruf='Q';
 	infoHuruf[16].poin=10;
 	infoHuruf[16].jumlah=1;
 	infoHuruf[17].huruf='R';
 	infoHuruf[17].poin=1;
 	infoHuruf[17].jumlah=6;
 	infoHuruf[18].huruf='S';
 	infoHuruf[18].poin=1;
 	infoHuruf[18].jumlah=4;
 	infoHuruf[19].huruf='T';
 	infoHuruf[19].poin=1;
 	infoHuruf[19].jumlah=6;
 	infoHuruf[20].huruf='U';
 	infoHuruf[20].poin=1;
 	infoHuruf[20].jumlah=4;
 	infoHuruf[21].huruf='V';
 	infoHuruf[21].poin=4;
 	infoHuruf[21].jumlah=2;
 	infoHuruf[22].huruf='W';
 	infoHuruf[22].poin=4;
 	infoHuruf[22].jumlah=2;
 	infoHuruf[23].huruf='X';
 	infoHuruf[23].poin=8;
 	infoHuruf[23].jumlah=1;
 	infoHuruf[24].huruf='Y';
 	infoHuruf[24].poin=4;
 	infoHuruf[24].jumlah=2;
 	infoHuruf[25].huruf='Z';
 	infoHuruf[25].poin=10;
 	infoHuruf[25].jumlah=1;
 	infoHuruf[26].huruf='_';
 	infoHuruf[26].poin=0;
 	infoHuruf[26].jumlah=2;
 }
 
 // modul persiapanPapan()
 // untuk menginisialisasi papan
 /*
 	Mengisi seluruh papan dengan spasi yang berarti papan masih kosong
 	Mengisi keterangan bonus pada setiap posisi papan
 	bonus = 1 --> 2 letter
 	bonus = 2 --> 3 letter
 	bonus = 3 --> 2 word
 	bonus = 4 --> 3 word
 */
 void persiapanPapan(){
 	int i, j;
 	for (i=0; i<15; i++){
		for (j=0; j<15; j++)
        {
            infoPapan[i][j].bonus = 0;
            infoPapan[i][j].huruf = ' ';
            if ((i==0 || i==7 || i==14) && (j==0 || j==7 || j==14) && !(i==7 && j==7))
                infoPapan[i][j].bonus = 4;
            else if ((i==5 || i==9) && ((j-1)%4==0))
                infoPapan[i][j].bonus = 2;
            else if ((j==5 || j==9) && ((i-1)%4==0))
                infoPapan[i][j].bonus = 2;
            else if ((i==6 || i==8) && (j==2 || j==6 || j==8 || j==12))
                infoPapan[i][j].bonus = 1;
            else if ((j==6 || j==8) && (i==2 || i==6 || i==8 || i==12))
                infoPapan[i][j].bonus = 1;
            else if ((i==3 || i==11) && (j==0 || j==7 || j==14))
                infoPapan[i][j].bonus = 1;
            else if ((j==3 || j==11) && (i==0 || i==7 || i==14))
                infoPapan[i][j].bonus = 1;
            else if ((i==j || i==(14-j)) && !(i==7 && j==7))
                infoPapan[i][j].bonus = 3;
        }
	}
 }
 
 // modul tampilPapan()
 // untuk menampilkan papan
 void tampilPapan(){
 	int i, j,a,b;
 	printf("\n\n\n");
 	printf("        ");
 	for (i = 0; i<15;i++){
 		printf("   %c",i+0x41);
 	}
 	printf("\n         +");
	for(b=0;b<15;b++){
 		printf("---+");
	 }
 	for (i = 0; i<15;i++){
	 	printf("\n      %d ",i+1);
	 	if (i>=0 && i<=8){
	 		printf(" ");
		}
		printf ("|");
	 	for (j = 0; j<15; j++){
	 		if (infoPapan[i][j].bonus==4){
	 			printf("+");
			} else if (infoPapan[i][j].bonus==3) {
				printf("~");
			} else if (infoPapan[i][j].bonus==2) {
				printf("^");
			} else if (infoPapan[i][j].bonus==1) {
				printf("`");
			} else if (i==7 && j==7){
				printf("*");
			} else {
				printf(" ");
			}
	 		printf("%c |", infoPapan[i][j].huruf);
		}
		printf(" %d",i+1);
		printf("\n         +");
		for(a=0;a<15;a++){
 			printf("---+");
	 	}
		
	}
	printf("\n        ");
	for (i = 0; i<15;i++){
 		printf("   %c",i+0x41);
 	}
 }
 
 // modul blokPemain()
 // untuk memberikan dan mengacak blok pemain
 void blokPemain(int giliran){
 	int i, j, idx=0, jml, total, jumlahBlokPemain;
	char temp, ran;	
 	char kantongHuruf[100];
 	
 	// mencari jumlah huruf tiap pemain saat ini
 	jumlahBlokPemain=strlen(Pemain[giliran].blokHuruf);
 	
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
	
    // random kantong huruf
    for (i=0;i<total;i++) {
        int p1 = rand() % total;
        int p2 = rand() % total;
        int temp = kantongHuruf[p1];
        kantongHuruf[p1] = kantongHuruf[p2];
        kantongHuruf[p2] = temp;
    }
 	
 	// memasukan huruf ke blok pemain
    for (i=0; i<7; i++) { 
        ran = 'A' + rand() % 26;
        temp = kantongHuruf[i]; 
    	Pemain[giliran].blokHuruf[i]=temp;    	
	}
 }
 
 // modul tampilBlokPemain()
 // untuk menampilkan 7 blok pemain
 /*
 	Contoh : 
 	+---+---+---+---+---+---+---+
 	| A | I | B | J | N | U | D |
 	+---+---+---+---+---+---+---+
 */
 void tampilBlokPemain(int giliran){
 	int i,a=10,b,x,y;
 	
 	gotoxy(80, 12);printf("Letter Block");
 	x=80;
	if(a==10){
		gotoxy(x, 13);printf("+");
		x++;
 	}
	for(a=0;a<7;a++){
 		gotoxy(x, 13);printf("---+");
 		x+=4;
	}
	x=80;
 	gotoxy(x, 14);printf("|");
 	x+=2;
 	for(i=0;i<strlen(Pemain[giliran].blokHuruf);i++){
 		gotoxy(x, 14);printf("%c", Pemain[giliran].blokHuruf[i]);
 		x+=2;
 		gotoxy(x, 14);printf("%|");
		x+=2;
	}
	x=80;
	a=10;
	if(a==10){
		gotoxy(x, 15);printf("+");
 		x+=1;
	}
	for(a=0;a<7;a++){
 		gotoxy(x, 15);printf("---+");
 		x+=4;
	}
 }
 
 // modul tampilKeterangan()
 // untuk menampilkan informasi keterangan saat bermain
 /*
 	Deskripsi bonus papan :
 	` --> 2 letter
	^ --> 3 letter
	~ --> 2 word
	+ --> 3 word
 	
 	Deskripsi fitur permainan yang bisa diinput pada saat memasukan arah
 	H --> Horizontal
	V --> Vertikal
	P --> Pass
	G --> Give Up
 */
 void tampilKeterangan(){
 	int i, x;
 	gotoxy(80,17);printf("=============================");
	gotoxy(80,18);printf("Description : ");
	gotoxy(80,19);printf("` : 2 letter   H : Horizontal");
	gotoxy(80,20);printf("^ : 3 letter   V : Vertikal");
	gotoxy(80,21);printf("~ : 2 word     P : Pass");
	gotoxy(80,22);printf("+ : 3 word     G : Give Up");
	gotoxy(80,23);printf("=============================");
 }
 
 // modul tambahPosisi()
 // untuk menambahkan posisi awal saat menginputkan kata
 /*
 	Contoh :
 	Ingin menambahkan kata di posisi baris : 8 dan kolom : H
 	Maka inputkan dengan format : 8H
 */
 void tambahPosisi(int *row, char *col){
 	int rowT;
 	char colT;
 	posisiX=80;
 	posisiY=27;
 	
 	add:
	gotoxy(posisiX,posisiY);printf("Insert Row & Column (ex : 8H) : "); 
	scanf("%d%c", &rowT, &colT);
	getchar();
	posisiY++;
	
	if(cekPosisi(rowT, colT)==false){
		gotoxy(posisiX,posisiY);printf("Wrong input!");
		posisiY++;
		goto add;
	} else {
		*row=rowT;
		*col=colT;
	}
 }

 // modul cekPosisi()
 // untuk mengecek kevalidan inputan posisi
 /*
 	Baris yang dimasukan harus berada diantara angka 1-15
 	Kolom yang dimasukan harus berada diantara huruf A-O
 */
 bool cekPosisi(int row, char col){
 	bool cek=false;
 	
 	if(row>=1 && row<=15){
 		if (col>=65 && col<=79 || col>=97 && col<=111){
	 		cek = true;
	 	}
	 }
	 return cek;
 }
 
 // modul tambahArah()
 // untuk mengecek kevalidan inputan arah
 /*
 	Pada modul ini tidak hanya bisa memasukan arah saat ingin menginput teks
 	1. H --> Menginputkan kata secara horizontal
 	2. V --> Menginputkan kata secara vertikal
 	3. P --> Memilih opsi pass (skip giliran bermain)
 	4. G --> Memilih opsi give up (menyerah)
 */
 char tambahArah(){
 	char arah;
 	posisiY++;
 	
 	add :
 	gotoxy(posisiX,posisiY);printf("Insert direction (H/V/P/G) : ");
 	scanf("%c", &arah);
 	fflush(stdin);
 	posisiY++;
 	
 	if (arah=='P' || arah=='G' || arah=='p' || arah=='g'){
 		return arah;
	} else if (cekArah(arah)==true){
 		return arah;
 	} 
 	else {
 		gotoxy(posisiX,posisiY);printf("wrong input!\n");
 		posisiY++;
 		goto add;
	}
 }
 
 // modul cekArah()
 // untuk mengecek inputan user tentang arah penginputan kata
 /*
 	H / h --> untuk arah horizontal
 	V / v --> untuk arah vertikal
 */
 bool cekArah(char arah){
 	char dir;
 	if (arah=='H' || arah=='V' || arah=='h' || arah=='v'){
 		return true;
	} 
	else {
		return false;
	}
 }
 
 // modul tambahHuruf()
 // untuk menerima inputan huruf dan akan di cek ke validannya dengan memanggil modul modul lain
 void tambahHuruf(char *kata, int giliran, int row, char col, char arah){
 	char kataBaru[100]={0};
	bool hasil_cekHuruf, hasil_cekAdaHuruf, hasil_cekKata;
	int poin, mulaiKata, kolom;
	kolom=kolomKeAngka(col);
 	
 	posisiY++;
 	
	add :
	gotoxy(posisiX,posisiY);printf("Input letter (*->restart) : ");
	posisiY++;
	scanf("%s", *&kata);
	if (*kata!='*'){
		hasil_cekHuruf=cekHuruf(kata, giliran);
		hasil_cekAdaHuruf=cekAdaHuruf(kata, row, col, arah);
		if (hasil_cekHuruf==false || hasil_cekAdaHuruf==false){
			gotoxy(posisiX,posisiY);printf("Wrong input!\n");
			posisiY++;
			goto add;
		}
		
		blokKosong(kata);
		kataTerbentuk(kata, row, col, arah, kataBaru, &mulaiKata);
		if (*kataBaru=='*'){
			gotoxy(posisiX,posisiY);printf("Wrong input!\n");
			posisiY++;
			goto add;
		}
		
		// pengecekan awal permainan
		cekAwalMain(kata, row, col, arah);
		if (Pemain[0].awalMain==true && cekAwalMain(kata, row, col, arah)==false){
			gotoxy(posisiX,posisiY);printf("You have to input word in the center!\n");
			posisiY++;
			goto add;
		}
		else {
			tambahKePapan(kata, row, col, arah);
			hapusBlokPemain(kata);
			strcpy(kata,kataBaru);
			gotoxy(posisiX,posisiY);printf("word : %s\n", kata);
			posisiY++;
			poin=akumulasiPoin(kata, giliran, mulaiKata, row, kolom, arah);
			gotoxy(posisiX,posisiY);printf("You get %d point!\n", poin);
			posisiY++;
			Pemain[giliran].score=poin+Pemain[giliran].score;
		}
	}
 }
 
 // modul cekHuruf()
 // untuk mengecek apakah inputan user ada di blok pemain atau tidak
 /*
 	jika blok pemain berisi --> A | B | E | O | P | D | N
	Lalu pemain menginputkan huruf AND maka akan memberikan keluaran true
	namun jika pemain menginputkan huruf NET maka akan memberikan keluaran false karena T tidak ada di blok pemain
 */
 bool cekHuruf(char *kata, int giliran){
 	int i,j,jumlahSama=0;
	bool ketemu, hasil=false;
 	for (i=0;i<strlen(kata);i++){
 		ketemu=false;
 		for (j=0;j<strlen(Pemain[giliran].blokHuruf) && ketemu==false;j++){
 			if(kata[i]==Pemain[giliran].blokHuruf[j]){
 				jumlahSama++;
 				ketemu=true;
			}
		}
	}
	if(jumlahSama==strlen(kata)){
		hasil=true;
	}
	return hasil;
 }
  
 // modul kataTerbentuk()
 // untuk menentukan kata yang terbentuk dari inputan yang dimasukan oleh pemain
 /*
 	Papan : A | N | D
	Lalu pemain ingin menambahkan dua huruf dibawah A yaitu huruf NT
	--> A | N | D
	    N
	    T
	maka kata yang terbentuk adalah ANT
 */
 void kataTerbentuk(char *kata, int row, char col, char arah, char *kataBaru, int *mulaiKata){
 	int i=1, j, akhir, kolom, batas, idxKata, mulai;
 	bool hasil_cekKamus=false, hasil_cekPapan=false;
 	char kata1[100]={0};
	
	kolom = kolomKeAngka(col);
	batas=strlen(kata);
	idxKata=0;
	if (arah=='V' || arah=='v'){
		// mencari mulai kata terbentuk dari arah atas
		mulai=row-1;
 		while(infoPapan[row-i-1][kolom].huruf!=' ' && row-i-1>=0){
 			mulai=row-i-1;
			i++;
		}
		i=0;
		
		// memasukan kedalam variabel kata terbentuk
		while(infoPapan[mulai+i][kolom].huruf!=' '){
			kata1[i]=infoPapan[mulai+i][kolom].huruf;
			akhir=mulai+i;
			i++;
		}
		for (j=0;j<batas;j++){
			if (infoPapan[row-1+j][kolom].huruf!=' '){
				kata1[i]=infoPapan[row-1+j][kolom].huruf;
				batas++;	
			}
			else {
				kata1[i]=kata[idxKata];
				idxKata++;
			}
			i++;
			akhir=mulai+i;
		}
		j=0;
		
		// mencari akhir kata terbentuk dan memasukan ke variabel kata terbentuk
		while(infoPapan[akhir+j][kolom].huruf!=' ' && akhir+j<15){
			kata1[i]=infoPapan[akhir+j][kolom].huruf;
			j++;
		}
	}
	else {
		// mencari mulai kata terbentuk dari arah atas
		mulai=kolom;
 		while(infoPapan[row-1][kolom-i].huruf!=' ' && kolom-i>=0){
 			mulai=kolom-i;
			i++;
		}
		
		// memasukan kedalam variabel kata terbentuk
		i=0;
		while(infoPapan[row-1][mulai+i].huruf!=' '){
			kata1[i]=infoPapan[row-1][mulai+i].huruf;
			akhir=mulai+i;
			i++;
		}
		for (j=0;j<batas;j++){
			if (infoPapan[row-1][kolom+j].huruf!=' '){
				kata1[i]=infoPapan[row-1][kolom+j].huruf;
				batas++;
			} else {
				kata1[i]=kata[idxKata];
				idxKata++;
			}
			i++;
			akhir=mulai+i;
		}
		j=0;
		
		// mencari akhir kata terbentuk dan memasukan ke variabel kata terbentuk
		while(infoPapan[row-1][akhir+j].huruf!=' '){
			kata1[i]=infoPapan[row-1][akhir+j].huruf;
			j++;
		}
	}
	
	// mengecek hasil kata terbentuk ke kamus
	hasil_cekKamus=cekKamus(kata1);
	
	// mengecek apakah kata yang terbentuk masih berada dalam papan 
	// yaitu baris antara 1-15 dan kolom antara A-O
	hasil_cekPapan=cekPosisiPapan(akhir);
	if (hasil_cekKamus==true && hasil_cekPapan==true){
		strcpy(kataBaru,strupr(kata1));
		*mulaiKata=mulai;
	} else {
		strcpy(kataBaru,"*");
	}
 }
 
 // modul cekAwalMain()
 // cek mulai permainan berada di posisi tengah atau tidak
 bool cekAwalMain(char *kata, int row, char col, char arah){
 	int i, j, kolom;
 	bool cek=false;

 	kolom=kolomKeAngka(col);
 	for (i=0;i<strlen(kata) && cek==false;i++){
 		if (arah=='V' || arah=='v'){
	 		if(row+i-1==7 && kolom==7){
	 			cek=true;
			}
		} 
		else {
			if(row-1==7 && kolom+i==7){
	 			cek=true;
			}
		}
	}
	return cek;
 }
 
 // modul cekAdaHuruf
 // untuk mengecek saat menginputkan kata harus berdeketan dengan kata lain di papan
 bool cekAdaHuruf(char *kata, int row, char col, char arah){
 	int i, j, kolom, batas;
 	bool cek=false;
 	
 	kolom=kolomKeAngka(col);
 	batas=strlen(kata);
 	// pengecualian untuk awal permainan
 	if (Pemain[0].awalMain==true){
 		cek=true;
	} 
	// pengecekan apakah kata yang diinput sudah berdekatan dengan kata sebelumnya
	else {
	 	if (arah=='V' || arah=='v'){
	 		for (i=0;i<=batas+1;i++){
		 		if (infoPapan[row-2+i][kolom].huruf!=' '){
		 			cek=true;
				}
			}
		} 
		else {
			for (i=0;i<=batas+1;i++){
				if (infoPapan[row-1][kolom+i-1].huruf!=' '){
					cek=true;
				}
			}
		}
	}
	return cek;
 }
 
 // modul blokKosong()
 // untuk mencari apakah ada blok kosong yang diinputkan pemain, lalu pemain akan diminta memilih satu huruf dari A-Z
 /*
 	Contoh : pemain menginputkan ingin menginputkan kata PAN namun ia hanya memiliki blok PA dan _ (blok kosong)
 	maka --> pemain dapat menginputkan PA_, lalu sistem akan meminta pemain untuk memilih satu huruf
 */
 void blokKosong(char *kata){
 	int i, j;
	char ganti;
	bool kurang=false;
 	
 	for (i=0;i<strlen(kata);i++){
 		if(kata[i]=='_'){
 			gotoxy(posisiX,posisiY);printf("Input the letter you want (A-Z) : ");
 			posisiY++;
 			scanf(" %c", &kata[i]);
 			infoHuruf[26].jumlah--;
 			/*
			 	menambah satu ke jumlah huruf yang diinputkan agar nanti saat di hapus 
				pada proses selanjutnya jumlah huruf yang terpakai tidak berkurang
 				contoh : menggunakan _ dan memilih huruf A, maka jumlah huruf A akan 
				ditambah satu dulu sehingga saat A sudah dipakai dan dikurangi jumlahnya
 				akan sama dengan sebelum dikurang
 			*/
 			for(j=0;j<27 && kurang==false;j++){
 				if (infoHuruf[j].huruf==kata[i]){
 					infoHuruf[j].jumlah--;
 					kurang=true;
				}
			}
		}	
	}
 }
 
 // modul cekPosisiPapan()
 // cek apakah kata yang diinputkan cukup didalam papan atau tidak
 /*
 	Kata yang akan diinputkan tidak boleh lebih dari 15 yaitu variabel akhir
 */
 bool cekPosisiPapan(int akhir){
 	int i=0;
 	bool cek=true;
	if(akhir>15){
		cek=false;
		gotoxy(posisiX,posisiY);printf("Wrong Input!\n");
		posisiY++;
	}
	
	return cek;
 }
 
 // modul tambahKePapan()
 // setelah semua kata yang terbentuk diperiksa dan valid maka kata akan ditambahkan ke papan
 void tambahKePapan(char *kata, int row, char col, char arah){
 	int i, kolom, batas, idxKata;
 	
 	kolom = kolomKeAngka(col);
 	batas=strlen(kata);
 	idxKata=0;
 	if (arah=='H' || arah=='h'){
	 	for(i=0;i<batas;i++){
	 		if (infoPapan[row-1][kolom+i].huruf==' '){
 				infoPapan[row-1][kolom+i].huruf=kata[idxKata];
 				idxKata++;
			} else {
				batas++;
			}
		}
	} 
	else {
		for(i=0;i<batas;i++){
			if (infoPapan[row-1+i][kolom].huruf==' '){
 				infoPapan[row-1+i][kolom].huruf=kata[idxKata];
 				idxKata++;
			} else {
				batas++;
			}
		}
	}
	Pemain[0].awalMain=false;
 }
 
 // modul kolomKeAngka
 // untuk memberikan nilai kolom dari inputan huruf
 int kolomKeAngka(char col){
 	int kolom;
 	
	// mengubah huruf ke angka untuk kolom
 	switch(col){
 		case 'A' : kolom=0; break;
 		case 'a' : kolom=0; break;
 		case 'B' : kolom=1; break;
 		case 'b' : kolom=1; break;
 		case 'C' : kolom=2; break;
 		case 'c' : kolom=2; break;
 		case 'D' : kolom=3; break;
 		case 'd' : kolom=3; break;
 		case 'E' : kolom=4; break;
 		case 'e' : kolom=4; break;
 		case 'F' : kolom=5; break;
 		case 'f' : kolom=5; break;
 		case 'G' : kolom=6; break;
 		case 'g' : kolom=6; break;
 		case 'H' : kolom=7; break;
 		case 'h' : kolom=7; break;
 		case 'I' : kolom=8; break;
 		case 'i' : kolom=8; break;
 		case 'J' : kolom=9; break;
 		case 'j' : kolom=9; break;
 		case 'K' : kolom=10; break;
 		case 'k' : kolom=10; break;
 		case 'L' : kolom=11; break;
 		case 'l' : kolom=11; break;
 		case 'M' : kolom=12; break;
 		case 'm' : kolom=12; break;
 		case 'N' : kolom=13; break;
 		case 'n' : kolom=13; break;
 		case 'O' : kolom=14; break;
 		case 'o' : kolom=14; break;
	}
	
	return kolom;
 }
 
 // modul akumulasiPoin()
 // untuk menghitung akumulasi poin
 /*
 	modul akan mencari poin tiap huruf dan mencari bonus dari posisi papan yang ditempati huruf
 */
 int akumulasiPoin(char *kata, int giliran, int mulaiKata, int row, int kolom, char arah){
	int poin=0, i, j, dw=0, tw=0, tempPoin=0;
 	bool ketemu;
 	
	row--;
 	
 	for(i=0;i<strlen(kata);i++){
 		tempPoin=poinHuruf(toupper(kata[i]));
 		if (arah=='H' || arah=='h'){
 			if(infoPapan[row][mulaiKata+i].bonus==1){
 				// point 2 letter
 				tempPoin=tempPoin+poinHuruf(toupper(kata[i]));	
			} else if (infoPapan[row][mulaiKata+i].bonus==2){
				// point 3 letter
				tempPoin=tempPoin+2*(poinHuruf(toupper(kata[i])));
			} else if (infoPapan[row][mulaiKata+i].bonus==3){
				// point 2 word
				dw++;
			} else if (infoPapan[row][mulaiKata+i].bonus==4){
				// point 3 word
				tw++;
			}
		}
		else{
 			if(infoPapan[mulaiKata+i][kolom].bonus==1){
 				// point 2 letter
 				tempPoin=tempPoin+poinHuruf(toupper(kata[i]));	
			} else if (infoPapan[mulaiKata+i][kolom].bonus==2){
				// point 3 letter
				tempPoin=tempPoin+2*(poinHuruf(toupper(kata[i])));
			} else if (infoPapan[mulaiKata+i][kolom].bonus==3){
				// point 2 word
				dw++;
			} else if (infoPapan[mulaiKata+i][kolom].bonus==4){
				// point 3 word
				tw++;
			}
		}
		poin=poin+tempPoin;
	}
	
	if (dw>0){
		for(j=0;j<dw;j++){
			poin=poin+poin;				
		}
	} else if (tw>0){
		for(j=0;j<tw;j++){
			poin=poin+2*(poin);				
		}
	}
	
	return poin;
 }
 
 // modul poinHuruf()
 // untuk menentukan poin dari tiap huruf
 int poinHuruf(char huruf){
 	int i, poin=0;
	bool ketemu=false;
	
 	for(i=0;i<27 && ketemu==false;i++){
 		if(huruf==infoHuruf[i].huruf){
 			poin=poin+infoHuruf[i].poin;
			ketemu=true;
		}	
	}
	
	return poin;
 }
 
 // modul hapusBlokPemain()
 // menghapus jumlah huruf yang sudah ditambahkan ke blok pemain
 void hapusBlokPemain(char *kata){
	int i,j;
 	for (i=0;i<strlen(kata);i++){
	   	for (j=0; j<27; j++){
	   		if(infoHuruf[j].huruf==kata[i]){
	   			infoHuruf[j].jumlah--;	
			}
		}
	}
 }
 
 // modul sisaBlokHuruf()
 // untuk menentukan sisa blok huruf keseluruhan dalam satu game
 int sisaBlokHuruf(){
 	int i, j, total=0;
 	for (i=0;i<27;i++){
 		total=total+infoHuruf[i].jumlah;
	}
	
	return total;
 }
 
 // modul cekKamus()
 // untuk menentukan apakah kata yang terbentuk ada di kamus atau tidak
 // referensi : https://www.codingunit.com/c-tutorial-searching-for-strings-in-a-text-file
 bool cekKamus(char *kata){
 	char cekKata[100];
 	int num;
 	bool ada=false;
 	FILE *in_file = fopen("kamus.txt", "r");
	
	if (in_file == NULL)
	{
	    gotoxy(posisiX,posisiY);printf("Error file missing\n");
	    posisiY++;
	    exit(-1);
	}
	
	while(ada==false && !feof(in_file))
	{
        fscanf(in_file,"%s", cekKata);
        if(strcmp(cekKata, strlwr(kata))==0){ // kondisi jika kata yang dicari ada di kamus
			ada = true;
		}
	}
	return ada;
 }
 
 // Modul pass()
 // untuk menambah jumlah pass pemain jika memilih opsi pass
 void pass(int giliran){
 	Pemain[giliran].pass++;
    system("cls");
 }
 
 // Modul menyerah()
 // untuk menambah jumlah menyerah pemain jika memilih opsi menyerah
 void menyerah(int giliran){
 	Pemain[giliran].menyerah=true;
 }
 
 // Modul Finish()
 // Modul untuk menentukan kondisi finish
 /*
 	Jika salah satu pemain menghabiskan blok nya atau ada yang memilih opsi menyerah
 */
 bool finish(int giliran){
 	int hasil;
 	if (sisaBlokHuruf()==0){
 		hasil=true;
	} else if(Pemain[giliran].menyerah==true) {
		hasil=true;
	} else {
		hasil=false;
	}
 	
 	return hasil;
 }
 
 // Modul Pemenang()
 // Modul yang digunakan untuk menentukan pemenang dari perolehan skor tertinggi
 void pemenang(){
 	if (Pemain[0].score==Pemain[1].score){
 		Pemain[0].win=true;
 		Pemain[1].win=true;
	} else if (Pemain[0].score>Pemain[1].score){
		Pemain[0].win=true;
	} else {
		Pemain[1].win=true;
	}
 }
 
 // Modul akhirPermainan()
 // Modul yang akan menampilkan akhir permainan
 void akhirPermainan(int level){
 	system("cls");
 	gotoxy(35,10);printf("+--- +---+ +-+ +-+ +--    +--+ +     + +--  +--+ ");
	gotoxy(35,11);printf("|    |   | | | | | |      |  |  |   |  |    |  |");
	gotoxy(35,12);printf("| __ |---| |  +  | +--    |  |   | |   +--  +--+");
	gotoxy(35,13);printf("|__| |   | |     | +__    +--+    +    +__  | |");
	gotoxy(45,18);printf("Press any key to continue");
	getch();
	tampilPemenang(level);
	inputHighScore();
 }
 
 // Modul poinAkhir()
 // Modul yang digunakan untuk menentukan akumulasi poin
 void poinAkhir(int level){
 	int i, penalty;
 	
 	// penentuan poin penalty masing-masing level
 	if (level==1){
 		penalty=1;	
	} else if (level==2){
		penalty=3;
	} else {
		penalty=5;
	}
 	
 	// pengurangan poin ke pemain 1
	for(i=0;i<Pemain[0].pass;i++){
	 	Pemain[0].score=Pemain[0].score-penalty;
	}
	for(i=0;i<Pemain[0].waktuTerlewat;i++){
	 	Pemain[0].score=Pemain[0].score-penalty;
	}
		
	// pengurangan poin ke pemain 2
	for(i=0;i<Pemain[1].pass;i++){
	 	Pemain[1].score=Pemain[1].score-penalty;
	}
	for(i=0;i<Pemain[1].waktuTerlewat;i++){
		Pemain[1].score=Pemain[1].score-penalty;
	}
 }
 
 // modul poinMenyerah
 // untuk menambahkan sisa poin pada blok huruf ke pemain yang tidak memilih menyerah
 /*
 	contoh :
 	jika pemain 1 menyerah dan pada permain bersisa beberapa huruf yang ditotalkan menjadi 11 poin
 	maka 11 poin tersebut akan dimasukan ke poin pemain 2
 */
 void poinMenyerah(){
 	int i, j, poinTambahan=0, jml;
	if(sisaBlokHuruf()==0){
 		gotoxy(35,19);printf("There is no letter left");
	} else {
		// mencari total poin tambahan dari sisa blok yang ada
		// contoh : terdapat sisa huruf A satu, dan C satu. Maka akumulasi poin tambahan adalah poin A=1+C=1 => 2
		for (i=0;i<27;i++){
	 		jml=infoHuruf[i].jumlah;
	 		if (jml!=0){
	 			for (j=0;j<jml;j++){
	 				poinTambahan=poinTambahan+infoHuruf[i].poin;
	 			}
			}	
		}	
		gotoxy(35,19);printf("There are %d points for players who don't give up", poinTambahan);
		// tambahan poin diberikan kepada pemain yang tidak menggunakan fitur menyerah
		if (Pemain[0].menyerah==true){
			Pemain[1].score=Pemain[1].score+poinTambahan;
		} else {
			Pemain[0].score=Pemain[0].score+poinTambahan;
		}
	}
 }

 // Modul tampilPemenang()
 // Modul yang digunakan menampilkan pemenang
 void tampilPemenang(int level){
 	int y;
	system("cls");
 	gotoxy(35,3);printf("===================================================");
	gotoxy(35,4);printf("                       GAME OVER");
	gotoxy(35,5);printf("===================================================");

	gotoxy(35,7);printf("Temporary score : ");	
	gotoxy(35,8);printf("%s: %d", Pemain[0].nama, Pemain[0].score);
	gotoxy(35,9);printf("%s: %d", Pemain[1].nama, Pemain[1].score);
		
	gotoxy(35,11);printf("Number of Passes : ");
	gotoxy(35,12);printf("%s: %d", Pemain[0].nama, Pemain[0].pass);
	gotoxy(35,13);printf("%s: %d", Pemain[1].nama, Pemain[1].pass);
		
	gotoxy(35,15);printf("Number of Time Elapsed : ");
	gotoxy(35,16);printf("%s: %d", Pemain[0].nama, Pemain[0].waktuTerlewat);
	gotoxy(35,17);printf("%s: %d", Pemain[1].nama, Pemain[1].waktuTerlewat);
	
	// menghitung poin akhir dengan mengurangi penalty jika ada
	poinAkhir(level);
	
	y=19;
	if (Pemain[0].menyerah==true || Pemain[1].menyerah==true){ // mengecek apakah ada pemain yang menyerah
		poinMenyerah();
		y=21;
	}
	
	gotoxy(35,y);printf("Final score : ");	
	y++;
	gotoxy(35,y);printf("%s: %d", Pemain[0].nama, Pemain[0].score);
	y++;
	gotoxy(35,y);printf("%s: %d", Pemain[1].nama, Pemain[1].score);
	y+=2;
	
	// dari poin yang sudah final maka akan dicari pemenang
	pemenang();
	if (Pemain[0].win==true && Pemain[1].win==true){
		gotoxy(35,y);printf("===================================================");
		y++;
		gotoxy(35,y);printf("Draw!");
		y++;
		gotoxy(35,y);printf("There is no winner");
		y+=2;
	}
	else if (Pemain[0].win==true){
		gotoxy(35,y);printf("The winner is %s!!!", Pemain[0].nama);
		y+=2;
	} else {
		gotoxy(35,y);printf("The winner is %s!!!", Pemain[1].nama);
		y+=2;
	}
	
	gotoxy(50,y);printf("Press any key to continue");
	getch();
	
 }

 // Modul StartTime()
 // Modul untuk mencatat waktu pertama dihitung
 int StartTime(){
    clock_t startInput;
    startInput = clock();

    return startInput;
 }

 // Modul EndTime()
 // Modul untuk mencatat waktu terakhir dihitung
 int EndTime(){
    clock_t endInput;
    endInput = clock();

    return endInput;
 }
 
 // Modul batasWaktuInput()
 // Modul untuk menentukan batas waktu input tiap level
 int batasWaktuInput(int level){
 	int waktu;
 	switch(level){
 		case 1 : waktu=0; break; // untuk level 1/easy tidak ada batas waktu
 		case 2 : waktu=120; break; // untuk level 2/medium ada 2 menit batas waktu
 		case 3 : waktu=60; break; // untuk level 3/hard ada 1 menit batas waktu
	}
	return waktu;
 }
 
 // Modul tampilExit()
 // Modul yang digunakan untuk menampilkan tampilan exit
 void tampilExit(){
 	system("cls");
 	gotoxy(40,10);printf("   +---+   |   |   +---       ^_______^   ");
	gotoxy(40,11);printf("   |   /    | |    |          | 0   0 |   ");
	gotoxy(40,12);printf("   |--+      +     +---        =  u  =    ");
	gotoxy(40,13);printf("   |   |     |     |         +|-------|+  ~~~ ");
	gotoxy(40,14);printf("   +---+     |     +---       |_______|   ");
	gotoxy(40,15);printf(" _________________________     +     +    ");
	printf("\n\n\n\n\n\n\n\n");
 }
 
 // modul inputHighScore()
 // modul untuk menambahkan score pemain saat permainan sudah berakhir
 // referensi : https://youtu.be/1lNL31q4T5I
 void inputHighScore(){	
	int i, n=2;
	highscore *s;
	
	FILE *fp;
	
	s=(highscore*)calloc(n, sizeof(highscore));	
	fp = fopen("highscore.dat", "a");
    
    if (fp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open 'highscore.dat' file.\n");
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }
	
	for(i=0;i<2;i++){
		strcpy(s[i].nama,Pemain[i].nama);
		s[i].score=Pemain[i].score;
		fwrite(&s[i],sizeof(highscore),1,fp);
	}
	fclose(fp);
 }
 
 // modul tampilHighScore()
 // menampilkan 10 pemain dengan skor tertinggi
  // referensi : https://youtu.be/1lNL31q4T5I
 void tampilHighScore(){
 	int i, j, n, x, y;
	highscore *s, s1;
	
	FILE *fp;
	fp = fopen("highscore.dat", "r");
	fseek(fp,0,SEEK_END);
	n=ftell(fp)/sizeof(highscore);
	s=(highscore*)calloc(n, sizeof(highscore));	
    
    if (fp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open 'highscore.dat' file.\n");
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }
    
    rewind(fp);
	for(i=0;i<n;i++){
		fread(&s[i],sizeof(highscore),1,fp);
	}
	
	// mengurutkan highscore
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			if(s[j].score>s[i].score){
				s1=s[i];
				s[i]=s[j];
				s[j]=s1;
			}
			
		}
	}
 	
 	x=40;
 	y=4;
 	gotoxy(x,y);printf("===================================");
 	y++;
 	gotoxy(x,y);printf("             HIGH SCORE");
 	y++;
 	gotoxy(x,y);printf("===================================");
 	y+=3;
 	gotoxy(x,y);printf("Nama");
 	gotoxy(x+30,y);printf("Score");
 	y++;
 	gotoxy(x,y);printf("-----------------------------------");
 	y++;
 	// menampilkan 10 data teratas yang sudah terurut
	for(i=0;i<10;i++){
		gotoxy(x,y);printf("%s", s[i].nama);
		gotoxy(x+30,y);printf("%d", s[i].score);
		y++;
	}
	fclose(fp);
	
	y+=2;
	gotoxy(45,y);printf("Press any key to back");
	getch();
 }