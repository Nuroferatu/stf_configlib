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

class SettingVarBase {
public:
    SettingVarBase( const std::string& name, const stf::eSettingLevel level ) : _name(name), _level(level) {}

protected:
    const std::string           _name;
    const stf::eSettingLevel    _level;
};

// Expectations
struct UserType {
    int x;
};

struct SettingVarBool : public SettingVarBase {
    SettingVarBool( const std::string& name, const stf::eSettingLevel level, bool defaultVal ) : SettingVarBase(name, _level), _defaultVal(defaultVal), _val(_defaultVal) {}
    const stf::eSettingType     _type = stf::eSettingType::BOOL;
    bool    _defaultVal;
    bool    _val;
};

struct SettingVarFloat : public SettingVarBase {
    SettingVarFloat( const std::string& name, const stf::eSettingLevel level, float defaultVal ) : SettingVarBase(name, _level), _defaultVal(defaultVal), _val(_defaultVal) {}
    const stf::eSettingType   _type = stf::eSettingType::FLOAT;
    float   _defaultVal;
    float   _val;
};

struct SettingVarUserType : public SettingVarBase {
    SettingVarUserType( const std::string& name, const stf::eSettingLevel level, UserType&& defaultVal ) : SettingVarBase(name, _level), _defaultVal(defaultVal), _val(_defaultVal) {}
    const stf::eSettingType   _type = stf::eSettingType::USER;
    UserType    _defaultVal;
    UserType    _val;
};


//SettingVarBool  sampleBoolParam{}
//// This is goood, i like it, but what is under the hood...
//static stf::SettingParam<bool>          sampleBoolParam    { "sampleBoolParam", stf::eSettingLevel::APP, false };
//static stf::SettingParam<std::int32_t>  sampleInt32Param   { "sampleIntParam32", stf::eSettingLevel::SYS, 100 };
//static stf::SettingParam<std::int64_t>  sampleInt64Param   { "sampleIntParam64", stf::eSettingLevel::SYS, 100 };
//static stf::SettingParam<float>         sampleFloatParam   { "sampleFloatParam", stf::eSettingLevel::USER, 1.1234f };
//static stf::SettingParam<std::string>   sampleStringParam  { "sampleStringParam", stf::eSettingLevel::USER, "sampleDefaultValue" };
//static stf::SettingParam<std::string>   sampleStringParam2 { "sampleStringParam2", stf::eSettingLevel::USER, std::string("sampleDefaultValue") };

// And would love to have something like this to be possible as well
//struct SomeUserDefinedType {
//    int somedata;
//};
//static stf::SettingParam<SomeUserDefinedType>   sampleSomeUserDefinedType { "sampleSomeUserDefinedType", stf::eSettingLevel::USER, std::string("sampleSomeUserDefinedType") };

int main( int argc, char* argv, char* env[] ) {
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
