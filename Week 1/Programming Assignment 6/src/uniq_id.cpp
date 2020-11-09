#include <string>
#include <vector>
using namespace std;

#define f(lineno) local_var_##lineno
#define g(lineno) f(lineno)
#define UNIQ_ID g(__LINE__)

