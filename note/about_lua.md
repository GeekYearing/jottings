# Lua

### 简介

Lua是一种嵌入式脚本，主要为应用程序提供灵活的扩展和定制功能，以下是Lua的特性：

* 轻量级，它用标准C语言编写并以源代码形式开放，编译后仅仅一百余K，可以很方便的嵌入别的程序里。
* 可扩展，Lua提供了非常易于使用的扩展接口和机制：由宿主语言（通常是C或C++）提供这些功能，Lua可以使用它们，就像是本来就内置的功能一样。
* 支持面向过程（procedure-oriented）编程和函数式编程（functional programming）。
* 自动内存管理，只提供了一种通用类型的表，用它可以实现数组，哈希表，集合，对象。

与其他脚本语言类似，Lua也支持命令行和脚本文件两种方式运行，例如实现第一个Lua程序可以使用如下方式：

```bash
# 案例1：命令行交互式
$ lua -i
>> print("hello world")
hello world

# 案例2：在脚本文件中编写代码
$ cat hello_world.lua
# /usr/local/bin/lua
print("hello world")
$ ./hello_world.lua
hello world
```

到此已经能够了解到Lua基本使用方式，接下来将详细描述Lua代码的编写规则。

### 语法

Lua的语法规则十分简洁，没有任何多余的特性来增加用户的学习成本，只需要几分钟时间就能够完全上手，其中Lua定义语法规则如下：

* 单行注释：以两个连字符 -- 开头，后面紧跟注释

```lua
-- 这是单行注释
```

* 多行注释：由 --[[ 和 ]] 闭包组成，作用域中包含注释

```lua
--[[
多行注释1
多行注释2
]]
```

* 标识符：用于定义变量名称，通常由字母、下划线开头加上0个或多个字母、下划线、数字组成，区分大小写，不允许使用特殊字符（如 @，$ 和 %）来定义标识符。

```lua
a = 0
_b = 0
a_123, b_123 = 0, 1
```

* 关键字：保留关键字不能作为常量或变量或其他用户自定义标示符，同时约定以下划线开头连接一串大写字母的名字（比如 _VERSION）被保留用于 Lua 内部全局变量。

```lua
-- 以下是列出来的是保留关键字
and         break      do         else
elseif      end        false      for
function    if         in         local
nil         not        or         repeat
return      then       true       until
while       goto
```

* 全局变量：默认情况下的变量都是全局变量，只需要通过对变量赋值即是创建全局变量，访问一个没有初始化的全局变量也不会有问题，它会返回 nil 值去标识，如果希望变量是局部变量可以使用 local 关键字描述。

```lua
global_a = 10
global_a = nil       -- 销毁全局变量 global_a
local local_a = 10   -- 临时变量 local_a
```

* 流程控制：通过一个或多个条件判断语句来设定，条件表达式结果为 false 或 nil 时为假，true 或 非nil 时为真。

```lua
-- 注意，该条件判断为真，因为 0 是 非nil 值
if (0) then
    ...
elseif (nil)
    ...
else
    ...
end
```

* 循环：默认支持3种类型的循环，while循环、for循环和repeat...until循环，其中repeat...until循环本质上等同于C语言的do...while循环。

```lua
-- while循环
while (condition) do 
    ...
end

-- for循环
for i=1, 1, -1 do
    ...
end

days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}
for i,v in ipairs(days) do
    ...
end

-- repeat...until循环
repeat
    ...
until (condition)
```

* goto...label：与C语言一致，可以通过goto语句跳转到任意标记的语句继续往下执行，与C语言有所不同的是标签名称需要被一组 :: 包括。

```lua
local a = 1
::label:: print("--- goto label ---")

if (0) then
    goto label
end
```

* 函数：函数是对语句和表达式进行抽象的主要方法。既可以用来处理一些特殊的工作，也可以用来计算一些值。

```lua
-- lua函数的基本形式
optional_function_scope function function_name( argument1, argument2, argument3..., argumentn)
    function_body
    return result_params_comma_separated
end

-- optional_function_scope：默认不设置为全局函数，如果你需要设置函数为局部函数需要使用关键字 local。
-- function_name：指定函数名称。
-- argument1, argument2, argument3..., argumentn：函数参数，多个参数以逗号隔开，函数也可以不带参数。
-- function_body：函数体，函数中需要执行的代码语句块。
-- result_params_comma_separated：函数返回值，Lua语言函数可以返回多个值，每个值以逗号隔开。

-- 变参函数
function average(...)
    local arg = {...}
    for i,v in ipairs(arg) do
      result = result + v
   end
   return result / select("#", ...)   -- select("#", ...)表示获取变参数目，通过select(n, ...)可以获取指定位置开始的数组
end
```

### 数据类型

Lua一共支持8种不同的数据类型，分别是 nil、boolean、number、string、table、function、thread 和 userdata。

| 数据类型 | 说明                                                         |
| -------- | ------------------------------------------------------------ |
| nil      | 空值，表示未定义的变量值和无效值。                           |
| boolean  | 布偶值，仅有 true 和 false 两种值。                          |
| number   | 双精度实浮点值。                                             |
| string   | 由一组单引号或双引号包含的值。                               |
| table    | 一组包含一个或多个键值对的值，键可以是数字、字符串和表类型，通常可以用于表示数组、字典等。 |
| function | 包含函数指针的值，可以是C或者Lua。                           |
| thread   | 表示执行的独立线路，用于执行协同程序。                       |
| userdata | 任意存储在C数据结构的值。                                    |

##### nil（空）

nil用于表示一种没有任何有效值，例如输出一个未定义的变量，它会返回 nil 值表示空：

```lua
print(type(xx))
>> nil
```

由于Lua中定义的变量通常都是全局变量（使用全局变量的好处是查找速度相对比较快），所以如果希望将某个属性标识为不再使用时，可以将变量设置为 nil。

```lua
xx = nil    -- 该变量将不再被使用
```

值得注意的是，判断一个变量类型是否是 nil 时，需要添加双引号，否则无法完成比对。

```lua
print(type(xx) == nil)
>> false
print(type(xx) == "nil")
>> true
```

##### boolean（布偶）

boolean仅包含 true 和 false 两个值，在Lua中 true 和 非nil 值都被视作 true，false 和 nil 被视作 false。

```lua
print(true)
>> boolean
print(false)
>> boolean

-- 这里需要注意的是，0也为true
if (0) then
    print("0 is true")
else
    print("0 is false")
end
>> 0 is true
```

##### number（数值）

number默认只有双精度实浮点值（即是double类型），如果需要修改默认类型可以查看 luaconf.h 中的定义，以下案例都是number类型：

```lua
print(type(2))
print(type(2.2))
print(type(0.2))
print(type(2e+1))
print(type(0.2e-1))
print(type(7.8263692594256e-06))
```

##### string（字符串）

string表示由数字、字母、下划线组成的一串字符，例如可以用以下三种方式创建字符串：

```lua
local xx = 'this is a string'     -- 使用一组单引号
local xx = "this is a string"     -- 使用一组双引号
local xx = [[                     -- 使用双括号
	many 
    string
    words
]]
```

如果希望获取指定字符串的长度可以采用 # 、string.len 或 utf8.len 三种方式，通常来说 # 和 string.len 用于仅用于包含 ASCII字符串 的长度，如果字符串中包含中文可以使用 utf8.len 去计算：

```lua
local xx = #"hello 世界"
>> 12
local xx = string.len("hello 世界")
>> 12
local xx = utf8.len("hello 世界")
>> 8
```

与C语言一致，通常也需要使用转义字符用于表示不能直接显示的字符，例如回车键、后退键等，以下列举的是所有转义字符及其含义：

| 转义字符 | 意义                                  | ASCII码（十进制） |
| -------- | ------------------------------------- | ----------------- |
| \a       | 响铃（BEL）                           | 007               |
| \b       | 退格（BS），将当前位置移到前一列      | 008               |
| \f       | 换页（FF），将当前位置移到下页开头    | 012               |
| \n       | 换行（LF） ，将当前位置移到下一行开头 | 010               |
| \r       | 回车（CR） ，将当前位置移到本行开头   | 013               |
| \t       | 水平制表（HT），跳到下一个TAB位置     | 009               |
| \v       | 垂直制表（VT）                        | 011               |
| \\\      | 代表一个反斜线字符 \\                 | 092               |
| \\\'     | 代表一个单引号（撇号）字符            | 039               |
| \\\"     | 代表一个双引号字符                    | 034               |
| \0       | 空字符（NULL）                        | 000               |
| \ddd     | 1到3位八进制数所代表的任意字符        | 三位八进制        |
| \xhh     | 1到2位十六进制所代表的任意字符        | 二位十六进制      |

Lua为字符串类型提供了默认的方法，例如字符串替换、字符串匹配、字符串格式化等。

* 字符串截取：sub

```lua
--[[ 
  string.sub(s, i, [, j])
  s：要截取的字符串
  i：截取开始位置
  j：截取结束位置，默认为-1, 最后一个字符
]]
print(string.sub("prefix--runoobgoogletaobao--suffix", 4, 15))
>> fix--runoobg
print(string.sub("prefix--runoobgoogletaobao--suffix", -10))
>> ao--suffix
print(string.sub("prefix--runoobgoogletaobao--suffix", -100))
>> prefix--runoobgoogletaobao--suffix
```

* 字符串大小写转换：upper、lower

```lua
print(string.upper("Lua"))
>> LUA
print(string.lower("Lua"))
>> lua
```

* 字符串反转：reverse

```lua
print(string.reverse("Lua Tutorial"))
>> lairotuT auL
```

* 字符串格式化：format

```lua
--[[
  string.format(fmt, ...)
  其中支持的转义符如下：
  %c - 接受一个数字, 并将其转化为ASCII码表中对应的字符
  %d, %i - 接受一个数字并将其转化为有符号的整数格式
  %o - 接受一个数字并将其转化为八进制数格式
  %u - 接受一个数字并将其转化为无符号整数格式
  %x - 接受一个数字并将其转化为十六进制数格式, 使用小写字母
  %X - 接受一个数字并将其转化为十六进制数格式, 使用大写字母
  %e - 接受一个数字并将其转化为科学记数法格式, 使用小写字母e
  %E - 接受一个数字并将其转化为科学记数法格式, 使用大写字母E
  %f - 接受一个数字并将其转化为浮点数格式
  %g（%G） - 接受一个数字并将其转化为%e(%E, 对应%G)及%f中较短的一种格式
  %q - 接受一个字符串并将其转化为可安全被Lua编译器读入的格式
  %s - 接受一个字符串并按照给定的参数格式化该字符串
]]
print(string.format("%02d/%02d/%04d", 18, 8, 2024)))
>> 18/08/2024
```

* 字符串与整数间转化：byte

```lua
--[[
  string.byte(s, i)
  s：需要翻译的字符/字符串
  i：指定字符下标
]]
print(string.byte("Lua"))
>> 76
print(string.byte("Lua", 3))
>> 97
```

* 字符串匹配查找：find、match、gmatch、gsub

```lua
print(string.find("Deadline is 18/08/2024, firm", "%d%d/%d%d/%d%d%d%d"))
>> 13  22
print(string.sub("Deadline is 18/08/2024, firm", string.find("Deadline is 18/08/2024, firm", "%d%d/%d%d/%d%d%d%d")))
>> 18/08/2024
--[[
  支持的所有字符类, 大体上与C语言的sscanf类似：
  .(点) - 与任何字符配对
  %a - 与任何字母配对
  %c - 与任何控制符配对(例如\n)
  %d - 与任何数字配对
  %l - 与任何小写字母配对
  %p - 与任何标点(punctuation)配对
  %s - 与空白字符配对
  %u - 与任何大写字母配对
  %w - 与任何字母/数字配对
  %x - 与任何十六进制数配对
  %z - 与任何代表0的字符配对
  %x(此处x是非字母非数字字符) - 与字符x配对, 主要用来处理表达式中有功能的字符(^$()%.[]*+-?)的配对问题, 例如%%与%配对
  [数个字符类] - 与任何[]中包含的字符类配对, 例如[%w_]与任何字母/数字, 或下划线符号(_)配对
  [^数个字符类] - 与任何不包含在[]中的字符类配对. 例如[^%s]与任何非空白字符配对
]]
print(string.gsub("hello, up-down!", "%A", "."))
>> hello..up.down.    4
```

* 其他字符串常用函数，字符串拼接、字符串复制等

```lua
print("www.".."baidu"..".com")
>> www.baidu.com
print(string.rep("123", 2))
>> 123123
```

##### table（表）

table表示由一组或多组任意非nil值作为索引的关联性数组，用于实现数组、字典等数据结构类型。

```lua
local empty_table = {}                                 -- 创建空表
local array_table = {"1", "2", "3"}                    -- 使用table实现数组
local dict_table = {["123"] = "4444", ["aaa"] = 333}   -- 使用table实现字典

print(type(empty_table))
>> table
print(type(array_table))
>> table
print(type(dict_table))
>> table

print(#dict_table)      -- 可以通过 # 获取table当前的长度
>> 2
```

##### function（函数）

function表示由C或Lua编写的函数指针，支持将lambda表达式赋值给变量。

```lua
function my_function(args)
	print(args)
end

print(my_function("123"))
>> 123
local function_ptr = my_function
print(function_ptr("123"))
>> 123

-- 将lambda表达式赋值给变量
local function_ptr = function ()
  return "123"
end
print(function_ptr())
>> 123
```

##### thread（线程）

thread用于表示执行的独立线路，在Lua中最主要的线程是协程，协程在任意时刻都只能运行一个，并且处于运行状态的协程只有被挂起才能够暂停。

> 在C中实现协程，主要是通过 setjmp 和 longjmp 实现，这两个函数支持跨函数式跳到任意位置执行，并且恢复 setjmp 时的堆栈状态。

##### userdata（自定义类型）

userdata是一种用户自定义数据，通常用于表示C/C++中的结构体和指针存储到Lua中调用。

### 模块和包

在Lua中，模块本质上就是创建一个由变量、函数等已知元素组成的table变量，通过导出该变量就能够实现常量、函数导出的导出功能，创建一个module.lua的案例如下：

```lua
-- module.lua
module = {}

-- 导出变量
module.version = [1, 0, 0]

-- 导出函数
module.my_function = function()
  print("my function")
end

-- 该函数不进行导出
local function _internel_function()
  print("internel function")
end

-- 导出函数来调用局部函数
module.my_function1 = function()
  _internel_function()
end

-- 最后导出该表
return module
```

通过以上案例可知，本质上封装一个模块就等同于定义table变量，导入该模块的地方只需要通过table变量的操作方式就能获取模块中的变量或函数。导入模块的方式如下：

```lua
-- 导入模块使用 require 关键字
require("module")
print(module.my_function())
>> my function
print(module.my_function1())
>> internel function

-- 也可以通过变量来存储该表
local my_module = require("module")
print(table.concat(my_module.version, "."))
>> 1.0.0
```

默认情况下，Lua会根据环境变量LUA_PATH去查找该模块，如果没有定义，则通过编译时定义的默认路径来初始化。

在Lua中，通常调用C都是使用包的方式实现的，本质上就是使用动态链接的方式（dlopen）将C函数链接到Lua中，然后通过函数指针的方式（dlsym）使用C函数，具体使用的方式如下：

```lua
local path = "/usr/local/lua/lib/libluasocket.so"
local c_pack = loadlib(path, "luaopen_socket")
```
