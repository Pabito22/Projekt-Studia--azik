#pragma once

#include "SMacierz.hh"
#include "tgmath.h"

#define PI 3.14159265


class Macierz3D: public SMacierz<double, ROZMIAR>
{
    public:

    /**
     * @brief Construct a new Macierz 3 D object with defeult angle = 0
     * 
     */
    /* Macierz3D(){   
        for(uint i = 0; i <ROZMIAR; ++i){
            for(uint j= 0; j<ROZMIAR;++j){
                (*this)[i][j]= 1;
            }
        }
     }*/

    //Macierz3D(double k){Kat = k;}

    /**
     * @brief Construct a new Macierz 3 D object with Calculated sine and cosine of rotation matrix
     * 
     * @param Kat 
     */
    Macierz3D(double Kat=0){
        //(*this).Transponuj();
        (*this)[0][0] = cos(Kat*PI/180);      (*this)[0][1] = sin(Kat*PI/180); (*this)[0][2] = 0;//first col
        (*this)[1][0] = (-1)* sin(Kat*PI/180);(*this)[1][1] = cos(Kat*PI/180); (*this)[1][2] = 0;//second col
        (*this)[2][0] = 0;                    (*this)[2][1] = 0;               (*this)[2][2] = 1;//third col
    }

    /*double get_Kat()const{return this->Kat;}
    double & get_Kat(){return this->Kat;}*/

    

    /**
     * @brief Creates Roptation Matrix 
     * used to rotate coordinaes
     * 
     * POST: CHANGES GIVEN OBJ VALUES!!
     * 
     * @param Kat angle in PI rad
     */
    Macierz3D Rotuj(double Kat){
        //(*this).Transponuj();

        (*this)[0][0] = cos(Kat*PI/180);      (*this)[0][1] = sin(Kat*PI/180); (*this)[0][2] = 0;//first col
        (*this)[1][0] = (-1)* sin(Kat*PI/180);(*this)[1][1] = cos(Kat*PI/180); (*this)[1][2] = 0;//second col
        (*this)[2][0] = 0;                    (*this)[2][1] = 0;               (*this)[2][2] = 1;//third col

        return (*this);
    }


    
    



};