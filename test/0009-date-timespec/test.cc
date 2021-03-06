#include "../testenv.hh"
#include <mod/mod.stdio.hh>
#include <mod/mod.sys.hh>

using namespace std;

void test(duktape::engine& js)
{
  #if defined(__linux__) || defined(__linux)
  test_expect( js.eval<uint64_t>("var d = new Date('1970-01-01T00:05:00'); d;") == 300000 );
  test_expect( js.eval<string>("typeof(d)") == "object");
  test_expect( js.eval<bool>("d instanceof Date") == true);

  {
    struct ::timespec ts { 3600, 987000000};
    js.define("thetime", ts);
    test_expect( js.eval<string>("thetime;") == "1970-01-01 02:00:00.987+01:00" );
  }
  {
    struct ::timespec ts = js.eval<struct ::timespec>("d = new Date('1970-01-01T00:05:00.1'); d;");
    test_expect( ts.tv_sec == 300 && ts.tv_nsec == 100000000 );
  }
  #else
  (void) js;
  #endif
}
