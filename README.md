# Software Tools Factory - ConfigLIB

### Platforms
 * Windows

### Branches
- master - Read only - Most stable version / Linear history
- devel  - Read only - Root for development / Linear history

### Concept

### Dependencies

### Dir struct

```
|- bin 
|  `- <platform><architecture>_<configuration>
|
|- include
|- sandbox
|- src
`- tmp
   `- <platform><architecture>_<configuration>
      ` - <project_name>
```
***bin*** - lib/exe and pdb files end up here colected per platform<br>
***include*** - library public include files<br>
***sandbox*** - code for test and develop (may contain local headers)<br>
***src*** - libaray source code (may contain local/private headers)<br>
***tmp*** - intermediete files, that are created in process of compilation organized per platform

Personaly I find such structure easy to manage, cross platform and obvius to any one who see it for first time.

### .vcxproj config
To make this repo *submodule ready* prjects are configured with assumption that main project solution file will be located in root folder of project.<br>
- bin/lib/tmp is writen relative to ***$(SolutionDir)***<br>
```
$(SolutionDir)bin\win$(PlatformArchitecture)_$(Configuration)\
```
- additional include files are relative to ***$(ProjectDir)***
```
$(ProjectDir)..\include;
```

This way, after adding project as submodule structure of directories will look like this:
```
|- bin 
|  `- <platform><architecture>_<configuration>
|
|- @stf_configlib
|  `- include
|  |- sandbox
|  `- src
|
`- tmp
   `- <platform><architecture>_<configuration>
      ` - <project_name>
```

### TODO:
