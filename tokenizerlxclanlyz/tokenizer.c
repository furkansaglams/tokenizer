#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/*
AD:FURKAN
SOYAD:SAÐLAM
NUMARA:02200201017
1.ÖÐRETÝM 2.SINIF
*/
//yorum satýrlarýný numaralandýrýrak yaptým her numara "//" arasýný ifade edicek
void kaynakodyazdir(char dizi[], int diziboyut)
{
	printf("  \nkaynak kodunuz:\n\n");
	int i;
	for (i = 0; i < diziboyut; i++)
	{
		printf("%c", dizi[i]);
	}
	printf("\n\n");
	printf("kelimelestirilmis hali:\n\n");
}

//yorum satýrý 1 alttaki kodda ++ -- gibi kontrolleri yaptým çünkü bunlar ayrý ayrý olucak kavramlar deðil
//c de beraber yazýlan yapýlar oldugu için böyle bir þey yaptým ayrýca virgül atarken dogru virgül atabilmemi saðladý.
//bunlar özel durumlar oldugu için diziye atmak daha fazla iþleme neden olacaðý içi böyle tercih ettim
int ozeldurum(char karakter1, char karakter2)
{
	if (

		(karakter1 == '+' && karakter2 == '+') ||
		(karakter1 == '-' && karakter2 == '-') ||
		(karakter1 == '=' && karakter2 == '=') ||
		(karakter1 == '+' && karakter2 == '=') ||
		(karakter1 == '-' && karakter2 == '=') ||
		(karakter1 == '/' && karakter2 == '=') ||
		(karakter1 == '*' && karakter2 == '=') ||
		(karakter1 == '<' && karakter2 == '=') ||
		(karakter1 == '>' && karakter2 == '=') ||
		(karakter1 == '|' && karakter2 == '|') ||
		(karakter1 == '&' && karakter2 == '&') ||
		(karakter1 == '!' && karakter2 == '=') ||
		(karakter1 == '%' && karakter2 == '=') ||
		(karakter1 == '?' && karakter2 == '=')

	)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
//yorum satýrý 1 bitti

//yorum satýrý 2 alttaki kodda ayraç olup omadýgýný kontrol ettim dogru bir biçimde virgül atabilmek için
//bazýlarýný ascii olarak yazdým "'" kodun okunurlugu açýsýndan güzel olmadýgýndan bunun gibi örnekleri ascii olarak yazdým
//32=bosluk tusu   34="(çift týrnak)  39='(tektýrnak)

int ayrac(char karakter)
{
	char dizi[26] = {'+', '-', '*', '/', ',', ';', '>', '<', '[', ']', '{', '}', ')', '(', '=', '|', '&', 34, 39, '!', 92, ':', '?', '^', '%', '.'};
	int i = 0, deger = 0;
	bool fonksiyondancik = true; // iki nedeni var 1.neden eger terminal'i bulursa deger=1 olucak ama hala devam edicek bir sonrakinde bulamayýnca deger 0 olucak ve hatalý çalýþýcak 2.neden ise buldugu anda diziye deam etmemesini saðlamak zaman kaybetmemesi için.
	while (i < 26 && fonksiyondancik == true)
	{
		if (dizi[i] == karakter)
		{
			deger = 1;
			fonksiyondancik = false;
		}
		else
		{
			deger = 0;
		}
		i++;
	}

	return deger;
}

int main(int argc, char *argv[])
{
	FILE *okunacakdosya;
	char dosyayolu[100] = "";
	printf("---------------------------------------------------------------------------------\n");
	printf("NOT:Lutfen dosya yolunu girerken arada bosluk veya turkce karakter kullanmayin!!!\n");
	printf("---------------------------------------------------------------------------------\n");
	printf("Okunacak olan dosyanizin dosya yolunu giriniz: ");
	scanf("%s", &dosyayolu);
	okunacakdosya = fopen(dosyayolu, "r");
	char kelime[1000000], yenidizi[1000000];

	char karakter;
	int i = 0;

	//yorum satýrý 3 bu kod satýrýný dosyanýn sonuna kadar okumamý ve fgetc fonksiyonu ile karakter karakter okuyup bir karakter dizisine
	//atmaiþlemini gerçekleþtirdim .dosyayý okurken EOF kavramýný kullandým EOF txt metinin son harfini gösteren bir iþaretçi
	if (okunacakdosya != NULL)
	{
		while (karakter != EOF)
		{
			karakter = fgetc(okunacakdosya);
			kelime[i] = karakter;
			i += 1;
		}
	}
	else
	{
		printf("Dosya bulunamadi. ");
	}
	kaynakodyazdir(kelime, i);

	// yorum satýrý 3 bitti

	// yorum satýrý 4 fgetc fonksiyonu bosluk tab enter tusunu da bir karakter olarak aldýgý için bunlarý dizide
	//kaydýrma yaparak bir nevi yok ettim yani karakter dizimde bosluk tab ve enter tuþlarýný kaldýrdým
	int k, j, bosluk = 0;

	for (k = 0; k < i - 1; k++)
	{
		for (j = 0; j < i - 1; j++)
		{
			if (kelime[j] == 32 || kelime[j] == 10 || kelime[j] == 9)
			{
				bosluk++;

				while (j < i - 1)
				{
					kelime[j] = kelime[j + 1];
					j++;
				}
			}
		}
	}
	//yorum satýrý 4 bitti

	//yorum satýrý 5 olasý bosluklarý garantilemek için yeni bir diziye bosluksuz halini attým
	int diziboyut = 0;
	for (j = 0; j < i - 1 - bosluk; j++)
	{
		if (kelime[j] != 32)
		{
			diziboyut++;
			yenidizi[j] = kelime[j];
		}
	}
	//yorum satýrý 5 bitti
	printf("{ "); //dizi biçiminde gozukmesi için kelimlestirilmis halinin basýna ve sonuna {} eklemek icin yapýldý yani görunum icin yapýldý
	bool ayracmi, ozel, ikisonrasiayracmi, birsonrasiayracmi;

	int l = 0;
	for (l = 0; l < diziboyut; l++)
	{
		ayracmi = ayrac(yenidizi[l]);				//karakter dizisinde eger bir terminal(; , " gibi degerlerin olup olmadýgýný kontrol ettim )
		birsonrasiayracmi = ayrac(yenidizi[l + 1]); // virgül atarken iki ayraç yanayana gelirse tek bir virgül atmak gerekiyor sonrasýnýn ayraçolup olmadýgýný kontrol ettim
		ikisonrasiayracmi = ayrac(yenidizi[l + 2]); // ++ -- gibi durumlarda bir sonrasýný kontrol ettiðimde + ve sonarsý da + yý kontrol etmiþ olurum buna gerek yok iki sonarsaýný yani ++ dan sonra bir terminal var mý ?

		if (l != diziboyut)
		{
			ozel = ozeldurum(yenidizi[l], yenidizi[l + 1]);
		}

		if (ayracmi == 1)
		{
			if (ozel == 1)
			{
				if (ikisonrasiayracmi == 1)
				{
					printf(",%c%c", yenidizi[l], yenidizi[l + 1]); //örneðin ,++ yapýp sonrasý ayraç ise ,(, yapmalýyýz bunun için yazdým ==> ,++,(,
					l++;
				}
				else
				{
					if (l == diziboyut - 1)
					{
						printf(",%c%c", yenidizi[l], yenidizi[l + 1]); //en sonda 1 virgül fazladan atmamasý gerektiðinden yazdým
						l++;
					}
					else
					{
						printf(",%c%c,", yenidizi[l], yenidizi[l + 1]);
						l++;
					}
				}
			}

			else if (birsonrasiayracmi == 1)
			{
				printf(",%c", yenidizi[l]); //örnek ); iki terminal yanyana gelirse baþýna ve sonuna virgül atarsak ,),,;, olacagý için yaptým
			}
			else
			{
				if (l == diziboyut - 1)
				{
					printf(",%c", yenidizi[l]); //sonda 1 virgül fazla dan oldugu için yapýldý
				}
				else
				{
					printf(",%c,", yenidizi[l]);
				}
			}
		}
		else
		{
			printf("%c", yenidizi[l]); //eger terminal degilse oldugu gibi yazmasý için yapýldý
		}
	}
	printf("}");

	fclose(okunacakdosya);

	return 0;
}
