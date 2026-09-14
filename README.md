# 基于 STM32 的独居青年 AI 语音陪伴与家居控制系统

物联网系统综合课程设计。STM32F103C8T6 主控 + ESP32-S3（小智 AI 语音模块），语音控制 LED 灯亮灭，OLED 显示状态，蜂鸣器提示。

## 功能

- ESP32-S3 负责语音唤醒、AI 闲聊对话、识别"开灯/关灯"指令
- 识别到指令后通过 GPIO18 输出电平，STM32 PA0 轮询检测
- STM32 控制继电器吸合/断开，驱动外接 LED 灯珠
- OLED（SSD1306, I2C）实时显示 `Light:ON/OFF`
- 状态变化时蜂鸣器短提示音

## 引脚分配

| 模块 | STM32 引脚 | 说明 |
|:-:|:-:|:-:|
| OLED SCL | PB8 | 软件 I2C |
| OLED SDA | PB9 | 软件 I2C |
| OLED VCC | 3.3V | |
| 蜂鸣器 I/O | PB12 | 低电平触发 |
| 蜂鸣器 VCC | 5V | |
| 继电器 IN | PB0 | 高电平触发 |
| 继电器 VCC | 5V | |
| 小智 GPIO18 | PA0 | 上拉输入 |
| 小智 GND | GND | 共地 |

## 硬件

- STM32F103C8T6 最小系统板
- ESP32-S3 N16R8（小智 AI 语音模块，预刷固件）
- 0.96 寸 OLED（SSD1306, 128×64）
- 1 路 5V 光耦继电器
- 有源蜂鸣器
- 红色直插 LED + 限流电阻

## 开发环境

- Keil uVision 5
- STM32F10x 标准外设库
- ST-Link V2 下载调试

## 目录结构

```
Hardware/   OLED、LED、Key 驱动
System/     延时函数
User/       main.c 主程序
Library/    STM32 标准外设库
Start/      启动文件与内核
```

## 使用

1. 用 Keil 5 打开 `project.uvprojx`
2. 编译下载到 STM32
3. ESP32-S3 小智模块独立供电（5V 充电器）
4. 说"开灯"/"关灯"控制 LED
