# TaskManager 🚀📋📝
![Language](https://img.shields.io/badge/C%2B%2B-20-blue)
![Build](https://img.shields.io/badge/Build-CMake-brightgreen)
![Test](https://img.shields.io/badge/Testing-CTest%20%2B%20Manual-orange)
![Memory](https://img.shields.io/badge/Checked%20with-Valgrind-critical)
![License](https://img.shields.io/badge/License-MIT-blue)
![Status](https://img.shields.io/badge/Project-Active-success)
![Style](https://img.shields.io/badge/Code%20Style-Modern%20C%2B%2B20-informational)

**TaskManager**是一个WIP的超级简单的可用任务管理工具，这个项目是笔者练习C++20的项目🧑‍💻✨

## 🚀功能说明

- 交互式命令行界面，支持连续参数输入
- 任务的添加、删除、列出、过滤等操作
- 使用 [nlohmann/json](https://github.com/nlohmann/json) 实现任务的 JSON 格式持久化存储
- 支持从本地的json文件加载和存储任务列表
- 健壮的输入处理，支持用户输入回退
- 使用 `std::getline` 和 `std::stoi` 实现安全的输入解析

## 🌟 项目亮点

* 真实可用的任务管理功能，支持任务创建、描述、截止时间等核心要素
* 支持表格化的控制打印
* 独特的 **UUID** 唯一标识机制，确保每个任务身份唯一，避免冲突
* 内置任务列表管理，支持高效的任务入队和遍历
* 利用 **C++20** 的现代特性，包括智能指针、`std::chrono` 时间处理, ranges with view等
* 轻量无依赖，易于集成与扩展，适合多种平台和环境
* 以及笔者非常感谢GPT大跌帮助我偷懒这个ReadMe

---

## 📦 依赖与构建

* 使用 **CMake** 进行项目构建
* 需要支持 C++20 的编译器（推荐 GCC 15+, 因为我只写了这个测试）
* 无额外第三方依赖，纯净且高效

对于应用程序的构建本身，十分的简单:
下面的shell命令将会生成应用程序测试本体和测试程序
```shell
	mkdir build && cd build
	cmake ..
	cmake --build . --target=all
```
运行在本机上的构建是否可靠，您可以运行ctest
```shell
	mkdir build && cd build
	cmake ..
	cmake --build . --target=all
	cd test
	ctest
```

项目支持Doxygen自动化生成开发文档，您可以非常轻松的按照下面的步骤生成Doxygen自动化的文档以供二次开发参考

```shell
	mkdir build && cd build
	cmake ..
	cmake --build . --target=doc
```

---

## 🚀 快速开始

​	构建结束后，您可以直接运行得到的TaskManager。

```
cd build
./TaskManager
```

```
+-----------------+---------------------------------------+
| Support Command | Descriptions                          |
+-----------------+---------------------------------------+
| help            | Show the help here                    |
| list            | List all the commands                 |
| add             | install new tasks                     |
| delete          | delete the target task                |
| exit            | exit the program                      |
| load            | load from the remote file             |
| store           | store the current list to the remote  |
| filter          | filter with target search expressions |
+-----------------+---------------------------------------+
```

## 💻 支持的命令

| 命令   | 描述                                                         |
| ------ | ------------------------------------------------------------ |
| help   | 显示帮助菜单（支持help + 子命令查看进一步说明）              |
| list   | 列出所有任务                                                 |
| add    | 添加新任务                                                   |
| delete | 删除指定任务（目前支持的是名称删除，后续维护比较随缘）       |
| exit   | 退出程序（支持退出前询问是否持久化）                         |
| load   | 从本地json文件中加载任务列表（支持动态参数直接给定加载路径（相对路径绝对路径均可）） |
| store  | 将当前任务列表存储到本地json（支持动态参数直接给定加载路径（相对路径绝对路径均可）） |
| filter | 使用目标搜索表达式过滤任务（支持动态参数直接进行查询，缺少参数可从控制台动态补充） |

---
