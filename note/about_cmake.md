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
  cmake_minimum_required(VERSION 2.6)
  project(hello_world)
  add_executable(hello_world hello_world.c)

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

* 