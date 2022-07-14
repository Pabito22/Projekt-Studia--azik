#pragma once

#include "ObiektGeom.hh"
#include "unistd.h"         //for sleep function

#define SZEROKOSC_LAZIKA 20


/**
 * @brief Describes A Mars Rover
 * 
 */
class Lazik: public ObiektGeom
{
    private:

    /** angle in pi radians describing how much u want to rotate the robot*/
    double KatOrientacji;

    /** How fast th Robot should move*/
    double Szybkosc;

    /*Distance too move*/
    double OdlegloscDoPrzejechania;


    public:

    /* return value*/
    double get_OdlegloscDoPrzejechania()const{return OdlegloscDoPrzejechania;}
    /*return access*/
    double & get_OdlegloscDoPrzejechania(){return OdlegloscDoPrzejechania;}

    /* return value*/
    double get_KatOrientacji()const{return KatOrientacji;}
    /* return acces*/
    double & get_KatOrientacji(){return KatOrientacji;}   //here you might want to take care of max value 360

    /*return value*/
    double get_Szybkosc()const{return Szybkosc;}
    /*return access*/
    double & get_Szybkosc(){return Szybkosc;}

    

    /**
     * @brief Destroy the Lazik object
     * virtual so father knows how to desroy
     */
    virtual ~Lazik(){}

    /**
     * @brief Construct a new Lazik object
     * 
     * @param K Kat Orientacji
     * @param S Szybkosc
     * @param Odl Odleglosc Do przejechannia
     */
    Lazik( const char*  sNazwaPliku_BrylaWzorcowa = "bryly_wzorcowe/szescian3.dat",
		        const char*  sNazwaObiektu = "FSR",
		        int          KolorID = Kolor_JasnoNiebieski,
            Wektor3D Skl = Wektor3D(20,20,10),
            Wektor3D Pl = Wektor3D(0,0,0),double K=0, double S=1, double Odl=0)
        :ObiektGeom(sNazwaPliku_BrylaWzorcowa,sNazwaObiektu,KolorID,Skl,Pl)
        {
        KatOrientacji = K;  Szybkosc = S; OdlegloscDoPrzejechania=Odl;
        if(S == 0){std::cout<<"lazik stworzony z zerowa predkoscia! Automatyczne ustawienie na 1!\n"; Szybkosc=1;}
        Macierz3D M(KatOrientacji);
        get_MacRotacji() = M;
    }


    /**
     * @brief Moves and Calculates new CoOrdinates for a given distance(from the Obj)
     * moves in direction from Katorientacji
     * 
     * @param dystans ktory ma przejechac lazik
     */
    void PrzejedzDystans(double dystans);
    
    /**
     * @brief Rotates given obj by Kat angle
     * 
     * @param Kat angle for obj to be rotated
     */
    void ObrocLazik(double Kat);


    /**
     * @brief Prints out info about Active Rover
     * 
     */
    virtual void WyswietlLazik()const;

    /*return id of Lazik class*/
    virtual int SprawdzIDklasy()const override{return ID_KLASY_LAZIK;}

    /**
     * @brief TO MA BYC VIRTUAL ALE NIE UMISZ!!
     * 
     * @brief Checs if there is a collision between Rovers
     * 
     * @param Wsk_Lazik smart pointer to a rover on the scene
     * @return TypKolizji 
     */

    /**
     * @brief Checks if there is a colission between this obj and Wsk_Lazik 
     * 
     * @param Wsk_Lazik 
     * @return TypKolizji 
     */
    virtual TypKolizji  CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik)const override
    {   
        if(this->get_Obrys().CzyNalozenie(Wsk_Lazik->get_Obrys())){
            return TK_Kolizja;
        }else{
            return TK_BrakKolizji;
        }
    }

};