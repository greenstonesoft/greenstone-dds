/**************************************************************
* @file TopicBuiltinTopicData.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
* All rights reserved
**************************************************************/
#ifndef GSTONE_TOPICBUILTINTOPICDATA_H
#define GSTONE_TOPICBUILTINTOPICDATA_H 1

#include "swiftdds/rtps/basetypes/BuiltinTopicKey.h"
#include "swiftdds/dcps/qos/QosPolicy.h"

namespace dds
{
namespace topic 
{
	/**
	 * @class TopicBuiltinTopicData
	 * @brief Information on a Topic that has been discovered on the network.
	 * @details	Data associated with the built-in topic. It contains QoS policies and additional information that apply to the remote Topic.
	 */
	class GS_DDS4CPP_API TopicBuiltinTopicData final
	{
	public:
		/**
		 * @brief get the topic name
		 * @return std::string 
		*/
		inline std::string name() const
		{
			return m_name;
		}

		/**
		 * @brief set the topic name
		 * @param [in] t_name,new topic name 
		*/
		inline gvoid_t name(std::string const &t_name)
		{
			m_name = t_name;
		}

		/**
		 * @brief get the type name
		 * @return std::string 
		*/
		inline std::string type_name() const
		{
			return m_typeName;
		}


		/**
		 * @brief set the type name
		 * @param [in] t_type_name 
		 * @return gvoid_t 
		*/
		inline gvoid_t type_name(std::string const &t_type_name)
		{
			m_typeName = t_type_name;
		}

		gstone::rtps::BuiltinTopicKey_t m_key;
		std::string m_name;
		std::string m_typeName;

		dds::qos::TopicDataQosPolicy m_topicData;
		dds::qos::LivelinessQosPolicy m_liveliness;
	};
}/*topic*/
}/*dds*/

#endif /*__GSTONE_TOPICBUILTINTOPICDATA_H*/
