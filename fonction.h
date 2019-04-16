#include <vector>
#include <iostream>
#include <cmath>
using namespace std;
const double epsilon = pow(10,-5);


//Definition de la classe Mere Fonction
class Fonction{
protected:
    //definition d'un nouveau champs integrale pour definir la derivee de la fonction tan
    Fonction* integrale;
public:
    virtual float operator()(float x) const{
        if(integrale != 0){
            float valeur = ((*integrale)(x+epsilon))/((*integrale)(x-epsilon))/(2*epsilon);
            return valeur;
        }
        else{
            throw("ERREUR");
        }
    }
    virtual Fonction* derivee() const;
    Fonction(Fonction* Inte);
    Fonction();
    float inverse(float y) const;
    virtual ~Fonction();
};


//Definition de la classe Polynome fille de la classe Mere Fonctions
class Polynome : public Fonction{
protected :
    // le degre du polynome s'obtient en faisant un coefficients.size();
    vector<float> coefficients;
public :
    //constructeur
    Polynome(vector<float> coef);
    //destructeur
    virtual ~Polynome(){
        cout << "~Polynome" << endl;
    }
    Fonction* derivee() const;
    float operator()(float x) const;
};


//Definition de la classe Affine, fille de la classe Polynome
class Affine : public Polynome{
private :
    vector<float> parametres;
public:
    //definition directe du constructeur d'une fonction de la classe Affine par utilisation de celui de la classe Polynome
    Affine(vector<float> param):Polynome(param){};
    ~Affine(){
        cout << "~Affine" << endl;
    }
    Fonction* derivee() const;
    float operator()(float x) const;
};


//Definition de la classe Fonction, fille de la classe Fonction
class Trigo : public Fonction {
protected:
    string type_fct_trigo;
public:
    //constructeur
    Trigo(string A);
    //destructeur
    ~Trigo() {
        cout << "~Trigo" << endl;
    }
    //Fonction* derivee() const;
    float operator()(float x) const;
    Fonction* derivee() const;
};
