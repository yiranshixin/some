package base

import (
	"fmt"
	"strconv"
	"strings"
)

//################################################################################################################//
//同一模块不同文件定义
func (node *Node) Ftraverse() {
	if nil == node {
		return
	}

	node.Print()
	node.Left.Ftraverse()
	node.Right.Ftraverse()
}

//################################################################################################################//
//utils
func T_strings() {
	month := []string{
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December",
	}

	joinMonth := strings.Join(month, ",")
	fmt.Println(joinMonth)

	splitMonth := strings.Split(joinMonth, ",")
	fmt.Println(splitMonth)

	snum := "1111"
	inum, err := strconv.Atoi(snum)
	if err != nil {
		panic("can to num")
	} else {
		fmt.Println(inum)
	}

	snum = strconv.Itoa(inum)
	fmt.Println(snum)
}

//################################################################################################################//
func T_nothing() {
	return
}

//################################################################################################################//
//测试值与指针类型接收者

type Rinterface interface {
	SubFunc0(x int)
	SubFunc1(x int)
}

type ImplEntry struct {
	Value int
}

func (entry ImplEntry) SubFunc0(x int) {
	fmt.Printf("v-addr = %p\n", &entry)
	entry.Value = x
}

func (entry *ImplEntry) SubFunc1(x int) {
	fmt.Printf("p-addr = %p\n", entry)
	entry.Value = x
}

func T_value_ref() {
	fmt.Println("============================")
	// value-recver
	/*
		ie0.SubFunc0() => SubFunc0(ie0), 实参和行参都是类型 值类型, 此时传递给SubFunc0为 ie0的拷贝
		ie0.SubFunc1() => SubFunc1(ie0) => SubFunc1(&ie0), 实参为 值类型, 形参为 指针类型, 此时编译器修改为传递参数为 &ie0
		ImplEntry 类型的变量这两个方法都是拥有的。
	*/
	ie0 := ImplEntry{}
	fmt.Printf("v-default-addr = %p\n", &ie0)
	fmt.Println("v-default = ", ie0.Value) //0

	ie0.SubFunc0(10)
	fmt.Println("vv-subfunc0 = ", ie0.Value) //0

	ie0.SubFunc1(100)
	fmt.Println("vp-subfunc1 = ", ie0.Value) //100

	fmt.Println("============================")
	// pointer-recver
	/*
		ie1.SubFunc0() => SubFunc0(ie1) => SubFunc0(*ie1)， ie1是指针类型,取ie1的值并拷贝一份传给SubFunc0
		ie1.SubFunc0() => SubFunc0(ie1)，都是指针类型，不需要转换
		*ImplEntry 类型的变量也是拥有这两个方法的
	*/
	ie1 := &ImplEntry{}
	fmt.Printf("p-default-addr = %p\n", ie1)
	fmt.Println("p-default = ", ie1.Value) //0

	ie1.SubFunc0(10)
	fmt.Println("pv-subfunc0 = ", ie1.Value) //0

	ie1.SubFunc1(100)
	fmt.Println("pp-subfunc1 = ", ie1.Value) //100

	// fmt.Println("============================")
	// interface-value-recver
	/*
		cannot use ImplEntry literal (type ImplEntry) as type Rinterface in assignment:
		ImplEntry does not implement Rinterface (SubFunc1 method has pointer receiver)
	*/
	// var inf0 Rinterface = ImplEntry{}
	// fmt.Printf("iv-default-addr = %p\n", inf)
	// fmt.Println("p-default = ", inf1.(*ImplEntry).Value)

	// inf0.SubFunc0(10)
	// fmt.Println("p-subfunc0 = ", inf1.(*ImplEntry).Value)

	// inf0.SubFunc1(100)
	// fmt.Println("p-subfunc1 = ", inf1.(*ImplEntry).Value)

	fmt.Println("============================")
	// interface-pointer-recver
	//接口变量=>指针类型
	var inf1 Rinterface = &ImplEntry{}
	fmt.Printf("ip-default-addr = %p\n", inf1)
	fmt.Println("p-default = ", inf1.(*ImplEntry).Value) //0

	inf1.SubFunc0(10)
	fmt.Println("p-subfunc0 = ", inf1.(*ImplEntry).Value) //0

	inf1.SubFunc1(100)
	fmt.Println("p-subfunc1 = ", inf1.(*ImplEntry).Value) //100
}

/*
何时使用值类型
1.如果接受者是一个 map，func 或者 chan，使用值类型(因为它们本身就是引用类型)。
2.如果接受者是一个 slice，并且方法不执行 reslice 操作，也不重新分配内存给 slice，使用值类型。
3.如果接受者是一个小的数组或者原生的值类型结构体类型(比如 time.Time 类型)，而且没有可修改的字段和指针，又或者接受者是一个简单地基本类型像是 int 和 string，使用值类型就好了。

何时使用指针类型
1.如果方法需要修改接受者，接受者必须是指针类型。
2.如果接受者是一个包含了 sync.Mutex 或者类似同步字段的结构体，接受者必须是指针，这样可以避免拷贝。
3.如果接受者是一个大的结构体或者数组，那么指针类型接受者更有效率。
4.从此方法中并发的调用函数和方法时，接受者可以被修改吗？一个值类型的接受者当方法调用时会创建一份拷贝，所以外部的修改不能作用到这个接受者上。如果修改必须被原始的接受者可见，那么接受者必须是指针类型。
5.如果接受者是一个结构体，数组或者 slice，它们中任意一个元素是指针类型而且可能被修改，建议使用指针类型接受者，这样会增加程序的可读性

当你看完这个还是有疑虑，还是不知道该使用哪种接受者，那么记住使用指针接受者。
*/
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
