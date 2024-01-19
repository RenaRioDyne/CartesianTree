// paper: Simone Faro et al., On the longest common Cartesian substring problem
// method: Compute-Longest-Cartesian-Substring(x,m,y,n), p.7

#include "parentDistance.h"
#include <iostream>

int lccs_dp_main(int argc, char **argv)
{
    if(argc < 3){
        fprintf(stderr, "give 2+ strings to compute their longest common cartesian subsequence.\n");
        return -1;
    }

    ParentDistance x(argv[1]);
    ParentDistance y(argv[2]);

    int maxlength = 1;
    int m = x.getLength();
    int n = y.getLength();

    for(int d = -m+2; d<=n-2; d++){
        int i = 2;
        int j = 2;
        if(d<0) i = -d+2;
        else if(d>0) j = d+2;
        int ip = i-1;
        int jp = j-1;

        while(i<=m && j<=n){
            int lx = (x[i] < i - ip + 1 ? x[i] : 0);
            int ly = (y[j] < j - jp + 1 ? y[j] : 0);
            int l;

            if(lx != ly){
                if(lx == 0){
                    l = ly;
                }else if(ly == 0){
                    l = lx;
                }else l=std::min(lx, ly);

                ip = i-l+1;
                jp = j-l+1;
            }else{
                maxlength = std::max(maxlength, i-ip+1);
            }

            i++;
            j++;
        }
    }

    std::cout << "DP lccs result: " << maxlength << std::endl;

    return 0;
}