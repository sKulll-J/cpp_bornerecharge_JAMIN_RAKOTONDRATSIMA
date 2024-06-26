#include<stdio.h>
#include<donnees_borne.h>
#include<memoire_borne.h>

#include "generateur_save.h"
#include "voyants.h"
#include "prise.h"

entrees* io ;
int shmid ;

void generateur_init()
{
	io=acces_memoire(&shmid);
}

void generateur_charger()
{
	voyants_set_charge(2); // Voyant charge => ROUGE
	prise_deverouiller_trappe(); 
	
	
// MEF
	typedef enum _etat {A,B,C,D,E} etat;
	etat etat_present, etat_suivant ;
	
	// initialisation 
	etat_present = A ;
	etat_suivant=A;
	
	while(etat_present!=E)
	{
		//Block F : transitions
		if ((etat_present == A) && (io->gene_u == 9))
			etat_suivant = B ;
	
 		else if (etat_present == B)
		{	
			if (io->gene_u == 9)
				etat_suivant = C;
			else if (io->bouton_stop ==1)
				etat_suivant = E;
			printf("Etat B\n");
		}
		else if (etat_present == C)
		{
			if(io->gene_u == 6)
				etat_suivant = D;
			else if( (io->bouton_stop==1)||(io->gene_u == 9) )
				etat_suivant=E;
			printf("Etat C\n");
		}
		else if (etat_present == D)
		{
			if( (io->bouton_stop==1)||(io->gene_u == 9) )
				etat_suivant=E;
			printf("Etat D\n");
		}
	
		//Blok M : mémoire
		etat_present = etat_suivant;

		//Block G : sorties
		if(etat_present == A)
		{
			voyants_set_charge(2); // Voyant charge => Rouge
			prise_deverouiller_trappe();
			generateur_generer_PWM(1); // 12V DC output
	
		}

		if(etat_present == B)
		{
			prise_set_prise(1); // Voyant prise => Vert
			prise_verouiller_trappe();
			generateur_generer_PWM(2); // AC_1K output
		}
		
		if(etat_present == C)
		{
			generateur_fermer_AC();
			generateur_generer_PWM(3); // AC_CL output
		}
		
		if(etat_present == D)
		{
			generateur_generer_PWM(3); // AC_CL output
		}
		if(etat_present == E)
		{
			generateur_ouvrir_AC();
			voyants_set_charge(1); // Voyant charge => Vert
			generateur_generer_PWM(1); // AC_CL output
			printf("Etat E\n");
		}
	}
}

void generateur_ouvrir_AC()
{
	io->contacteur_AC = 0;
}

void generateur_fermer_AC()
{
	io->contacteur_AC = 1;
}



void generateur_generer_PWM(int etat)
{
	switch(etat)
	{
		case 0:
			io->gene_pwm = STOP;
			break;
		case 1 :
			io->gene_pwm = DC;
			break;
		case 2 :
			io->gene_pwm = AC_1K;
			break;
		case 3 :
			io->gene_pwm =  AC_CL;
			break;
		default :
			io->gene_pwm = STOP;
			break;	
	}		
}
