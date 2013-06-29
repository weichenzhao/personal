def func1():
    print '1'
def func2():
    print '2'
def func3():
    print '3'
def func4():
    print '4'
def func5():
    print '5'
def func6():
    print '6'
def func7():
    print '7'
def func8():
    print '8'
def func9():
    print '9'
def func10():
    print '10'

def testing(value):
    ca = {
        1: lambda: func1(),
        2: lambda: func2(),
        3: lambda: func3(),
        4: lambda: func4(),
        5: lambda: func5(),
        6: lambda: func6(),
        7: lambda: func7(),
        8: lambda: func8(),
        9: lambda: func9(),
        10: lambda: func10()}
    return ca[value]()

testing(1)
testing(2)
testing(3)
for i in range (10000):
    testing(10)
