#include "Scena.hh"

Scena::Scena(std::shared_ptr<Lazik> A1, std::shared_ptr<Lazik> A2,std::shared_ptr<Lazik> A3, std::shared_ptr<ProbkaRegolitu> P1, std::shared_ptr<ProbkaRegolitu> P2 ,
std::shared_ptr<ProbkaRegolitu> P3,std::shared_ptr<ProbkaRegolitu> P4, std::shared_ptr<ProbkaRegolitu> P5){
        if(A1 == nullptr || A2 == nullptr || A3 == nullptr|| P1 == nullptr || P2 == nullptr || P3 == nullptr || P4 == nullptr || P5 == nullptr ){
            std::cout<<"!!!!!!!!!!!!!!!!!!!!!utworzono obiet sceny ktory nie ma wskazanego lazika!! (Scena Constructor\n";   //usun to potem
        }
            std::cout<<"Normalnie mordo\n";
            AktywnyLazik = A1;



            ObiektySceny.push_back(A1);     //pushing the Lazik(probably automaticly rzutowanie) pointers into the list
            ObiektySceny.push_back(A2);     
            ObiektySceny.push_back(A3);
            ObiektySceny.push_back(P1);
            ObiektySceny.push_back(P2);
            ObiektySceny.push_back(P3);
            ObiektySceny.push_back(P4);
            ObiektySceny.push_back(P5);     

            Inicjalizuj_Lacze(Lacze);       //inicjalizacja Lacza and checking if evrything right
            if (!Inicjalizuj_PowierzchnieMarsa(Lacze)) throw std::invalid_argument("Error while incializing MarsSpace (Scena Constr)");


            
            for(std::list<std::shared_ptr<ObiektGeom> >::iterator iter = ObiektySceny.begin(); iter != ObiektySceny.end(); ++iter){
                DodajDoListyRysowania(Lacze,(*(*iter)));
                std::cout<<(*iter)->get__NazwaObiektu()<<std::endl;
                std::cout<<(*iter)->get_Polozenie()<<std::endl;
                (*iter)->Przelicz_i_Zapisz_Wierzcholki();
            }
        }


std::shared_ptr<ObiektGeom>  Scena::get_ScenaObj(uint ID){
            if(ID > ObiektySceny.size()){throw std::invalid_argument("Asked for too big obj id - there are less obj(from Scena class)\n");}
            uint j = 0;
            for(std::list<std::shared_ptr<ObiektGeom> >::iterator iter = ObiektySceny.begin(); iter != ObiektySceny.end(); ++iter){
                ++j;
                if(j==ID){
                    return (*iter);
                    //iter=ObiektySceny.end();    //end becaouse element found
                }
            }
        }


void Inicjalizuj_Lacze(PzG::LaczeDoGNUPlota  &rLacze)
{
  rLacze.ZmienTrybRys(PzG::TR_3D);
  rLacze.UstawZakresX(-ROMIAR_POWIERZCHNI_X/2, ROMIAR_POWIERZCHNI_X/2);
  rLacze.UstawZakresY(-ROMIAR_POWIERZCHNI_Y/2, ROMIAR_POWIERZCHNI_Y/2);
  rLacze.UstawZakresZ(-0, 90);  
  rLacze.UstawRotacjeXZ(40,60); // Tutaj ustawiany jest widok

  rLacze.Inicjalizuj();  // Tutaj startuje gnuplot.
}


void DodajDoListyRysowania(PzG::LaczeDoGNUPlota &rLacze, const ObiektGeom  &rOb)
{
  PzG::InfoPlikuDoRysowania *wInfoPliku;
  
  wInfoPliku = &rLacze.DodajNazwePliku(rOb.WezNazwePliku_BrylaRysowana());
  wInfoPliku->ZmienKolor(rOb.WezKolorID());
}



void Scena::PrzejedzDystans_anim(double dystans){
  //if SFR rides over a probe and user decided that he wants to drive over it
   static int Ride_decision = RIDE_NO;
  

    this->get_AktywnyLazik().get_OdlegloscDoPrzejechania() = dystans;              //save the data about final distance into the obj
        
      if(dystans > -1 && dystans < 1 ){                       //if systans very small then drav only once
          this->get_AktywnyLazik().PrzejedzDystans(dystans);
          this->get_Lacze().Rysuj();
      }else{

        double finalDistance = this->get_AktywnyLazik().get_OdlegloscDoPrzejechania(); //variable to countn evry step    

        dystans = 1;                                                                        //if moving forwoard

        if(finalDistance < 0){                                                              //if movinng backword
          dystans = -1;
          finalDistance*=(-1);
        }
        
        double counter = 1;

          std::shared_ptr<Lazik> LazikFSR =  std::static_pointer_cast<Lazik>(get_ScenaObj(1));
          std::shared_ptr<Lazik> Lazik2 =  std::static_pointer_cast<Lazik>(get_ScenaObj(2));
          std::shared_ptr<Lazik> Lazik3 =  std::static_pointer_cast<Lazik>(get_ScenaObj(3));



        while(counter <= finalDistance){
          
          

          this->get_AktywnyLazik().PrzejedzDystans(dystans);
          this->get_Lacze().Rysuj();
          ++counter;
          usleep(this->get_AktywnyLazik().get_Szybkosc() *  100000);

          //if collision between any posible Rovers then print info and stop the Movement
          if(LazikFSR->CzyKolizja(Lazik2) == TK_Kolizja || Lazik2->CzyKolizja(LazikFSR) == TK_Kolizja){
            std::cout<<"\n\n  Uderzenie!\n\n";
            counter = finalDistance;
            this->get_AktywnyLazik().PrzejedzDystans(-2*dystans);
          }        
          if(LazikFSR->CzyKolizja(Lazik3) == TK_Kolizja || Lazik3->CzyKolizja(LazikFSR) == TK_Kolizja){
            std::cout<<"\n\n  Uderzenie!\n\n";
            counter = finalDistance;
            this->get_AktywnyLazik().PrzejedzDystans(-2*dystans);
          }        
          if(Lazik2->CzyKolizja(Lazik3) == TK_Kolizja || Lazik3->CzyKolizja(Lazik2)==TK_Kolizja){
            std::cout<<"\n\n  Uderzenie!\n\n";
            counter = finalDistance;
            this->get_AktywnyLazik().PrzejedzDystans(-2*dystans);
          }  

          //check if collison between the Active Rover and a Probe occured
          if(Sprawdz_Czy_kolizja_Lazika_Probka()){

            std::cout<<"\n\n  Uderzenie!\n\n";
            counter = finalDistance;
            this->get_AktywnyLazik().PrzejedzDystans(-2*dystans);
          }     

          if(Sprawdz_Czy_Przejazd_Lazika_nad_Probka()!=0){
            if((get_AktywnyLazik().SprawdzIDklasy() == ID_KLASY_LAZIK_FSR)  && (Ride_decision==RIDE_NO)){

              std::cout<<"Uderzenie Lazika FSR- mozna podjac Probke!\n\n";
              std::cout<<"Czy chcesz podjac Probke?\n-Tak kliknij 't'\n Nie,kontynuuj jazde - kliknij dowolny przycisk\n";
              char c_decision;
              std::cin>>c_decision;
              if(c_decision=='t'){
                counter = finalDistance;
                this->get_AktywnyLazik().PrzejedzDystans(-2*dystans);
                Ride_decision = RIDE_NO;
                }
              else{Ride_decision = RIDE_YES;
              }
              
            }
            //std::cout<<"\n-----------------\n-----------------\n";
            //std::cout<<"uderzenie!\n";
            //counter=finalDistance;
          } 


          
        }/*while*/

        Ride_decision = RIDE_NO;
      }/*if normal distance*/
}


void Scena::ObrocOKat_anim(double obrot_calkowiy){

  std::shared_ptr<Lazik> LazikFSR =  std::static_pointer_cast<Lazik>(get_ScenaObj(1));
          std::shared_ptr<Lazik> Lazik2 =  std::static_pointer_cast<Lazik>(get_ScenaObj(2));
          std::shared_ptr<Lazik> Lazik3 =  std::static_pointer_cast<Lazik>(get_ScenaObj(3));
    double obrot = 1;

        if(obrot_calkowiy < 0){
          obrot = -1;
          obrot_calkowiy*=(-1);
        }

        double counter =1;
        while(counter < obrot_calkowiy){
          this->get_AktywnyLazik().ObrocLazik(obrot);
          this->get_Lacze().Rysuj();
          ++counter;
          usleep(this->get_AktywnyLazik().get_Szybkosc() *  10000);

          //if collision between any posible Rovers then print info and stop the Movement
          if(LazikFSR->CzyKolizja(Lazik2) == TK_Kolizja){
            std::cout<<"\n\n  Uderzenie!\n\n";
            counter = obrot_calkowiy;
            this->get_AktywnyLazik().ObrocLazik(-2*obrot);
          }        

          if(LazikFSR->CzyKolizja(Lazik3) == TK_Kolizja){
            std::cout<<"\n\n  Uderzenie!\n\n";
            counter = obrot_calkowiy;
            this->get_AktywnyLazik().ObrocLazik(-2*obrot);
          }        

          if(Lazik2->CzyKolizja(Lazik3) == TK_Kolizja){
            std::cout<<"\n\n  Uderzenie!\n\n";
            counter = obrot_calkowiy;
            this->get_AktywnyLazik().ObrocLazik(-2*obrot);
          } 

          //if colision between active rover and the probe occurs
          if(Sprawdz_Czy_kolizja_Lazika_Probka()!=0){
            std::cout<<"\n\n  Uderzenie!\n\n";
            counter = obrot_calkowiy;
            this->get_AktywnyLazik().ObrocLazik(-2*obrot);
          }             

        }
}


void Scena::Podejmij_probke(){
  if(AktywnyLazik->SprawdzIDklasy() == ID_KLASY_LAZIK_FSR){   //check if SFR rover(can take the probe)
    AktywnyLazik->PrzejedzDystans(5);
    int ID_Probki = Sprawdz_Czy_Przejazd_Lazika_nad_Probka();
    if(ID_Probki == 0){                 //if nothing found print info about it
      std::cout<<"Brak probek w poblizu\n";
    }else{                              //if smth found print info about it
      std::shared_ptr<ObiektGeom> pointToRover = get_ScenaObj(ID_Probki);
      get_ScenaObj(ID_Probki)->get_Skala() = Wektor3D(200,2000,0);
      pointToRover->Przelicz_i_Zapisz_Wierzcholki();
      this->get_Lacze().Rysuj();
      WezProbkeZeScenyDoLazika(get_ScenaObj(ID_Probki));
    }
  }
  else{      //if not FSR rover then print the info
    std::cout<<"Tylko Lazik SFR moze podejmowac pobke!\n\n";
  }
}


void Scena::Wyswietl_Probki_NaScenie()const{
  for(std::_List_const_iterator<std::shared_ptr<ObiektGeom>> iter = ObiektySceny.begin(); iter != ObiektySceny.end(); ++iter){
    if((*iter)->SprawdzIDklasy() == ID_KLASY_PROBAREGOLITU){std::cout<<(*iter)->get__NazwaObiektu()<<"\n";}
  }
}