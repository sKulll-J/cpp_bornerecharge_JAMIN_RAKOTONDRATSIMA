#include "Generateur.h"

#include<donnees_borne.h>
#include<memoire_borne.h>


#include "voyant.h"
#include "Prise.h"

entrees* io ;
int shmid ;

Generateur :: Generateur()
{
	io=acces_memoire(&shmid);
}

Generateur :: charger()
{
	Voyant :: set_charge(2); // Voyant charge => ROUGE
	Prise_deverouiller_trappe(); 
	
	
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
			Voyant :: set_charge(2); // Voyant charge => Rouge
			Prise :: deverouiller_trappe();
			Generateur :: generer_PWM(1); // 12V DC output
	
		}

		if(etat_present == B)
		{
			Prise :: set_Prise(1); // Voyant Prise => Vert
			Prise :: verouiller_trappe();
			Generateur :: generer_PWM(2); // AC_1K output
		}
		
		if(etat_present == C)
		{
			Generateur :: fermer_AC();
			Generateur :: generer_PWM(3); // AC_CL output
		}
		
		if(etat_present == D)
		{
			Generateur :: generer_PWM(3); // AC_CL output
		}
		if(etat_present == E)
		{
			Generateur :: ouvrir_AC();
			voyant :: set_charge(1); // Voyant charge => Vert
			Generateur :: generer_PWM(1); // AC_CL output
			printf("Etat E\n");
		}
	}
}

Generateur :: ouvrir_AC()
{
	io->contacteur_AC = 0;
}

Generateur :: fermer_AC()
{
	io->contacteur_AC = 1;
}



Generateur :: generer_PWM(int etat)
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