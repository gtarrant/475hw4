#include "uberzahl.h"
#include <iostream>
#include <ctime>
#include <cassert>

using namespace std;

uberzahl RED(const uberzahl &T, const uberzahl &R, const uberzahl &MPrime, const uberzahl &M, const long long int &n){
    assert(T < )
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
    uberzahl r(1);
    r = r << n;
    
    a = a * r % M;
    
    uberzahl MPrime(M);
    MPrime = r - MPrime.inverse(r);
    
    uberzahl rInverse(r);
    rInverse = r.inverse(M);
    
    uberzahl multiplyStep(1);
    
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

int main(){
    //---// Original modexp time-trial //---//
    float run_time = 0;
    
    run_time=0;
    for(int i=0; i<3; i++){
    //Run three trials and average per timing run to account for clock resolution
        clock_t start = clock();
        cout << modexp1(uberzahl(13), uberzahl(1023), uberzahl(881*883)) << endl;
        clock_t end = clock();
        cout<<"Trial "<<i<<" time elapsed: "<<(end-start)*((float)1000)/CLOCKS_PER_SEC<<"millise}conds"<<endl;
            
        run_time+=run_time;
    }
    cout<<"Trial Average "<<run_time<<endl;
    run_time=0;
    
    run_time = 0;
    for(int i=0; i<3; i++){
    //Run three trials and average per timing run to account for clock resolution
        clock_t start = clock();
        cout << modexp3(21, uberzahl(13), uberzahl(1023), uberzahl(881*883)) << endl;
        clock_t end = clock();
        cout<<"Trial "<<i<<" time elapsed: "<<(end-start)*((float)1000)/CLOCKS_PER_SEC<<"millise}conds"<<endl;
        
        run_time+=run_time;
    }
    cout<<"Trial Average "<<run_time<<endl;
    run_time=0;
    
    //check consistency
    cout << modexp1(uberzahl(13), uberzahl(1023), uberzahl(881*883)) << endl;
    cout << modexp2(uberzahl(13), uberzahl(1023), uberzahl(881), uberzahl(883)) << endl;
    cout << modexp3(21, uberzahl(13), uberzahl(1023), uberzahl(881*883)) << endl;
}
