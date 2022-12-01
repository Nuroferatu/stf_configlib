//                                    .-""-.
//                                   / _  _ \
//                                   |(_)(_)|
// .------------------------------ooO(_ /\ _)Ooo-----------------------------.
// |                                  |====|                                 |
// |                                  '-..-'                                 |
// | Desc: Types and Enums used in ConfigLib                                 |
// |                                                                         |
// | By: Nuroferatu - https://github.com/Nuroferatu                          |
// |                                                                         |
// | Copyright (C)2022 SoftwareToolsFactory                                  |
// |                   http://softwaretoolsfactory.com                       |
// '-------------------------------------------------------------------------'
#pragma once
#ifndef __STF_SETTINGS_TYPES_H__
#define __STF_SETTINGS_TYPES_H__

#include <cstdint>

namespace stf {

enum class eSettingLevel {
    UNDEFINED,
    APP,        // Application level setting is defined in application and can not be modified by config file or by user when app is running - it's read only setting,to be modified by app it self if needed
    SYS,        // System level can be modyfied only by config file that cames from system directory - it's read only
    USER        // User level can be modified by user and system configuration files - it's RW and might also be saved back to config file
};

enum class eSettingType : std::uint32_t {
    UNDEFINED,      // Undefined aka not initialized
    UNKNOWN,        // Unknown is for user defined types that use SettingsParam without template specialization and userType
    BOOL,
    INT32,
    INT64,
    FLOAT,
    STRING,
    USER = 1000     // Dedicated for user defined types
};

// Helper struct to generate ID for user defined types stored in Settings
// Sample Usage: 
// static constexpr std::uint32_t SETTINGS_USER_ID = stf::eSettingUserID<1>::val;
template<int userTypeId>
struct eSettingUserID {
    static constexpr std::uint32_t val = static_cast<std::uint32_t>(eSettingType::USER)+userTypeId;
};

}; // ns:stf

#endif /* ndef __STF_SETTINGS_TYPES_H__ */
// vim: ts=4:sw=4:et:nowrap
