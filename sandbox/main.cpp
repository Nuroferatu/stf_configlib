//                                    .-""-.
//                                   / _  _ \
//                                   |(_)(_)|
// .------------------------------ooO(_ /\ _)Ooo-----------------------------.
// |                                  |====|                                 |
// |                                  '-..-'                                 |
// | Desc: Sandbox main - to test ConfigLIB                                  |
// |                                                                         |
// | By: Nuroferatu - https://github.com/Nuroferatu                          |
// |                                                                         |
// | Copyright (C)2022 SoftwareToolsFactory                                  |
// |                   http://softwaretoolsfactory.com                       |
// '-------------------------------------------------------------------------'
#include <iostream>
#include "configlib.h"

#include <vector>
#include <list>

// Expectations
struct UserType {
    UserType( int i ) : x(i) {}
    ~UserType() = default;

    int x;
};

struct SettingVarBool : public stf::SettingVarBase {
    SettingVarBool( const std::string& name, const stf::eSettingLevel level, bool defaultVal ) : SettingVarBase(name, level, stf::eSettingType::BOOL), _defaultVal(defaultVal), _val(_defaultVal) {}

    bool    getVal( void ) const { return _val; }

protected:
    bool    _defaultVal;
    bool    _val;
};

struct SettingVarFloat : public stf::SettingVarBase {
    SettingVarFloat( const std::string& name, const stf::eSettingLevel level, float defaultVal ) : SettingVarBase(name, level,stf::eSettingType::FLOAT), _defaultVal(defaultVal), _val(_defaultVal) {}

    float   getVal( void ) const { return _val; }

protected:
    float   _defaultVal;
    float   _val;
};

struct SettingVarUserType : public stf::SettingVarBase {
    SettingVarUserType( const std::string& name, const stf::eSettingLevel level, UserType&& defaultVal ) : SettingVarBase(name, level,stf::eSettingType::USER), _defaultVal(defaultVal), _val(_defaultVal) {}

    UserType    getVal( void ) const { return _val; }

protected:
    UserType    _defaultVal;
    UserType    _val;
};

template<class T>
class SettingParam : public stf::SettingVarBase {
public:
    SettingParam( const std::string& name, const stf::eSettingLevel level, T defaultVal );

    T   getVal( void ) const { return _val; }

protected:
    T   _defaultVal;
    T   _val;
};

template<class T> SettingParam<T>::SettingParam( const std::string& name, const stf::eSettingLevel level, T defaultVal ) : SettingVarBase(name, level, stf::eSettingType::USER), _defaultVal(defaultVal), _val(_defaultVal) {}
template<> SettingParam<bool>::SettingParam( const std::string& name, const stf::eSettingLevel level, bool defaultVal ) : SettingVarBase(name, level, stf::eSettingType::BOOL), _defaultVal(defaultVal), _val(_defaultVal) {}
template<> SettingParam<float>::SettingParam( const std::string& name, const stf::eSettingLevel level, float defaultVal ) : SettingVarBase(name, level, stf::eSettingType::BOOL), _defaultVal(defaultVal), _val(_defaultVal) {}
template<> SettingParam<std::int32_t>::SettingParam( const std::string& name, const stf::eSettingLevel level, std::int32_t defaultVal ) : SettingVarBase(name, level, stf::eSettingType::INT32), _defaultVal(defaultVal), _val(_defaultVal) {}
template<> SettingParam<std::int64_t>::SettingParam( const std::string& name, const stf::eSettingLevel level, std::int64_t defaultVal ) : SettingVarBase(name, level, stf::eSettingType::INT64), _defaultVal(defaultVal), _val(_defaultVal) {}
template<> SettingParam<std::string>::SettingParam( const std::string& name, const stf::eSettingLevel level, std::string defaultVal ) : SettingVarBase(name, level, stf::eSettingType::INT64), _defaultVal(defaultVal), _val(_defaultVal) {}

int main( int argc, char* argv, char* env[] ) {
    static SettingParam<UserType>       sampleUserTypeParam      { "SettingParam<UserType>", stf::eSettingLevel::APP, UserType(1234) };
    static SettingParam<bool>           sampleBoolParam          { "SettingParam<bool>", stf::eSettingLevel::SYS, false };
    static SettingParam<float>          sampleFloatParam         { "SettingParam<float>", stf::eSettingLevel::USER, 1.2345f };
    static SettingParam<std::int32_t>   sampleInt32SmallNumParam { "SettingParam<std::int32_t>", stf::eSettingLevel::USER, 100 };
    static SettingParam<std::int64_t>   sampleInt64SmallNumParam { "SettingParam<std::int64_t>", stf::eSettingLevel::USER, 101 };
    static SettingParam<std::int32_t>   sampleInt32SMaxNumParam  { "SettingParam<std::int32_t>", stf::eSettingLevel::USER, INT32_MAX };
    static SettingParam<std::int64_t>   sampleInt64SMaxlNumParam { "SettingParam<std::int64_t>", stf::eSettingLevel::USER, INT64_MAX };
    static SettingParam<std::string>    sampleStringParam        { "SettingParam<std::string>", stf::eSettingLevel::USER, "SampleValue"};

    //// Planed usage
    //// 1. Direct in place of declatarion
    //bool bVal = sampleBoolParam.getVal();
    //std::cout << std::endl << bVal << std::endl;
    //std::cout << sampleStringParam2.getVal() << std::endl << std::endl;

    //static stf::Settings& ref = stf::Settings::get();

    ////// 2. Indirect using Settings find
    ////// int iVal = stf::Settings::Get().Find( "sampleIntParam" ).GetVal();
    ////// stf::Settings::Get().Find( "sampleStringParam" ).SetVal( "otherValue" );
    ////ref.registerSetting( sampleBoolParam );
    ////ref.registerSetting( sampleInt32Param );
    ////ref.registerSetting( sampleInt64Param );
    ////ref.registerSetting( sampleFloatParam );
    ////ref.registerSetting( sampleStringParam );
    ////ref.registerSetting( sampleStringParam2 );

    //// This works
    //for( auto& item : ref._registry ) {
    //    std::cout << item.ptr.spAll->getName() << " TypeOf: " << item.ptr.spAll->getTypeAsStr() << std::endl;
    //}
    return 0;
}

#ifdef _WIN32

#include <windows.h>

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
    return 0;
}

#endif // def _WIN32

// vim: ts=4:sw=4:et:nowrap
