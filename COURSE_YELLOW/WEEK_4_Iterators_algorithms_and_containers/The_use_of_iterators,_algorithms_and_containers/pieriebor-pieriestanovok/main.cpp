#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void permute(const int &N);

int main()
{

    int N;
    cin>>N;
    permute(N);
    return 0;
}

void permute(const int &N){
    vector<int> spec;
    for(int i=1;i<=N;i++){
        spec.push_back(i);
    }
    sort(spec.rbegin(), spec.rend());
    do {
        for(int i:spec){
            cout<<i<<" ";
        }
        cout<< '\n';
    } while(prev_permutation(spec.begin(), spec.end()));
}
