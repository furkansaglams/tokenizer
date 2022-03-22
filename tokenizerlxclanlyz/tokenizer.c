#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/*
AD:FURKAN
SOYAD:SA�LAM
NUMARA:02200201017
1.��RET�M 2.SINIF
*/
//yorum sat�rlar�n� numaraland�r�rak yapt�m her numara "//" aras�n� ifade edicek
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

//yorum sat�r� 1 alttaki kodda ++ -- gibi kontrolleri yapt�m ��nk� bunlar ayr� ayr� olucak kavramlar de�il
//c de beraber yaz�lan yap�lar oldugu i�in b�yle bir �ey yapt�m ayr�ca virg�l atarken dogru virg�l atabilmemi sa�lad�.
//bunlar �zel durumlar oldugu i�in diziye atmak daha fazla i�leme neden olaca�� i�i b�yle tercih ettim
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
//yorum sat�r� 1 bitti

//yorum sat�r� 2 alttaki kodda ayra� olup omad�g�n� kontrol ettim dogru bir bi�imde virg�l atabilmek i�in
//baz�lar�n� ascii olarak yazd�m "'" kodun okunurlugu a��s�ndan g�zel olmad�g�ndan bunun gibi �rnekleri ascii olarak yazd�m
//32=bosluk tusu   34="(�ift t�rnak)  39='(tekt�rnak)

int ayrac(char karakter)
{
	char dizi[26] = {'+', '-', '*', '/', ',', ';', '>', '<', '[', ']', '{', '}', ')', '(', '=', '|', '&', 34, 39, '!', 92, ':', '?', '^', '%', '.'};
	int i = 0, deger = 0;
	bool fonksiyondancik = true; // iki nedeni var 1.neden eger terminal'i bulursa deger=1 olucak ama hala devam edicek bir sonrakinde bulamay�nca deger 0 olucak ve hatal� �al���cak 2.neden ise buldugu anda diziye deam etmemesini sa�lamak zaman kaybetmemesi i�in.
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

	//yorum sat�r� 3 bu kod sat�r�n� dosyan�n sonuna kadar okumam� ve fgetc fonksiyonu ile karakter karakter okuyup bir karakter dizisine
	//atmai�lemini ger�ekle�tirdim .dosyay� okurken EOF kavram�n� kulland�m EOF txt metinin son harfini g�steren bir i�aret�i
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

	// yorum sat�r� 3 bitti

	// yorum sat�r� 4 fgetc fonksiyonu bosluk tab enter tusunu da bir karakter olarak ald�g� i�in bunlar� dizide
	//kayd�rma yaparak bir nevi yok ettim yani karakter dizimde bosluk tab ve enter tu�lar�n� kald�rd�m
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
	//yorum sat�r� 4 bitti

	//yorum sat�r� 5 olas� bosluklar� garantilemek i�in yeni bir diziye bosluksuz halini att�m
	int diziboyut = 0;
	for (j = 0; j < i - 1 - bosluk; j++)
	{
		if (kelime[j] != 32)
		{
			diziboyut++;
			yenidizi[j] = kelime[j];
		}
	}
	//yorum sat�r� 5 bitti
	printf("{ "); //dizi bi�iminde gozukmesi i�in kelimlestirilmis halinin bas�na ve sonuna {} eklemek icin yap�ld� yani g�runum icin yap�ld�
	bool ayracmi, ozel, ikisonrasiayracmi, birsonrasiayracmi;

	int l = 0;
	for (l = 0; l < diziboyut; l++)
	{
		ayracmi = ayrac(yenidizi[l]);				//karakter dizisinde eger bir terminal(; , " gibi degerlerin olup olmad�g�n� kontrol ettim )
		birsonrasiayracmi = ayrac(yenidizi[l + 1]); // virg�l atarken iki ayra� yanayana gelirse tek bir virg�l atmak gerekiyor sonras�n�n ayra�olup olmad�g�n� kontrol ettim
		ikisonrasiayracmi = ayrac(yenidizi[l + 2]); // ++ -- gibi durumlarda bir sonras�n� kontrol etti�imde + ve sonars� da + y� kontrol etmi� olurum buna gerek yok iki sonarsa�n� yani ++ dan sonra bir terminal var m� ?

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
					printf(",%c%c", yenidizi[l], yenidizi[l + 1]); //�rne�in ,++ yap�p sonras� ayra� ise ,(, yapmal�y�z bunun i�in yazd�m ==> ,++,(,
					l++;
				}
				else
				{
					if (l == diziboyut - 1)
					{
						printf(",%c%c", yenidizi[l], yenidizi[l + 1]); //en sonda 1 virg�l fazladan atmamas� gerekti�inden yazd�m
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
				printf(",%c", yenidizi[l]); //�rnek ); iki terminal yanyana gelirse ba��na ve sonuna virg�l atarsak ,),,;, olacag� i�in yapt�m
			}
			else
			{
				if (l == diziboyut - 1)
				{
					printf(",%c", yenidizi[l]); //sonda 1 virg�l fazla dan oldugu i�in yap�ld�
				}
				else
				{
					printf(",%c,", yenidizi[l]);
				}
			}
		}
		else
		{
			printf("%c", yenidizi[l]); //eger terminal degilse oldugu gibi yazmas� i�in yap�ld�
		}
	}
	printf("}");

	fclose(okunacakdosya);

	return 0;
}
