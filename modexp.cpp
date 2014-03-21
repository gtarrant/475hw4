#include "uberzahl.h"
#include <iostream>

using namespace std;

uberzahl modexp1(uberzahl n, uberzahl k, uberzahl m){
  uberzahl a(1);
  while(k > uberzahl(2)){
    if (k%2 == 0){
      k = k/2;
      n = (n*n)%m;
    }
    else{
      k = k - 1;
      a = (a*n)%m;
    }
  }
  return (a*n*n)%m; 
}

int main(){
  //cout << modexp1(uberzahl(2), uberzahl(10), uberzahl(1000)) << endl;
}
