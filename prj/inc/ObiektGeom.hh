#ifndef OBIEKTGEOM_HH
#define OBIEKTGEOM_HH

#include <string>
#include <memory>
#include "Wektor3D.hh"
#include "Macierz3D.hh"
#include "ObrysXY.hh"
#include "Kolory.hh"





#define IloscWektorowBrylaWzorcowa  24      //for XOY aproximation how many points describing a single box

#define NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA    "pliki_do_rysowania"

#define ID_KLASY_LAZIK 1              /*<defines id of Classes which inherit after ObiektGeom class>*/
#define ID_KLASY_LAZIK_FSR  2
#define ID_KLASY_PROBAREGOLITU 3

/**
 * @brief Describes 3 posible types of colision between GeomObjs
 * 
 */
enum TypKolizji{
  TK_BrakKolizji,
  TK_PrzejazdNadProbka,
  TK_Kolizja
};


class Lazik;  //info for compilatror that this class will exist

class ObiektGeom {
    std::string   _NazwaPliku_BrylaWzorcowa;
    std::string   _NazwaPliku_BrylaRysowana;
    std::string   _NazwaObiektu;
    int           _KolorID;

    Wektor3D Skala;       //defines how the box looks like

    Wektor3D Polozenie;   //defines where the box will be drawn

    Macierz3D MacRotacji; //matrix used for multiplicationa and recieving new rotated obj

    ObrysXY _Obrys;       //aproximates a square so a colission is eaier to detect
  
  public:

    //added by you:

    /**returns color id*/
    int get_KolorID()const{return _KolorID;}
    /**return access to color ID*/
    int & get_KolorID(){return _KolorID;}

    /**
     * @brief Get the value of Skala object
     * 
     * @return Wektor3D 
     */
    Wektor3D get_Skala()const{return this->Skala;}

    /**
     * @brief Get acces to the the Skala object
     * 
     * @return Wektor3D& 
     */
    Wektor3D & get_Skala(){return this->Skala;}

    /**
     * @brief Get the Polozenie object
     * 
     * @return Wektor3D 
     */
    Wektor3D get_Polozenie()const{return this->Polozenie;}

    /**
     * @brief Get the Polozenie object
     * 
     * @return Wektor3D 
     */
    Wektor3D & get_Polozenie(){return this->Polozenie;}

    /**recieve the value or the access to rotation matrix*/
    Macierz3D get_MacRotacji()const{return this->MacRotacji;}
    Macierz3D & get_MacRotacji(){return this->MacRotacji;}

    /**return value*/
    ObrysXY get_Obrys()const{return _Obrys;}
    /*return access*/
    ObrysXY & get_Obrys(){return _Obrys;}

    /**returns name of the obj**/
    std::string get__NazwaObiektu()const{return _NazwaObiektu;}
    /*return acces to the name of the obj*/
    std::string & get__NazwaObiektu(){return _NazwaObiektu; }

    //ObiektGeom(){}


    ObiektGeom(const char* sNazwaPliku_BrylaWzorcowa = "bryly_wzorcowe/szescian3.dat", const char* sNazwaObiektu = "", int KolorID=Kolor_JasnoNiebieski, Wektor3D Skl = Wektor3D(5,5,5), Wektor3D Pl= Wektor3D(0,0,0));

    int WezKolorID() const { return _KolorID; }
  
    const std::string & WezNazweObiektu() const { return _NazwaObiektu; }
  
    const std::string & WezNazwePliku_BrylaRysowana() const
                 { return _NazwaPliku_BrylaRysowana; }

    /**
     * @brief Destroy the Obiekt Geom object
     * VIRTUAL ,must be so this abstractt class will be also desroyed when accestor class is destroued
     */
    virtual ~ObiektGeom(){}

    
    
    /**
     * @brief Writes then Calculates and prints new Coordinates to a given file
     * 
     * @param StrmWe Where old coordinates are stored
     * @param StrmWy Where print te calculated values
     * @return true if all OK
     * @return false when mistakes in given files
     */
    bool Przelicz_i_Zapisz_Wierzcholki(std::istream &StrmWe, std::ostream &StrmWy);


    /**
     * @brief Opens files to write and read Co-ordinates
     * 
     * @return true when opened
     * @return false when failure in opening the data
     */
    bool Przelicz_i_Zapisz_Wierzcholki();

    /**
     * @brief Used to recieve the id of secondary class obj
     * 
     * @return int ID of ObiektGeom Accessor class
     */
    virtual int SprawdzIDklasy()const = 0;
    
    /**
     * @brief Checks if there is any type of possible collisons
     * ABSTRACT
     * @param Wsk_Lazik smart pointer to Rover 
     * @return TypKolizji 
     */
   virtual TypKolizji CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik)const=0;

    //void Koko(std::shared_ptr<Lazik> &ala);
};


#endif
