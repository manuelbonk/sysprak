#include <float.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
  double *eintraege;
  unsigned int breite;
  unsigned int hoehe;
} matrix;

/*
Initialisiert eine neue Matrix:
- reserviert lediglich den notwendigen Speicher
*/
matrix initMatrix(unsigned int breite, unsigned int hoehe){
	matrix result;
	double  *werte= malloc(breite*hoehe*sizeof(double));
	result.eintraege = werte;
	result.breite = breite;
	result.hoehe = hoehe;
	return result;

}


/*
Initialisiert eine neue Matrix:
- reserviert den notwendigen Speicher
- befuellt die Matrix mit 0
*/
matrix initMatrixZero(unsigned int breite, unsigned int hoehe){
	matrix result;
	double  *werte= calloc(breite*hoehe,sizeof(double));
	result.eintraege = werte;
	result.breite = breite;
	result.hoehe = hoehe;
	return result;
}

/*
Initialisiert eine neue Matrix:
- reserviert den notwendigen Speicher
- befuellt die Matrix mit Zufallszaheln
*/
matrix initMatrixRand(unsigned int breite, unsigned int hoehe){
	matrix result = initMatrix(breite, hoehe);
	srand(time(NULL));
	for (int i=0;i<breite*hoehe;i++){
		result.eintraege[i]=rand()%100;
	}
	return result;
}

/*
Kopiert eine Matrix und gibt die Kopie zurueck
*/
matrix copyMatrix(matrix toCopy){
	matrix result = initMatrix(toCopy.breite,toCopy.hoehe);
	result.eintraege=toCopy.eintraege;
	return result;
}

/*
"Zerstoert" eine Matrix
- gibt reservierten Speicher wieder frei
- setzt alle Werte auf NULL bzw. "0"
*/
void freeMatrix(matrix toDestroy){
	toDestroy.breite=0;
	toDestroy.hoehe=0;
	free(toDestroy.eintraege);
}

/*
Gibt den Eintrag der Matrix an der Stelle (xPos, yPos) zurueck, DBL_MAX im Fehlerfall
*/
double getEntryAt(matrix a, unsigned int xPos, unsigned int yPos){
	return a.eintraege[xPos+a.breite*yPos];
}

/*
Setzt den Eintrag der Matrix an der Stelle (xPos, yPos)
Rueckgabe: true, false im Fehlerfall
*/
bool setEntryAt(matrix a, unsigned int xPos, unsigned int yPos, double value){
	if (xPos > a.breite || yPos > a.hoehe){
		return false;
	}
	a.eintraege[xPos+a.breite*yPos]=value;
	return true;
}

/*
Gibt eine Matrix auf der Kommandozeile aus
*/
void prettyPrint(matrix a){

	for(int y=0;y<a.hoehe;y++){
		for(int x=0;x<a.breite;x++){
			printf("%15.7f ",a.eintraege[x+a.breite*y]);
		}
		printf("\n");
	}
	printf("\n");
}

/*
Addiert zwei Matrizen
Rueckgabe:
- Ergebnis der Addition in neu erzeugter Matrix
- Matrix der Groesse "0" im Fehlerfall
*/
matrix addMatrix(matrix a, matrix b){
	if (a.breite != b.breite || a.hoehe != b.hoehe){
		return initMatrix(0,0);
	}
	matrix result=initMatrix(a.breite,a.hoehe);
	for (int i=0;i<a.breite*a.hoehe;i++){
		result.eintraege[i]=a.eintraege[i]+a.eintraege[i];
	}
	return result;
}

/*
Subtrahiert zwei Matrizen:
Rueckgabe: "a - b"
- Ergebnis der Subtraktion in neu erzeugter Matrix
- Matrix der Groesse "0" im Fehlerfall
*/
matrix subMatrix(matrix a, matrix b){
	if (a.breite != b.breite || a.hoehe != b.hoehe){
		return initMatrix(0,0);
	}
	matrix result=initMatrix(a.breite,a.hoehe);
	for (int i=0;i<a.breite*a.hoehe;i++){
		result.eintraege[i]=a.eintraege[i]-a.eintraege[i];
	}
	return result;
}

/*
Multipliziert zwei Matrizen:
Rueckgabe: "a * b"
- Ergebnis der Multiplikation in neu erzeugter Matrix
- Matrix der Groesse "0" im Fehlerfall
*/

// probably broken

matrix multMatrix(matrix a, matrix b){
	if (a.breite != b.hoehe){
		return initMatrix(0,0);
	}
	matrix result=initMatrixZero(b.breite,a.hoehe);
	// calculate every result.eintraege value
	for (int i=0;i<b.breite*a.hoehe;i++){
		int x,y;
		if ((i+1)%result.breite!=0){
			x=i%result.breite;
			y=(i-x)/result.breite;
		}
		else {
			x=result.breite-1;
			y=i%result.breite;
			}
		// do the actual math
		double cellvalue = 0;
		for (int j=0;j<a.breite;j++){
			cellvalue+=(getEntryAt(a,j,y)*getEntryAt(b,x,y));
		}
		setEntryAt(result,x,y,cellvalue);
	}
	return result;
}

/*
Transponiert eine Matrix:
Rueckgabe: "a^T"
*/
matrix transposeMatrix(matrix a);

/*
Gibt die Determinante der Matrix a zurueck, DBL_MAX im Fehlerfall
*/
double determinante(matrix a); // ein einfacher Algorithmus reicht fuer kleine Matrizen
double detQuick(matrix a);     // wer moechte kann ein effizientes Verfahren implementieren
