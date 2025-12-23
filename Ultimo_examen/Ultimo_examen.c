#include <stdio.h>

/*
Equipo: Azul;

Integrantes: Gonzalez Melchor Abraham

*/

//prototipos
float sigma (int n, float x[]);
int Maximo (int n, float x[]);
int Minimo (int n, float x[]);
void Ordena ();
float Mediana ();

int NAños;
float Copia[50];

int main(){
	
	int i,j,Año[50],Mes_Max[50],Mes_Min[50],Anio_Max[12],Anio_Min[12];
	float Ventas[50][12],Suma_An[50],Prom_An[50],Max_An[50],Min_An[50];
	float Suma_Mes[12],Prom_Mes[12],Max_Mes[12],Min_Mes[12];
	float VentasOrd[50][12], mediana[50];

	FILE *Entrada;
	Entrada = fopen("Ventas.txt","r");

	FILE *Salida;
	Salida = fopen("Resultados.txt","w");

	fscanf(Entrada,"%d",&NAños);

	for(i=0;i<NAños;i++){

		fscanf(Entrada,"%d",&Año[i]);

		for(j=0;j<12;j++){
			fscanf(Entrada,"%f",&Ventas[i][j]);
			Copia[j] = Ventas[i][j];
		}
		Suma_An[i] = sigma(12,Copia);
		Prom_An[i] = Suma_An[i]/12;

		Mes_Max[i] = Maximo(12,Copia);
		Max_An[i] = Copia[Mes_Max[i]];

		Mes_Min[i] = Minimo(12,Copia);
		Min_An[i] = Copia[Mes_Min[i]];
	}

	for(j=0;j<12;j++){

		for(i=0;i<NAños;i++){
			Copia[i] = Ventas[i][j];
		}

		Suma_Mes[j] = sigma(NAños,Copia);
		Prom_Mes[j] = Suma_Mes[j]/NAños;

		Anio_Max[j] = Maximo(NAños,Copia);
		Max_Mes[j] = Copia[Anio_Max[j]];

		Anio_Min[j] = Minimo(NAños,Copia);
		Min_Mes[j] = Copia[Anio_Min[j]];
		Ordena();
		for(i=0;i<NAños;i++){
			VentasOrd[i][j] = Copia[i];
		}
		mediana[j] = Mediana();
	}

	fprintf(Salida,"|------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|--------|--------|---------|--------|---------|\n");
	fprintf(Salida,"| An~o |   ENE   |   FEB   |   MAR   |   ABR   |   MAY   |   JUN   |   JUL   |   AGO   |   SEP   |   OCT   |   NOV   |   DIC   |  SUMA   |  PROM  |  MAX   | MES_MAX |  MIN   | MES_MIN |\n");
	fprintf(Salida,"|------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|--------|--------|---------|--------|---------|\n");
	for(i=0;i<NAños;i++){
		fprintf(Salida,"|%5d |", Año[i]);

		for(j=0;j<12;j++){
			fprintf(Salida," %7.2f |",Ventas[i][j]);
		}

		fprintf(Salida," %7.2f | %6.2f | %6.2f |   %2d    | %6.2f |   %2d    |\n",Suma_An[i],Prom_An[i],Max_An[i],Mes_Max[i],Min_An[i],Mes_Min[i]);

	}
	fprintf(Salida,"|------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|--------|--------|---------|--------|---------|\n");

	fprintf(Salida,"| SUMA |");
	for(i=0;i<12;i++){
		fprintf(Salida,"%7.2f |",Suma_Mes[i]);
	}

	fprintf(Salida,"\n");
	fprintf(Salida,"| PROM |");
	for(i=0;i<12;i++){
		fprintf(Salida," %7.2f |",Prom_Mes[i]);
	}

	
	fprintf(Salida,"\n\n");
	fprintf(Salida,"| MAX  |");
	for(i=0;i<12;i++){
		fprintf(Salida," %7.2f |",Max_Mes[i]);
	}
	
	fprintf(Salida,"\n");
	fprintf(Salida,"|AN_MAX|");
	for(i=0;i<12;i++){
		fprintf(Salida," %7d |",Año[Anio_Max[i]]);
	}
	
	fprintf(Salida,"\n\n");
	fprintf(Salida,"| MIN  |");
	for(i=0;i<12;i++){
		fprintf(Salida," %7.2f |",Min_Mes[i]);
	}
	
	fprintf(Salida,"\n");
	fprintf(Salida,"|AN_MIN|");
	for(i=0;i<12;i++){
		fprintf(Salida," %7d |",Año[Anio_Min[i]]);
	}
	
	fprintf(Salida,"\n");
	fprintf(Salida,"|------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|\n");

	fprintf(Salida,"\n|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|\n");
	fprintf(Salida,"|   NUM   |   ENE   |   FEB   |   MAR   |   ABR   |   MAY   |   JUN   |   JUL   |   AGO   |   SEP   |   OCT   |   NOV   |   DIC   |\n");
	fprintf(Salida,"|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|\n");
	for(i=0;i<NAños;i++){
		fprintf(Salida,"|   %3d   |",i+1);
		for(j=0;j<12;j++){
			fprintf(Salida," %7.2f |",VentasOrd[i][j]);
		}
		fprintf(Salida, "\n");
	}
	fprintf(Salida,"|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|\n");
	fprintf(Salida,"|   MED   |");
	for(i=0;i<12;i++){
		fprintf(Salida," %7.2f |",mediana[i]);
	}
	fprintf(Salida,"\n");
	fprintf(Salida,"|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|\n");
	fclose(Entrada);
	fclose(Salida);
	return 0;
}

float sigma (int n, float x[]){
	int k;
	float suma;
	suma = 0;
	for(k=0;k<n;k++)
		suma += x[k];
	return suma;
}

int Maximo (int m, float y[]){
	int k,max;
	float big = -999999;
	for(k=0;k<m;k++){
		if(big<y[k]){
			big = y[k];
			max = k;
		}
	}
	return max;
}

int Minimo (int p, float z[]){
	int k,min;
	float small = 999999;
	for(k=0;k<p;k++){
		if(small>z[k]){
			small = z[k];
			min = k;
		}
	}
	return min;
}

void Ordena(){
	int Arriba,Abajo;
	float temp;
	for(Arriba = 0; Arriba < NAños-1; Arriba++){
		for(Abajo = Arriba+1; Abajo < NAños; Abajo++){
			if(Copia[Arriba] > Copia[Abajo]){
				temp = Copia[Arriba];
				Copia[Arriba] = Copia[Abajo];
				Copia[Abajo] = temp;
			}
		}
	}
}

float Mediana(){
	if(NAños%2 == 1){
		return Copia[NAños/2];
	}
	else{
		return (Copia[(NAños/2)-1] + Copia[NAños/2])/2;
	}
}