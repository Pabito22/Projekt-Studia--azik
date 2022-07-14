#include "Lazik.hh"

void Lazik::PrzejedzDystans(double dystans)
    {
        get_Polozenie()[0] = get_Polozenie()[0] + dystans*cos(this->KatOrientacji*PI/180);//this only tells in witch direction to move (dosent rotate the obj)

        get_Polozenie()[1] = get_Polozenie()[1] + dystans*sin(this->KatOrientacji*PI/180);
        
        Przelicz_i_Zapisz_Wierzcholki();
    }

void Lazik::ObrocLazik(double Kat){

        KatOrientacji = Kat+KatOrientacji;  //add old plus new rotation
        if(KatOrientacji == 360){KatOrientacji = 0;}

        Macierz3D M(KatOrientacji);     

        get_MacRotacji() = M;   //change the rotationmatrix

        Przelicz_i_Zapisz_Wierzcholki();    //write and save the rotation
    }

 void Lazik::WyswietlLazik()const{
        std::cout<<"        Nazwa: "<<this->WezNazweObiektu()<<std::endl;
        std::cout<<"    Polozenie (x,y,z): "<<this->get_Polozenie()<<std::endl;
        std::cout<<     "Orientacja [st]: "<<this->KatOrientacji<<std::endl;
    }


/*TypKolizji Lazik::CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik)const{
    return TK_BrakKolizji;
}*/