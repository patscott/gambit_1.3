//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  General small utility functions.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2013 Apr, July, Aug, Dec
///  \date 2014 Mar
///  \date 2015 Apr
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2013 May, June, July
///
///  *********************************************


#ifndef __util_functions_hpp__
#define __util_functions_hpp__

#include <vector>
#include <chrono>
#include <cmath>

#include "gambit/Utils/util_types.hpp"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

extern "C"
{
  #include "mkpath/mkpath.h"
}

# if GAMBIT_CONFIG_FLAG_use_std_regex
  #include <regex>
  #define GAMBIT_CONFIG_FLAG_use_regex 1
  namespace Gambit { using std::regex; using std::regex_replace; }
#elif GAMBIT_CONFIG_FLAG_use_boost_regex
  #include <boost/regex.hpp>
  #define GAMBIT_CONFIG_FLAG_use_regex 1
  namespace Gambit { using boost::regex; using boost::regex_replace; }
#else
  #include <boost/algorithm/string/replace.hpp>
  #define GAMBIT_CONFIG_FLAG_use_regex 0
#endif

namespace Gambit
{

  /// Redirection function to turn an lvalue into an rvalue, so that it
  /// is correctly passed by value when doing perfect forwarding with
  /// functor typecasting.
  template <typename T>
  T byVal(T t) { return t; }

  template <typename T>
  int sgn(T val) { return (T(0) < val) - (val < T(0)); }

  /// Make sure there are no nasty surprises from regular C abs()
  using std::abs;

  namespace Utils
  {

    /// Split a string into a vector of strings, using a delimiter,
    /// and removing any whitespace around the delimiter.
    EXPORT_SYMBOLS std::vector<str> delimiterSplit(str s, str delim);

    /// Strips namespace from the start of a string, or after "const".
    EXPORT_SYMBOLS str strip_leading_namespace(str s, str ns);

    /// Strip all whitespace except that following "const",
    /// in which case the whitespace is replaced by a single space.
    EXPORT_SYMBOLS void strip_whitespace_except_after_const(str&);

    /// Strips leading and/or trailing parentheses from a string.
    EXPORT_SYMBOLS void strip_parentheses(str&);

    /// Created a str of a specified length.
    EXPORT_SYMBOLS str str_fixed_len(str, int);

    /// Copy a str to a character array, stripping the null termination character.
    EXPORT_SYMBOLS void strcpy2f(char*, int, str);

    /// Checks whether `str' ends with `suffix'
    EXPORT_SYMBOLS bool endsWith(const std::string& str, const std::string& suffix);

    /// Checks whether `str' begins with `prefix'
    EXPORT_SYMBOLS bool startsWith(const std::string& str, const std::string& prefix);

    /// Get pointers to beginning and end of array.
    // Useful for initialising vectors with arrays, e.g.
    //   int vv[] = { 12,43 };
    //   std::vector<int> v(beginA(vv), endA(vv));
    // Though 'begin' is unnecessary, can just do
    //   std::vector<int> v(vv, endA(vv));
    template <typename T, size_t N>
    T* beginA(T(&arr)[N]) { return &arr[0]; }
    template <typename T, size_t N>
    T* endA(T(&arr)[N]) { return &arr[0]+N; }

    /// Test if two sets are disjoint (works on any sorted std container I think)
    // From http://stackoverflow.com/questions/1964150/c-test-if-2-sets-are-disjoint
    template<class Set1, class Set2>
    bool is_disjoint(const Set1 &set1, const Set2 &set2)
    {
      if(set1.empty() || set2.empty()) return true;

      typename Set1::const_iterator
          it1 = set1.begin(),
          it1End = set1.end();
      typename Set2::const_iterator
          it2 = set2.begin(),
          it2End = set2.end();

      if(*it1 > *set2.rbegin() || *it2 > *set1.rbegin()) return true;

      while(it1 != it1End && it2 != it2End)
      {
          if(*it1 == *it2) return false;
          if(*it1 < *it2) { it1++; }
          else { it2++; }
      }

      return true;
    }

    /// Ensure that a path exists (and then return the path, for chaining purposes)
    EXPORT_SYMBOLS const str& ensure_path_exists(const str&);

    /// Check if a file exists
    EXPORT_SYMBOLS bool file_exists(const std::string& filename);

    /// Return a vector of strings listing the contents of a directory (POSIX)
    EXPORT_SYMBOLS std::vector<str> ls_dir(const str& dir);

    /// Get directory name from full path+filename (POSIX)
    EXPORT_SYMBOLS str dir_name(const str& path);

    /// Get file name from full path+filename (POSIX)
    EXPORT_SYMBOLS str base_name(const str& path);

    /// Delete all files in a directory (does not act recursively)
    EXPORT_SYMBOLS int remove_all_files_in(const str& dirname, bool error_if_absent = true);


    typedef std::chrono::time_point<std::chrono::system_clock> time_point;

    /// Get clock time
    EXPORT_SYMBOLS time_point get_clock_now();

    /// Get date and time
    EXPORT_SYMBOLS str return_time_and_date(const time_point& in);

    /// Check if two strings are a "close" match
    /// Used for "did you mean?" type checking during command line argument processing
    EXPORT_SYMBOLS bool are_similar(const str& s1, const str& s2);

    /// Sub-check for are_similar.
    /// true if s1 can be obtained by deleting one character from s2
    bool check1(const str& s1, const str& s2);

    /// Sub-check for are_similar.
    /// true if s1 can be obtained from s2 by changing no more than X characters (X=2 for now)
    bool check2(const str& s1, const str& s2);

    /// returns square of double - saves tedious repetition
    EXPORT_SYMBOLS double sqr(double a);

    /// Local GAMBIT definition of isnan.  Could be redefined at a later point, depending on compiler support.
    using std::isnan;

    /// Local GAMBIT definition of isinf.  Could be redefined at a later point, depending on compiler support.
    using std::isinf;

    /// Check if a string represents an integer
    /// From: http://stackoverflow.com/a/2845275/1447953
    EXPORT_SYMBOLS bool isInteger(const std::string&);

    // Dummy functions for variadic variables to avoid compiler warnings
    template<typename... T> void dummy_function() {}
    template<typename T> void dummy_function(T one)
    {
      (void)one;
    }

    template<typename T1, typename... T> void dummy_function(T1 first, T... args)
    {
     (void)first;
     dummy_function(args...);
    }

  }

}

#endif //defined __util_functions_hpp__
