﻿Multi Link 技术，这个技术帮助使用者利用qmake这款工程管理工具来进行多个增删link-library。全称Multi-link technology，“多链接”技术，专门解决这些个app链接library出现的手工解决太多困难的问题。

现在的Multi Link和LibQQt绑定在一起，还未分离。在这里介绍现在的样子和将会实现的功能。

# 文件组成和功能介绍  

1. qqt_version.pri 用于更改Library的版本信息。只需要更改这一个地方就可以了

2. qqt_qkit.pri 用于支持目标平台信息，读取环境变量QKIT设置SYSNAME。

3. qqt_function.pri 提供丰富的操作函数，分为两类两种，一类获取命令字符串，一类执行命令，一种条件函数，一种求解函数。
    - mkdir system_errcode read_ini write_ini  empty_file write_line copy_dir user_home user_config_path
    - 相应的get函数
    - 支持windows 和 *nix。

4. qqt_header.pri 包含qqt的特性开关，在这里决定library的大小和内部函数数目。
    - QQT_STATIC_LIBRARY 宏的开关判断也在这里。在linux等posix平台，这种区分动态静态的宏意义不是很大，一般不定义就可以。在windows平台要求很强烈，在QQt中，windows平台，编译静态库，无论编译还是链接，QQT_STATIC_LIBRARY都是需要的。动态库，编译时需要QQT_LIBRARY宏，链接时不需要宏。在qqt.pro和link_qqt.pri当中自动做了适配。

5. qqt_source.pri 包含所有对应qqt的特性的源文件和头文件，HEADERS+= SOURCES+=全在这里。

6. qqt_3rdparty.pri 包含所有的第三方源代码。对于GPL，第三方的还是单独拿出来。找问题和开关特性都比较清晰。

7. qqt_install.pri 这里负责发布QQt SDK，所有的函数都在这里，但是发布工作在qqt_library.pri里，编译QQt时不发生任何发布sdk的问题，只有在app当中pre link的时候才会create sdk，link from sdk。

8. qqt_library.pri qqt的sdk发布工作，app链接QQt工作，要求用户进行BUILD-SDK-DEPLOY ROOT路径指定也发生在这里。它会自动生成一个pri，给用户指定这三个变量。

9. link_qqt_library.pri 包含以上这几个app需要的pri，这个文件现在只能放在library目录里。

10. app_configure.pri app配置文件，这个一般是公共配置文件，里面包含了link_qqt_library.pri。更改意义不大，将来可能会被生成，而不是开始就存在。

11. app_deploy.pri app发布文件，app发布到指定位置的工作就在这里实现，这个文件将来也可能被生成而不是开始就存在。

# 将要实现
 - qqt_header.pri qqt_source.pri 两个pri将会自动生成lib_header.pri，lib_source.pri，用户实现这两个pri，填充和自己的library有关的头文件和源文件，模块开关等信息。
 - qqt_library.pri 将会自动生成app_configure.pri用于用户配置
 - app_deploy.pri 将会更名为qqt_deploy.pri，用来完成支援app发布所需的功能。
 - qqt_install.pri 将会负责和sdk发布相关的工作。
 - 这些pri将会全部转移到MLMA技术仓库，用户可以独立将其下载、配置，在一个地方完成多个lib和app工程的部署。
    -  初步规划用户要clone到library目录。

相信在Multi Link技术的帮助下，用户开发Library和Application肯定会如虎添翼，节省巨大的工时和精力。（现在仅仅支持LibQQt使用）
