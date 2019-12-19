#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#define R_SARI "\x1b[33m"
#define R_KRMZ "\x1b[31m"
#define R_REST "\x1b[0m"
#define R_MAVI "\x1b[36m"

void Menu();
void SoruEkle();
void SoruSil();
void Listele(int sayac);
void SadeceSoru(int sayac);
void Guncelle();
void goruntulemeEkrani();
void DosyaYaz();
void oyun(void);
void oyungoster (int sayac);
void skorkayit(int bilinen,char kullanici[]);
int skorgoster();
void siralama(int skorsay);

int secim;

int N=0;//Soru ID sayýsý tutan deðiþken


struct database 	
    {	char sorumetni[100];
		char seca[100];
		char secb[100];
		char secc[100];
		char secd[100];
		char dogru[100];
		char ad[100];
		int skor;
		
	
	}data[BUFSIZ];


main()
{
	//DOSYA OKUMA KISMI : program ilk acildiginda dosyada kac soru var, onu tespite calisiyor...
	
	int skorSayisi = skorgoster();
	FILE *fp;//Dosya tanimlama islemi
	fp = fopen("Sorular.txt","r");//dosya acma islemi
	
	if (fp == NULL)
		printf("Dosya Bulunamadi...\n"); 
		
	else
	{	int x=0;
		while (!feof(fp))//dosyanin sonuna gelene kadar 
		{ 
			fscanf(fp,"%s\t%s\t%s\t%s\t%s\t\n%s",&data[x].sorumetni, &data[x].seca, &data[x].secb, &data[x].secc, &data[x].secd, &data[x].dogru);
			x++;	
		}
		x--;  //N sayisi 1 fazla sayiliyordu bu hatayi gidermek için N'i 1 azalttýk...
		N=x;
		fclose(fp);
	}

	//MENUDE SECÝM
	char cikis = 'h';
	
	while(cikis == 'h')
	{
		system("CLS"); //EKRANI TEMIZLER
		Menu(); // fonksiyonu cagirildi..
		char secim =0; // menu secim
		char devamEt = 'e'; 
		secim = getch();
		
		if(secim == '1')  //SORU EKLE
		{
			while(devamEt == 'e' || devamEt == 'E')
			{
				SoruEkle();
				DosyaYaz();
				printf("\n\t"R_MAVI"Soru eklemeye devam edecek misiniz? [E/H]\n"R_REST);
				devamEt = getch();
			}	
		}
		else if (secim == '2')  //GORUNTULE
		{
			goruntulemeEkrani();
			printf(R_MAVI"\n==> Menuye donmek icin herhangi bir tusa basiniz!\n"R_REST);
			getch();
		}
		else if (secim == '3') //GUNCELLE
		{
			while(devamEt == 'e' || devamEt == 'E')
			{
				Guncelle();
				DosyaYaz();
				printf("\n"R_MAVI"Guncellemeye islemine devam edecek misiniz? [E/H]\n"R_REST);
				devamEt = getch();
			}
		}
		else if (secim == '4')  //SORU SÝL
		{
			SoruSil();
			DosyaYaz();
			
		}
		else if (secim == '5')//oyun oyna
		{
			while(devamEt == 'e' || devamEt == 'E')
			{
				if (N>5)
				{
					oyun();
					printf("\n\n  ==> Oynamaya Devam Etmek istiyor musunuz?"R_SARI" [E/H] \n"R_REST);
					devamEt = getch();
				}
				else
				{
					printf("\t"R_SARI"Oynamak icin en az 5 Soru eklenmis olmalidir!"R_REST"");
					Sleep(3000);
					main();
				}
			}
		}
		else if (secim == '6')//yuksek skorlar
		{
			skorSayisi = skorgoster();
			siralama(skorSayisi);
			system("CLS");
			printf("\n\n\n\t\t"R_SARI" ==================>- SKORLAR -<======================="R_REST"\n\n");
			printf("\t\t\t\t"R_SARI"1."R_REST"===>\t%d Puan  %s\n\n",data[skorSayisi-1].skor,data[skorSayisi-1].ad);
			printf("\t\t\t\t"R_SARI"2."R_REST"===>\t%d Puan  %s\n\n",data[skorSayisi-2].skor,data[skorSayisi-2].ad);
			printf("\t\t\t\t"R_SARI"3."R_REST"===>\t%d Puan  %s\n\n",data[skorSayisi-3].skor,data[skorSayisi-3].ad);
			printf("\t\t"R_SARI"========================================================"R_REST"\n");
			printf("\n\n\t\t\tMenuye donmek icin bir tusa basiniz.");
			getch();
		}
		else if (secim == '7')  //ÇIKIÞ
		{
			printf(R_SARI"\n\n                                  Oyun Kapatiliyor"R_REST);
			Sleep(800); printf("."); Sleep(800); printf("."); Sleep(800); printf(".");
			Sleep(250); printf(R_MAVI"\n                      Cikmak icin herhangi bir tusa basiniz!"R_REST);
			cikis = 'e';
		}
		else //BASKA BIR TUSA BASILIRSA
		{
			printf(R_KRMZ"\n\n                                   Lutfen menudeki seceneklerden birini seciniz!"R_REST);Sleep(650);
		}
	}
}

void Menu()
{
	printf("\n\t\t\t     "R_SARI"  TEST OYUNU UYGULAMASI"R_REST"  \n");
	printf("\t\t\t ******************************** \n");
	printf("\t\t\t|\t"R_SARI" 1."R_REST" SORU EKLE            |\n");
	printf("\t\t\t|\t"R_SARI" 2."R_REST" SORU GORUNTULE       |\n");  
	printf("\t\t\t|\t"R_SARI" 3."R_REST" SORU GUNCELLE        |\n");// Menünün görünümü
	printf("\t\t\t|\t"R_SARI" 4."R_REST" SORU SiL             |\n");
	printf("\t\t\t|\t"R_SARI" 5."R_REST" OYUN OYNA            |\n");
	printf("\t\t\t|\t"R_SARI" 6."R_REST" EN YUKSEK SKORLAR    |\n");
	printf("\t\t\t|\t"R_SARI" 7."R_REST" "R_MAVI"CIKIS"R_REST"                |\n");
	printf("\t\t\t ******************************** \n");

	
	printf("\n\n\t\t\t   "R_MAVI"LUTFEN BiR SECENEK SECINIZ.\n\n"R_REST"");
}	

void SoruEkle()
{
	system("CLS"); 
	printf("           ____________________                                               \n");
	printf("          |                    |                                              \n");
	printf("  "R_SARI"*******"R_REST" | "R_SARI"    SORU EKLE   "R_REST"   | "R_SARI"*******"R_REST"\n");
	printf("          |____________________|                                              \n");
	
	
	printf("\n"R_SARI" %d."R_REST" Soru Eklemek icin bilgileri doldurun....\n",N+1);
	
	printf(R_SARI"\n  SORU METNi:"R_REST);
	gets(data[N].sorumetni);
	
	printf(R_SARI"\n  A-Secenegi:"R_REST);
	gets(data[N].seca);
	
	printf(R_SARI"\n  B-Secenegi:"R_REST);
	gets(data[N].secb);  
	
	printf(R_SARI"\n  C-Secenegi:"R_REST);
	gets(data[N].secc);
	
	printf(R_SARI"\n  D-Secenegi:"R_REST);
	gets(data[N].secd);
	
	printf(R_SARI"\n  DOGRU CEVAP:"R_REST);
	gets(data[N].dogru);
	
	N++;
	
}

void DosyaYaz()  // DOSYA YAZMA ISLEMI bu fonkla yapýldý
{
	FILE *fp;
	fp = fopen("Sorular.txt","w");
	
	if(fp==NULL)
    	printf("Dosya Bulunamadi...");
    	
    else
	{
		for (int i = 0; i < N; i++)
		{
			fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t\n",data[i].sorumetni,data[i].seca,data[i].secb,data[i].secc,data[i].secd,data[i].dogru);
		}
	}
	fclose(fp);
}

void Listele(int sayac)  // GORUNTULEME ISLEMi YAPAN FONKSÝYON
{

	printf(R_SARI"\n=======>"R_MAVI" %d.Soru "R_SARI"<=======\n"R_REST,sayac+1);
	printf("SORU METNi : %s\n",data[sayac].sorumetni);
	printf("A-Secenegi : %s\n",data[sayac].seca);
	printf("B-Secenegi : %s\n",data[sayac].secb);
	printf("C-Secenegi : %s\n",data[sayac].secc);
	printf("D-Secenegi : %s\n",data[sayac].secd);
	printf("DOGRU CEVAP: %s\n",data[sayac].dogru);
	
}
void SadeceSoru(int sayac)//görüntüleme ekranýnda sadece soru görüntülenmesini saðlar
{
	printf(R_SARI"\n=======>"R_MAVI" %d.Soru "R_SARI"<=======\n"R_REST,sayac+1);
	printf("==> %s\n",data[sayac].sorumetni);
	
}


void goruntulemeEkrani()
{	
	
	system("CLS");
	printf("           ____________________                                               \n");
	printf("          |                    |                                              \n");
	printf("  ******* | "R_SARI" SORU GORUNTULEME "R_REST" | *******\n");
	printf("          |____________________|                                              \n");
	

	if(N == 0)
	{
		printf(R_KRMZ"\n      UYARI!"R_REST" Suan Hicbir soru ekli degil. Ekleme yapmak icin "R_SARI"[E/H]"R_REST" tusuna basiniz : "R_REST);//Soru olusturulamamissa veya daha önce silinmisse bu uyari gösterilir
		secim = getch();
		if(secim == 'e' || secim == 'E')
		{
			printf("\n\n                          ==> Soru Ekleme Ekrani aciliyor");
			Sleep(750); printf("."); Sleep(500); printf("."); Sleep(500); printf(".");Sleep(750);
			SoruEkle();
		}
	}
	else
	{
		for(int i = 0; i < N; i++)
		SadeceSoru(i);	
	}
}
void Guncelle()
{
	system("CLS"); 
	printf("           ____________________                                               \n");
	printf("          |                    |                                              \n");
	printf("  ******* | "R_SARI" SORU GUNCELLEME "R_REST"  | *******\n");
	printf("          |____________________|                                              \n");
		
	int noGuncellenen,secenek;  
	if(N == 0)
	{
		printf(R_KRMZ"\n      UYARI! Suan Hicbir soru ekli degil. "R_REST);
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
		SadeceSoru(i); // TUM SORULARI EKRANA YAZDIRIR.
		}
		printf("\n\n"R_SARI"==>"R_REST"GUNCELLEMEK istediginiz sorunun "R_SARI"NUMARASINI"R_REST" giriniz: ");
		scanf("%d",&noGuncellenen);
		noGuncellenen=noGuncellenen - 1;
		system("CLS");
		printf(R_MAVI"    GUNCELLENECEK SORU"R_REST);
		Listele(noGuncellenen);
	
		printf("\n\n"R_SARI"\t==>Guncellemek istediginiz bilginin numarasini giriniz. \n\n");
		
		
		printf(R_MAVI"\n  1-"R_REST"SORU METNi: \n ");
		printf(R_MAVI"\n  2-"R_REST"SECENEKLER: \n ");
		printf(R_MAVI"\n  3-"R_REST"DOGRU CEVAP: \n ");
		printf("\n\n\t");
		scanf("%d" ,&secenek);//Guncellenecek istek alinir.
		
		if (secenek == 1)
		{
			printf("\n            YENi SORU METNi = ");  
			scanf("%s",data[noGuncellenen].sorumetni);  //YENi bilgi ile güncelleme
		}
		else if (secenek == 2)
		{
			printf("\n       Yeni  A-Secenegi = ");  
			scanf("%s",data[noGuncellenen].seca);
            printf("\n       Yeni  B-Secenegi = ");  
			scanf("%s",data[noGuncellenen].secb);
	 	    printf("\n       Yeni  C-Secenegi = ");  
			scanf("%s",data[noGuncellenen].secc);
			printf("\n       Yeni  D-Secenegi = ");  
			scanf("%s",data[noGuncellenen].secd);
		}
		else if (secenek == 3)
		{
			printf("\n        YENi DOGRU CEVAP = ");  
			scanf("%s",data[noGuncellenen].dogru);
		}
	}	
}
void SoruSil()
{
	system("CLS");
	printf("           ____________________                                               \n");
	printf("          |                    |                                              \n");
	printf("  ******* | "R_SARI" SORU SiLME "R_REST"       | *******\n");
	printf("          |____________________|                                              \n");
	
	int noSilinen = 0;
	char kontrol;
	int sec;//Silinenecek bilginin numarasi
	if(N == 0)
	{
		printf(R_KRMZ"\n      UYARI! Suan Hicbir soru ekli degil. "R_REST);
	}
	else
	{
		
		for (int i = 0; i < N; i++)
		{
			Listele(i);
		}
		printf(R_SARI"\n----> Silmek istediginiz sorunun numarasini giriniz.  <--- "R_REST);
		scanf("%d",&noSilinen);
	
		system("CLS");
	
		noSilinen=noSilinen - 1;
	
		printf(R_MAVI"     SILINECEK SORU"R_REST);
		Listele(noSilinen);
		printf(R_SARI"\n---> "R_MAVI"%d"R_REST" numarali soruyu silmeye" R_KRMZ" EMiN MiSiNiZ?"R_REST" [E/H]",noSilinen+1);
		kontrol = getch();
	
		if (kontrol == 'e' || kontrol =='E')
		{
			strcpy(data[noSilinen].sorumetni, 			data[N-1].sorumetni);
			strcpy(data[noSilinen].seca,		data[N-1].seca);
			strcpy(data[noSilinen].secb,		data[N-1].secb);
			strcpy(data[noSilinen].secc,		data[N-1].secc);
			strcpy(data[noSilinen].secd,		data[N-1].secd);
			strcpy(data[noSilinen].dogru,		data[N-1].dogru);
		
			N--;
		
			printf("\n\n\t"R_SARI"---> Islem basariyla gerceklesti..."R_REST"");
			Sleep(1500);
		}
	}
}

void oyun( void )	// Oyun oyna */
{
	
	char cevap[5],dg[5],kullanici[20];
	int r=1,m=1,dz[5],t=1;
	int bilinen=0;
	system("cls");
	printf("\n\n\n\t\t"R_MAVI"TEST OYUNUNA HOSGELDINIZ!\n\n");
	printf("   "R_SARI"KULLANICI ADI GIRINIZ: "R_REST"");
    gets(kullanici);



	for (m=0 ; m<5 ; m++)
	{
		system("cls");
		basla:
    	srand(time(NULL)); //rastgele sayý uretme
    	r=rand()%N;//n soru sayýmýz
		for (t=0 ; t<m ; t++)//ayný soru gelmemesi için
			if(dz[t]==r)goto basla;
	
		dz[m]=r;
		oyungoster(r);
		printf("\n\n\t"R_MAVI"CEVABINIZ: "R_REST"\n");
		cevap[m]=getch();
		strcpy(&dg[m],data[r].dogru);//üretilen sayý nolu soruyu diziye aktarýyor
		if (strcmp(&cevap[m],&dg[m])==0)//cevaplarý karþýlaþtýrýyor
		{
			bilinen++;//doðruysa puaný arttýrýr
			printf("\n\n  "R_SARI"TEBRIKLER DOGRU CEVAP!"R_REST"");Sleep(900);
		}
		else
		{
			printf("\n\n\t"R_KRMZ"YANLIS CEVAP!"R_REST"");Sleep(900);
		}	
			printf("\n\n\n\n Yeni Soru Geliyor");printf(".");Sleep(50);printf(".");Sleep(100);printf(".");Sleep(150);printf(".");Sleep(250);
	}
	
	system("CLS");
	printf("\n\t\t"R_SARI" Tebrikler ,"R_REST" %s\n",kullanici);
	printf("\n\t\t"R_SARI" SKORUNUZ : "R_REST"%d\n",bilinen);
	skorkayit(bilinen,kullanici);//skorlarý kaydetmek için caðýrýlan fonksiyon
	
}

void oyungoster (int sayac) //oyun fonkun içinde geçen oyungöster fonskiyonu
{
	FILE *fp;

  	if ((fp=fopen ("Sorular.txt", "r")) == NULL) 
  	{
      	printf("Veri dosyasý mevcut deðil!\n");
      	return;
 	}
  	printf(R_SARI"\n=======>"R_MAVI" %d.Soru "R_SARI"<=======\n"R_REST,sayac+1);
	printf("SORU METNi : %s\n",data[sayac].sorumetni);
	printf("A-Secenegi : %s\n",data[sayac].seca);
	printf("B-Secenegi : %s\n",data[sayac].secb);
	printf("C-Secenegi : %s\n",data[sayac].secc);
	printf("D-Secenegi : %s\n",data[sayac].secd);
	printf("Dogru Cevap : %s\n",data[sayac].dogru);
	
  	fclose (fp);
}

void skorkayit(int bilinen,char kullanici[])
{
	FILE *fp2;
	fp2 = fopen("Skorlar.txt","a");
	if(fp2 != NULL)
	{
		fprintf(fp2,"%d\t%s\t",bilinen,kullanici);	
	}
	fclose(fp2);
}

int skorgoster()
{
	FILE *fp2;
	fp2 = fopen("Skorlar.txt","r");
	int skorsay=0;
	if(fp2 != NULL)
	{
		while(!feof(fp2))
		{
			fscanf(fp2,"%d\t%s",&data[skorsay].skor,&data[skorsay].ad);
			skorsay++;
		}
	}
	else
	{
		printf("Dosya okunamadi.\n");
		fp2 = fopen("Skorlar.txt","w");
	}
	fclose(fp2);
	return skorsay-1;
}	

void siralama(int skorsay){//bubblesort kullanýldý
	int k = 0;
	int a = 0;
	for(k=0;k<skorsay-1;k++)
	{
		for(a=0;a<skorsay-1;a++)
		{
			if(data[a].skor > data[a+1].skor)
			{
				int temp = data[a].skor;
				char tempisim[50] ;
				strcpy (tempisim,data[a].ad);
				data[a].skor = data[a+1].skor;
				strcpy (data[a].ad,data[a+1].ad);
				strcpy (data[a+1].ad,tempisim);
				data[a+1].skor = temp;
			}
		}
	}
}

