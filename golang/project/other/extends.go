package other

import (
	"fmt"
	"project/base"
)

type NodeExtension struct{
	node *base.Node
}

func (nodex *NodeExtension) Btraverse(){
	if nil == nodex || nil == nodex.node {
		return
	}

	left := &NodeExtension{nodex.node.Left}
	left.Btraverse()
	
	right := &NodeExtension{nodex.node.Right}
	right.Btraverse()
	
	nodex.node.Print()
}

func T_other_extension(){
	root := base.CreateNode(1)
	root.Left = base.CreateNode(2)
	root.Right = base.CreateNode(3)
	root.Left.Left = base.CreateNode(4)
	root.Left.Right = base.CreateNode(5)
	root.Right.Left = base.CreateNode(6)
	root.Right.Left = base.CreateNode(7)

	root.Traverse()
	root.Ftraverse()
	
	nodeExtension := NodeExtension{node:root}
	nodeExtension.Btraverse()
}


//################################################################################################################//
type Queue []int

func (queue *Queue) Push(v int) {
	*queue = append((*queue),v)
}


func (queue *Queue) Pop() int {
	ret := (*queue)[0];
	*queue = (*queue)[1:]

	return ret
}

func (queue *Queue) Empty() bool {
	return 0 == len(*queue)
}

func (queue *Queue) Print() {
	if nil == queue {
		fmt.Println("queue is nil")
	}

	fmt.Println(*queue)
}

func T_alias() {
	queue := Queue{}
	queue.Print()
	
	queue.Push(0)
	queue.Push(1)
	queue.Push(2)
	queue.Print()

	queue.Pop()
	queue.Print()
}
//################################################################################################################//
type Stack []interface{}

func (stack *Stack) Push(v interface{}) {
	*stack = append((*stack),v)
}


func (stack *Stack) Pop() interface{} {
	ret := (*stack)[len(*stack) - 1];
	*stack = (*stack)[:len(*stack) - 1]

	return ret
}

func (stack *Stack) Empty() bool {
	return 0 == len(*stack)
}

func (stack *Stack) Print() {
	if nil == stack {
		fmt.Println("stack is nil")
	}

	fmt.Println(*stack)
}

func T_stack() {
	stack := Stack{}
	stack.Print()
	
	stack.Push(0)
	stack.Push("abc")
	stack.Push(false)
	stack.Print()

	stack.Pop()
	stack.Print()
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
func T_nothing(){
	return
}
//################################################################################################################//
