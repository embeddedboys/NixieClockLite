# NixieClockLite的工程文档

## 介绍

------
Nixie Clock Lite 是使用[共阴极数码管](https://baike.baidu.com/item/%E5%85%B1%E9%98%B4%E6%9E%81%E6%95%B0%E7%A0%81%E7%AE%A1/18884048?fr=aladdin)
模拟的辉光/荧光管时钟，该工程作为辉光/荧光管时钟工程的铺垫，实现了基本时钟功能，数码管的前两位表示小时(hour)，后两位表示分钟(minute)。


## 硬件参数
------
* `接口` - Type-C

* `输入电压` - 5V

* `主控制芯片` - STC8G1K08-38I-TSSOP20

* `时钟芯片` - DS1302Z

* `数码管驱动芯片` - TM1650

* `电压转换芯片` - AMS1117-3.3

* `纽扣电池` - CR1220

* `操作按键` - 1x复位、4x用户按键

* `数码管型号` - 0.36英寸 4位时钟共阴极数码管

* `引出接口` - SPI、I2C、UART1、UART2


## 工程结构
------
    Documentation/                 # 文档目录
        NixieClockLite/            # 本站工程
        
    hardware/                      # 有关硬件的部分
        nixieclock_kicad_project   # 本项目kicad的工程

    references/                    # 本项目参考的内容

    source/                        # 程序源码
        include/                   # 头文件
        src/                       # 源文件
        tests/                     # 测试程序

    .gitignore                     # git忽略文件
    LICENSE                        # 许可证
    README.md                      # 项目自述文件

## 说明
------
如果你打算从该工程的基础上进行二次开发，请阅读开发者页面中的内容。

工程发布于 MIT 许可证下，有关该许可证的详细信息，请到 `关于 -> 许可证` 中查看

## FAQ
------