---
layout: post
title:  "Golang进阶之路: flag的使用"
excerpt: "Usage of flag in golang"
categories: [golang]
comments: true
---

    Golang命令行参数的使用，官方提供了flag。大致使用格式: `scriptname -boolflag1 -intflag2=1 -stringflag=abc` 。flag包提供了这部分脚本参数的解析功能，方便开发者。

### 简单使用
{% highlight golang %}
package main

import (
	"flag"
	"fmt"
)

func main() {
	var flag1 int
	flag.IntVar(&intflag, "intflag", 1234, "help message for intflag")
	flag.Parse()
	fmt.Println("intflag value is ", intflag)
}
{% endhighlight %}

命令行执行该脚本，效果如下:
{% highlight shell %}
./flagtest
--> intflag value is  1234 //返回默认值
./flagtest -intflag=100
--> intflag value is  100 //返回传递的参数值
{% endhighlight %}

### 可设置的值类型
flag包支持的参数类型为以下几类:

#### bool
1. 参数为1, t, T, true, TRUE, True表示真
2. 参数为0, f, F, false, FALSE, False表示假

#### int，int64，uint，uint64, float64

#### string

#### duration

### 整个命令行参数的调用过程可以细分为3步:
1. 定义参数变量
2. 注册参数
3. 解析参数

### 解析参数源码分析
{% highlight golang %}
func Parse() {
	CommandLine.Parse(os.Args[1:]) //flag的入参为Args[1:],即除脚本名外的所有以空格分隔的命令行参数
}

func (f *FlagSet) Parse(arguments []string) error {
	f.parsed = true
	f.args = arguments
	for {
		seen, err := f.parseOne()
		if seen {
			continue   //这里，通过seen的返回值，控制是否继续解析flag，如果解析过程中发现--，-，seen返回为false，则终止解阿析
		}
		if err == nil {
			break
		}
		switch f.errorHandling {
		case ContinueOnError:
			return err
		case ExitOnError:
			os.Exit(2)
		case PanicOnError:
			panic(err)
		}
	}
	return nil
}

func (f *FlagSet) parseOne() (bool, error) {
	if len(f.args) == 0 {
		return false, nil
	}
	s := f.args[0]
	if len(s) < 2 || s[0] != '-' {
		return false, nil
	}
	numMinuses := 1
	if s[1] == '-' {
		numMinuses++
		if len(s) == 2 { // "--" terminates the flags
			f.args = f.args[1:]
			return false, nil
		}
	}
	name := s[numMinuses:]
	if len(name) == 0 || name[0] == '-' || name[0] == '=' {
		return false, f.failf("bad flag syntax: %s", s)
	}

	// it's a flag. does it have an argument?
	f.args = f.args[1:]
	hasValue := false
	value := ""
	for i := 1; i < len(name); i++ { // equals cannot be first
		if name[i] == '=' {
			value = name[i+1:]
			hasValue = true
			name = name[0:i]
			break
		}
	}
	m := f.formal
	flag, alreadythere := m[name] // BUG
	if !alreadythere {
		if name == "help" || name == "h" { // special case for nice help message.
			f.usage()
			return false, ErrHelp
		}
		return false, f.failf("flag provided but not defined: -%s", name)
	}

	if fv, ok := flag.Value.(boolFlag); ok && fv.IsBoolFlag() { // special case: doesn't need an arg
		if hasValue {
			if err := fv.Set(value); err != nil {
				return false, f.failf("invalid boolean value %q for -%s: %v", value, name, err)
			}
		} else {
			if err := fv.Set("true"); err != nil {
				return false, f.failf("invalid boolean flag %s: %v", name, err)
			}
		}
	} else {
		// It must have a value, which might be the next argument.
		if !hasValue && len(f.args) > 0 {
			// value is the next arg
			hasValue = true
			value, f.args = f.args[0], f.args[1:]
		}
		if !hasValue {
			return false, f.failf("flag needs an argument: -%s", name)
		}
		if err := flag.Value.Set(value); err != nil {
			return false, f.failf("invalid value %q for flag -%s: %v", value, name, err)
		}
	}
	if f.actual == nil {
		f.actual = make(map[string]*Flag)
	}
	f.actual[name] = flag
	return true, nil
}
{% endhighlight %}

### Reference
1. 源码包/src/flag/flag.go
