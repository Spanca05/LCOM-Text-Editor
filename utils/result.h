#ifndef RESULT_H
#define RESULT_H

typedef enum {
    // Success, no error
    RES_OK = 0,

    // Error, no specific message
    RES_ERROR,

    // Add more specific errors here
    // Always add a comment above it explaining what it means (it can be multiple lines)
    // Example errors: RES_IO_ERROR, RES_INVALID_ARGUMENT, RES_TIMEOUT...
} Result;

#endif
