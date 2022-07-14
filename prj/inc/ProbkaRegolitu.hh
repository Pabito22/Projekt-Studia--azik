#pragma once 

#include "ObiektGeom.hh"
#include "Lazik.hh"


class Lazik;


/**
 * @brief Simulates Probes
 * 
 */
class ProbkaRegolitu: public ObiektGeom
{

    public:

    /**
     * @brief Construct a new Probka Regolitu object
     * 
     * @param sNazwaObiektu Name of the probe
     * @param KolorID 
     * @param x axis, where the probe will be
     * @param y axis, where the probe will be
     * @param z axis, where the probe will be
     */
    ProbkaRegolitu(const char* sNazwaObiektu, unsigned int KolorID, double x = 0, double y=0, double z = 0)
    :ObiektGeom("bryly_wzorcowe/szescian3.dat", sNazwaObiektu, KolorID)
    {
        //get__NazwaObiektu() += sNazwaObiektu;
        get_KolorID() = KolorID;
        get_Polozenie()[0] = x;
        get_Polozenie()[1] = y;
        get_Polozenie()[2] = z;
    }

    /**
     * @brief Destroy the Probka Regolitu object
     * 
     */
    virtual ~ProbkaRegolitu(){};

    /**
     * @brief Returns ID of the class
     * 
     * @return int 
     */
    virtual int SprawdzIDklasy()const override{return ID_KLASY_PROBAREGOLITU;}


    /**
     * @brief Calculates new Coordinates of a given obj in position relative to the givn Probe
     * 
     * @param Wsk_Na_Ob Poiter to a Lazik obj
     * @return Wektor3D 
     */
    Wektor3D Transformuj_Wsp_do_Probki(const std::shared_ptr<ObiektGeom> &Wsk_Na_Ob)const;


    /*this one will be virtual*/

    /**
     * @brief Checs if there is a collision between Probe and the Rover
     * 
     * @param P_Rover Rover with which the probe could possibly colide
     * @return TypKolizji 
     */
    virtual TypKolizji CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik)const override;
    

};