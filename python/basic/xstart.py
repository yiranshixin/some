# -*- coding: utf-8 -*-
from collections import Iterable
from collections import  Iterator
from io import StringIO
import os

import pickle
import json

import logging

logging.basicConfig(level=logging.INFO,
                    format='[%(asctime)s] [%(process)d-%(thread)d] [%(levelname)s] %(message)s [%(funcName)s:%(lineno)d]',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    )

"""
#12.25-12.28
l1 = [553,315,33,30,100]
#2.20-3.10
l2 = [615,553,28,34,31,28,33,29,33,29,40,31,28,33,29,32,29,29,31,28,50,50,50]
#3.30-4.2
l3 = [615,870,50]
#4.17-4.27
l4 = [111.5,73,523.5,750,28,27,28,14,32,42,16,30,24,29,50,50]
#5.21-5.27
l5 = [818,553,14,52]
#5.31-6.18
l6 = [518,448.5,18,14,50,50,50]
#6.18-6.24
l7 = [515.5,476,119,41]
lall = l1+l2+l3+l4+l5+l6+l7

def sadd(x,y):
    return x+y

print reduce(sadd,l1)
print reduce(sadd,l2)
print reduce(sadd,l3)
print reduce(sadd,l4)
print reduce(sadd,l5)
print reduce(sadd,l6)
print reduce(sadd,l7)
print reduce(sadd,lall)
"""

"""
######################################################################################################
#单默认参数
def power(x,n=2):
    ret = 1
    while(n >0):
        ret = ret * x
        n = n-1
    return ret

print power(3)
print power(3,4)
######################################################################################################
#多默认参数
def studentInfo(name, age = 6, level = 1):
    print("name = %s, age = %d, level = %d"%(name, age, level))
    return

studentInfo("xiaoming")
studentInfo("xiaoli",7)
studentInfo("xiaohan",8,3)
studentInfo("xiaoye",level=4)
#######################################################################################################
#列表参数
def addEnd(l = None):
    if l is None:
        l = []
    l.append("end")
    return l

print addEnd()
print addEnd([1,2,3])
#######################################################################################################
#可变参数
def calc(*l):
    sum = 0
    for x in l:
        sum += x
    return sum

print calc(1)
print calc(1,2)
cl = [1,2,3]
print calc(*cl)
ct = (1,2,3,4)
print calc(*ct)
#######################################################################################################
#关键字参数
def person(**kw):
    print kw

person(name="xiaoli",age = 10)
person(name="xiaoxu",age=30,sex="man")
kw={"name" :"xiaowang","age":40,"sex":"man","addr":"beijing"}
person(**kw)
#######################################################################################################
#命名关键字参数
#def teacher(name, age, *, city, job):
#    print(name,age,city,job)

#teacher("lili",23)
#teacher("lala",24,city = "beijing")
#teacher("lulu",25,"man",job = "math")
#teacher("lucy",26,"male",city = "shanghai", job = "langue")

########################################################################################################
#多种类型参数组合
def muiltArgsFuc(a, b, c=0, *args, **kw):
    print('a =', a, 'b =', b, 'c =', c, 'args =', args, 'kw =', kw)

muiltArgsFuc(1,2)
muiltArgsFuc(1,2,3)
muiltArgsFuc(1,2,3,"a")
muiltArgsFuc(1,2,3,"a",{"7":"s","8":"e"})
#muiltArgsFuc(1,2,3,"a",b="999")

########################################################################################################
#list操作
L = ['Michael', 'Sarah', 'Tracy', 'Bob', 'Jack']
print L
print L[:]
print L[0:5]
print L[1:]
print L[:4]
print L[1:4]
print L[::2]
print L[1:4:2]
print L[-1]
#===================
print L[-1:-3]
print L[-3:-1]
#===================

L = list(xrange(100))
print L
########################################################################################################
#tuple操作
T = ('Michael', 'Sarah', 'Tracy', 'Bob', 'Jack')
print T
print T[:]
print T[0:5]
print T[1:]
print T[:4]
print T[1:4]
print T[::2]
print T[1:4:2]
print T[-1]
#===================
print T[-1:-3]
print T[-3:-1]
#===================

T = tuple(xrange(100))
print T
#########################################################################################################

#字符串遍历
S = "abc"
for s in S:
    print s

#list遍历
L = [1,2,3]
for l in L:
    print l

#tuple遍历
T = (1,2,3)
for t in T:
    print t

#字典遍历
d = {'a': 1, 'b': 2, 'c': 3}
for key in d:
    print key
for value in d.values():
    print value
for key,value in d.items():
    print key,value

############################################################################################################
#列表生成式
L = list(range(1,20))
print L

L = [x*x for x in range(1,20) if x%2 == 0]
print L

L = [m + n for m in 'ABC' for n in 'XYZ']
print L

d = {'x': 'A', 'y': 'B', 'z': 'C' }
L = [k + "=" + v for k,v in d.items()]
print L

#生成器
G = (x * x for x in range(10))
print isinstance(G,Iterable)
for g in G:
    print g

def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        a, b = b, a + b
        n = n + 1
    return

g= fib(6)
while True:
    try:
        print g.next()
    except StopIteration as e:
        print "done"
        break

def odd():
    print "step 1"
    yield 1
    print "step 2"
    yield 3
    print "step 3"
    yield 5

g=odd()
print g.next()
print g.next()
print g.next()

##########################################################################################################
#可迭代对象
print isinstance("abc",Iterable)
print isinstance([1,2,3],Iterable)
print isinstance((1,2,3),Iterable)
print isinstance({"a": 1, "b": 2, "c": 3},Iterable)
print isinstance([x*x for x in range(1,10)],Iterable)
print isinstance((x*x for x in range(1,10)),Iterable)

for i, value in enumerate(['A', 'B', 'C']):
    print i,value
for x, y in [(1, 1), (2, 4), (3, 9)]:
    print x,y

#迭代器
print isinstance("abc",Iterator)
print isinstance([1,2,3],Iterator)
print isinstance((1,2,3),Iterator)
print isinstance({"a": 1, "b": 2, "c": 3},Iterator)
print isinstance([x*x for x in range(1,10)],Iterator)
print isinstance((x*x for x in range(1,10)),Iterator)

print isinstance(iter("abc"),Iterator)
print isinstance(iter([1,2,3]),Iterator)
print isinstance(iter((1,2,3)),Iterator)
print isinstance(iter({"a": 1, "b": 2, "c": 3}),Iterator)
print isinstance(iter([x*x for x in range(1,10)]),Iterator)

####################################################################################################
#函数式编程
#高阶函数
def add(x, y, f):
    return f(x) + f(y)

print add(-1,-2,abs)

#map()函数接收两个参数，一个是函数，一个是Iterable，map将传入的函数依次作用到序列的每个元素，并把结果作为新的Iterator返回
def f(x):
    return x*x
r = map(f,[1,2,3])
print list(r)

print list(map(str, [1, 2, 3, 4, 5, 6, 7, 8, 9]))

#reduce把一个函数作用在一个序列[x1, x2, x3, ...]上，这个函数必须接收两个参数，reduce把结果继续和序列的下一个元素做累积计算
#reduce(f, [x1, x2, x3, x4]) = f(f(f(x1, x2), x3), x4)

def sadd(x,y):
    return x+y

print reduce(sadd,[1,2,3])

def str2int(s):
    def fn(x, y):
        return x * 10 + y
    def char2num(sq):
        return {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}[sq]
    return reduce(fn, map(char2num, s))

print str2int("198928989345")

def char2num(s):
    return {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}[s]

def str2int(s):
    return reduce(lambda x, y: x * 10 + y, map(char2num, s))

print str2int("89808023423481298028340932840821408")

#filter()也接收一个函数和一个序列。把传入的函数依次作用于每个元素，然后根据返回值是True还是False决定保留还是丢弃该元素
#filter()函数返回的是一个Iterator
def is_odd(n):
    return n % 2 == 1

print(list(filter(is_odd,[1,2,3,4,5,6])))

def not_empty(s):
    return s and s.strip()

print list(filter(not_empty, ['A', '', 'B', None, 'C', '  ']))

#sorted
print sorted([36, 5, -12, 9, -21])
print  sorted([36, 5, -12, 9, -21],key=abs)
print  sorted([36, 5, -12, 9, -21],key=abs,reverse=True)

print sorted(['bob', 'about', 'Zoo', 'Credit'])
print  sorted(['bob', 'about', 'Zoo', 'Credit'],key=str.lower)
print  sorted(['bob', 'about', 'Zoo', 'Credit'],key=str.lower,reverse=True)


l = [('Bob', 75), ('Adam', 92), ('Bart', 66), ('Lisa', 88)]
print sorted(l,key = lambda t:t[0])
print sorted(l,key = lambda t:t[1])

def retFirst(t):
    return t[0]
def retSecond(t):
    return t[1]

print sorted(l,key=retFirst)
print sorted(l,key=retSecond)

###############################################################################################################
#函数作为返回值
def lazy_sum(*args):
    def sum():
        ax = 0
        for n in args:
            ax = ax + n
        return ax
    return sum

ls = lazy_sum(1,2,3,4,5,6)
print ls()
print ls()
#在函数lazy_sum中又定义了函数sum，并且，内部函数sum可以引用外部函数lazy_sum的参数和局部变量
#当lazy_sum返回函数sum时，相关参数和变量都保存在返回的函数中，这种称为闭包（Closure）
#当我们调用lazy_sum()时，每次调用都会返回一个新的函数，即使传入相同的参数

def count():
    fs = []
    for i in range(1, 4):
        def f():
             return i*i
        fs.append(f)
    return fs

f1, f2, f3 = count()
print f1(),f2(),f3()

#返回函数不要引用任何循环变量，或者后续会发生变化的变量。
#如果一定要引用循环变量,则再创建一个函数，用该函数的参数绑定循环变量当前的值，无论该循环变量后续如何更改，已绑定到函数参数的值不变
def count():
    def f(j):
        def g():
            return j*j
        return g
    fs = []
    for i in range(1, 4):
        fs.append(f(i)) # f(i)立刻被执行，因此i的当前值被传入f()
    return fs

f1, f2, f3 = count()
print f1(), f2(), f3()


#修饰函数
def log(func):
    def wrapper(*args,**kw):
        print('call %s():' % func.__name__)
        return func(*args,**kw)
    return wrapper

@log
def now():
    print('2015-3-25')

now()
###############################################################################################################

#模块
import xmodule
xmodule.test()
#pip install xxx
#python 库搜索目录
import sys
print sys.path
###############################################################################################################
#类
class Student(object):

    def __init__(self, name, score):
        self.__name = name
        self.__score = score

    def print_score(self):
        print('%s: %s' % (self.__name, self.__score))

s1 = Student("xiaoming",100)
s1.print_score()
#在Python中，变量名类似__xxx__的,是特殊变量，特殊变量是可以直接访问的，不是private变量
#以一个下划线开头的实例变量名_x,实例变量外部是可以访问的。但是，请把它视为私有变量，不要随意访问
#变量名如果以__开头，就变成了一个私有变量（private），只有内部可以访问，外部不能访问

class Animal(object):
    def run(self):
        print('Animal is running...')

class Dog(Animal):
    def run(self):
        print('Dog is running...')
    def eat(self):
        print('Eating meat...')

class Cat(Animal):
    def run(self):
        print('Cat is running...')

animal = Animal()
animal.run()

dog = Dog()
dog.run()

cat = Cat()
cat.run()

import types
print type(123)
print type("123")
print type([1,2,3])
print type((1,2,3))
print type({"k1":1,"k2":2,"k3":3})
print type([x for x in range(10)])
print type((x for x in range(10)))
print type(lambda x:x)

print type(abs)
print type(animal)
print type(dog)

print type(123)==int
print type("123")==str
print type([1,2,3])==list
print type((1,2,3))==tuple
print type({"k1":1,"k2":2,"k3":3})==dict
print type([x for x in range(10)])==list
print type(lambda x: x)==types.LambdaType
print type((x for x in range(10)))==types.GeneratorType

print type(abs)==types.BuiltinFunctionType
def fn():
    pass
print type(fn)==types.FunctionType

print type(animal)
print type(dog)

print isinstance([1, 2, 3], (list, tuple))
#打印支持的方法
print dir(dog)

class Stu(object):
    def __init__(self, name):
        self.name = name

s = Stu('Bob')
s.score = 90

s1 = Stu("tim")
print s.name
print s.score
print dir(s)
print dir(s1)
print dir(Stu)

class Stus(object):
    name = 'Students'
ss = Stus()
ss.name = "teacher"
print ss.name
ss1 = Stus()
print ss1.name
print Stus.name
print dir(ss)
print dir(ss1)
print dir(Stus)

print id(ss.name)
print id(ss1.name)
print id(Stus.name)
del ss.name
print id(ss.name)
#类属性,实例属性;类属性类似于static成员变量,为所有实例共有.实例属性归实例所有，各个实例属性由不同实例决定.实例属性与类属性同名时，实例属性掩盖类属性
#正常情况下，当我们定义了一个class，创建了一个class的实例后，我们可以给该实例绑定任何属性和方法

class MClassTest(object):
    pass
ct = MClassTest()
ct.name = "ct"
print ct.name

def set_age(self, age):
    self.age = age

from types import MethodType
ct.set_age = MethodType(set_age, ct) # 给实例绑定一个方法
ct.set_age(23)
print ct.age

ct1 = MClassTest()

MClassTest.set_age = set_age #给类绑定方法，所有实例均可用
ct1.set_age(10)
print ct1.age

#Python允许在定义class的时候，定义一个特殊的__slots__变量，来限制该class实例能添加的属性
class SlotTest(object):
    __slots__ = ('name', 'age') # 用tuple定义允许绑定的实例属性名称
class GraduateStudent(SlotTest):# 子类中不受父类slot限制
    pass
#############################################################################################
class ProTest(object):

    @property
    def birth(self):
        return self._birth

    @birth.setter
    def birth(self, value):
        self._birth = value

    @property
    def age(self):
        return 2015 - self._birth

pro = ProTest()
pro.birth =1
pro.birth

pro.age
#birth 读写属性，age只读属性

#组父类
class Animal(object):
    pass

# 大类:
class Mammal(Animal):
    pass

class Bird(Animal):
    pass

#动作类
class Runnable(object):
    def run(self):
        print('Running...')

class Flyable(object):
    def fly(self):
        print('Flying...')

#子类
class Dog(Mammal, Runnable):
    pass

class Bat(Mammal, Flyable):
    pass
###############################################################################################################
class Studs(object):

    def __init__(self, name):
        self.name = name

    def __str__(self):
        return 'Studs object (name=%s)' % self.name

    __repr__ = __str__

    def __getattr__(self, attr):
        if attr == 'age':
            return 25
        raise AttributeError('\'Student\' object has no attribute \'%s\'' % attr)

print Studs("xiaoli")
print Studs("xiaolu").age
#print Studs("xiaomi").sex

class Fib(object):
    def __init__(self):
        self.a, self.b = 0, 1
        self.name = "Fib"

    def __iter__(self):
        return self # 实例本身就是迭代对象，故返回自己

    def __next__(self):
        self.a, self.b = self.b, self.a + self.b # 计算下一个值
        if self.a > 100000: # 退出循环的条件
            raise StopIteration()
        return self.a # 返回下一个值

    def __getitem__(self, n):
        if isinstance(n,int):
            a, b = 1, 1
            for x in range(n):
                a, b = b, a + b
            return a
        if isinstance(n, slice):
            start = n.start
            stop = n.stop
            if start is None:
                start = 0
            if stop is None or stop > 10:
                stop = 10
            a, b = 1, 1
            L = []
            for x in range(stop):
                if x >= start:
                    L.append(a)
                a, b = b, a + b
            return L

    def __call__(self):
        print('My name is %s.' % self.name)

fib = Fib()
#for n in fib:
#    print(n)
print fib[9]
print fib[:4]
print fib[4:10]
print fib[2:100]
fib()
print callable(Fib)

#__setitem__()方法，把对象视作list或dict来对集合赋值。最后，还有一个__delitem__()方法，用于删除某个元素

#from enum import Enum
#Month = Enum('Month', ('Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'))

try:
    print('try...')
    r = 10 / int('2')
    print('result:', r)
except ValueError as e:
    print('ValueError:', e)
except ZeroDivisionError as e:
    print('ZeroDivisionError:', e)
else:
    print('no error!')
finally:
    print('finally...')
print('END')


def foo(s):
    return 10 / int(s)

def bar(s):
    return foo(s) * 2

def main():
    try:
        bar('0')
    except Exception as e:
        print('Error:', e)
    finally:
        print('finally...')

def mainUnsafe():
    bar('0')

#mainUnsafe()
#如果错误没有被捕获，它就会一直往上抛，最后被Python解释器捕获，打印一个错误信息，然后程序退出

import logging

def mainLogging():
    try:
        bar('0')
    except Exception as e:
        logging.exception(e)

mainLogging()
print("continuing!!!")
#如果不捕获错误，自然可以让Python解释器来打印出错误堆栈，但程序也被结束了。
#既然我们能捕获错误，就可以把错误堆栈打印出来，然后分析错误原因，同时，让程序继续执行下去。

def fooRasing(s):
    n = int(s)
    if n==0:
        raise ValueError('invalid value: %s' % s)
    return 10 / n

def barRasing():
    try:
        fooRasing('0')
    except ValueError as e:
        print('ValueError!')
        raise

#barRasing()
#raise语句如果不带参数，就会把当前错误原样抛出
#################################################################################################
#日志操作
logging.info("hello,just a loging")
#logging.info(10/0)
#################################################################################################################
#文件操作
try:
    f = open('E:\\xx-out\\test.txt', 'r')
    print(f.read())
finally:
    if f:
        f.close()

with open('E:\\xx-out\\test.txt', 'r') as f:
    print(f.read())


with open("E:\\xx-out\\test.txt","r") as f:
    for line in f.xreadlines():
        print line

#f = open('/Users/michael/test.jpg', 'rb')
#f = open('/Users/michael/gbk.txt', 'r', encoding='gbk')
#f = open('/Users/michael/gbk.txt', 'r', encoding='gbk', errors='ignore')

with open("E:\\xx-out\\test.txt", 'w') as f:
    f.write('Hello, world!')

mf = StringIO()
mf.write(unicode('hello\nstring\nmemory\nio'))
print mf.getvalue()

mf.write(unicode("\n"))
print mf.getvalue()
mf.writelines(unicode("====="))
print mf.getvalue()
mf.writelines(unicode("-----"))
print mf.getvalue()
mf.close()

print os.name
print os.environ
print os.environ.get("path")
print os.path.abspath(".")
print os.path.abspath("..")
print os.path.join("e:\\src","test")
os.mkdir("e:\\src\\test")
os.rmdir("e:\\src\\test")

print os.path.split('/Users/michael/testdir/file.txt')

os.rename("E:\\xx-out\\test.txt","E:\\xx-out\\test-1.txt")
os.remove("E:\\xx-out\\test-1.txt")

print [x for x in os.listdir('.') if os.path.isfile(x) and os.path.splittext(x)[1]=='.py']
###################################################################################################
#序列化操作
dd = dict(name="xiaoming",age=10,sex=True)
ff = open("./test.txt",'wb')
pickle.dump(dd,ff)
ff.close()
ff = open("./test.txt",'rb')
ddd = pickle.load(ff)
ff.close()
print ddd

print json.dumps(dd)
class xperson:
    def __init__(self,name,age,addr):
        self.name = name
        self.age = age
        self.addr = addr


def xperson2json(xp):
        return {
            "name":xp.name,
            "age":xp.age,
            "addr":xp.addr
        }

def dict2xperson(d):
    return xperson(d["name"],d["age"],d["addr"])

ff = open("./test.txt","wb")
json.dump(xperson("lili",23,"zhonghuadajie"),ff,default=xperson2json)
ff.close()

ff = open("./test.txt","rb")
xinfo = json.load(ff,object_hook=dict2xperson)
ff.close()
print xinfo.name,xinfo.age,xinfo.addr
###################################################################################################
"""
#进程线程
print('Process (%s) start...' % os.getpid())

