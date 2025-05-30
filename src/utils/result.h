#ifndef RESULT_H
#define RESULT_H

typedef enum Result {
    // Success, no error
    RES_OK = 0,

    // Error, no specific message
    RES_ERROR,

    // Specific errors
    RES_DOES_NOT_EXIST,   // Resource or entity does not exist
    RES_UNIMPLEMENTED,    // Feature or functionality is not implemented
    RES_INVALID_ARGUMENT, // Invalid argument passed to a function
    RES_IO_ERROR,         // Input/output operation failed
    RES_MEMORY_ERROR,     // Memory allocation or mapping failed
    RES_PERMISSION_ERROR, // Insufficient permissions for the operation
    RES_TIMEOUT,          // Operation timed out
    RES_UNSUPPORTED_MODE, // Unsupported mode or configuration
    RES_HARDWARE_ERROR,   // Hardware-related error
    RES_NOT_READY         // Value not ready
} Result;

#endif
