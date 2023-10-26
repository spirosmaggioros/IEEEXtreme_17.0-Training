#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif
using namespace std;

#define ll long long
#define vector_ll vecor<long long>
#define MOD 1000000007

typedef long long int int64;
typedef unsigned long int uint32;

int minMaxSubarray(const vector<int>& v) {
    auto minim = *min_element(v.begin() , v.end());
    auto maxim = *max_element(v.begin() , v.end());
    int lo = 0 , hi = 0 , ans = v.size();
    while(hi < v.size()){
        if(v[hi] == minim){
            if(v[lo] == maxim){
                ans = min(ans , hi - lo + 1);
            }
            for(; lo<hi; lo++){
                if(v[lo] == maxim){
                    ans = min(ans , hi - lo + 1);
                }
            }
        }
        else if(v[hi] == maxim){
            if(v[lo] == minim){
                ans = min(ans , hi - lo + 1);
            }
            for(; lo < hi; lo++){
                if(v[lo] == minim){
                    ans = min(ans , hi - lo + 1);
                }
            }
        }
        hi++;
    }
    return ans;
}
