/**
 * @file Location.h
 */

#ifndef LOCATION_H
#define LOCATION_H

//{------------------------------------------------------------------------------------------------
/**
 * Defining standard function name macros
 */

#ifndef __FUNCTION__

    #ifdef __FUNC__
        #define __FUNCTION__ __FUNC__
    #elifdef __func__
        #define __FUNCTION__ __func__
    #elifdef __func_name__
        #define __FUNCTION__ __func_name__
    #elifdef __function__
        #define __FUNCTION__ __function__
    #elifdef __function_name__
        #define __FUNCTION__ __function_name__
    #elifdef __PRETTY_FUNCTION__
        #define __FUNCTION__ __PRETTY_FUNCTION__
    #elifdef __FUNCTION_NAME__
        #define __FUNCTION__ __FUNCTION_NAME__
    #endif

#endif // __FUNCTION__
//}------------------------------------------------------------------------------------------------

#define __LOCATION__ {__FILE__, __LINE__, __FUNCTION__}

#endif // LOCATION_H
