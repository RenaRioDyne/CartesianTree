#pragma once

// paper: Simone Faro et al., On the longest common Cartesian substring problem
// method: Compute-Parent-Distance(x,m), p.5

#include <string_view>
#include <vector>

struct stackItem {
    int value;
    int index;
};

class ParentDistance {
private:
    std::vector<int> distance;
    int length;
    
public:
    ParentDistance(std::string_view targetString);  // Compute-Parent-Distance

    int getDistance(int index);

    int operator[](int idx);

    int getLength();
};