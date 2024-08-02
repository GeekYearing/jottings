# CMake

### 简介

cmake是一款跨平台的代码编译工具集，从可执行程序来看它分为五个不同用途的可执行文件组成：

* cmake.exe：配置、生成和构建项目的主要可执行文件的工具
* cmake_gui.exe：cmake的图形配置界面
* cpack.exe：生成安装程序和源包的打包工具
* ctest.exe：允许和报告测试结果的测试驱动程序
* cmcldeps.exe：未知，在网上没有找到相关定义

与make一致整个编译过程通过CMakeLists.txt文件进行描述，比如说想要编译hello_world程序，就只需要按照以下几个步骤：

```bash
# 文件夹结构
-- demo
 |-- hello_world.c
 |-- CMakeLists.txt
 
# 编译脚本
-- CMakeLists.txt
  CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
  PROJECT(hello_world)
  ADD_EXECUTABLE(hello_world hello_world.c)

# 执行编译
-- cmd/bash
  键入 `cmake -B build` 命令
  此时文件夹中会创建 build 文件夹，里面会存放根据当前环境编译出来的中间文件(!此时不是可执行程序)
  根据对应中间文件编译可执行程序，例如 Linux下是makefile, 只需要在 build/ 目录下, 执行 make all 即可
```

到这里已经有了良好的开端，拥有了第一个跨平台的程序hello_world。

### 语法

通过简介，可以了解到想要使用CMake进行编译工作，就需要提供CMakeLists.txt文件并通过该文件说明整个编译操作流程。如果想编译器了解你的编译需求，那就需要按照编译器理解的语法去交流。

CMake定义的语法规则如下：

* 注释：使用 # 表示该行内容为注释。

```cmake
# this is a comment
```

* 变量：仅有数字和字符串两种变量类型，通过SET命令进行定义，如果需要使用变量则只需要在变量名外增加 ${} 进行包裹。

```cmake
SET(timeNow, "23:00:00")
MESSAGE("time now is ${timeNow}")
```

* 运算：内置了EXPR表达式计算工具，通过内置提供的MATH函数，能够实现变量的运算(加、减、乘、除、取余...)。

```cmake
MATH(EXPR res "${a} + ${b}")
MESSAGE("a + b : ${res}")
# 其他运算符类似, 替换对应的运算操作符即可...

# 注：这里值得一提的是，可以通过命令行给指定变量设置值，例如：下面命令会得到 "a + b : 3" 的结果：
cmake -Da=1 -Db=2 -P CMakeLists.txt
# 通常这种方式可以用来指定当前编译环境是DEBUG版本还是RELEASE版本，例如：下面命令设置当前编译环境为DEBUG:
cmake -DCMAKE_BUILD_TYPE=DEBUG
```

* 流程控制：与大部分语言类似，可以通过if-else、while、foreach等语法对编译流程进行控制。

```cmake
IF (ARCH MATCHS "x86")
  ...
ELSE()
  ...
ENDIF()

SET(i, "0")
WHILE (${i} LESS "5")
  ...
ENDWHILE()

FOREACH (${i} range "5")   # 支持枚举 FOREACH (language C C++ Python Java)
  ...
ENDFOREACH()
```

* 宏与函数：CMake中的宏与C语言的宏定义不太一样，这里的宏跟函数用法一致，只是为闭包内部处理的变量作用域是全局的。

```cmake
# 定义名称为 setTime 的函数
FUNCTION(setTime timeUS)
  MESSAGE("${timeUS}")
  MATH(EXPR timeMS ${timeUS}/1000)
ENDFUNCTION()

# 执行 setTime(1000) 后，获取 timeMS 的值为空
MESSAGE("timeMS = ${timeMS}") ==> "timeMs = " 

# 定义名称为 setTime 的宏
MACRO(setTime timeUS)
  MESSAGE("${timeUS}")
  MATH(EXPR timeMS ${timeUS}/1000)
ENDMACRO()

# 执行 setTime(1000) 后，获取 timeMS 的值为1ms
MESSAGE("timeMS = ${timeMS}") ==> "timeMs = 1" 
```

到此CMake整个语法内容就全部介绍完毕，通过这些语法就能够描述整个项目代码的编译流程，但是对于项目的构建还需要配合命令完成。

### 命令

命令可以理解为CMake内置的函数，通常这些命令构成整个编译主体，比如说需要设置当前项目编译完成后的目标程序名称、当前所支持的语言环境版本等。具体CMake所支持的命令可以通过如下方式获取：

```cmake
cmake --help-command-list
# 当然，也可以通过如下参数查询命令的说明信息，例如查询MESSAGE命令的说明信息
cmake --help-command MESSAGE
```

在构建编译脚本时，会需要用到许多不同的命令参数，以下将介绍构建时常用的命令：

* CMAKE_MINIMUM_REQUIRED：设置CMake最低版本

```cmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
```

* PROJECT：用于指定项目名称

```cmake
PROJECT(hello_world)
```

* ADD_EXECUTABLE：用于指定编译源代码与可执行程序

```cmake
ADD_EXECUTABLE(hello_world hello_world.c)
```

* AUX_SOURCE_DIRECTORY：用于将文件夹下的所有源文件存储在指定变量中

```cmake
AUX_SOURCE_DIRECTORY(. sourceFiles)
```

* ADD_SUBDIRECTORY：用于添加一个需要进行构建的子目录

```cmake
ADD_SUBDIRECTORY(subPath)
```

* ADD_LIBRARY：用于指定从一组源文件中编译出指定名称的静态/动态库文件

```cmake
# 默认情况下，该指令是编译成静态库，也可以显式指定编译成静态库: ADD_LIBRARY(static_library STATIC ${sourceFiles})
ADD_LIBRARY(static_library ${sourceFiles})
# 需要编译动态库，则需要添加 SHARED 参数
ADD_LIBRARY(shared_library SHARED ${sourceFiles})
```

* TARGET_LINK_LIBRARYS：用于指定目标程序需要链接的库文件

```cmake
TARGET_LINK_LIBRARYS(hello_world static_library)
```

* INCLUED_DIRECTORIES：用于添加头文件路径

```cmake
INCLUED_DIRECTORIES(incluedFiles)
```

### 内置变量

CMake提供了一些内置的变量，便于获取设置编译时的环境参数。

* PROJECT_SOURCE_DIR：目前正在处理的最上层目录，即 PROJECT() 命令所对应的文件夹

* CMAKE_BUILD_TYPE：控制构建类型，以下是目前可选值：
  * NONE：编译器默认值
  * DEBUG：调试版本
  * RELEASE：稳定版本
  * RELWITHDEBINFO：最佳化，但仍会启动 DEBUG
  * MINISIZEREL：最小化

* CMAKE_C_FLAGS：C编译器的编译选项
* CMAKE_CXX_FLAGS：C++编译器的编译选项

到此整个CMake基础知识和构建相关内容已经全部结束，后续内容是对实际开发使用过程中的总结。

### 杂项1：项目

从工程学的角度来说，定义良好的项目结构决定着以后项目的质量和未来的走向，不仅能够提高项目的可读性还便于其他开发者能够快速清晰的认识到整个项目的结构层级。

