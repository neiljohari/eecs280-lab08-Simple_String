#include <ostream>

class Simple_String {
  size_t length;
  char *c_ptr;
public:
  Simple_String(const char *cstr_ = ""); // Default/custom constructor
  Simple_String(const Simple_String &original); // Copy constructor
  Simple_String& operator= (const Simple_String &rhs); // Assignment operator
  ~Simple_String(); // Destructor

  // don't worry about this too much:
  //    (if you're curious: this is me overloading the << operator so we can cout Simple_Strings)
  friend std::ostream& operator<<(std::ostream& os, const Simple_String& str);
};
