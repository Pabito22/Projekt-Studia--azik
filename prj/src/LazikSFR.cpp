#include "LazikSFR.hh"

void LazikSFR::Wypisz_Zebrane_Probki()const
{
        for(std::_List_const_iterator<std::shared_ptr<ProbkaRegolitu>> iter = _ListaProbek.begin(); iter != _ListaProbek.end(); ++iter){
            if((*iter)->SprawdzIDklasy() == ID_KLASY_PROBAREGOLITU){std::cout<<(*iter)->get__NazwaObiektu()<<"\n";}
        }
    }

void LazikSFR::WyswietlLazik()const
{
    std::cout<<"        Nazwa: "<<this->WezNazweObiektu()<<std::endl;
    std::cout<<"    Polozenie (x,y,z): "<<this->get_Polozenie()<<std::endl;
    std::cout<<     "Orientacja [st]: "<<this->get_KatOrientacji()<<std::endl;
    std::cout<<"lista Probek na Laziku SFR:\n";
    Wypisz_Zebrane_Probki();
}

TypKolizji LazikSFR::CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik)const
{
    if(this->get_Obrys().CzyNalozenie(Wsk_Lazik->get_Obrys())){
        return TK_Kolizja;
    }else{
        return TK_BrakKolizji;
    }
}