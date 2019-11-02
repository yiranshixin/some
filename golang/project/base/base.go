package base

import (
	"bufio"
	"fmt"
	"io"
	"io/ioutil"
	"math"
	"net/http"
	"net/http/httputil"
	"os"
	"reflect"
	"runtime"
	"strings"
	"time"
	"unicode/utf8"
)

//变量，函数 大写为public，小写为private，针对包来讲

/*
bool string
(u)int (u)int8 (u)int16 (u)int32 (u)int64 uintptr
byte rune(32位，字符型) (char 类型，go 中没有明确char类型)
float32 float64 complex64 complex128
*/
/*
*go 中只有值传递
 */

//################################################################################################################//
//定义形式0
func T_variables_0() {
	var i int
	fmt.Println(i)
	var s string
	fmt.Println(s)
	var arr [5]int
	fmt.Println(arr)
	var sl = make([]string, 3)
	fmt.Println(sl)
	var m = make(map[int]string)
	fmt.Println(m)
}

//定义形式1
func T_variables_1() {
	var i, s, b = 1, "abc", true
	fmt.Println(i, s, b)
}

//定义形式2
func T_variables_2() {
	i, s, b := 1, "abc", true
	fmt.Println(i, s, b)
}

var gia int = 1
var gsa = "abc"

//b := true //包内变量不能用 := 定义,只能定义函数内部局部变量

var (
	gib = 1
	gsb = "abc"
	gbb = true
)

//定义形式3
func T_variables_3() {
	fmt.Println(gia, gsa)
	fmt.Println(gib, gsb, gbb)
}

//rune
func T_rune() {
	s := "YES我爱慕课网!"
	iLen := len(s)              //#19
	fmt.Println("存储空间: ", iLen) //#19
	iLen = utf8.RuneCountInString(s)
	fmt.Println("字符个数: ", iLen)

	for _, item := range []byte(s) {
		//#59 45 53 E6 88 91 E7 88 B1 E6 85 95 E8 AF BE E7 BD 91 21
		fmt.Printf("%X ", item)
	}
	fmt.Printf("\n")

	for index, item := range s {
		//#(0, 59) (1, 45) (2, 53) (3, 6211) (6, 7231) (9, 6155) (12, 8bfe) (15, 7f51) (18, 21)
		fmt.Printf("(%d, %x) ", index, item)
	}
	fmt.Printf("\n")

	for index, item := range []rune(s) {
		//#(0, 59) (1, 45) (2, 53) (3, 6211) (4, 7231) (5, 6155) (6, 8bfe) (7, 7f51) (8, 21)
		fmt.Printf("(%d, %x) ", index, item)
	}
	fmt.Printf("\n")

	//其他操作：
	// Fields, Splite, Join
	// Contain, index
	// TOLower, ToUpper
	// TrimRight, TrimLeft

}

//强制类型转换(go 只有强制类型转化)
func T_casts() {
	a, b := 3, 4

	var c int

	c = int(math.Sqrt(float64(a*a + b*b)))

	fmt.Println(c)
}

//const定义形式,go中的常量一般不大写，大写代表public
func T_consts() {

	//const var ciosv int = 1 #const 不能与 var 并存
	//const csosv := "cstring" #const 不能与 := 并存

	const cios int = 1
	const csos string = "cstring"
	const cbos bool = true

	const cio, cso, cbo = 1, "cstring", true

	const (
		cii = 1
		csi = "cstring"
		cbi = true
	)

	//cii = 10 #const 不能再次赋值

	fmt.Println(cios, csos, cbos)
	fmt.Println(cio, cso, cbo)
	fmt.Println(cii, csi, cbi)
}

//枚举 go中没有专门的枚举类型，可用const定义来代替
const (
	b = 1 << (iota * 10)
	kb
	mb
	gb
	tb
	pb
)

func T_enums() {
	const (
		c      = 1
		cpp    = 2
		java   = 3
		python = 4
		shell  = 5
	)

	fmt.Println(c, cpp, java, python, shell)

	const (
		mysql = iota
		sqlserver
		oracle
		postsql
		sqlite
	)
	fmt.Println(mysql, sqlserver, oracle, postsql, sqlite)

	const (
		ash = iota
		_
		csh
		dsh
		esh
		_
		_
		ksh
	)
	fmt.Println(ash, csh, dsh, esh, ksh)

	fmt.Println(b, kb, mb, gb, tb, pb)

}

//################################################################################################################//
//语义 if 条件不能()
func T_segment_if() {
	filename := "abc.log"
	if content, err := ioutil.ReadFile(filename); err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(content)
	}
}

//语义 switch 条件不能()
func T_segment_switch() {
	a, b := 1, 2
	op := "+"

	ret := 0

	switch op {
	case "+":
		ret = a + b
	case "-":
		ret = a - b
	case "*":
		ret = a * b
	case "/":
		ret = a / b
	default:
		panic("no support the op")
	}

	fmt.Println(a, op, b, "=", ret)

	odd := 1
	switch odd {
	case 1, 3, 5, 7, 9:
		fmt.Println("odd")
	case 2, 4, 6, 8, 0:
		fmt.Println("even")
	default:
		panic("not in set")
	}

	score := 70
	switch {
	case score > 100 || score < 0:
		panic("not in range")
	case score > 90:
		fmt.Println("wonderful")
	case score > 80:
		fmt.Println("greatful")
	case score > 60:
		fmt.Println("just ok")
	default:
		fmt.Println("unbelivable")
	}
}

//语义 for 条件不能()
func T_segment_for() {
	for i := 1; i < 3; i++ {
		fmt.Print(i)
	}
	fmt.Print("\n")

	j := 1
	for ; j < 3; j++ {
		fmt.Print(j)
	}
	fmt.Print("\n")

	k := 1
	for k < 3 {
		fmt.Print(k)
		k++
	}
	fmt.Print("\n")

	for {
		fmt.Println("loop")
		break
	}
	fmt.Print("\n")
}

//语义 func(没有默认参数，函数重载等概念)

//################################################################################################################//
//无参无返回值
func T_segment_func_0() {
	fmt.Println("no args, no return")
}

//单参
func T_segment_func_1(a int) {
	fmt.Println("no return, args: ", a)
}

//多参
func T_segment_func_2(a, b int) {
	fmt.Println("no return, args: ", a, b)
}

//无参，单返回值
func T_segment_func_3() int {
	ret := 1
	fmt.Println("no agrs, return: ", ret)
	return ret
}

//多参，单返回值
func T_segment_func_4(i int, s string) int {
	fmt.Println("args, return: ", i)
	return i
}

//多参，多返回值
func T_segment_func_5(i int, s string) (int, string) {
	fmt.Println("args, return: ", i, s)
	return i, s
}

//多参，指定返回值
func T_segment_func_6(i int, s string) (ii int, ss string) {
	ii = i
	ss = s
	fmt.Println("args, return: ", ii, ss)
	return
}

//函数参数
func mod(a, b int) int {
	return a % b
}

func T_segment_func_7(op func(int, int) int, a int, b int) int {
	p := reflect.ValueOf(op).Pointer()
	opName := runtime.FuncForPC(p).Name()

	fmt.Printf("calling func %s with args (%d, %d)\n", opName, a, b)
	ret := 0
	ret = op(a, b)
	return ret
}

//高阶函数
func T_segment_func_8() func() int {
	i := 0
	return func() int {
		i += 1
		return i
	}
}

//可变参数列表
func T_segment_func_9(nums ...int) int {
	fmt.Println(nums)

	sum := 0
	for _, it := range nums {
		sum += it
	}
	return sum
}

func T_segment_func() {
	T_segment_func_0()
	T_segment_func_1(1)
	T_segment_func_2(1, 2)
	f3 := T_segment_func_3()
	f4 := T_segment_func_4(1, "abc")
	f50, f51 := T_segment_func_5(1, "abc")
	f60, f61 := 0, ""
	T_segment_func_6(f60, f61)

	fmt.Println(f3, f4, f50, f51, f60, f61)

	T_segment_func_7(mod, 1, 2)

	T_segment_func_7(func(a, b int) int {
		return int(math.Pow(float64(a), float64(b)))
	}, 3, 4)

	var f = T_segment_func_8()
	fmt.Println(f(), f(), f(), f(), f())

	T_segment_func_9(1, 2, 3, 4, 5, 6, 7, 8, 9)
}

//################################################################################################################//
//指针 不支持+ - 等运算
func T_pointer_0(a, b int) {
	a, b = b, a
}

func T_pointer_1(a, b *int) {
	*a, *b = *b, *a
}

func T_pointer() {
	a, b := 3, 4
	T_pointer_0(a, b)
	fmt.Println(a, b)

	T_pointer_1(&a, &b)
	fmt.Println(a, b)
}

//array 值类型,不同长度其类型也不同,永远不为nil
func T_arr_0(arr [5]int) {
	for i := range arr {
		arr[i] += 1
	}

	fmt.Println(arr)
}

func T_arr_1(arr *[5]int) {
	for i := range arr {
		arr[i] += 1
	}

	fmt.Println(arr)
}

func T_arr_2(sl []int) {
	for i := range sl {
		sl[i] += 1
	}

	fmt.Println(sl)
}

func T_segment_arr() {
	var arr0 [5]int //普通定义方式
	fmt.Println(arr0)

	arr1 := [5]int{0, 1, 2, 3, 4} //此定义方式 需要初始化
	fmt.Println(arr1)

	arr2 := [...]int{0, 1, 2} //此定义方式 需要[...],也需要初始化
	fmt.Println(arr2)

	var arr45 [4][5]int //二维数组定义方式
	fmt.Println(arr45)

	T_arr_0(arr1)
	fmt.Println(arr1)

	T_arr_1(&arr1)
	fmt.Println(arr1)

	T_arr_2(arr1[:])
	fmt.Println(arr1)
}

//slice

// type slice struct{
// 	ptr *int
// 	len int
//	cap int
// }

//1. 底层是array,仅是array的view
//2. slice 可向后扩展，不可以向前扩展
//3. 添加元素超过cap时，系统会重新分配更大的底层数组
//4. cap为0时，为nil, 即用make创建的不是nil

func updateSlice(sl []int) {
	sl[0] = 100
}

func delSlice1(sl []int, f func(int) bool) {
	bflag := false
	ns := make([]int, len(sl))
	i := 0

	for _, item := range sl {
		bflag = f(item)
		if !bflag {
			ns[i] = item
			i++
		}
	}
	fmt.Println(ns)
	sl = ns
}

func isodds(x int) bool {
	return 0 == x%2
}
func T_segment_slice() {
	arr := [...]int{0, 1, 2, 3, 4, 5, 6, 7, 8}

	fmt.Println("arr[2:6]: ", arr[2:6]) //[2 3 4 5]
	fmt.Println("arr[2:]: ", arr[2:])   //[2 3 4 5 6 7 8]
	fmt.Println("arr[:6]: ", arr[:6])   //[0 1 2 3 4 5]
	fmt.Println("arr[:]: ", arr[:])     //[0 1 2 3 4 5 6 7 8]

	s1 := arr[2:]
	s2 := arr[:]

	updateSlice(s1)
	fmt.Println(s1)  //[100 3 4 5 6 7 8]
	fmt.Println(arr) //[0 1 100 3 4 5 6 7 8]

	updateSlice(s2)
	fmt.Println(s2)  //[100 1 100 3 4 5 6 7 8]
	fmt.Println(arr) //[100 1 100 3 4 5 6 7 8]

	//reslice
	s3 := arr[:]
	s3 = s3[:5]
	fmt.Println(s3) //[100 1 100 3 4]
	s3 = s3[2:]
	fmt.Println(s3) //[100 3 4]

	//扩展
	arr1 := [...]int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
	s4 := arr1[4:6]
	fmt.Println(s4)                                         //[4 5]
	fmt.Printf("s4 len = %d, cap = %d\n", len(s4), cap(s4)) //s4 len = 2, cap = 6
	//fmt.Println(s4[4]) #panic: runtime error: index out of range
	s5 := s4[3:5]
	fmt.Println(s5)                                         //[7 8]
	fmt.Printf("s5 len = %d, cap = %d\n", len(s5), cap(s5)) //s5 len = 2, cap = 3

	s6 := append(s5, 10)
	s7 := append(s6, 11) //#超过cap,重新分配底层数组，不再使用arr1作为底层数组
	s8 := append(s7, 12)

	fmt.Println("s6,s7,s8 = ", s6, s7, s8) //s6,s7,s8 =  [7 8 10] [7 8 10 11] [7 8 10 11 12]
	fmt.Println(arr1)                      //[0 1 2 3 4 5 6 7 8 10]

	var ss1 []int
	if ss1 != nil {
		fmt.Println("slice not nil")
	} else {
		fmt.Println("slice is nil") //#命中
	}
	fmt.Println(ss1, len(ss1), cap(ss1)) //[] 0 0

	for i := 0; i < 32; i++ { //slice 内存分配翻倍
		fmt.Println(len(ss1), cap(ss1))
		ss1 = append(ss1, i*2+1)
	}
	fmt.Println(ss1)

	var ss2 = []int{1, 3, 5, 7, 9}
	fmt.Println(ss2)

	ss3 := []int{0, 2, 4, 6, 8}
	fmt.Println(ss3)

	ss4 := make([]int, 10)
	fmt.Println(ss4)

	if ss4 != nil {
		fmt.Println("slice not nil") //#命中
	} else {
		fmt.Println("slice is nil")
	}

	copy(ss4, ss3)
	fmt.Println(ss4)

	//删除第三个元素
	ss4 = append(ss4[:3], ss4[4:]...)
	fmt.Println(ss4)

	//删除头
	ss4 = ss4[1:]
	fmt.Println(ss4)

	//删除尾
	ss4 = ss4[:len(ss4)-1]
	fmt.Println(ss4)

	ss5 := []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
	delSlice1(ss5, isodds)
	fmt.Println(ss5)
}

//map
//map[k]v
//map[k0]map[k1]v
//用make创建的不为nil
//存储方式为hashmap方式
//不能用slice,map,func,及包含slice和map的struct作为key
//map[key] 返回值为 value:existed; 若key不存在，value取默认值

func T_segment_map() {
	var m0 map[int]string
	fmt.Println(m0)

	if m0 != nil {
		fmt.Println("map not nil")
	} else {
		fmt.Println("map is nil") //#命中
	}

	//m0 is nill，不能插入值
	// m0[1] = "a"
	// m0[2] = "b"
	// m0[3] = "c"
	// fmt.Println(m0)

	var m1 = map[int]string{
		1: "a",
		2: "b",
		3: "c",
	}
	fmt.Println(m1)
	for k, v := range m1 {
		fmt.Println(k, v)
	}

	m2 := map[int]string{
		1: "a",
		2: "b",
		3: "c",
	}
	fmt.Println(m2)

	if v, b := m2[10]; b {
		fmt.Println("exist: ", v)
	} else {
		fmt.Println("not exist: ", b)
	}

	m3 := make(map[int]string)
	fmt.Println(m3)
	if m3 != nil {
		fmt.Println("map not nil") //#命中
	} else {
		fmt.Println("map is nil")
	}

	m3[10] = "A"
	m3[11] = "B"
	m3[12] = "C"
	fmt.Println(m3)

	m4 := make(map[[3]int]int)
	fmt.Println(m4)
	//m5 := make(map[[]int]int) #不能将slice作为key
	//m6 := make(map[map[int]int]int) #不能将map作为key
}

//struct
//没有构造函数说法，可以用工厂函数代替
//本来接收指针，但实体亦能调用，反之，如果接收实体，指针也能调用，中间存在转换过程

type Node struct {
	Value       int
	Left, Right *Node
}

func CreateNode(v int) *Node {
	return &Node{Value: v}
}

func (node *Node) Print() {
	if node != nil {
		fmt.Println(node)
	} else {
		fmt.Println("caller is nil")
	}
}

func (node *Node) SetValue(v int) {
	if node != nil {
		node.Value = v
	} else {
		fmt.Println("caller is nil")
	}
}

func (node *Node) Traverse() {
	if node == nil {
		return
	}

	node.Left.Traverse()
	node.Print()
	node.Right.Traverse()
}

func T_struct() {
	var root Node
	fmt.Println(root)

	root = Node{Value: 1}
	root.Left = &Node{}
	root.Right = &Node{2, nil, nil}
	root.Left.Right = new(Node)

	nodes := []Node{
		{Value: 3},
		{},
		{6, nil, nil},
	}

	fmt.Println(nodes)

	root.Print() //#print本来接收指针，但实体亦能调用，反之，如果接收实体，指针也能调用，中间存在转换过程
	n0 := CreateNode(3)
	fmt.Println(n0)
	n0.SetValue(4)
	n0.Print()

	var n1 *Node //#nil 也能调用方法
	n1.Print()

	root.Traverse()
	root.Ftraverse() //#在其他文件中定义
}

//interface
//1. interface变量既能接收 值 也能接收 指针
//2. interface变量因内部自带指针，所以不需要在接收 指针 变量时，将interface变量也定义为 指针变量
//3. 指针接收者 只能 接收指针变量，而值接收者两者皆可
//4.
//	interface类型转换: v, ok : = instance.(shouldbetype)
//	interface取类型:v := instance.(type)
//4. 表示任何类型 interface{},
type Downloader interface {
	Download(url string) string
}

type FakeDownloader struct {
	Content string
}

func (fdl FakeDownloader) Download(url string) string {
	return fmt.Sprintf("Fake: %s : %s", url, fdl.Content)
}

type RealDownloader struct {
	UserAgent string
	TimeOut   time.Duration
}

func (rdl *RealDownloader) Download(url string) string {
	resp, err := http.Get(url)
	if err != nil {
		panic(err)
	}

	result, err := httputil.DumpResponse(resp, true)

	resp.Body.Close()

	if err != nil {
		panic(err)
	}

	return fmt.Sprintf("Real: %s : %s", url, string(result))
}

func inspect(downloader Downloader) {
	fmt.Println("inspect: ", downloader)
	fmt.Printf(" > Type: %T, Value: %v\n", downloader, downloader)
	fmt.Println(" > Type switch:")

	switch v := downloader.(type) {
	case FakeDownloader:
		fmt.Println("\t> Content: ", v.Content)
	case *FakeDownloader:
		fmt.Println("\t> Content: ", v.Content)
	case *RealDownloader:
		fmt.Println("\t> UserAgent: ", v.UserAgent)
		fmt.Println("\t> UserAgent: ", v.TimeOut)
	default:
		fmt.Println("\t> ...")
	}
}

func typeAssert(downloader Downloader) {
	fmt.Println("typeassert: ", downloader)
	if fakeDownloader, ok := downloader.(FakeDownloader); ok {
		fmt.Println("\t> fake Content: ", fakeDownloader.Content)
	}

	if fakeDownloader, ok := downloader.(*FakeDownloader); ok {
		fmt.Println("\t> *fake Content: ", fakeDownloader.Content)
	}

	if realDownloader, ok := downloader.(*RealDownloader); ok {
		fmt.Println("\t> *real UserAgent: ", realDownloader.UserAgent)
		fmt.Println("\t> *real UserAgent: ", realDownloader.TimeOut)
	}

}

type Isimple interface {
	Add(x, y int) int
	Sub(x, y int) int
}

type IComplex interface {
	Multi(x, y int) int
	Divis(x, y int) int
}

type Iother interface {
	Mod(x, y int) int
}

type S1 struct {
}

func (s1 *S1) Add(x, y int) int {
	return x + y
}

func (s1 *S1) Sub(x, y int) int {
	return x - y
}

func (s1 *S1) Mod(x, y int) int {
	return x % y
}

type S2 struct {
}

func (s2 *S2) Multi(x, y int) int {
	return x + y
}

func (s2 *S2) Divis(x, y int) int {
	return x + y
}

func (s2 *S2) Mod(x, y int) int {
	return x % y
}

func T_interface() {
	const url = "http://www.imooc.com"
	var downloader Downloader

	downloader = FakeDownloader{"200 Ok"}
	fmt.Printf("%T %v\n", downloader, downloader)
	content := downloader.Download(url)
	fmt.Println(content)
	inspect(downloader)
	typeAssert(downloader)

	downloader = &FakeDownloader{"404 Error"}
	fmt.Printf("%T %v\n", downloader, downloader)
	content = downloader.Download(url)
	// fmt.Println(content)
	inspect(downloader)
	typeAssert(downloader)

	//#编译错误，指针接收者，只能接受指针，不能为值类型
	// downloader = RealDownloader{
	// 	UserAgent : "Mozilla/5.0",
	// 	TimeOut : time.Minute,
	// }
	// fmt.Printf("%T %v\n", downloader, downloader)
	// content = downloader.Download(url)
	// fmt.Println(content)
	// inspect(downloader)

	downloader = &RealDownloader{
		UserAgent: "Mozilla/5.0",
		TimeOut:   time.Minute,
	}
	fmt.Printf("%T %v\n", downloader, downloader)
	content = downloader.Download(url)
	// fmt.Println(content)
	inspect(downloader)
	typeAssert(downloader)

	var s1 Isimple
	var s2 IComplex
	var s3 Iother

	s1 = &S1{}
	s1.Add(1, 2)
	s1.Sub(1, 2)

	s2 = &S2{}
	s2.Multi(3, 4)
	s2.Divis(3, 4)

	s3 = &S1{}
	s3.Mod(1, 2)

	s3 = &S2{}
	s3.Mod(3, 4)
}

//################################################################################################################//
//#函数式编程
// 1. 闭包
func Fib() func() int {
	a, b := 0, 1
	return func() int {
		a, b = b, a+b
		return a
	}
}

//#2. 为函数添加接口，其实函数也可看为特殊的结构
type gen func() int

func Gen() gen {
	a, b := 0, 1
	return func() int {
		a, b = b, a+b
		return a
	}
}

func (g gen) Read(p []byte) (n int, err error) {
	next := g()

	if next > 10000 {
		return next, io.EOF
	}

	s := fmt.Sprintf("%d\n", next)
	return strings.NewReader(s).Read(p)
}

func printFileContents(reader io.Reader) {
	scanner := bufio.NewScanner(reader)

	for scanner.Scan() {
		fmt.Println(scanner.Text())
	}
}

func T_functional() {
	// generator := Fib()
	// fmt.Println(generator())
	// fmt.Println(generator())
	// fmt.Println(generator())
	// fmt.Println(generator())
	// fmt.Println(generator())

	f := Gen()
	printFileContents(f)
}

//#3. 将函数做为会参数，进行回调
//################################################################################################################//
//#错误处理
func T_error_0() {
	defer fmt.Println("defer...1")
	defer fmt.Println("defer...2")
	fmt.Println("normal...1")
	panic("something wrong...")
	//fmt.Println("normal...2")
}

func writeToFile(filename string) {
	file, err := os.Create(filename)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	defer writer.Flush()

	for i := 0; i < 100; i++ {
		fmt.Fprintln(writer, i)
	}

}

func T_error_1() {
	writeToFile("printer.log")
}

//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//################################################################################################################//
//包
//#1. 每个目录一个包,包名无需同包同名
//#2. main包包含可执行文件入口main函数
//#3. 为结构定义的方法必须放在同一个包内，但可以是不同文件
//#4. import 中引入的为包的目录,而非包名,但使用的时候，用包名即可
//#5. 保重大写的 变量和函数 为public，在其他包可见
//################################################################################################################//
