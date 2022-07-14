#include "ProbkaRegolitu.hh"

Wektor3D ProbkaRegolitu::Transformuj_Wsp_do_Probki(const std::shared_ptr<ObiektGeom> &Wsk_Na_Ob)const{
        if(!(Wsk_Na_Ob->SprawdzIDklasy()==ID_KLASY_LAZIK || Wsk_Na_Ob->SprawdzIDklasy()==ID_KLASY_LAZIK_FSR)){throw std::invalid_argument("Only Lazik allowed in this Function(Transformuj_Wsp_do_Probki!\n");}
        Wektor3D Wynik;
        Wynik[0] = Wsk_Na_Ob->get_Polozenie()[0] - this->get_Polozenie()[0];
        Wynik[1] = Wsk_Na_Ob->get_Polozenie()[1] - this->get_Polozenie()[1];
        Wynik[2] = 0;
        return Wynik;
    }


TypKolizji ProbkaRegolitu::CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik)const
{
    //calculate new coordinates and length between Rover and Probe
        Wektor3D Wsp_wzgledem_Probki = this->Transformuj_Wsp_do_Probki(Wsk_Lazik);
        double R_odleglosc = Wsp_wzgledem_Probki.get_Length();

        //get info obout speed Vec(in witch direction is rover moving)
        Wektor3D Speed_Vector; Speed_Vector[0] = cos(Wsk_Lazik->get_KatOrientacji()*PI/180);  Speed_Vector[1] = sin(Wsk_Lazik->get_KatOrientacji()*PI/180); Speed_Vector[2] = 0;
        double Lgth_ofSpeedVec = Speed_Vector.get_Length();

        double D_distance =  (Wsp_wzgledem_Probki & Speed_Vector).get_Length()/Lgth_ofSpeedVec;     //now you have the distance

        //here checking if probe and the rover are even connected
        if(this->get_Obrys().CzyNalozenie(Wsk_Lazik->get_Obrys()) || Wsk_Lazik->get_Obrys().CzyNalozenie(this->get_Obrys())){
            if(D_distance < SZEROKOSC_LAZIKA/5){return TK_PrzejazdNadProbka;}   else{return TK_Kolizja;}
        }
        
        return TK_BrakKolizji;
}