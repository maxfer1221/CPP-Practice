// Example program
#include <iostream>
#include <vector>

using namespace std;

vector<int> insert_sort(vector<int> a, vector<int> b)
{
    for(vector<int>::iterator it = b.begin(); it != b.end(); ++it)
    {
        int bval = *it;
        for(vector<int>::iterator it2 = a.begin(); it2 != a.end(); ++it2)
        {
            int aval = *it2;
                        
            if(aval == bval)
            {
                a.erase(it2);
                break;
            }
            else if(aval > bval)
            {
                a.insert(it2, bval);
                break;   
            }
        }
    }
    return a;
}

int main()
{
  	// test case below
    int aarr[] = {1,5,7,8,16};
    int barr[] = {2,3,5,7,13};
    vector<int> a (aarr, aarr + sizeof(aarr) / sizeof(int) );
    vector<int> b (barr, barr + sizeof(barr) / sizeof(int) );
    
    vector<int> result = insert_sort(a,b);
  
  	// output results
  	cout << "Result of insert sort of a and b is: ";
 	for(vector<int>::iterator it = result.begin(); it != result.end(); ++it)
    {
      cout << *it << " ";
    }
}
