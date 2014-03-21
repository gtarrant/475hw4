#include "uberzahl.h"
#include <iostream>

using namespace std;

uberzahl modexp1(uberzahl n, uberzahl k, uberzahl m){
// original modexp: n^k mod m
  uberzahl a(1);
  while(k > uberzahl(2)){
    if (k & 1 == 0){
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
    return a_p * q * q.inverse(p) + a_q * p * p.inverse(q);
}



uberzahl modexp3(long long int n, uberzahl a, uberzahl k, uberzahl M){
    //Version with Montgomery Residues + Reductions
    uberzahl r(1);
    r = r << n;
    
    a = a * r % M;
    
    uberzahl rInverse;
    rInverse = r.inverse(M);
    
    uberzahl multiplyStep(1);
    
    while( k > uberzahl(2)) {
        if (k & 1 == 0) {
            k = k >> 1;
            a = (a*a*rInverse) % M;
        }
        
        else {
            k = k - 1;
            multiplyStep = (multiplyStep*a*rInverse) % M;
        }
    }
    return (multiplyStep*a*a*rInverse*rInverse*rInverse) % M;
}

int main(){
    cout << modexp3(21, 13, 1023, 881*883)
  //cout << modexp1(uberzahl(2), uberzahl(10), uberzahl(1000)) << endl;
}

uberzahl Red(uberzahl T, uberzahl rInverse, uberzahl M) {
    return T * rInverse % M;
}

uberzahl RED(uberzahl T, uberzahl r, uberzahl rInverse, uberzahl M){

	uberzahl MInverse = r*rInverse/M;
	uberzahl m = T*MInverse)

}
