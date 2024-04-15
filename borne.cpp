#include <iostream>
#include <memoire_borne.h>
#include <donnees_borne.h>

#include "lecteurcarte.h"

#include "voyant.h"
#include "voyant.cpp"

#include "bouton.h"
#include "bouton.cpp"

#include "prise.h"
#include "prise.cpp"

#include "timer.h"
#include "timer.cpp"

#include "generateur.h"
#include "generateur.cpp"

#include "baseclient.h"
#include "baseclient.cpp"

using namespace std;


int shmid ;

void charger(Voyant voyant, Prise prise, Generateur generateur, Baseclient baseclient, LecteurCarte lecteurcarte);

int main()
{	
	io = acces_memoire(&shmid);
    	int carte_id ;
    	int strt_timer, time;
    	
	LecteurCarte lecteurcarte ;
	Voyant voyant ;
	Timer timer;
	Bouton bouton;
	Generateur generateur;
	Prise prise;
	Baseclient database;

    while (1)
    {
	// lecteurcarte.lire_carte();	// test 
		
	cout<<"==== \nnew Lecture\n"<<endl;
	
	cout<<"Inserez votre carte"<<endl;
	attente_insertion_carte();
	
	carte_id = lecture_numero_carte();
	
	cout<<">Carte insérée .." << endl << endl;
	cout<<">Carte numéro " << lecture_numero_carte() << endl;
	
	if (database.authentifier(carte_id) == 1)
	{	
		// AUTHENTIFICATION REUSSIE
		cout<< "Autentification réussie \n" <<endl ;
	
		timer.raz(&strt_timer);//mise a zero du timer
		while( (bouton.charge() != 1) && (timer.elapsed(&time,&strt_timer) <=8))
		{	// attente de 8 secondes d'un appui sur le bouton charge
	
			voyant.blink_charge();

		}

		if(bouton.charge() ==1)
		{	// si bouton appuyé dans les temps
			
			voyant.set_dispo(0);
			
			cout<< "retirer carte\n" << endl ;
			attente_retrait_carte();

		
			//generateur.charger(voyant, prise, generateur); // charger
			charger(voyant, prise, generateur, database, lecteurcarte);
		}

		else
		{	// temps imparti écoulé
			voyant.set_default(2);
			cout<< "Temps ecoule\n"<< endl; 	
			cout<< "retirer carte\n"<<endl;
			attente_retrait_carte();
			cout<< "carte retiree \n"<<endl;
		}
	}
    }
    
    return 0;
}

void charger(Voyant voyant, Prise prise, Generateur generateur, Baseclient baseclient, LecteurCarte lecteurcarte )
{
	voyant.set_charge(2); // Voyant charge => ROUGE
	prise.deverouiller_trappe(); 
	
	
// MEF
	typedef enum _etat {A,B,C,D,E,F, pre_deconnect, deconnect, END} etat;
	etat etat_present, etat_suivant ;
	
	// initialisation 
	etat_present = A ;
	etat_suivant = A ;
	
	cout << "Branchez la prise\n" << endl;
	while(etat_present!=END)
	{
		//Block F : transitions
		if ((etat_present == A) && (io->gene_u == 9) && io->gene_pwm==DC)
		{	etat_suivant = B ;
			cout << ">prise branchee \n" << endl ;
		}
		
 		else if (etat_present == B)
		{	
			if ((io->gene_u == 9) && io->gene_pwm == AC_1K )
			{	etat_suivant = C;
				cout << "connection à la voiture\n" << endl;
			}
			else if (io->bouton_stop ==1)
			{	etat_suivant = E;
				cout << "demande STOP\n" << endl;
			}
		}
		else if (etat_present == C)
		{
			if(io->gene_u == 6)
			{	etat_suivant = D;
				cout << "charge en cours ...\n" <<endl;
			}
			else if(io->bouton_stop==1)
			{	etat_suivant=E;
				cout << "demande STOP\n" << endl;
			}
		}
		else if (etat_present == D)
		{
			if( (io->bouton_stop==1) || (io->gene_u == 9) && (io->gene_pwm !=DC) )
			{
				etat_suivant=E;
				cout << "Fin de charge\n" << endl;
			}
		}
		else if (etat_present == E)
		{
			if (io->gene_pwm = DC)
			{	etat_suivant =F;
				cout << "recuperer vehicule\n" <<endl ;
			}
		}
		//-----------------------------------------------------
		else if (etat_present == F)
		{	
			attente_insertion_carte();
			int carte_id = lecture_numero_carte();
			
			if (lecteurcarte.get_id() == carte_id)
			{
				cout << "\n---\nID Correct\n---\n" <<endl;
				if (baseclient.authentifier(carte_id)==1)
				{
					// authentification réussie
					cout << "debrancher vehicule \n" << endl;
					voyant.set_charge(0); // voyant charge : off
					prise.deverouiller_trappe();
					etat_suivant = deconnect;
				}
				else
				{	//authentification echec
					cout << "mauvais mdp \n" <<endl ;
					cout << "retirer carte \n"<< endl;
					attente_retrait_carte();
					cout << "carte retiree\n" <<endl;
					etat_suivant=F;
				}
			}
			else
			{
				cout <<"CECI N'EST PAS VOTRE VEHICULE \n" <<endl;
				cout <<"retirer carte et reessayer\n"<<endl;
				attente_retrait_carte();
				cout << "carte retiree\n" <<endl;
				etat_suivant=F;
			}
		}
		else if (etat_present == deconnect)
		{
			if ( (io->gene_u=12) && (io->gene_pwm = DC) )
			{
				prise.verouiller_trappe();
				cout << "retirer carte \n"<< endl;
				attente_retrait_carte();
				cout << "carte retiree\n" <<endl;
				etat_suivant=END;
			}
		}
		//-----------------------------------------------------
		//Blok M : mémoire
		etat_present = etat_suivant;

		//Block G : sorties
		if(etat_present == A)
		{
			voyant.set_charge(2); // Voyant charge => Rouge
			prise.deverouiller_trappe();
			generateur.generer_PWM(1); // 12V DC output
	
		}

		if(etat_present == B)
		{
			prise.set_prise(1); // Voyant Prise => Vert
			prise.verouiller_trappe();
			generateur.generer_PWM(2); // AC_1K output
		}
		
		if(etat_present == C)
		{
			generateur.fermer_AC();
			generateur.generer_PWM(3); // AC_CL output
		}
		
		if(etat_present == D)
		{
			generateur.generer_PWM(3); // AC_CL output
		}
		if(etat_present == E)
		{
			generateur.ouvrir_AC();
			voyant.set_charge(1); // Voyant charge => Vert
			generateur.generer_PWM(1); // DC output
		}
	}
}
