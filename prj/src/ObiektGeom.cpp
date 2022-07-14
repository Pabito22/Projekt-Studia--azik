#include <iostream>
#include <fstream>
#include "ObiektGeom.hh"





using namespace std;

ObiektGeom::ObiektGeom( const char*  sNazwaPliku_BrylaWzorcowa,
		        const char*  sNazwaObiektu,
		        int          KolorID,
            Wektor3D Skl,
            Wektor3D Pl
		       ):
  _NazwaPliku_BrylaWzorcowa(sNazwaPliku_BrylaWzorcowa), _KolorID(KolorID)
{
  _NazwaObiektu = sNazwaObiektu;
  _NazwaPliku_BrylaRysowana = NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA;
  _NazwaPliku_BrylaRysowana += "/";
  _NazwaPliku_BrylaRysowana += sNazwaObiektu;
  _NazwaPliku_BrylaRysowana += ".dat";
  Skala = Skl;        //added
  Polozenie = Pl;     //added
}




bool ObiektGeom::Przelicz_i_Zapisz_Wierzcholki(std::istream &StrmWe, std::ostream &StrmWy)
{
  

  double All_X[IloscWektorowBrylaWzorcowa];
  double All_Y[IloscWektorowBrylaWzorcowa];

  //double  WspX, WspY, WspZ;
  Wektor3D Wsp;

  int Indeks_Wiersza = 0;
  int Indeks_Wektora_zPliku = 0;
  
  //StrmWe >> WspX >> WspY >> WspZ;
  StrmWe >> Wsp[0] >> Wsp[1] >> Wsp[2];

  if (StrmWe.fail())return false;
  
  do {
    /*WspX = WspX*SkalaX+PolozenieX;
    WspY = WspY*SkalaY+PolozenieY;    
    WspZ = WspZ*SkalaZ+PolozenieZ;*/

    

    Wsp = MacRotacji * Wsp;

    for(uint  i=0; i<ROZMIAR; ++i){
      Wsp[i] = Wsp[i]*(this->Skala[i])+this->Polozenie[i];
    }

    /*Wsp[0] = Wsp[0]*(this->Skala[0])*sin(30*PI/180)+this->Polozenie[0];
    Wsp[1] = Wsp[1]*(this->Skala[1])*cos(30*PI/180)+this->Polozenie[1];
    Wsp[2] = Wsp[2]*(this->Skala[2])+this->Polozenie[2];*/

    //std::cout<<"MAcierz :"<<MacRotacji<<std::endl;
    //Wsp = ((this->MacRotacji*(this->Skala))&(Wsp)) + this->Polozenie;
    

    //StrmWy << WspX << " " << WspY << " " << WspZ << endl;
    StrmWy << Wsp[0] << " " << Wsp[1] << " " << Wsp[2] << endl;

    //save all the data 
    All_X[Indeks_Wektora_zPliku] = Wsp[0];
    All_Y[Indeks_Wektora_zPliku]= Wsp[1];


    ++Indeks_Wiersza;
    ++Indeks_Wektora_zPliku;
    
    if (Indeks_Wiersza >= 4) {
      StrmWy << endl;
      Indeks_Wiersza = 0;
    }
    
    StrmWe >> Wsp[0] >> Wsp[1] >> Wsp[2];

    
    
  } while (!StrmWe.fail());

  if (!StrmWe.eof()) return false;


  
  

  //now taking the LeftBottom and Right Up values
  
  double Min_x = All_X[0];
  for(int i= 0; i< IloscWektorowBrylaWzorcowa; ++i){
    if(All_X[i] < Min_x){
      Min_x = All_X[i];
    }
  }

  
  double Min_y = All_Y[0];
  for(int j=0; j< IloscWektorowBrylaWzorcowa; ++j){
    if(All_Y[j] < Min_y){
      Min_y = All_Y[j];
    }
  }

  
  double Max_x = All_X[0];
  for(int z = 0; z < IloscWektorowBrylaWzorcowa; ++z){
    if(All_X[z] >Max_x){
      Max_x = All_X[z];
    }
  }

  
  double Max_y = All_Y[0];
  for(int w=0; w < IloscWektorowBrylaWzorcowa; ++w){
    if(All_Y[w] >Max_y){
      Max_y = All_Y[w];
    }
  }

  _Obrys.get_Wiersz_DolnyLewy()[0] = Min_x;
  _Obrys.get_Wiersz_DolnyLewy()[1] = Min_y;
  _Obrys.get_Wiersz_GornyPrawy()[0] = Max_x;
  _Obrys.get_Wiersz_GornyPrawy()[1] = Max_y;


  return Indeks_Wiersza == 0 && !StrmWy.fail();

}



bool ObiektGeom::Przelicz_i_Zapisz_Wierzcholki()
{
  ifstream  StrmWe(_NazwaPliku_BrylaWzorcowa);
  ofstream  StrmWy(_NazwaPliku_BrylaRysowana);

  if (!(StrmWe.is_open() && StrmWy.is_open())) {
    cerr << endl << "Nie mozna otworzyc jednego z plikow:" << endl
	 << "    " << _NazwaPliku_BrylaWzorcowa << endl
	 << "    " << _NazwaPliku_BrylaRysowana << endl
	 << endl;
    return false;
  }

  //count and write new alues to files
  return  Przelicz_i_Zapisz_Wierzcholki(StrmWe, StrmWy);
}
