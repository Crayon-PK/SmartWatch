# SmartWatch - 基于 ESP32 的分层架构智能手表
项目总结：[CSDN博客](https://blog.csdn.net/2301_80190305/article/details/161125500?spm=1001.2014.3001.5501)  
项目演示：[B站视频链接](https://www.bilibili.com/video/BV1zfDvB4Egr/?vd_source=31a857204b1be48fb3dedea9e91da57f)  
这是一个基于 ESP32-WROOM 的智能手表项目，采用 **分层架构** 设计。项目实现了应用管理、GUI 交互、硬件抽象等功能，具有高度的可扩展性和解耦性。

## 📺 功能特性

本项目采用模块化设计，主菜单包含以下独立应用与功能集合：

* 🕒 **主表盘 (WatchFace)**:
    * 极简风格设计，实时刷新时间与日期。
    * 顶部实时显示 **WiFi / 蓝牙连接状态**。
    * 底部显示 **实时天气** 与 **今日步数** (基于 MPU6050 计步)。
* ☁️ **天气 (Weather)**: 
    * 联网获取并显示当前城市 **三日内** 的气温与天气状况。
* ⏰ **闹钟 (Alarm)**: 
    * 支持独立的闹钟设置与响铃提醒。
* 📅 **日历 (Calendar)**: 
    * **假期倒计时**: 自动计算并显示距离下一个法定节假日的剩余天数。
    * **每日占卜**: 趣味交互彩蛋，长按上键蓄力解锁“今日运势”。
* ⚙️ **设置 (Settings)**: 
    * 管理 WiFi 与 蓝牙连接、调整系统参数与个性化选项。
* 🎮 **游戏 (Games)**: 
    * 这是一个**游戏容器**，支持扩展更多游戏。
    * 目前内置：**恐龙快跑 (Dino Run)**。
* 🛠 **工具 (Tools)**: 
    * 这是一个**实用工具集合**。
    * 目前内置：**手电筒**、**陀螺仪校准**。
* ℹ️ **关于本机 (About)**:
    * **硬件检测**: 动态读取 CPU 主频、Flash 容量及 **实时剩余堆内存 (Free Heap)**。
    * **设备指纹**: 显示芯片唯一的 WiFi MAC 与 BLE MAC 地址。

## 🛠 软件架构

本项目采用了类似 MVC 的分层设计模式，各模块职责如下：

* **`/src/hal`**: 
    * **硬件抽象层**。负责直接与 ESP32 寄存器或外设库（如 MPU6050, SSD1306）交互。
    * 向上传递标准化数据，屏蔽底层硬件差异。
* **`/src/service`**:
    * **服务层**。后台处理 WiFi连接和蓝牙连接、时间同步 (NTP)、数据持久化 (Preferences)。
* **`/src/model`**:
    * **数据模型层**。定义系统数据结构，管理运行时状态。
* **`/src/view`**:
    * **视图层**。负责 UI 绘制 (U8g2)，不包含任何业务逻辑，只负责“显示”。
* **`/src/controller`**:
    * **控制层**。连接 Model 和 View 的桥梁，处理用户输入并更新 UI。
* **`/src/apps`**:
    * **应用层**。具体的应用程序入口，每个 App 继承自基类，实现**即插即用**。

### 系统架构图

```mermaid
graph TD
    %% --- 硬件交互 ---
    User([用户输入 / 传感器]) --> HAL[HAL 硬件抽象层]
    HAL ==> Controller
    
    %% --- 核心系统 ---
    subgraph Core [核心系统]
        direction TB
        Controller[Controller 控制层]
        Model[Model 数据模型]
        Service[(Service 后台服务)]
        
        Controller <--> Model
        Controller <--> Service
    end
    
    %% --- 视图输出 ---
    Controller ==> View[View 视图层]
    View --> Display([屏幕硬件 / Display])

    %% --- 应用层 (仅展示核心示例) ---
    subgraph Apps [应用层]
        direction TB
        Weather[☁️ Weather App]
        
        %% 容器示例
        Games[🎮 Games 容器] -.-> Dino[🦖 Dino Run]
        
        %% 省略号表示还有更多
        Etc[... 其他应用]
    end
    
    %% --- 连接关系 ---
    Controller -.-> Weather
    Controller -.-> Games
    Controller -.-> Etc
