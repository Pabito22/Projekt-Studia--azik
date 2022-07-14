#ifndef SWEKTOR_HH
#define SWEKTOR_HH

#define ROZMIAR 3
#include "tgmath.h"

#include <iostream>

template<typename Typ, uint Rozmiar = ROZMIAR>
class SWektor{

    private:

    /**
   * do przechowywania informacji z ukadu rownan
   * */
    Typ wektor[Rozmiar];

    static int _IloscAktualna;
    static int _IlsocOgolna;

    public:

    static int Ile_Ogolnie(){return _IlsocOgolna;}
    static int Ile_Aktualnie(){return _IloscAktualna;}

    static void Wyswietl_Ilosc_Wektorow(){
        std::cout<<"\nOgolnie: "<<Ile_Ogolnie()<<std::endl;
        std::cout<<"Aktualnie: "<<Ile_Aktualnie()<<std::endl;
    }

    /**
     * @brief Construct a new SWektor object
     * 
     */
    SWektor(){
        for(Typ &ElemTab : wektor){
            ElemTab = 0;
        }
       // std::cout<<"konstr bezparam\n";
        ++_IloscAktualna; ++_IlsocOgolna;
    }

    /**
     * @brief Construct a new SWektor object
     * 
     * @param a 
     * @param b 
     * @param c 
     */
    SWektor(Typ a, Typ b , Typ c){
        wektor[0] = a;
        wektor[1] = b;
        wektor[2] = c;
       // std::cout<<"konstr param\n";
        ++_IloscAktualna; ++_IlsocOgolna;
    }

    /**
     * @brief Copies and Constructs a new SWektor object 
     * 
     */
    SWektor(const SWektor &W){
        for(uint i=0; i< Rozmiar;++i){
            wektor[i] = W[i];
        }

        ++_IloscAktualna; ++_IlsocOgolna;
    }

    /**
     * @brief Rewrites given obj with R-side SWektor
     * 
     * @param W Wector to be copied into obj
     * @return SWektor& 
     */
    SWektor & operator = (const SWektor &W){
        for(uint i = 0; i<Rozmiar; ++i){  wektor[i] = W[i];  }
        return (*this);
    }


    /**
     * @brief Destroy the SWektor object
     * POST: Redces by one IloscAktualna
     */
    ~SWektor(){
        --_IloscAktualna;
    }


    



    /**
     * @brief Return a part of wektor of id's value
     * 
     * @param id - number of wektor part that you want to get
     * @return Typ 
     */
    Typ operator [](uint id)const{
        if(id<=Rozmiar){
            return this->wektor[id];
        }else{
            throw 1;
        }
    }

    /**
     * @brief Return acces to change parts of given Vector
     * 
     * @param id - number of Vector's part that you want to change
     * @return Typ& 
     */
    Typ& operator [](uint id){
        if(id<=Rozmiar){
            return this->wektor[id];
        }else{
            throw 1;
        }
    }

    /**
     * @brief calculates substraction of two Wektors
     * 
     * @param wek2 second vector
     * @return reult of substraction
     */
    SWektor operator - (const SWektor &wek2)const{
        SWektor wynik;
        for(int i=0;i<Rozmiar;++i){
            wynik[i] = this->wektor[i] - wek2[i];
        }
        return wynik;
    }

    /*realization of Vector addition*/
    SWektor operator + (const SWektor &wek2)const{
        SWektor wynik;
        for(uint i=0;i<Rozmiar;++i){
            wynik[i] = this->wektor[i] + wek2[i];
        }
        return wynik;
    }   

    /*multiplication of vactor and noumber of type Typ*/
    SWektor operator * (Typ d)const{
        SWektor wynik;
        for(uint i=0; i<Rozmiar; i++){
            wynik[i]=(this->wektor[i]*d);
        }
        return wynik;
    }
    
    /**
     * @brief Scalar multiplication of two Vectors
     * 
     * @param wek2 
     * @return result of scalar multiplication
     */
    Typ operator*(const SWektor &wek2)const{
        Typ wynik;
        for(int i=0;i<Rozmiar;++i){
            wynik+=(wek2[i]*this->wektor[i]);
        }
        return wynik;
    }

    /**
     * @brief Vector multiplication of two Vectors
     * 
     * @param wek2 
     * @return SWektor 
     */
    SWektor operator&(const SWektor &wek2)const{
        SWektor Wynik;

        Wynik[0] =((*this)[1]*wek2[2]) - ((*this)[2]*wek2[1]);
        Wynik[1] = (((*this)[0]*wek2[2]) - ((*this)[2]) * wek2[0]) * ( -1);
        Wynik[2] = ((*this)[0] * wek2[1])  - (wek2[0]* (*this)[1]);

        return Wynik;
    }


    /**
     * @brief Get the Length of Vector
     * 
     * @return Typ Length
     */
    Typ get_Length()const{
        SWektor<Typ,Rozmiar> this_vec = (*this);
        Typ Wynik = 0;
        for(uint i = 0; i <Rozmiar; ++i){
            Wynik+=this_vec[i]*this_vec[i];
        }

        return sqrt(Wynik);
    }


};

/**inicjalizacja statycznej zmiennej opisujacej ilosc constr*/
template<typename Typ, uint Rozmiar>
int SWektor<Typ, Rozmiar>::_IloscAktualna=0;

/**inicjalizacja statycznej zmiennej opisujacej ilosc constr*/
template<typename Typ, uint Rozmiar>
int SWektor<Typ, Rozmiar>::_IlsocOgolna=0;





/**
 * @brief prints out given vector to given output
 * 
 * @tparam Typ one of domain types
 * @tparam Rozmiar size of vector
 * @param StrOut chosen output for vector to be printed
 * @param Wek Vector to be printed
 * @return std::ostream& 
 */
template<typename Typ, uint Rozmiar = ROZMIAR>
std::ostream& operator << (std::ostream &StrOut,const SWektor<Typ> &Wek){
    for(uint i = 0; i<Rozmiar ; ++i){
        StrOut<<" "<<Wek[i];
    }
    return StrOut;
}

template<typename Typ, uint Rozmiar = ROZMIAR>
std::istream& operator >> (std::istream& StrIn, SWektor<Typ> &Wek){
    for(uint i =0; i<Rozmiar; ++i){
        StrIn>>Wek[i];
    }


    return StrIn;
}


#endif