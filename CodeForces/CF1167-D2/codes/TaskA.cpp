#include "../library/mylibrary.h"

void solve(istream &in, ostream &out)
{
  int t;
  in >> t;

  while(t--)
  {
    int n;
    in >> n;
    bool ok = false;
    for(int i=1;i<=n;++i)
    {
      char x;
      in >> x;
      if(x == '8' && n - i > 9)
        ok = true;
    }
    if(ok) out << "YES\n";
    else out << "NO\n";
  }
}
void clear()
{
}