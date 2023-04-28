/**************************************************************
* @file ForwardDeclaration.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/
#ifndef GSTONE_FORWARDDECLARATION_API_H
#define GSTONE_FORWARDDECLARATION_API_H 1

namespace dds {
namespace domain {
class DomainParticipant;
class DomainParticipantListener;
class RemoteParticipantInfo;
} /*domain*/

namespace core {
class StatusCondition;
} /*core*/

namespace pub {
class DataWriter;
class Publisher;
class DataWriterListener;
class PublisherListener;
} /*pub*/

namespace sub {
class DataReaderListener;
class SubscriberListener;
class Subscriber;
class DataReader;
class DataReaderRTPSListener;
} /*sub*/

namespace topic {
class Topic;
class TopicDescription;
class TopicDataType;
} /*topic*/
} /*dds*/

#endif /*__GSTONE_FORWARDDECLARATION_API_H*/
