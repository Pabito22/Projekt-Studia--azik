#pragma once

#include <memory>
 #include <list>

#include "Lazik.hh"
#include "ObiektGeom.hh"
#include "PowierzchniaMarsa.hh"
#include "lacze_do_gnuplota.hh"

#include "ProbkaRegolitu.hh"

#include "LazikSFR.hh"
/**those 2 are added here so Scena Constr Works properly**/

#define RIDE_YES 1  //used for @PrzejedzDystans_anim to save the decision to ride over a probe
#define RIDE_NO  0  //with the FSR rover





/*!
 *  \brief Inicjalizuje połączenie z programem gnuplot oraz rozmiar świata.
 *
 *  Inicjalizuje podstawowe parametry "swiata", tzn. jego wymiary,
 *  które będą widoczne jako obszar objęty układem współrzędnych.
 *  Następnie w tle uruchamiany jest program gnuplot.
 *  \param[in] rLacze - nieaktywne łącze do gnuplota.
 */
 void Inicjalizuj_Lacze(PzG::LaczeDoGNUPlota  &rLacze);

/**
 * \brief Adds given obj to be drawn by gnuplot
 * 
 * @param rLacze connnection to gnuplot
 * @param rOb GeomObj to obe drawn
 */
 void DodajDoListyRysowania(PzG::LaczeDoGNUPlota &rLacze, const ObiektGeom  &rOb);




/**
 * @brief Describes the Scene where all of the Rovers are
 * 
 */
class Scena
{
private:

/**
 * @brief Inteligent Pointer to Lazik
 * 
 */
std::shared_ptr<Lazik> AktywnyLazik;

/**
 * @brief list of pointers to the Objects on the Scene
 * 
 */
std::list<std::shared_ptr<ObiektGeom>> ObiektySceny;    //tera chuj wi jak do tego konstruktor zrobic i po co to wogole


/**
 * @brief Connection to the GnuPlot obj
 * for now its value while creating is given by its default constructor
 */
PzG::LaczeDoGNUPlota  Lacze;


    
public:

    
    /**
     * @brief Get the Lacze object Value
     * 
     * @return PzG::LaczeDoGNUPlota 
     */
    PzG::LaczeDoGNUPlota get_Lacze()const {return this->Lacze;}

    /**
     * @brief Get the access to the Lacze object
     * 
     * @return PzG::LaczeDoGNUPlota& 
     */
    PzG::LaczeDoGNUPlota & get_Lacze(){return this->Lacze;}

    /**
     * @brief Get the AktywnyLazik object
     * Zwraca dereferencje aktywnego lazika (czyli dostep do odczytania jego wartosci)
     * 
     * @return Lazik 
     */
    Lazik get_AktywnyLazik()const {
        Lazik Wynik = *(this->AktywnyLazik);
        return Wynik;
    }

    /**
     * @brief Get the AktywnyLazik object
     * Zwraca dereferencje aktywnego lazika (czyli dostep do jego wartosci)
     * Za pomoca tego mozesz zmieniac wartosci tego na co wskazuje Aktywny lazik
     * @return Lazik 
     */
    Lazik & get_AktywnyLazik() {
        return *(this->AktywnyLazik);
    }

    /**
     * @brief Get the ObiektySceny object
     * 
     * @return std::list<std::shared_ptr<ObiektGeom>> 
     */
    std::list<std::shared_ptr<ObiektGeom>> get_ObiektySceny()const{return this->ObiektySceny;}

    /**
     * @brief Get the ObiektySceny object
     * 
     * @return std::list<std::shared_ptr<ObiektGeom>> 
     */
    std::list<std::shared_ptr<ObiektGeom>>  & get_ObiektySceny(){return this->ObiektySceny;}

    /*!
    *  \brief Inicjalizuje połączenie z programem gnuplot oraz rozmiar świata.
    *
    *  Inicjalizuje podstawowe parametry "swiata", tzn. jego wymiary,
    *  które będą widoczne jako obszar objęty układem współrzędnych.
    *  Następnie w tle uruchamiany jest program gnuplot.
    *  \param[in] rLacze - nieaktywne łącze do gnuplota.
    */
    friend void Inicjalizuj_Lacze(PzG::LaczeDoGNUPlota  &rLacze);
    

    

    /**
     * @brief Construct a new Scena object
     * All the AktywnyLazi pointers points to zero by default!
     * Sets first parameter as Aktywny Lazik
     * and puts all the Lazik pointers to ObiektySceny list
     * @param A1 First lazik pointer
     * @param A2 Second LAzik pointer
     * @param A3 Third LAzik pointer
     * 
     * @param P1 First pointer to th Probe on the scene
     * 
     */
    Scena(std::shared_ptr<Lazik> A1 = nullptr, std::shared_ptr<Lazik> A2 = nullptr,std::shared_ptr<Lazik> A3 = nullptr,
     std::shared_ptr<ProbkaRegolitu> P1 = nullptr, std::shared_ptr<ProbkaRegolitu> P2 = nullptr,std::shared_ptr<ProbkaRegolitu> P3 = nullptr,
     std::shared_ptr<ProbkaRegolitu> P4 = nullptr, std::shared_ptr<ProbkaRegolitu> P5 = nullptr);

        /**
         * @brief Get the address of ScenaObj object of ID number from the list 
         * 
         * PRE: ID must be smaller than the number of the obj on the scene
         * 
         * @param ID which number of the obj from the list you want to get
         * @return std::shared_ptr<ObiektGeom>
         */
        std::shared_ptr<ObiektGeom>  get_ScenaObj(uint ID);

        /**
         * @brief Changes the AktiveLazik Pointer to given ID of the Rver
         * 
         * @param ID of hte Rover (Must me smaller than number of the obj on the Scene)
         */
        void WybierzLazika(uint ID){
            if(ID > ObiektySceny.size()){throw std::invalid_argument("Asked for too big obj id - there are less obj(from Scena class)\n");}
            AktywnyLazik = std::static_pointer_cast<Lazik>(get_ScenaObj(ID));
        }

        /**
         * @brief Get the LazikSFR object
         * 
         * @return std::shared_ptr<ObiektGeom> 
         */
        std::shared_ptr<ObiektGeom>  get_LazikSFR(){
            for(std::list<std::shared_ptr<ObiektGeom> >::iterator iter= ObiektySceny.begin(); iter != ObiektySceny.end(); ++iter){
                if((*iter)->SprawdzIDklasy() == ID_KLASY_LAZIK_FSR){
                    return (*iter);
                }
            }
        }


    /**
     * @brief finds the number of a Obj on the Scene from the ObiektySceny list
     * 
     * @param ptr_Probe 
     * @return uint number of the obj on the list
     * 0 when no such rover existts on the list
     */
    uint Find_Probe_number(const std::shared_ptr<ObiektGeom> &ptr_Probe)const{
        int probe_Number = 0;

        for(std::_List_const_iterator<std::shared_ptr<ObiektGeom>>iter = ObiektySceny.begin(); iter != ObiektySceny.end(); ++iter){
            ++probe_Number;
            if((*iter)->get__NazwaObiektu() == ptr_Probe->get__NazwaObiektu()){
               return probe_Number;
            }
        }
        return 0;
    }

    /**
     * @brief Returns Id of the Probe when collision between active Rover and some Probe occured
     * 
     * @return uint 0 when no collision or ID of the Probe
     */
    uint  Sprawdz_Czy_kolizja_Lazika_Probka()const{
        for(std::_List_const_iterator<std::shared_ptr<ObiektGeom>>iter = ObiektySceny.begin(); iter != ObiektySceny.end(); ++iter){
            if((*iter)->SprawdzIDklasy() == ID_KLASY_PROBAREGOLITU){
                if((*iter)->CzyKolizja(AktywnyLazik)==TK_Kolizja){return Find_Probe_number((*iter));}
            }
        }
        return 0;
    }

    /**
     * @brief Returns Id of the Probe when  Active Rover drives over it
     *  
     * @return uint 0 when no such situation occured or ID of the Probe
     */
    uint  Sprawdz_Czy_Przejazd_Lazika_nad_Probka()const{
        for(std::_List_const_iterator<std::shared_ptr<ObiektGeom>>iter = ObiektySceny.begin(); iter != ObiektySceny.end(); ++iter){
            if((*iter)->SprawdzIDklasy() == ID_KLASY_PROBAREGOLITU){
                if((*iter)->CzyKolizja(AktywnyLazik)==TK_PrzejazdNadProbka){return Find_Probe_number((*iter));}
                //(*iter) = ObiektySceny.end();
            }
        }
        return 0;
    }

    

    /**
     * @brief Moves and animates active Rover on the Scene
     * POST: overrites the OdlefloscDoPrzejechania Field in the active Rover by dystans
     * 
     * @param dystans how far to go
     */
    void PrzejedzDystans_anim(double dystans);

    /**
     * @brief Rotates and animates the rotation of th =e Active Rover
     * POST: Active rover KatOrientacji Overriten will have be ve
     * 
     * @param obrot_calkowiy 
     */
    void ObrocOKat_anim(double obrot_calkowiy);

    /**
     * @brief Takes a probe on the FSR Rover
     * 
     */
    void Podejmij_probke();

    /**
     * @brief Prints out all the Probes witch are lying on the mars Surface
     * 
     */
    void Wyswietl_Probki_NaScenie()const;


    


    /**
     * @brief Takes the given probe From the Scene to a SFRRover
     * 
     * PRE: ptr_Probe have to point to the Probe
     * 
     * POST:_ListaProbek will be overriden with ptr_Probe and Scene list of ObiektGeom will be cut
     * 
     * @param ptr_Probe Pointer to the Probe which will be taken away from the Scene and will be put in LazikSFR
     */
    void WezProbkeZeScenyDoLazika(const std::shared_ptr<ObiektGeom> &ptr_Probe){
        //if PRE condition is not satisfaied throw an exception
        if(ptr_Probe->SprawdzIDklasy() != ID_KLASY_PROBAREGOLITU){throw std::invalid_argument("Only ProbkaRegolitu allowed in this Function(WezProbkeZeScenyDoLazika in Scena.hh)!\n");}

                                                    //check if active rover is a FSR Rover
        if(this->get_AktywnyLazik().SprawdzIDklasy()!= ID_KLASY_LAZIK_FSR)
        {std::cout<<"Tylko LazikSFR moze podejmowac probke!\n";}
        else                                        //if working on a FSR Rovewr then yace care of Probes 
        {
            //geting the LazikSFR
            std::shared_ptr<LazikSFR> Ptr_SFR_Rover = std::static_pointer_cast<LazikSFR>(get_LazikSFR());
            //puting the probe into FSR(we can becouse the PRE condition is taking care of that)
            Ptr_SFR_Rover->get__ListaProbek().push_back(std::static_pointer_cast<ProbkaRegolitu>(ptr_Probe));
            //removing the Probe from the Scene
            ObiektySceny.remove(ptr_Probe);

        }/*else*/

    }/*end fun*/
    
};







 
