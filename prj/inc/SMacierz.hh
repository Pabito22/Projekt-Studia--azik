

#include "SWektor.hh"

#define ROZMIAR 3

#include <iostream>

/**
 * @brief Simulates Matrix
 * 
 * @tparam Typ -  what cind of built in type you want to use
 * @tparam Rozmiar - dimension of matrix
 */
template<typename Typ, uint Rozmiar = ROZMIAR>
class SMacierz {

    private:

    /*describes a matrix*/
    SWektor<Typ> cols[Rozmiar];

    public:

    SMacierz(Typ a = 0){
        for(uint i=0; i< Rozmiar; ++i){
            for(uint j=0; j < Rozmiar; ++j){
                cols[i][j] = a;
            }
        }
    }


    /*uses domain constructor*/

    /**
     * @brief allows to read one partial vector from the matrix
     * 
     * @param column_id index of wektor which we want to read
     *                      must be between [0 ; Rozmiar)
     * @return SWektor 
     */
    SWektor<Typ> operator[] (uint column_id)const{
        if(column_id < Rozmiar){
            return this->cols[column_id];
        }else{
            throw std::invalid_argument("Matrix operator[] - too big id\n");
        }
    }

    /**
     * @brief allows to write into partial Vector from the matrix
     * 
     * @param column_id index of wektor to which we want to write into
     *                      must be between [0 ; Rozmiar)
     * @return SWektor& 
     */
    SWektor<Typ>& operator[](uint column_id){
        if(column_id < Rozmiar){
            return this->cols[column_id];
        }else{
            throw std::invalid_argument("Matrix operator[] - too big argument\n");
        }
    }

    /**
     * @brief allows to read one particular field from the matrix
     * 
     * @param column_id number of the column from which we want to read
     * @param row_id number of the row from which we want to read
     * @return Typ 
     */
    Typ operator()(uint column_id, uint row_id)const{
        if(column_id < Rozmiar && row_id <Rozmiar){
            return this->cols[column_id][row_id];
        }else{
            throw std::invalid_argument("Matrix operator() - too big argument\n");
        }
    }
    
    /**
     * @brief allows to write into one particular field from the matrix
     * 
     * @param column_id number of the column from which we want to read
     * @param row_id number of the row from which we want to read
     * @return Typ 
     */
    Typ& operator()(uint column_id, uint row_id){
        if(column_id < Rozmiar && row_id < Rozmiar){
            return this->cols[column_id][row_id];
         }else{
            throw std::invalid_argument("Matrix operator() - too big argument\n");
        }
    }

    /**
   * wykonuje zamiane n-tego wektora z macierzy na podany wektor
   * @arg:
   * wek_nr - numer wektora z macierzy ktory ma zostac zamieniony
   * wektor - nowy wektor ktory zostanie wpisany do macierzy
   * PRE:
   * wek_nr (0;ROZMIAR)
   * @return:
   * Macierz ze zmienionzm n-tym wektorem
   * */
    SMacierz zamienWektor(uint wek_nr,const SWektor<Typ> &wektor)const{
        if(wek_nr < Rozmiar){
            SMacierz<Typ> wynik;
            wynik = *this;
            wynik[wek_nr] = wektor;
            return wynik;
        }else{
            throw std::invalid_argument("Matrix operator() - too big argument\n");
        }
    }

    /**
     * @brief makes a matrix transponation
     * 
     * @return SMacierz 
     */
    SMacierz Transponuj()const{
        SMacierz wynik;

        for(uint i =0; i<Rozmiar; ++i)
        {
            for(uint j = 0; j<ROZMIAR; ++j){
                wynik(i,j)= this->cols[j][i];
            }
        }
        return wynik;
    }

    Typ Wyznacznik()const{
        Typ wynik;
    
        wynik = this->cols[0][0]*this->cols[1][1]*this->cols[2][2] + this->cols[1][0]*this->cols[2][1]*this->cols[0][2] + this->cols[2][0]*this->cols[0][1]*this->cols[1][2];
        wynik = wynik - this->cols[0][2]*this->cols[1][1]*this->cols[2][0] + this->cols[1][2]*this->cols[2][1]*this->cols[0][0] + this->cols[2][2]*this->cols[0][1]*this->cols[1][0];
        return wynik;
    }

    


    Typ Gauss()const{
        

        Typ Wynik = 1;  //


        SMacierz<Typ> M = (*this);  //macierz z ktorej liczymy wyznacznik
        const SWektor<Typ> W = M[0];      //za
        SWektor<Typ> Wpom = M[0];       //
        
        uint col_nr=0;         //zlicza kolumny
        uint vec_nr=0;        //zlicza wektory
        uint ilosc_zmian=0;     //ile zmian kolumn (do przemnozenia przez 1)
        SWektor<Typ> Wekdozmiany;

        for(uint i = 0; i < Rozmiar; ++i){

            if(M(i,i)==0){      //jezeli na przekatnej zero to zamien

                for(uint z = i; z < Rozmiar; ++z){   //przeszukujemy aktualna kolumne i szukamy czegos != 0 
                    if(M(z,i)!=0){
                        vec_nr=z;
                        Wekdozmiany = M[z];
                        M = M.zamienWektor(i,M[z]);     //zamien jezeli znalazles
                        M = M.zamienWektor(z,(*this)[i]);

                        ++ilosc_zmian;
                        z = Rozmiar;    //zakoncz poszuiwania
                    }
                   
                }
                
                if((ilosc_zmian==0)){         //jezeli nie znalezlismy 0 to zakoncz
                    std::cout<<"zero\n";
                     Wynik = 0;
                     return Wynik;
                } 
            }
            Wpom = M[i];//

            for(uint j = i+1;j <Rozmiar; ++j ){     //wyzeruj elementy pod diagonalia

                Wpom = (Wpom * (M(j,i)/M(i,i))) ;
                
                M[j] = (M[j] - Wpom);
                

                Wpom = M[i];
            }
        }//konie z gausem for

        for(uint p=0; p< Rozmiar; ++p){     //przemnoz diagonalia
            Wynik= Wynik * M(p,p);
        }
        
        if(ilosc_zmian%2){              //pomnoz przez minus 1 jezeli  czea
            Wynik= Wynik * (-1.0);
            std::cout<<"wynik"<<Wynik<<'\n';
        }

        return Wynik;
    }

    /**
   * realizuje mnozenie macierzy przez wektor
   * @arg:
   * wektor - wektor przez ktory bd mnozona macierz
   * @return:
   * wektor,ktory jest wynikiem mnozenia
   * */
  SWektor<Typ> operator *(const SWektor<Typ> &wektor)const{

    SWektor<Typ> wynik;
    double add_counter=0;

    SMacierz<double,3> M = (*this).Transponuj();

    for(uint i= 0; i<Rozmiar; ++i){
        for(uint j = 0; j< Rozmiar; ++j){
            add_counter += M[i][j]* wektor[j];
        }
        wynik[i] = add_counter;
        add_counter = 0;
    }

    return wynik;
  }

};

/**
 * @brief writes values to matrix from given input
 * 
 * @tparam Typ what type of built in variables you use
 * @tparam Rozmiar how big is the matrix
 * @param StrIn input 
 * @param mac matrix to be overriten by input
 * @return std::istream& 
 */
template<typename Typ, uint Rozmiar = ROZMIAR>
std::istream& operator >> (std::istream &StrIn, SMacierz<Typ> &mac){
    for(uint i = 0; i<Rozmiar; ++i){
        StrIn>>mac[i];
    }
    return StrIn;
}

/**
 * @brief prints out Matrix to given output
 * 
 * @tparam Typ what type of built in variables you use
 * @tparam Rozmiar how big is the matrix
 * @param StrOut output
 * @param mat matrix to bi printed to the given output
 * @return std::ostream& 
 */
template<typename Typ, uint Rozmiar = ROZMIAR>
std::ostream& operator <<(std::ostream &StrOut, SMacierz<Typ> &mat){
    for(uint i = 0; i<Rozmiar ; ++i){
        StrOut<<mat[i]<<std::endl;
    }
    return StrOut;
}