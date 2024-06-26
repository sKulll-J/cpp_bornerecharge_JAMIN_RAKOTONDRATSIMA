#include<stdio.h>

#include <unistd.h>
#include "lecteurcarte.h"
#include "baseclient.h"

#include "voyants.h"
#include "bouton.h"
#include "prise.h"
#include "timer.h"
#include "generateur_save.h"

//=================================================================

// attributs privés
int carte_id ;

//=================================================================

// méthodes
void lecteurcarte_initialiser()
{
	initialisations_ports();
	init_voyant();
	init_bouton();
	init_timer();
	generateur_init();
}

void lecteurcarte_lire_carte()
{	
	int strt_timer, timer;
	printf("inserer carte \n");
	attente_insertion_carte();
	
	carte_id = lecture_numero_carte();

	printf("numero carte : %d \n", carte_id );

	if ( baseclient_authentifier( carte_id ) == 1 )
	{	
		// AUTHENTIFICATION REUSSIE
		printf("Autentification réussie \n");

		timer_raz(&strt_timer); //mise a zero du timer
		while( (bouton_charge() != 1) && (timer_elapsed(&timer,&strt_timer)<=8))
		{	// attente de 8 secondes d'un appui sur le bouton charge

			voyants_blink_charge();
			//printf("--\nbut charge :%d\n",bouton_charge());
			//printf("blink - time:%d\n",timer_elapsed(&timer,&strt_timer)<=8);
		}

		if(bouton_charge() ==1)
		{	// si bouton appuyé dans les temps
			
			voyants_set_dispo(0);
			
			printf("retirer carte\n");
			attente_retrait_carte();
			//printf("carte retiree \n");
			
			generateur_charger(); // charger
		}

		else
		{	// temps imparti écoulé
			voyants_set_default(2);
			printf("Temps ecoule\n"); 	
			printf("retirer carte\n");
			attente_retrait_carte();
			printf("carte retiree \n");
		}
		
		
	}

	else 
	{	//ECHEC AUTHENTIFICATION
		voyants_set_default(2);
		printf("Autentification echec \n"); 	
		printf("retirer carte\n");
		attente_retrait_carte();
		printf("carte retiree \n");
	}

	
	
	
}
