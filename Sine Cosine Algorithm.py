import matplotlib.pyplot as plt
import random
import math

iterations = 1000
agents = 100
rr1 = 0.0
xmin = 0.0
xmax = 0.0
ymin = 0.0
ymax = 0.0
x = []
y = []
x_fit = []
y_fit = []
xb = 0.0
yb = 0.0

#------------------------------------------------------------------------------- For plotting the points into plane -----------------------------------------------------------------------------------------------------------------------------------------------
def plot():
    plt.scatter(x, y)
    plt.xlabel("X-axis")
    plt.ylabel("Y-axis")
    plt.xlim(xmin, xmax)
    plt.ylim(ymin, ymax)
    plt.show()


#------------------------------------------------------------------------------- r1 ranges in (0.00 - 1.00) ----------------------------------------------------------------------------------------------------------------------------------------------------------
def r1():
    return random.uniform(0, 1)


#------------------------------------------------------------------------------- r2 ranges in (0.00, 2pi) -----------------------------------------------------------------------------------------------------------------------------------
def r2():
    return random.uniform(0, 2 * math.pi)


#------------------------------------------------------------------------------- r3 ranges in (0.00, 2.00) --------------------------------------------------------------------------------------------------------------------------------------------------------
def r3():
    return random.uniform(0, 2)


#------------------------------------------------------------------------------- r4 ranges in (0.00 - 1.00) ----------------------------------------------------------------------------------------------------------------------------------------------------------
def r4():
    return random.uniform(0, 1)



#------------------------------------------------------------------------------ Generate Initial Population ----------------------------------------------------------------------------------------------------------------------------------------------------------
def generate_initial_population():
    for i in range(agents):
        xx = xmin + r1() * (xmax - xmin)
        yy = ymin + r1() * (ymax - ymin)
        x.append(xx)
        y.append(yy)


#------------------------------------------------------------------------------- Bringing points into bounds --------------------------------------------------------------------------------------------------------------
def position_update_check():
    for i in range(agents):
        if x[i] < xmin:
            x[i] = xmin
        if x[i] > xmax:
            x[i] = xmax
        if y[i] < ymin:
            y[i] = ymin
        if y[i] > ymax:
            y[i] = ymax



#-------------------------------------------------------------------------------- Calculating the fitness ----------------------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------- Using Sphere Function ------------------------------------------------------------------------------------------------------------------
def calculate_fitness():
    global xb, yb
    mn = float('inf')
    for i in range(agents):
        cur = x[i]**2 + y[i]**2
        if cur < mn:
            mn = cur
            xb = x[i]
            yb = y[i]



#-------------------------------------------------------------------------------- Updating points ------------------------------------------------------------------------------------------------------------------------------
def update_populations():
    for i in range(agents):
        if(r4() < 0.5):
            x[i] = x[i] + rr1 * math.sin(r2()) * abs(r3() * xb - x[i])
        else:
            x[i] = x[i] + rr1 * math.cos(r2()) * abs(r3() * xb - x[i])

        if (r4() < 0.5):
            y[i] = y[i] + rr1 * math.sin(r2()) * abs(r3() * yb - y[i])
        else:
            y[i] = y[i] + rr1 * math.cos(r2()) * abs(r3() * yb - y[i])



#-------------------------------------------------------------------------------- Sine Cosine Algorithm ----------------------------------------------------------------------------------------------------------------------
def SCA():
    print("(_,_) ----------------- (_,_)")
    for i in range(10):
        print("  |                       |  ")
    print("(_,_) ----------------- (_,_)")

    global xmin, xmax, ymin, ymax
    xmin = float(input("Choose the left point of x-axis : "))
    xmax = float(input("Choose the right point of x-axis : "))
    ymin = float(input("Choose the down point of y-axis : "))
    ymax = float(input("Choose the upper point of y-axis : "))

    if xmin > xmax:
        xmin, xmax = xmax, xmin
    if ymin > ymax:
        ymin, ymax = ymax, ymin

    generate_initial_population()
    position_update_check()
    calculate_fitness()
    plot()

    for i in range(1, iterations + 1):
        global rr1
        rr1 = 2.0 - 2.0 * (i / iterations)
        update_populations()
        position_update_check()
        calculate_fitness()
        #plot()

    plot()
    print("The optimal point is: (" + str(xb) + ", " + str(yb) + ")")


def zahid():
    print("The algorithm is implemented by Zahid Hasan Mozumder")
    print("This is an implementation of Sine Cosine Algorithm on 2D plane")


zahid()
SCA()
