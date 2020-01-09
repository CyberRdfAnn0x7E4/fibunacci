#include <stdio.h>
#include <time.h>
#define MAX 10000

int main()
{

/*
 * Zahl soll als Array, wobei jede Stelle im Dezimalsystem einer Array-Komponente entspricht
 *
 * z.B. 1234567891234567 soll im int-Array so aussehen:
 *
 * int char[MAX] = {1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,-10};
 *
 * Umwandlung in:
 *
 * int zahl[MAX] = {7,6,5,4,3,2,1,9,8,7,6,5,4,3,2,1,10};
 *
 * die unötigen {}-Klammern dienen nur zur übersicht. Funktionen darf man ja nicht :'(
 *
 */
	int sehrAlt[MAX] = {0,-10}, alt[MAX] = {0,-10}, neu[MAX] = {1,-10}, anzahlFibonacciZahlen[MAX] = {1, -10}, fiboZahlNr[MAX] = {2, -10};
	int k = 0, i = 0, gemerkt, temp,
			anzahlStellenAktuellerFiboZahl, //Anzahl Ziffern in der aktuellen fibo zahl
			anzahlStellenEingabe; // Anzhal Ziffern in der Eingabe
	char eingabe[MAX] = "500";
	char stop = 0;
	clock_t begin = clock();


	{	//umdrehen und int wandlung der eingabe zu maxStelle:
		printf("Fibonacci-Folge bis %s\n", eingabe);
		while(eingabe[i+1] != 0) i++;

		while(i >= 0){
			anzahlFibonacciZahlen[k++] = eingabe[i--] - '0';
		}
		anzahlStellenEingabe = k;
		anzahlFibonacciZahlen[k] = -10;
		i = 0;

		printf("Max stelle als int und umgedreht: ");
		while(anzahlFibonacciZahlen[i] != -10){
			printf("%d", anzahlFibonacciZahlen[i++]);
		}
	}

	while (anzahlFibonacciZahlen[anzahlStellenEingabe] != -10) anzahlStellenEingabe++;

	while(1){

		{	//ueberpruefung ob die letzte Zahl schon erreicht ist, wenn ja -> break:
			anzahlStellenAktuellerFiboZahl = 0;
			while(fiboZahlNr[anzahlStellenAktuellerFiboZahl] != -10) anzahlStellenAktuellerFiboZahl++;

			if(anzahlStellenAktuellerFiboZahl > anzahlStellenEingabe){
				stop = 1;
			}else if(anzahlStellenAktuellerFiboZahl == anzahlStellenEingabe){
				i = anzahlStellenEingabe-1;
				while(i >= 0){
					if(fiboZahlNr[i] > anzahlFibonacciZahlen[i]){
						stop = 1;
						break;
					}
					else if(fiboZahlNr[i] < anzahlFibonacciZahlen[i]){
						break;
					}

					i--;
				}
			}
			if(stop) break;
		}

		{	// copy arrays: alt -> sehrAlt; neu -> alt
			i = 0;
			do{
				sehrAlt[i] = alt[i];
			}while(alt[i++] != -10);
			i = 0;
			do{
				alt[i] = neu[i];
			}while(neu[i++] != -10);
		}

		{	// berechnung der näschsten fibo zahl (könnte man optimieren)
			gemerkt = i = 0;
			while(alt[i] != -10 || gemerkt != 0){
				if(alt[i] == -10) {
					alt[i] = 0;
					alt[i+1] = -10;
				}
				if(sehrAlt[i] == -10){
					sehrAlt[i] = 0;
					sehrAlt[i+1] = -10;
				}
				temp = alt[i] + sehrAlt[i];
				temp += gemerkt;

				if(temp > 9){
					gemerkt = temp / 10;
					temp -= (gemerkt * 10);
				}
				else{
					gemerkt = 0;
				}
				neu[i] = temp;
				i++;
			}

			neu[i] = -10;
		}

		{// ausgabe der fibo zahl
			printf("\n");
			i = anzahlStellenAktuellerFiboZahl - 1;
			while(i >= 0) printf("%d", fiboZahlNr[i--]);
			printf("\t->\t");
			i = 0;
			while(neu[i+1] != -10) i++;
			while(i >= 0) printf("%d", neu[i--]);
		}


		{// erhohe fiboZahlNr um 1
			i = 0;
			k = 1;
			while(fiboZahlNr[i] + 1 >= 10){
				fiboZahlNr[i] = fiboZahlNr[i] + 1 - 10;
				i++;
				if(fiboZahlNr[i] == -10) {
					fiboZahlNr[i] = 0;
					fiboZahlNr[i+1] = -10;
				}
			}
			fiboZahlNr[i]++;
		}
	}

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\n\nBerechnungsdauer: %f Sekunden", time_spent);

	printf("\n\n");
	return 0;
}

