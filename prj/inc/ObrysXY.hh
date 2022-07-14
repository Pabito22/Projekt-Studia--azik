#pragma once

#include "SWektor.hh"

typedef SWektor<double,2> Wektor2D;

#define IloscPunktowObrysu 4

class ObrysXY{

    private:

    Wektor2D Wiersz_DolnyLewy;

    Wektor2D Wiersz_GornyPrawy;


    public:

    /*take points from the rover and calculate its minleftbottom and max right values*/

    /**
     * @brief Construct a new Obrys X Y object
     * 
     * @param Dlx Bottom left x axis value
     * @param Dly Bottom left y axis value
     * @param GPx Right Up x value (must be bigger than Dlx)
     * @param GPy Right up y value (must be bigger than Dly)
     */
    ObrysXY(double Dlx = 0, double Dly=0, double GPx = 0, double GPy=0){
        if(Dlx > GPx){throw std::invalid_argument("Zly arg funkcji Lewyx wiekszy niz Prawy X in(OBRYSXY)\n");}
        if(Dly > GPy){throw std::invalid_argument("Zly arg funkcji DolnyY wiekszy niz Gorny Y in(OBRYSXY)\n");}

        Wiersz_DolnyLewy[0] = Dlx;   Wiersz_DolnyLewy[1] = Dly;
        Wiersz_GornyPrawy[0] = GPx;  Wiersz_GornyPrawy[1] = GPy;
    }

    /*return value*/
    Wektor2D get_Wiersz_DolnyLewy()const {return Wiersz_DolnyLewy;}
    /*return value*/
    Wektor2D get_Wiersz_GornyPrawy()const {return Wiersz_GornyPrawy;}

    /**
     * @brief Get the Wiersz DolnyLewy object
     * PRE: remember that WierszDolny level values have to be smaller than Wierszgorny prawy
     * @return Wektor2D& 
     */
    Wektor2D & get_Wiersz_DolnyLewy() {return Wiersz_DolnyLewy;}

    /**
     * @brief Get the Wiersz GornyPrawy object
     * PRE: remember that WierszDolny level values have to be bigger than Wiersz_DolnyLewy(
     * @return Wektor2D& 
     */
    Wektor2D & get_Wiersz_GornyPrawy(){return Wiersz_GornyPrawy;}

    /**
     * @brief Checks if two squares are on them selves
     * 
     * @param Ob2 Second ObrysXY obj
     * @return true when collide
     * @return false whaen everythink ok
     */
    bool CzyNalozenie(const ObrysXY &Ob2)const{
        //save the data about second obj points
        double LewyX = Ob2.Wiersz_DolnyLewy[0];/*2*/    double PrawyX = Ob2.Wiersz_GornyPrawy[0];    /*4*/
        double DolnyY = Ob2.Wiersz_DolnyLewy[1];    double GornyY = Ob2.Wiersz_GornyPrawy[1];
        
        //save the thata about obj
        double X1 = this->Wiersz_DolnyLewy[0];     double X2 = this->Wiersz_GornyPrawy[0];
        double Y1 = this->Wiersz_DolnyLewy[1];     double Y2 = this->Wiersz_GornyPrawy[1];

        //if collision return true
        if((X1 >= LewyX && X1 <= PrawyX) && (Y1>=DolnyY && Y1<= GornyY)){return true;}
        else if((X2>=LewyX && X2<=PrawyX) && (Y1>=DolnyY && Y1<= GornyY)){return true;}
        else if((X2 >= LewyX && X2 <= PrawyX) && (Y2>=DolnyY && Y2<= GornyY)){return true;}
        else if((X1 >= LewyX && X1 <= PrawyX) && (Y2>=DolnyY && Y2<= GornyY)){return true;}
        else{return false;}        
    }
};
