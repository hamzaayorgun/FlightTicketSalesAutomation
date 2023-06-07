#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int matris[10][15][4];
int sira = 15 , koltuk=4;

//Ucak durumu dosyalarini okuma
int oku(){
	fflush(stdin);
	
	FILE *fp;
	
	char dosya[20];
	char num[2];
	int i , j ,k , sayi;
	for(i = 1; i<=10; i++){
		
		strcpy(dosya, "dosyalar\\UcakDurumu");
		itoa(i, num, 10);            // itoa = Integer TO Ascii, sayi 10'luk tabanda oldugu icin son parametre 10   
		strcat(dosya, num);
		strcat(dosya, ".txt");
		
		fp = fopen(dosya, "r");
		if(fp == NULL)
			printf("hata");
			
		for(j=0; j<15; j++){
			for(k=0; k<4; k++){
				fscanf(fp, "%d", &sayi);
				matris[i-1][j][k] = sayi;
			}
		}
	}
			
	fclose(fp);		
	anamenu();
}

//Musteri yapisi tanımlama
typedef struct musteriler{
	char ad[50];
	char soyad[50];
	double tc;
	int koltukNumarasi;
}musteri;

//Ana menü işlem seçimi
int anamenu(){
	fflush(stdin);
	system("cls");	
	printf("		Yorgun Hava Yollari\n");
	int islemNumarasi; 
	printf("\n\n1-Ucak Durumunu Goster\n2-Bilet Satisi\n3-Bilet Iptal\n4-Kisi Arama\n5-Cikis\n\n");
	printf("Yapmak istediginiz islemi seciniz:"); 
	scanf("%d" , &islemNumarasi); // Ekranda görünen işlem seçimi
	switch(islemNumarasi){
		case 1: durum();
				break;
		case 2: satis();
				break;
		case 3: iptal();
				break;
		case 4: arama();
				break;
		case 5: system("cls");
				exit(0);
		default : printf("HATALI GIRISI YAPTINIZ.\nTEKRAR GIRMEK ICIN HERHANGI BIR TUSA BASINIZ."); 
				getch();
				main();	
	}
}

//Uçak Koltuk Durumu
int durum(){
	fflush(stdin);
	
	system("cls");
	printf("		Yorgun Hava Yollari\n\n");
	FILE*fp; // Seferlerin gösterilmesi >>
	fp = fopen("dosyalar\\Hatlar.txt", "r");
	if(fp == NULL){
		printf("dosya acmada hata oldu.");
		exit(1);
	}
	
	int seferSirasi , hatNo;
	char Nereden[100] ,  Nereye[100] ;
	while(! feof(fp)){ 
		fscanf(fp , " %d %d %s %s " , &seferSirasi, &hatNo, Nereden , Nereye );
		printf( "%d\t%s - %s\n" , seferSirasi , Nereden ,  Nereye);
	}
	fclose(fp); // Dosya kapandi >> 
	
	int i , j ,k , seferNo , sayac=0;
	
	printf("Ana Menuye Donmek icin 0'a basiniz");
	printf("\nGormek istediginiz seferi giriniz:");
	scanf("%d", &seferNo); // Görmek istenilen sefer seçimi
	
	if(seferNo == 0){ // 0 ise ana menüye dön
		main();
	}
	
	while(seferNo<1 || seferNo>10){ // seferNo 1den küçük veya 10'dan büyük ise tekrar iste
	fflush(stdin);
	printf("HATALI GIRIS!");
	printf("\nGormek istediginiz seferi giriniz:");
	scanf("%d" , &seferNo);
		
	}
	// Kullanici Sefer Numarasini Girdi >> 
	
	FILE*fSefer;
	fSefer = fopen("dosyalar\\Hatlar.txt", "r");
	if(fSefer == NULL){
		printf("dosya acmada hata oldu.");
		exit(1);
	}
	
	
	while(! feof(fSefer)){ 
		fscanf(fp , " %d %d %s %s " , &seferSirasi, &hatNo, Nereden , Nereye );
		if(seferNo == seferSirasi)
		printf( "\n\t%d\t%s - %s\n\n" , seferSirasi , Nereden ,  Nereye);
	}
	fclose(fSefer);
	
	for(j=0; j<15; j++){
			
		for(k=0; k<4; k++){
			sayac++;
			if(matris[seferNo-1][j][k] == 0){
				printf("\t%d\t|" , sayac);
			}
			else if(matris[seferNo-1][j][k] == 1){
					printf("\tX\t|");
			}
		}
			printf("\n");
	}
	
	int secim;
	printf("Yeni bir Ucak koltuk durumu ogrenmek icin 1'e basiniz. \n Ana Menuye Donmek icin 0'a basiniz:");
	scanf("%d" , &secim);
	switch (secim){
		case 0: main();
				break;
		case 1: durum();
				break;
	    default: printf("HATALI GIRIS! ANA MENUYE YONLENDIRILIYORSUNUZ.");
	    		sleep(4);
				main();
	}
}

int satis(){
	fflush(stdin);
	system("cls");
	printf("\t\t\tYorgun Hava Yollari\n\n\n");
	
	int hatSecim;
	printf("Ana Menuye Donmek icin 0'a basiniz.\n");
	printf("Ucusunuz ic hatlar ise 1, dis hatlar ise 2'ye basiniz:");
	scanf("%d" , &hatSecim); // Hat secimi veya ana menüye dönüş için secim
	switch(hatSecim){
		case 0: main(); // 0 ise ana menüye den
				break;
		case 1: break; // 1 ise devam et
		case 2: break; // 2 ise devam et 
		default: main(); // Hicbiri degilse tekrar gir
				break;
	}
	
	printf("Ucak seferlerimiz asagidaki gibidir: \n\n\n"); 
	printf("\tNereden");
	printf(" - Nereye\n\n");
	FILE*fHat; 
	fHat = fopen("dosyalar\\Hatlar.txt", "r"); // Hatlar dosyasini açıyoruz.
	if(fHat == NULL){
		printf("dosya acmada hata oldu.");
		exit(1);
	}
	
	
	int seferNo, hatNo; 
	char Nereden[100], cizgi, Nereye[100];
	while(! feof(fHat)){ 
		fscanf(fHat, " %d %d %s %s ", &seferNo, &hatNo, Nereden, Nereye); // İÇ VEYA DIŞ HATA GÖRE EKRANA UÇUŞLAR GELİR.
		if(hatNo == hatSecim){ // Seçilen hat eşit ise hatNo'ya göster.
		printf("%d\t%s - %s\n", seferNo, Nereden, Nereye);
		}          
	} 
	
	fclose(fHat); // Hat Dosyasini kapatiyoruz.
	
	int ucusSecim; 
	printf("\n\nUcus Seciniz:");
	scanf("%d" , &ucusSecim); /// UCUS SECİMİ
 	if(hatSecim==1){   //EĞER İÇ HAT SEÇİLİ İSE 1'DEN KÜÇÜK VE 5'DEN BÜYÜK OLAMAZ
 		while(ucusSecim<1 || ucusSecim>5){
 			printf("\nHATALI GIRIS!");
			printf("\n\nUcus Seciniz:");
			fflush(stdin);
			scanf("%d" , &ucusSecim); /// ucus secimi
		 }
	 }
 	
 	else if(hatSecim==2){ // EĞER DIŞ HAT SEÇİLİ İSE 6'DAN KÜÇÜK VE 10'DAN BÜYÜK OLAMAZ.
 		while(ucusSecim<6 || ucusSecim>10){
 			printf("\nHATALI GIRIS!");
			printf("\n\nUcus Seciniz:");
			fflush(stdin);
			scanf("%d" , &ucusSecim); /// ucus secimi
		 }
	 }
 	
 	
	FILE*fSefer; // SEÇİLEN SEFERİ GÖSTERMEK İCİN DOSYA AÇILIR
	fSefer = fopen("dosyalar\\Hatlar.txt", "r");
	if(fSefer == NULL){
		printf("dosya acmada hata oldu.");
		exit(1);
	}
	
	
	while(! feof(fSefer)){  
			
		fscanf(fSefer , " %d %d %s %s " , &seferNo, &hatNo, Nereden , Nereye );
		
		if(seferNo == ucusSecim){
		
		printf( "\n%d\t%s - %s\n\n" , seferNo , Nereden ,  Nereye);
		
		}
	
	}
	
	fclose(fSefer); // SEÇİLEN SEFERİ GÖSTERMEK İÇİN DOSYA KAPANIR.
	
	printf("Ucak Durumu:\n\n"); // Seçilen seferin uçak durumu;
	
	int j , k , sayac=1;
	for(j=0; j<sira; j++){
		for(k=0; k<koltuk; k++){
			if(matris[ucusSecim-1][j][k]==0){
				printf("\t%d\t|" , sayac);
			}
			else if(matris[ucusSecim-1][j][k]==1){
				printf("\tX\t");
			}
			if(sayac%4==0){
				printf("\n");
			}
			
			sayac++;
		}
	}
	//
	
	fflush(stdin); // INTEGER BİR SAYIDAN SONRA STRING ALINAMADIĞI İÇİN ENTER TEMİZLENİR.
	
	musteri o;  // YAPIYI OLUŞTURMUŞTUK O ADINDA BİR DEGİSKEN TANIMLADIK.
 	
	printf("\nAdinizi Giriniz:"); 
	gets(o.ad); // AD ALINIR.
	
	printf("Soyadinizi Giriniz:");
	gets(o.soyad);// SOYAD ALINIR
	
	
	
	printf("\nTC Numaranizi Giriniz:");
	scanf("%lf" , &o.tc); //TC ALINIR.
	
		
	
	int sayi=1;
	while(sayi != 0){ // SAYI 0'DAN FARKLI OLDUĞU SÜRECE DÖN 1 OLUNCA DÖNGÜDEN ÇIKAR.
		int sayac=1;
		
		printf("\nKoltuk Numarasi Giriniz:");
		scanf("%d" , &o.koltukNumarasi);
		 
		 while(o.koltukNumarasi<1 || o.koltukNumarasi>60){ //Koltuk numarasi 1 ile 60 arasindadir.
		 	printf("HATALI GIRIS !\n");
			printf("\nKoltuk Numarasi Giriniz:");
			scanf("%d" , &o.koltukNumarasi);
		 }
		
		int j , k ; // sayac 1'den başlıyor çünkü koltuk numarasi 1'den başlıyor.
		for(j=0; j<sira; j++){
			for(k=0; k<koltuk; k++){
				
				if(sayac==o.koltukNumarasi){
					
					if(matris[ucusSecim-1][j][k] == 0){
						matris[ucusSecim-1][j][k] = 1;	
							
						sayi = 0;
						
						FILE*fKayit;
						fKayit = fopen("dosyalar\\kayit.txt" , "a");
						if(fKayit == NULL){
							printf("Hata");
						}
						
						fprintf(fKayit , "\n%s %s %.0lf %d %d %d" , o.ad , o.soyad , o.tc , o.koltukNumarasi , ucusSecim , hatSecim );
						
						fclose(fKayit);
						 
						printf("Isleminiz tamamlanmistir.\n");
						 
					}
						
				}
				
				sayac++;
				
			}
		}
		
	}
	
	
	FILE *fp; // Secilen uçağın koltuk durumu;
	char dosya[20];
	char num[2];
	int i;
	sayac=1;
	for(i = ucusSecim; i <= ucusSecim; i++){
		
		strcpy(dosya, "dosyalar\\UcakDurumu");
		itoa(i, num, 10);            // itoa = Integer TO Ascii, sayi 10'luk tabanda oldugu icin son parametre 10   
		strcat(dosya, num);
		strcat(dosya, ".txt");
		
		
		
		
		fp = fopen(dosya, "w");
		
		if(fp == NULL)
			printf("hata");
	}	
	 
	 for(j=0; j<sira; j++){
	 	for(k=0; k<koltuk; k++){
	 		fprintf(fp , "%d\t" , matris[ucusSecim-1][j][k]);
		 	if(sayac%4==0){
		 		fprintf(fp , "%s" , "\n");
			 }
			 sayac++;
		 	
		}
		 
	  
	 }
	
	fclose(fp);
	

	int secim;
	printf("Ana Menuye Donmek icin 0'a basiniz. \nYeni bilet almak icin 1'e basiniz. ");
	scanf("%d" , &secim);
	switch(secim){
		case 0: main();
				break;
		case 1: satis();
				break;
		default: main();
				break;
	}
}

int arama(){
	
	fflush(stdin);
	system("cls");
	
	double aranan;
	
	printf("Aradiginiz kisinin TC Kimlik Numarasini giriniz:");
	scanf("%lf" , &aranan);
    
	musteri o;
    
	int ucusSecim, hatSecim , sayac=0;
	
	FILE*fp;
	
	fp = fopen("dosyalar\\kayit.txt" , "r");
	if(fp == NULL){
		printf("HATA!\n\n");
		int islem;
	
		printf("Ana menuye donmek icin 0'a basiniz. \nYeni Kisi Aramak icin 1'e basiniz:");
		scanf("%d" , &islem);
		switch(islem){
			case 0:main();
				break;
			case 1: arama();
				break;
			default:main();		
		}
		
	}
	
	int seferNo , hatNo;
	char Nereden[100], Nereye[100];
	while(! feof(fp)){
		fscanf(fp , "%s %s %lf %d %d %d" , o.ad , o.soyad , &o.tc , &o.koltukNumarasi , &ucusSecim , &hatSecim);
		
			
		
		if(aranan == o.tc){
		
			printf("\n Adi:%s\n Soyadi:%s\n TC Kimlik:%.0lf\n Koltuk Numarasi:%d\n" ,  o.ad , o.soyad , o.tc , o.koltukNumarasi);
			
			if(hatSecim==1){
				printf("Ucus ic hatlardadir.\n");
			}
			
			else if(hatSecim==2){
				printf("Ucus dis hatlardadir.");
			}
			
			FILE*fSefer; // SEÇİLEN SEFERİ GÖSTERMEK İCİN DOSYA AÇILIR
			fSefer = fopen("dosyalar\\Hatlar.txt", "r");
			if(fSefer == NULL){
				printf("dosya acmada hata oldu.");
				exit(1);
			}
	
	
			while(! feof(fSefer)){  
				
				fscanf(fSefer , " %d %d %s %s " , &seferNo, &hatNo, Nereden , Nereye );
				
				if(seferNo == ucusSecim)
					printf( "\n%d\t%s - %s\n\n" , seferNo , Nereden ,  Nereye);
				
		
			}
			fclose(fSefer); // SEÇİLEN SEFERİ GÖSTERMEK İÇİN DOSYA KAPANIR.
			o.tc = 0;
			sayac++;
		   	
		}
	}
	
	if(sayac==0){
		printf("Aradiginiz kisi bulunamadi.\n");
	}
	
	fclose(fp);
	
	
	int islem;
	printf("Ana menuye donmek icin 0'a basiniz. \nYeni Kisi Aramak icin 1'e basiniz:");
	scanf("%d" , &islem);
	switch(islem){
		case 0:	main();
				break;
		case 1: arama();
				break;
		default:main();
				break;		
	}
}
   
int iptal(){
	
	
	
	
	fflush(stdin);
	
	system("cls");
	
	double aranan;
	printf("Silmek istediginiz TC'yi giriniz:");
	scanf("%lf", &aranan);
	musteri o;
	
	
	
	int ucusSecim , hatSecim;
	
	int sayac=1 , kontrol=0;
	
	
	
	FILE *fp, *fp2;
	
	fp = fopen("dosyalar\\kayit.txt", "r");
	fp2 = fopen("dosyalar\\yeniKayit.txt", "w"); 
	
	if(fp == NULL){
		printf("HATA!");
		exit(0);
	}
	
	if(fp2 == NULL){
		printf("HATA!");
		exit(0);
	}
	
	while(! feof(fp))
	{
		
		fscanf(fp , "%s %s %lf %d %d %d" , o.ad , o.soyad , &o.tc , &o.koltukNumarasi , &ucusSecim , &hatSecim);
		
		
		sayac=1;
		if(aranan == o.tc){
			
			kontrol=1; // tc var yok kontrol.
			
			int i,j ,k;
			
			for(j=0; j<sira; j++){
				for(k=0; k<koltuk; k++){
					
					if(sayac == o.koltukNumarasi){
						matris[ucusSecim-1][j][k] = 0;
					}
					
					sayac++;
				}
			}
			
			// Koltuk Durumu Güncelleme
			FILE *fSil; // Secilen uçağın koltuk durumu;
			char dosya[20];
			char num[2];
			
			sayac=1;
			j=0;
			k=0;
			for(i = ucusSecim ; i <= ucusSecim; i++){
	
		
		
			strcpy(dosya, "dosyalar\\UcakDurumu");
			itoa(i, num, 10);            // itoa = Integer TO Ascii, sayi 10'luk tabanda oldugu icin son parametre 10   
			strcat(dosya, num);
			strcat(dosya, ".txt");
		
			
		
		
			fSil = fopen(dosya, "w");
		
			if(fSil == NULL)
				printf("hata");
			}	
	 
			for(j=0; j<sira; j++){
	 			for(k=0; k<koltuk; k++){
	 				fprintf(fSil , "%d\t" , matris[ucusSecim-1][j][k]);
		 			if(sayac%4==0){
		 			fprintf(fSil , "%s" , "\n");
			 		}
			 		sayac++;
		 	
				}
		 
	  
			}
			
			fclose(fSil); // Koltuk Durumu Güncelleme Bitis;
			
			
			
			continue;
		}
		
		
		
			if(o.tc != 0)
			fprintf(fp2 , "\n%s %s %.0lf %d %d %d" , o.ad , o.soyad , o.tc , o.koltukNumarasi , ucusSecim , hatSecim);
		
	}
	
	fclose(fp);
	fclose(fp2);
	
	
	
	
	
	
	
	

	
	
	
	if(kontrol==1){
		printf("\nSilme isleminiz tamamlanmistir.\n");
	}
	
	else{
		printf("\n\nTC kimlik numarasi bulunamadi.\n\n");
	}
	
	
	
	
		
	
			
		
		
		
	
	
	remove("dosyalar\\kayit.txt");
	
	rename("dosyalar\\yeniKayit.txt","dosyalar\\kayit.txt");
	
	
	int islem;
	printf("Yeni kisi silmek icin 1'e Ana Menuye Donmek icin 0'a basiniz.");
	scanf("%d" , &islem);
	
	switch(islem){
		case 0: main();
				break;
		case 1: iptal();
		default:main();
				break;
	}
	
	
	
	
	
}

int main(int argc, char *argv[]) {
	
	fflush(stdin);
	system("cls");
	oku();
	
	return 0;
	
}

