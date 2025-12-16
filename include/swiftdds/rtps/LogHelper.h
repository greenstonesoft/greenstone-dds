/**************************************************************
 * @file LogHelper.h
 * @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2026
 * All rights reserved
 **************************************************************/
#ifndef GSTONE_RTPS_LOGHELPER_H
#define GSTONE_RTPS_LOGHELPER_H
#include "swiftdds/dcps/PITypes.h"
#include "swiftdds/dcps/DeclExport.h"

namespace gstone {
namespace common {
/**
* @class EasyLogger
* @brief This class is use for log. The log will be output to gsdds.log in the same directory as the executable file by default.
*/
class GS_DDS4CPP_API EasyLogger final
{
public:
	/**
	* @brief Destructor of the class EasyLogger.
	*/
	~EasyLogger() noexcept;

	/**
	* @brief This function returns the EasyLogger singleton.
	* @return Return the singleton EasyLogger instance.
	*/
	static EasyLogger* get_instance() noexcept;
	
	/**
    * @brief set log level.
    * @param [in] level If the log level exceeds the set level, it will be output.
    * @return return -1 if The set level exceeds 6(OFF), else return 0;
	* @details The default level is OFF.
    * INFO = 2
    * WARN = 3
    * ERROR = 4
    * FATAL = 5
    * OFF = 6	
    */
	gint32_t dynamic_set_log_level(guint16_t const level);

	/**
    * @brief set log screen print status.
    * @param [in] status If the status is true, the log will print to screen.
    * @return 
	* @details The default status is false.
    */
	gvoid_t set_log_screen_print_status(gbool_t const status) noexcept;

	/**
    * @brief set log file param.
    * @param [in] log_file_name Create the log file name.
    * @param [in] max_log_size The maximum size of a single log file.
    * @param [in] max_log_count Number of archived logs.
    * @return return true if set file module sucess, else return false.
	* @details The default file param value are "./gsdds.log", 1000 * 1024 * 1024 Byte, 10 respectively.
    */
	gbool_t set_log_file_module(gchar_t const* const log_file_name, gint32_t const max_log_size, gint32_t const max_log_count) noexcept;

private:
	/**
	* @brief Constructor of the class EasyLogger.
	*/
	EasyLogger() noexcept;

	/**
	* @brief Don't use constructor of the class EasyLogger by another EasyLogger object.
	* @param [in] . Const reference of a EasyLogger object.
	*/
	EasyLogger(EasyLogger const &) = delete;

	EasyLogger(EasyLogger &&) = delete;

	/**
	* @brief Don't use assign a EasyLogger object to the locally EasyLogger object.
	* @param [in] . Const reference of a EasyLogger object.
	* @return Reference of the locally EasyLogger object.
	*/
	EasyLogger& operator=(EasyLogger const &) = delete;

	EasyLogger& operator=(EasyLogger &&) = delete;
};

}/*common*/
}/*gstone*/

#endif

