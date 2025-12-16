/**************************************************************
* @file TypeSupport.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_TYPESUPPORT_API_H
#define GSTONE_TYPESUPPORT_API_H 1

#include "swiftdds/dcps/DdsBaseTypes.h"
#include "swiftdds/dcps/domain/DomainParticipant.h"
#include "swiftdds/dcps/DeclExport.h"

__GS_DDS4CPP_BEGIN_DECLS

namespace dds {
namespace core {
/**
* @class TypeSupport
* @brief The TypeSupport interface is an abstract interface that has to be specialized for each concrete type that will be used by the application.
* @note A TypeSupport must be registered using the register_type operation on this type-specific class before it can be used to create Topic objects.
*/
class GS_DDS4CPP_API TypeSupport
{
public:
    /**
     * @brief Construct a new TypeSupport object with default parameter.
     */
    TypeSupport() = default;

    /**
     * @brief Destroy the TypeSupport object.
     */
    virtual ~TypeSupport() = default;

    /**
     * @brief Construct a new TypeSupport object with copying TypeSupport object.
     * @param [in] a_type_support A new TypeSupport object is created by copying this TypeSupport object.
     */
    TypeSupport(TypeSupport const & a_type_support) = default;

    /**
     * @brief Construct a new Base Status object with moving TypeSupport object.
     * @param [in] a_type_support A new TypeSupport object is created by moving this TypeSupport object.
     */
    TypeSupport(TypeSupport && a_type_support) = default;

    /**
     * @brief Copy a TypeSupport object with a TypeSupport object.
     * @param [in] a_type_support The TypeSupport object that need to copy.
     * @return TypeSupport object that after copying.
     */
    TypeSupport &operator=(TypeSupport const & a_type_support) = default;

    /**
     * @brief Move a TypeSupport object with a TypeSupport object.
     * @param [in] a_type_support The TypeSupport object that need to move.
     * @return TypeSupport object that after moving.
     */
    TypeSupport &operator=(TypeSupport && a_type_support) = default;

    /**
     * @brief This operation allows an application to communicate to the Service the existence of a data type.
     * @param [in] a_participant  The pointer of participant object whose type needs to register.
     * @param [in] a_type_name    The name of type that needs to register.
     * @return DDS state code. 
     * @retval RETCODE_OK This operation registers type successfully.
     * @note This operation must be provided by each of the derived TypeSupport classes.
     */
    virtual DDS::ReturnCode_t register_type(dds::domain::DomainParticipant* a_participant,
                                            std::string &a_type_name) = 0;

    /**
     * @brief This operation returns the default name for the data-type represented by the TypeSupport.
     * @return The default name for the data-type represented by the TypeSupport. 
     * @note This operation must be provided by each of the derived TypeSupport classes.
     */
    virtual std::string const &get_type_name() const noexcept = 0;
};
} /*core*/
} /*dds*/

__GS_DDS4CPP_END_DECLS

#endif /*__GSTONE_TYPESUPPORT_API_H*/
