#include <iostream>
using namespace std;

int Mystery(int, int);

int Mystery(int x, int n)
{
if (n == 1)
   return x;
else
   return(x + Mystery(x, (n + 1)));
}
int main ()
{
int x, n;

cout << "input x." <<endl;
cin >> x;
cout << "input y." <<endl;
cin >> n;

cout << Mystery(x,n) << endl;




}
