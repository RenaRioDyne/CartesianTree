// paper: Simone Faro et al., On the longest common Cartesian substring problem
// method: Compute-Parent-Distance(x,m), p.5

#include <string_view>
#include <stack>
#include "parentDistance.h"
#include <iostream>

ParentDistance::ParentDistance(std::string_view targetString){
    std::stack<stackItem> stack;
    stackItem cur;

    length = targetString.length();
    distance.resize(length);

    for(int i=0; i<length; i++){
        while(!stack.empty()){
            cur = stack.top();
            if(cur.value <= targetString[i]){
                distance[i] = i - cur.index;
                break;
            }
            stack.pop();
        }
        if(stack.empty()){
            distance[i] = 0;
        }

        cur.index = i;
        cur.value = targetString[i];
        stack.push(cur);

        std::cout << distance[i] << " ";
    }
    std::cout << std::endl;
}

int ParentDistance::getDistance(int index){
    if(index <= 0 || index > length){
        throw 0;
    }
    return distance[index-1];
}

int ParentDistance::operator[](int idx) {
    return getDistance(idx);
}

int ParentDistance::getLength(){
    return length;
}