#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//yorum satırlarını numaralandırırak yaptım her numara "//" arasını ifade edicek
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

//yorum satırı 1 alttaki kodda ++ -- gibi kontrolleri yaptım çünkü bunlar ayrı ayrı olucak kavramlar değil
//c de beraber yazılan yapılar oldugu için böyle bir şey yaptım ayrıca virgül atarken dogru virgül atabilmemi sağladı.
//bunlar özel durumlar oldugu için diziye atmak daha fazla işleme neden olacağı içi böyle tercih ettim
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
//yorum satırı 1 bitti

//yorum satırı 2 alttaki kodda ayraç olup omadıgını kontrol ettim dogru bir biçimde virgül atabilmek için
//bazılarını ascii olarak yazdım "'" kodun okunurlugu açısından güzel olmadıgından bunun gibi örnekleri ascii olarak yazdım
//32=bosluk tusu   34="(çift tırnak)  39='(tektırnak)

int ayrac(char karakter)
{
	char dizi[26] = {'+', '-', '*', '/', ',', ';', '>', '<', '[', ']', '{', '}', ')', '(', '=', '|', '&', 34, 39, '!', 92, ':', '?', '^', '%', '.'};
	int i = 0, deger = 0;
	bool fonksiyondancik = true; // iki nedeni var 1.neden eger terminal'i bulursa deger=1 olucak ama hala devam edicek bir sonrakinde bulamayınca deger 0 olucak ve hatalı çalışıcak 2.neden ise buldugu anda diziye deam etmemesini sağlamak zaman kaybetmemesi için.
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

	//yorum satırı 3 bu kod satırını dosyanın sonuna kadar okumamı ve fgetc fonksiyonu ile karakter karakter okuyup bir karakter dizisine
	//atmaişlemini gerçekleştirdim .dosyayı okurken EOF kavramını kullandım EOF txt metinin son harfini gösteren bir işaretçi
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

	// yorum satırı 3 bitti

	// yorum satırı 4 fgetc fonksiyonu bosluk tab enter tusunu da bir karakter olarak aldıgı için bunları dizide
	//kaydırma yaparak bir nevi yok ettim yani karakter dizimde bosluk tab ve enter tuşlarını kaldırdım
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
	//yorum satırı 4 bitti

	//yorum satırı 5 olası boslukları garantilemek için yeni bir diziye bosluksuz halini attım
	int diziboyut = 0;
	for (j = 0; j < i - 1 - bosluk; j++)
	{
		if (kelime[j] != 32)
		{
			diziboyut++;
			yenidizi[j] = kelime[j];
		}
	}
	//yorum satırı 5 bitti
	printf("{ "); //dizi biçiminde gozukmesi için kelimlestirilmis halinin basına ve sonuna {} eklemek icin yapıldı yani görunum icin yapıldı
	bool ayracmi, ozel, ikisonrasiayracmi, birsonrasiayracmi;

	int l = 0;
	for (l = 0; l < diziboyut; l++)
	{
		ayracmi = ayrac(yenidizi[l]);				//karakter dizisinde eger bir terminal(; , " gibi degerlerin olup olmadıgını kontrol ettim )
		birsonrasiayracmi = ayrac(yenidizi[l + 1]); // virgül atarken iki ayraç yanayana gelirse tek bir virgül atmak gerekiyor sonrasının ayraçolup olmadıgını kontrol ettim
		ikisonrasiayracmi = ayrac(yenidizi[l + 2]); // ++ -- gibi durumlarda bir sonrasını kontrol ettiğimde + ve sonarsı da + yı kontrol etmiş olurum buna gerek yok iki sonarsaını yani ++ dan sonra bir terminal var mı ?

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
					printf(",%c%c", yenidizi[l], yenidizi[l + 1]); //örneğin ,++ yapıp sonrası ayraç ise ,(, yapmalıyız bunun için yazdım ==> ,++,(,
					l++;
				}
				else
				{
					if (l == diziboyut - 1)
					{
						printf(",%c%c", yenidizi[l], yenidizi[l + 1]); //en sonda 1 virgül fazladan atmaması gerektiğinden yazdım
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
				printf(",%c", yenidizi[l]); //örnek ); iki terminal yanyana gelirse başına ve sonuna virgül atarsak ,),,;, olacagı için yaptım
			}
			else
			{
				if (l == diziboyut - 1)
				{
					printf(",%c", yenidizi[l]); //sonda 1 virgül fazla dan oldugu için yapıldı
				}
				else
				{
					printf(",%c,", yenidizi[l]);
				}
			}
		}
		else
		{
			printf("%c", yenidizi[l]); //eger terminal degilse oldugu gibi yazması için yapıldı
		}
	}
	printf("}");

	fclose(okunacakdosya);

	return 0;
}
