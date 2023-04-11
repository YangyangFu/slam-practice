// header file is used to define the interface of a library
// the interface is the method name, the input and output parameters
// the implementation of the method is in the cpp file

// Define a macro to avoid multiple inclusion of the header file
// #ifndef and #endif are used to define a macro
// #ifndef LIBHELLOSLAM_H_ means if the macro LIBHELLOSLAM_H_ is not defined
#ifndef LIBHELLOSLAM_H_
#define LIBHELLOSLAM_H_

// specify the method name and the input and output parameters
void printHello();

#endif
