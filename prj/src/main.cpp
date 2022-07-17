#include <iostream>
#include <fstream>
#include "lacze_do_gnuplota.hh"
#include "PowierzchniaMarsa.hh"
#include "Lazik.hh"
#include "Kolory.hh"
#include "Scena.hh"
#include "unistd.h" //for uslepp
#include <memory>
#include "ObrysXY.hh"

//#include "ProbkaRegolitu.hh"

using namespace std;




int main()  
{
 
  {//used to make all the wektors local

  //define how the box looks like
  Wektor3D Skal1(20,20,10);
  Wektor3D Skal2(20,20,10);
  Wektor3D Skal3(20,20,10);

  //defines where the box will be
  Wektor3D Pol1(0,15,0);
  Wektor3D Pol2(60,60,0);
  Wektor3D Pol3(-20,70,0);
  

  //creating inteligent pointers to dynamicly allocated Rovers
  shared_ptr<LazikSFR> WskLazik_FSR(new LazikSFR());
  shared_ptr<Lazik> WskLazik_2(new Lazik("bryly_wzorcowe/szescian3.dat","Perseverance",Kolor_Czerwony, Skal2, Pol2,45));
  shared_ptr<Lazik> WskLazik_3(new Lazik("bryly_wzorcowe/szescian3.dat","Curiosity",Kolor_Czerwony, Skal3, Pol3));

  //creating ineligent pointers to dynamicly allocated Probes
  shared_ptr<ProbkaRegolitu> WskProbe1(new ProbkaRegolitu("Montdenier", Kolor_Czerwony,30,30,0));
  shared_ptr<ProbkaRegolitu> WskProbe2(new ProbkaRegolitu("Montagnac", Kolor_Czerwony,-30,-30,0));
  shared_ptr<ProbkaRegolitu> WskProbe3(new ProbkaRegolitu("Salette", Kolor_Czerwony,80,80));
  shared_ptr<ProbkaRegolitu> WskProbe5(new ProbkaRegolitu("Robine ", Kolor_Czerwony,80,-80));
  shared_ptr<ProbkaRegolitu> WskProbe4(new ProbkaRegolitu("Coulettes", Kolor_Czerwony,-80,-80));
  

  //create Mars surface
  Scena Mars_Scene(WskLazik_FSR,WskLazik_2,WskLazik_3, WskProbe1, WskProbe2, WskProbe3, WskProbe4, WskProbe5);

  
  cout << endl << "Start programu gnuplot" << endl << endl;
  Mars_Scene.get_Lacze().Rysuj();  //before Lacze.Rysuj();

  
  Mars_Scene.get_AktywnyLazik().WyswietlLazik();

  char WczytanyZnak;

  while(WczytanyZnak != 'k'){

    cout<<"Aktywny Lazik\n\n";
    Mars_Scene.get_AktywnyLazik().WyswietlLazik();

    cout<<"j - jazda na wprost\n";
    cout<<"o - zmien orientacje\n";
    cout<<"w - wybor lazika\n";
    cout<<"l - lista probek na scenie\n";
    cout<<"p - podejmij probke (tylko FSR)\n";
    cout<<"z - pozostaw probke na scenie(Tylko FSR)\n";
    cout<<"m - wyswietl menu\n\nk - koniec dzialania programu\n";
    

    cin>>WczytanyZnak;
    if(cin.fail()){throw std::invalid_argument("Nie podano znaku\n");}
    

    switch(WczytanyZnak){

      case 'j':
        {
        double dystans=0;

        cout<<"Twoj wybor, "<<WczytanyZnak<<" - jazda na wprost\n";
        cout<<"Podaj odleglosc, na ktora ma sie przemiescic lazik (w jednostkach sceny)\n";
        
        cin>>dystans;
        if(cin.fail()){throw std::invalid_argument("Nie podano liczby\n");}

        Mars_Scene.PrzejedzDystans_anim(dystans);  //animates and moves the rover
        
        }
    
      break;


      case 'o':
        {
        double obrot_calkowiy=0;

        cout<<"Twoj wybor, "<<WczytanyZnak<<" - zmien orientacje\n";
        cin>>obrot_calkowiy;
        if(cin.fail()){throw std::invalid_argument("Nie podano liczby\n");}

        Mars_Scene.ObrocOKat_anim(obrot_calkowiy);
        
        }
      break;

      case 'w':
        {
          uint Lazik_ID=0;
          cout<<"Twoj wybor, "<<WczytanyZnak<<" - wybor lazika\n";

          cout<<"Lazik numer: 1\n";
          Mars_Scene.WybierzLazika(1);
          Mars_Scene.get_AktywnyLazik().WyswietlLazik();

          cout<<"Lazik numer: 2\n";
          Mars_Scene.WybierzLazika(2);
          Mars_Scene.get_AktywnyLazik().WyswietlLazik();

          cout<<"Lazik numer: 3\n";
          Mars_Scene.WybierzLazika(3);
          Mars_Scene.get_AktywnyLazik().WyswietlLazik();

          cin>>Lazik_ID;
          if(cin.fail()){throw std::invalid_argument("Nie podano liczby\n");}

          if(Lazik_ID<=0||Lazik_ID> Mars_Scene.get_ObiektySceny().size()){
            throw std::invalid_argument("Nie ma takiego Lazika !\n");
          }

          //final user setting if everything right
          Mars_Scene.WybierzLazika(Lazik_ID);
        }
        break;

        case 'l':
            cout<<"Twoj wybor, "<<WczytanyZnak<<" - lista Probek\n";
            Mars_Scene.Wyswietl_Probki_NaScenie();
        break;

        case 'p':
          cout<<"Twoj wybor, "<<WczytanyZnak<<" - podjecie probki\n";
          Mars_Scene.Podejmij_probke();
          break;
        case 'z':
          cout<<"Twoj wybor, "<<WczytanyZnak<<" - pozostawienie probki\n";
          Mars_Scene.Pozostaw_probke();
        case 'm':
          cout<<"Twoj wybor, "<<WczytanyZnak<<" - menu\n";
        break;

      default:
        cout<<"cos nie halo podales \n";
      break;

      
    }

    
  }
  
  }//used to make all the Wektors local

  Wektor3D::Wyswietl_Ilosc_Wektorow();
}
