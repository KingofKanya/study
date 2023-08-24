"""Functions that simulate dice rolls.

A dice function takes no arguments and returns a number from 1 to n
(inclusive), where n is the number of sides on the dice.

Types of dice:

 -  Dice can be fair, meaning that they produce each possible outcome with equal
    probability. Examples: four_sided, six_sided

 -  For testing functions that use dice, deterministic test dice always cycle
    through a fixed sequence of values that are passed as arguments to the
    make_test_dice function.
"""

from random import randint

def make_fair_dice(sides): # 用来创建骰子函数
    """Return a die that returns 1 to SIDES with equal chance."""
    assert type(sides) == int and sides >= 1, 'Illegal value for sides'
    def dice():
        return randint(1,sides)
    return dice # 返回一个函数

# make_fair_dice(6) 只负责创建骰子函数,并不执行实际的掷骰子操作
# 要模拟掷骰子还需要调用它返回的函数

four_sided = make_fair_dice(4)
six_sided = make_fair_dice(6) # 返回一个函数,也就是 six_sided 这个骰子函数

def make_test_dice(*outcomes):
    """Return a die that cycles deterministically through OUTCOMES.

    >>> dice = make_test_dice(1, 2, 3)
    >>> dice()
    1
    >>> dice()
    2
    >>> dice()
    3
    >>> dice()
    1
    >>> dice()
    2

    This function uses Python syntax/techniques not yet covered in this course.
    The best way to understand it is by reading the documentation and examples.
    """
    assert len(outcomes) > 0, 'You must supply outcomes to make_test_dice'
    for o in outcomes:
        assert type(o) == int and o >= 1, 'Outcome is not a positive integer'
    index = len(outcomes) - 1
    def dice():
        nonlocal index # 可以在 dice 函数内部和外部访问
        index = (index + 1) % len(outcomes) # 类似于约瑟夫循环,循环取数,在outcome这tuple中
        return outcomes[index] # 外层函数返回值指向内层函数名
    return dice

# dice = make_test_dice(1, 2, 3)  调用后,dice指向内嵌函数dice()
# 之后再执行时,相当于执行dice()这内嵌函数
# 此函数叫做闭包函数

# https://zhuanlan.zhihu.com/p/440539226