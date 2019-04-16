#include <iostream>
#include "fonction.h"
#include "math.h"
using namespace std;

int main(){

    vector<float> v(2);
    v[0] = 1;
    v[1] = 8;
    Affine A(v);
    float b = A.inverse(14);
    cout << b << endl;
    Polynome P(v);
    Fonction* D = A.derivee();
    cout << D->operator()(2) << endl;
    Trigo B("cos");
    cout << B.operator()(M_PI/2) << endl;
    //Trigo E("tan");
    //cout << E.operator ()(M_PI/4) << endl;

    // Premier Test
    //   vector<float> u(4);
    //   u[0] = 0;
    //   u[1] = 0;
    //   u[2] = 0;
    //   u[3] = 1;
    //   Polynome Q(u);
    //   cout << Q.operator ()(3) << endl;
    //   float q = Q.inverse(27);
    //   cout << "q vaut :" << q << endl;

    // Deuxième Test
    //    Trigo C("tan");
    //    float d = 4*C.inverse(1);
    //    cout << "d vaut :" << d << endl;


    return 0;
}
