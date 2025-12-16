/**************************************************************
 * @file DeclExport.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_DECLEXPORT_H__
#define GSTONE_DECLEXPORT_H__

#ifdef __cplusplus
#define __GS_DDS4CPP_BEGIN_DECLS
#define __GS_DDS4CPP_END_DECLS
#else
#define __GS_DDS4CPP_BEGIN_DECLS
#define __GS_DDS4CPP_END_DECLS
#endif


#if defined(WIN32) || defined(__CYGWIN__)
    #undef GS_DDS4CPP_API
    #ifdef GS_DDS4CPP_EXPORTS
    #define GS_DDS4CPP_API __declspec(dllexport)
    #else
    #define GS_DDS4CPP_API __declspec(dllimport)
    #endif
#elif defined(__linux__) || defined(__QNX__)
    #undef GS_DDS4CPP_API
    #ifdef GS_DDS4CPP_EXPORTS
        //#if __GNUC__ >= 4
            #define GS_DDS4CPP_API __attribute__ ((visibility ("default")))
        //#else
        //    #define GS_DDS4CPP_API
        //#endif
    #else
        #define GS_DDS4CPP_API
    #endif
#else
    #define GS_DDS4CPP_API
#endif

#endif
