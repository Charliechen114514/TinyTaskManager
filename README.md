# TaskManager 🚀📋
![Language](https://img.shields.io/badge/C%2B%2B-20-blue)
![Build](https://img.shields.io/badge/Build-CMake-brightgreen)
![Test](https://img.shields.io/badge/Testing-CTest%20%2B%20Manual-orange)
![Memory](https://img.shields.io/badge/Checked%20with-Valgrind-critical)
![License](https://img.shields.io/badge/License-MIT-blue)
![Status](https://img.shields.io/badge/Project-Active-success)
![Style](https://img.shields.io/badge/Code%20Style-Modern%20C%2B%2B20-informational)

**TaskManager**是一个WIP的超级简单的可用任务管理工具，这个项目是笔者练习C++20的项目🧑‍💻✨

## 🌟 项目亮点

* 真实可用的任务管理功能，支持任务创建、描述、截止时间等核心要素
* 独特的 **UUID** 唯一标识机制，确保每个任务身份唯一，避免冲突
* 内置任务列表管理，支持高效的任务入队和遍历
* 利用 **C++20** 的现代特性，包括智能指针、`std::chrono` 时间处理、类内初始化等，代码风格现代简洁
* 轻量无依赖，易于集成与扩展，适合多种平台和环境
* 以及笔者非常感谢GPT大跌帮助我偷懒这个ReadMe
---

## 🚀 快速开始

```cpp
#include "Core/Task.h"
#include "Core/TaskLists.h"
#include <iostream>

int main() {
	TaskLists tasklists;

	auto task = Task::TaskBuilder()
	                .set_name("Learn Modern C++20")
	                .set_description("My Formal Try in Modern C++")
	                .set_ddl(std::chrono::system_clock::now() + std::chrono::hours(72))
	                .build_finish();

	tasklists.enqueue_managing_task(task);

	for (const auto& t : tasklists.get_all_tasks()) {
		std::cout << "Format Print: \n"
		          << task->toStdString() << "\n";
	}
	return 0;
}
```

---

## 📦 依赖与构建

* 使用 **CMake** 进行项目构建
* 需要支持 C++20 的编译器（推荐 GCC 15+, 因为我只写了这个测试）
* 无额外第三方依赖，纯净且高效

---

## 🛠️ 功能模块（目前）

| 模块        | 功能描述                    | Emoji标识 |
| --------- | ----------------------- | ------- |
| Task      | 任务对象，封装名称、描述和截止时间       | 📝      |
| TaskLists | 任务容器，管理所有任务的集合          | 📋      |
| UUID支持    | 唯一标识生成，保证任务唯一性          | 🔑      |
| 时间处理      | 使用 `std::chrono` 完成时间管理 | ⏰       |

---

## 🎯 未来规划

* 集成更多任务优先级和状态管理
* 增加基于时间的提醒和通知功能
* 支持多线程异步任务处理
* 提供网络同步和多设备协同功能

---
