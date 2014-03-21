#include "uberzahl.h"
#include <iostream>

using namespace std;

uberzahl modexp1(uberzahl n, uberzahl k, uberzahl m){
// original modexp: n^k mod m
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
        if (k % 2 == 0) {
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
    cout << modexp3(21, uberzahl(13), uberzahl(1023), uberzahl(881*883)) << endl;
  //cout << modexp1(uberzahl(2), uberzahl(10), uberzahl(1000)) << endl;
}

uberzahl RED(uberzahl T, uberzahl R, uberzahl rInverse, uberzahl M, long long int n){

	uberzahl MPrime = R - (M.inverse(R));
    uberzahl m = (T*MPrime);
    
    //m=m<<(m.bitLength()-n);
    //m = m >> n;
    
    m = m & (R-1);
    
    uberzahl t((T+m*M)/R);
    if(t>=M) return (t-M);
    else return t;
}
