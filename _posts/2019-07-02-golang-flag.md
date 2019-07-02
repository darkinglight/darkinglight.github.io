---
layout: post
title:  "Golang进阶之路: flag的使用"
excerpt: "Usage of flag in golang"
categories: [golang]
comments: true
---
    Golang命令行参数的使用，官方提供了flag。大致使用格式: `scriptname -boolflag1 -intflag2=1 -stringflag=abc`。flag包提供了这部分脚本参数的解析功能，方便开发者。具体如何使用flag包，我们先从一个简单的范例开始，如下:
```
package main

import (
	"flag"
	"fmt"
)

func main() {
	var flag1 int
	flag.IntVar(&intflag, "intflag", 1234, "help message for intflag")
	flag.Parse()
	fmt.Println("intflag's value is ", intflag)
}
```
整个命令行参数的调用过程可以细分为3步:
1. 定义参数变量
2. 注册参数
3. 解析参数

### Reference
1. 源码包/src/flag/flag.go
