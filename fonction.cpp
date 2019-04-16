#include "fonction.h"
#include <vector>
#include <iostream>
#include <cmath>
#include "assert.h"
#include "string.h"
#include "math.h"
using namespace std;

//definition du nombre d'iterations maximum pour la methode de Newton
int iter_max = 100;

//Definition de la methode derivee de Fonction
Fonction* Fonction::derivee() const{
    return new Fonction(*this);
}


//constructeur de Fonction
Fonction::Fonction(){
    integrale = 0;
}

//constructeur de Fonction prenant en parametre le pointeur integrale
Fonction::Fonction(Fonction* Inte){
    integrale = Inte;
}


//destructeur de Fonction
Fonction::~Fonction(){
    delete integrale;
}



// Calcul de l'inverse d'une fonction par utilisation de la méthode de Newton
float Fonction::inverse(float y) const{
    double x0 = 1;
    double x = x0;
    double xnew;
    int i = 0;
    Fonction* der = this->derivee();
    while(i<iter_max && abs(xnew-x)>epsilon){
        xnew = x + (y- this->operator()(x)) / (der->operator()(x));
        x = xnew;
        i++;
    }
    delete der;
    if (i== iter_max){
        cout << "la méthode ne converge pas" << endl;
    }
    else {
        cout << "la méthode converge en" << i << "itérations" << endl;
    }
    return xnew;
}


//Constructeur de la classe Polynome
//Utiliastion de vector pour stocker les coefficients de polynome plutot que d'un tableau pour ne pas faire d'allocations dynamiques.
Polynome::Polynome(vector<float> coef) {
    vector<float>::const_iterator it;
    for(it= coef.begin(); it!=coef.end(); ++it){
        coefficients.push_back(*it);
    }
}


//Definition de la derivee de Polynome
Fonction* Polynome::derivee() const{
    int l = coefficients.size();
    std::vector<float> coef(l-1);
    for (int i=0; i<l-1; i++){
        coef.push_back((i+1)*coefficients[i+1]);
    }
    Fonction* fonction_derivee;
    *fonction_derivee = Polynome(coef);
    return fonction_derivee;
}

//Definition de la methode d'évaluation d'une fonction de la classe Polynome par l'algorithme de Horner
float Polynome::operator()(float x) const{
    float valeur = 0;
    for (int i=coefficients.size()-1;i>-1;i--) {
        valeur = x*valeur + coefficients[i];
    }
    return valeur;
}


// Definition de la methode de derivation d'une fonction de la classe Affine
Fonction* Affine::derivee() const{
    std::vector<float> coef(2);
    coef[0] = coefficients[1];
    coef[1] = 0;
    return new Affine(coef);
}


//Definition de la methode d'evaluation d'une fonction de la classe Affine
float Affine::operator()(float x) const{
    return coefficients[0] + coefficients[1]*x;
}


//Constructeur de la classe Trigo :
Trigo::Trigo (string A){
    assert ((A == "cos") || (A == "sin") || (A == "tan"));
    type_fct_trigo = A;
}

//Definition de la methode d'evaluation d'une fonction de la classe Trigo :
float Trigo::operator()(float x) const{
    if (type_fct_trigo == "cos"){
        return cos(x);
    }
    if (type_fct_trigo == "sin"){
        return sin(x);
    }
    if (type_fct_trigo == "tan"){
        return tan(x);
    }
}

//Definition de la fonction derivee pour la classe Trigo : s'il s'agit de la fonction sinus on renvoit le cosinus
// sinon appel a la fonction derivee de Fonction

Fonction* Trigo::derivee() const{
    if(type_fct_trigo == "sin"){
        return new Trigo("cos");
    }
    return Fonction::derivee();
}
