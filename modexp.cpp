#include "uberzahl.h"
#include <iostream>
#include <ctime>
#include <cassert>
#include <cstdlib>

using namespace std;

uberzahl RED(const uberzahl &T, const uberzahl &R, const uberzahl &MPrime, const uberzahl &M, const long long int &n){
    uberzahl m(T*MPrime);
    m = m & (R-uberzahl(1));
    uberzahl t((T+m*M) >> n);
    
    if(t>=M) return (t-M);
    else return t;
}

uberzahl modexp1(uberzahl n, uberzahl k, uberzahl m){
// original modexp: n^k mod mR
  uberzahl a(1);
  while(k > uberzahl(2)){
    if (k % 2 == 0){
      k = k >> 1;
      n = (n*n)%m;
    }
    else{
      k = k - 1;
      a = (a*n)%m;
    }
  }
  return (a*n*n)%m; 
}

// compute a^k mod pq using CRT
uberzahl modexp2(uberzahl a, uberzahl k, uberzahl p, uberzahl q){
    uberzahl a_p = modexp1(a, k % (p-uberzahl(1)), p);
    uberzahl a_q = modexp1(a, k % (q-uberzahl(1)), q);
    return a_q + q * ((q.inverse(p)*(a_p - a_q))%p);
}

uberzahl modexp3(long long int n, uberzahl a, uberzahl k, uberzahl M){
    //Version with Montgomery Residues + Reductions
    //a^k mod M
    uberzahl r(1);
    r = r << n;
    
    a = a * r % M;
    
    uberzahl MPrime = r - M.inverse(r);
    
    uberzahl rInverse = r.inverse(M);
    
    uberzahl multiplyStep = r % M;
    
    while( k > uberzahl(2)) {
        if (k % 2 == 0) {
            k = k >> 1;
            //a = (a*a*rInverse) % M;
            a = RED(a*a, r, MPrime, M, n);
        }
        
        else {
            k = k - 1;
            //multiplyStep = (multiplyStep*a*rInverse) % M;
            multiplyStep = RED(multiplyStep*a, r, MPrime, M, n);
            
        }
    }
    //return (multiplyStep*a*a*rInverse*rInverse*rInverse) % M;
    return RED(RED(RED(a*multiplyStep, r, MPrime, M, n) * a, r, MPrime, M, n), r, MPrime, M, n);
}

uberzahl modexp4(long long int n, uberzahl a, uberzahl k, uberzahl p, uberzahl q) {
    uberzahl a_p = modexp3(n, a, k % (p-uberzahl(1)), p);
    uberzahl a_q = modexp3(n, a, k % (q-uberzahl(1)), q);
    return a_q + q * ((q.inverse(p)*(a_p - a_q))%p);
  
}

int main(int argc, char ** argv){
    
    //check consistency
    cout << "\ncheck\n";
    cout << modexp1(uberzahl(13), uberzahl(1023), uberzahl(881*883)) << endl;
    cout << modexp2(uberzahl(13), uberzahl(1023), uberzahl(881), uberzahl(883)) << endl;
    cout << modexp3(100, uberzahl(13), uberzahl(1023), uberzahl(881*883)) << endl;
    cout << modexp4(100, uberzahl(13), uberzahl(1023), uberzahl(881), uberzahl(883)) << endl;
    
    cout << modexp1(uberzahl(13), uberzahl(1024), uberzahl(881*883)) << endl;
    cout << modexp2(uberzahl(13), uberzahl(1024), uberzahl(881), uberzahl(883)) << endl;
    cout << modexp3(100, uberzahl(13), uberzahl(1024), uberzahl(881*883)) << endl;
    cout << modexp4(100, uberzahl(13), uberzahl(1024), uberzahl(881), uberzahl(883)) << endl;
	
    cout << modexp1(uberzahl(13), uberzahl(1025), uberzahl(881*883)) << endl;
    cout << modexp2(uberzahl(13), uberzahl(1025), uberzahl(881), uberzahl(883)) << endl;
    cout << modexp3(100, uberzahl(13), uberzahl(1025), uberzahl(881*883)) << endl;
    cout << modexp4(100, uberzahl(13), uberzahl(1025), uberzahl(881), uberzahl(883)) << endl;
    
    //performance test
    srand(atoi(argv[3]));
    int fn = atoi(argv[1]);
    int bits = atoi(argv[2]);
    
    uberzahl base, exp;
    base.random(bits/2);
    exp.random(bits/2);
    uberzahl p = nextprime(base, 50);
    uberzahl q = nextprime(p, 50);
    
    switch (fn) {
        case 1:
            modexp1(base, exp, p*q);
            break;
        case 2:
            modexp2(base, exp, p, q);
            break;
        case 3:
            modexp3(bits+1, base, exp, p*q);
            break;
        case 4:
            modexp4(bits+1, base, exp, p, q);
            break;
    }
    
}
