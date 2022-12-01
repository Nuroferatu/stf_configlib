//                                    .-""-.
//                                   / _  _ \
//                                   |(_)(_)|
// .------------------------------ooO(_ /\ _)Ooo-----------------------------.
// |                                  |====|                                 |
// |                                  '-..-'                                 |
// | Desc: ConfigLib - main include                                          |
// |                                                                         |
// | By: Nuroferatu - https://github.com/Nuroferatu                          |
// |                                                                         |
// | Copyright (C)2022 SoftwareToolsFactory                                  |
// |                   http://softwaretoolsfactory.com                       |
// '-------------------------------------------------------------------------'
#pragma once
#ifndef __STF_CONFIGLIB_H__
#define __STF_CONFIGLIB_H__

#include <string>
#include <vector>
#include <iostream>

namespace stf {

// Concept - Want something that will work a bit like console variables in games
enum class eSettingLevel {
    UNDEFINED,
    APP,        // Application level setting is defined in application and can not be modified by config file or by user when app is running - it's read only setting,to be modified by app it self if needed
    SYS,        // System level can be modyfied only by config file that cames from system directory - it's read only
    USER        // User level can be modified by user and system configuration files - it's RW and might also be saved back to config file
};

enum class eSettingType : std::uint32_t {
    UNDEFINED,
    BOOL,
    INT32,
    INT64,
    FLOAT,
    STRING,
    USER = 1000,    // Dedicated for user defined types
    UNKNOWN
};

// Helper struct
template<int userTypeId>
struct eSettingUserID {
    static constexpr std::uint32_t val = static_cast<std::uint32_t>(eSettingType::USER)+userTypeId;
};

const std::string& settingTypeToStr( const eSettingType& type, std::uint32_t userType );
const std::string& settingLevelToStr( const eSettingLevel& level );

class SettingVarBase {
public:
    SettingVarBase( const std::string& name, const stf::eSettingLevel level, const stf::eSettingType type );
    SettingVarBase( const std::string& name, const stf::eSettingLevel level, const std::int32_t type );

    const std::string&          getName( void ) const { return _name; }
    const stf::eSettingLevel    getSettingsLevel( void ) const { return _level; }
    const stf::eSettingType     getType( void ) const { return _type; }
          std::uint32_t         getUserType( void ) const { return _userType; }

    const std::string&  getSettingsLevelAsStr( void ) const { return settingLevelToStr(_level); }
    const std::string&  getTypeAsStr( void ) const { return settingTypeToStr( _type, _userType ); }

protected:
    const std::string           _name;
    const stf::eSettingLevel    _level;
    const stf::eSettingType     _type;
    std::uint32_t               _userType;

private:
    static constexpr   std::uint32_t   UNDEFINED_USER_TYPE = UINT32_MAX;
};

template<class T>
class SettingParam : public stf::SettingVarBase {
public:
    SettingParam( const std::string& name, const stf::eSettingLevel level, T defaultVal );

    T       getVal( void ) const { return _val; }
    void    setVal( const T& val ) { _val = val; }
    void    resetToDefault( void ) { _val = _defaultVal; }

protected:
    T   _defaultVal;
    T   _val;
};

// Singleton that is container for SettingParam's
class Settings {
public:
    static Settings&    get( void );

    void registerSetting( stf::SettingVarBase* param );
    std::vector<SettingVarBase*>    getRegistry( void ) const { return _registry; }

protected:
    std::vector<SettingVarBase*>  _registry;
};

}; // ns:stf

#endif /* ndef __STF_CONFIGLIB_H__ */
// vim: ts=4:sw=4:et:nowrap
