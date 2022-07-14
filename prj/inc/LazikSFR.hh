#pragma once 

#include "Lazik.hh"
#include "ProbkaRegolitu.hh"
#include <list>

/**
 * @brief Simulates the SFR Rover, which will be able to collect the Probes
 * 
 */
class LazikSFR: public Lazik
{

    private:

    /**
     * @brief List of the Probes collected by the SFR Rover
     * 
     */
    std::list<std::shared_ptr<ProbkaRegolitu>> _ListaProbek;


    public:

    /**
     * @brief Destroy the Lazik S F R object
     * 
     */
    virtual ~LazikSFR(){};

    /**
     * @brief Construct a new Lazik S F R object
     * Uses default constr values from lazik
     */
    LazikSFR()
    :Lazik()
    {
       
    };

    /**
     * @brief Get the ListaProbek object
     * 
     * @return std::list<std::shared_ptr<ProbkaRegolitu>> 
     */
    std::list<std::shared_ptr<ProbkaRegolitu>> get__ListaProbek()const{return _ListaProbek;}

    /**
     * @brief Get the acces to the ListaProbek object
     * 
     * @return std::list<std::shared_ptr<ProbkaRegolitu>>& 
     */
    std::list<std::shared_ptr<ProbkaRegolitu>> & get__ListaProbek(){return _ListaProbek;}

    /**
     * @brief Returns Id of LazikSFR class
     * 
     * @return int ID
     */
    virtual int SprawdzIDklasy()const override{return ID_KLASY_LAZIK_FSR;}

    
    /**
     * @brief Prints out colected Probes 
     * 
     */
    void Wypisz_Zebrane_Probki()const;

    /**
     * @brief Prints info about SFR rover and Probes which it contains
     * 
     */
    virtual void  WyswietlLazik()const override;


    /**
     * @brief If FSR 
     * 
     * @return TypKolizji 
     */
    virtual TypKolizji CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik)const override;
    
};