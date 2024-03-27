#ifndef LECTEURCARTE_H
#define LECTEURCARTE_H
//#include <lcarte.h>

class LecteurCarte
{
	private :
		int id ;

  	public :
		int id_vehicule ; 

		void initialiser();
		void lire_carte();
		int get_id();
		void attente_insertion();
		void attente_retrait();

};

#endif // LECTEURCARTE_H
