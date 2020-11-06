#include "Simple_String.h"
#include <cstring>
#include <iostream>

/*
  Notes:
  - Q: Why do we take in "const char*" parameters?
    * A: A few reasons. The most basic superficial answer is "because if you
         want to take in a parameter that's a string literal, that's what you do".

         If you're happy with that, awesome. 

         For more detail:
          1. Why const? Because string literals (strings created with quotation marks) are stored in
             read-only memory because the C++ spec says so. Why? Mostly due to
             optimization reasons, read here to learn more:
             https://stackoverflow.com/questions/14570993/why-are-string-literals-const#:~:text=If%20one%20program%20uses%20the,a%20separate%20chunk%20of%20memory.
          2. The actual type of "Hello, World" is not `const char*`; it is `const char[13]`. Here, we are implicitly letting the argument convert to a `const char*`
             pointing to the first element. 

  - Q: What's with the `length + 1` everywhere?
    * A: See here for a refresher on C-style strings: https://eecs280staff.github.io/notes/05_Strings_Streams_IO.html#c-style-strings

         Since we are representing strings internally as C-style strings, we need to include the null terminator '\0'.

         The string "Hello, world!" has a length of 13, but if we were to represent it in memory as a C-style string, we would need 13+1=14 characters:

         const char[14] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd', '!', '\0'}
                                                                                              ^

  - Q: Why are we calling the default/regular ctor in the copy ctor's initializer list?
    * A: To reduce duplicated code (DRY principle). 

         When writing the copy ctor, the goal is to construct a new
         Simple_String based off of another one such that our new instance has
         copied over all basic member variables and deep copied any dynamic
         resources. 

         If we look at what our default ctor does... it takes in a pointer to a
         character array and determines the length + allocates new memory and
         copies over the data from the passed in pointer. That's exactly what we want our copy ctor to do as well.

         Let's try just calling the default constructor then! That's what we do
         with procedural abstraction at least... just call the method that
         already does what you want instead of duplicating code:

         Simple_String::Simple_String(const Simple_String &original) {
          Simple_String(original.c_ptr);
         }

         Unfortunately... this doesn't do what we want. This winds up
         constructing _another_ Simple_String that immediately destructs (a
         temporary object). This is a consequence of constructors being distinct
         from functions

         Instead, we turn to C++11 "delegating constructor" syntax. 
         See here for Professor Kamil's notes about delegating ctors:
         https://eecs280staff.github.io/notes/08_ADTs_in_C++.html?highlight=delegating#delegating-constructors

         See here for a more detailed article from Microsoft about it:
         https://docs.microsoft.com/en-us/cpp/cpp/delegating-constructors?view=msvc-160

  - Q: Why are we saying that the Simple_String regular ctor is also the default ctor?
    * A: A default ctor is just one that can be invoked without any parameters. 

         It turns out that the rules for default arguments apply not only to
         functions, but to ctors too.

         We can leverage these rules to write a ctor that can be invoked with an
         optional parameter. If the ctor has all optional parameters, that means
         we can choose to invoke the ctor with 0 arguments which means we
         effectively just called a default ctor.

         See here to learn more about default arguments: https://www.learncpp.com/cpp-tutorial/77-default-arguments/

         A useful way to think about default arguments that comes from the
         article: "a parameter with a default value provided is often called an
         optional parameter."
  
*/

// Out of line definition for the default/regular ctor
// Note that in the declaration, cstr_ is an optional parameter that defaults to
// ""
Simple_String::Simple_String(const char *cstr_)
    : length(strlen(cstr_)), c_ptr(new char[length + 1]) {
  std::cout << "default/regular ctor called\n";

  // not only do we need to allocate enough memory, we need to copy the C-style
  // string from cstr_ into c_ptr
  strcpy(c_ptr, cstr_);
}

/* ==== BEGIN BIG 3: ==== */

// Out of line definition for the copy ctor
Simple_String::Simple_String(const Simple_String &original)
    : Simple_String(original.c_ptr) { // this is a C++11 delegating ctor
  std::cout << "copy ctor called\n";
}

// Out of line definition for the overloaded assignment operator
Simple_String &Simple_String::operator=(const Simple_String &rhs) {
  std::cout << "overloaded assignment operator called\n";
  if (this != &rhs) { // guarding against self assignment
    delete[] c_ptr;   // delete with [] because c_ptr is a dynamically allocated
                      //   _array_

    // shallow copy simple member variables
    length = rhs.length;

    // deep clone dynamic resources
    c_ptr = new char[length + 1];
    strcpy(c_ptr, rhs.c_ptr);
  }
  return *this;
}

// Out of line definition for the destructor
Simple_String::~Simple_String() {
  std::cout << "cleaning up memory\n";
  delete[] c_ptr; // delete with [] because c_ptr is a dynamically allocated
                  //   _array_
}

/* ==== END BIG 3: ==== */




// don't worry about this too much:
//  (if you're curious: this is me overloading the << operator so we can cout
//  Simple_Strings)
std::ostream &operator<<(std::ostream &os, const Simple_String &str) {
  os << str.c_ptr;
  return os;
}
